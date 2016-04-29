//
// Created by zaiyangli on 4/22/16.
//


#include "fs.h"

#ifdef BITMAP_64
BITMAP_GEN_BODY(64)
#endif

static fs_table file_open_table;

void fs_init(){
    int error;
    disk_mount(&error);
    if(error == DISK_UNFORMATTED_ERROR){
        disk_format();
        disk_mount;
    }else if(error == DISK_NO_ROOT_FOUND){
        disk_format();
        disk_mount;
    }
    fs_table_init(&file_open_table);
}
int fs_table_allocate(p_fs_table table){
    int index = bitmap_scan_first_zero_64(&table->file_table);
    if(index > -1)
        bitmap_set_on_64(&table->file_table, (uint32_t) index);
    return index;
}
void fs_table_free(p_fs_table table, int index){
    if(index < 0 || index >= FILE_TABLE_SIZE) return;
    else
        bitmap_set_off_64(&table->file_table, (uint32_t) index);
}
void fs_table_init(p_fs_table table){
    bitmap_init_64(&table->ft_alloc_map);
    table->lock = LOCK_FREE;
}

p_file fs_open_file(char* path, int mode){
    mutex_spinlock(&file_open_table.lock);
    int fp_index = fs_table_allocate( & file_open_table);
    if(fp_index < 0) return NULL;

    p_file fp = NULL;
    fp = &file_open_table.file_table[fp_index];

    char* parts[16];
    int count = 0;
    p_fnode root = ftree_get_root_node();
    fnode parent_dir;
    fnode open_node;
    parse_path(path, parts, 16, &count);
    char** filename = parts + count - 1;

    int found = ftree_traverse_path_from(root, parts, count -1,&parent_dir);
    if(! found)
        goto error;
    found = ftree_traverse_path_from(root, filename, 1, &open_node);
    if(found && open_node.type == FNODE_TYPE_DIRECTORY){
        goto error;
    }else if(!(found ||( mode & FILE_CREATE )))
        goto error;
    else if(!found && (mode & FILE_CREATE))
        ftree_create_file_at(&parent_dir, *filename, 1, &open_node);
    else if(found && (mode & FILE_CREATE)){
        ftree_delete_node_at(&open_node);
        ftree_create_file_at(&parent_dir, *filename, 1, &open_node);
    }
    fp->flag = mode;
    fp->id = fp_index;
    fp->node = open_node;
    fstream_init(&fp->stream, &fp->node);

    finally:
        mutex_unlock(&file_open_table.lock);
    return fp;

    error:
        fs_table_free(&file_open_table, fp_index);
        fp = NULL;
    goto finally;

}
void fs_close_file(p_file file){
    mutex_spinlock(&file_open_table.lock);
    int index = (int) (file - file_open_table.file_table);
    if(bitmap_get_64(&file_open_table.ft_alloc_map, index)){
        fs_flush_file(file);
        bitmap_set_off_64(&file_open_table.file_table, index);
    }
    mutex_unlock(&file_open_table.lock);
}
void fs_flush_file(p_file file){
    ftree_node_commit(&file->node);
    ftree_block_commit(&file->stream.buffer);
}

int fs_read_file(p_file file, char* buf, int size){

    p_fstream stream = &file->stream;
    int available = fstream_get_available_bytes(stream, file->node.filesize);

    if(size < 1) return 0;
    else if(available < size) size = available;

    return fstream_read(stream, buf, size);

}
void fs_write_file(p_file file, char* buf, int size){
    p_fstream stream = & file->stream;
    fstream_write(stream, buf, size);
}
int fs_file_get_size(p_file file){
    return ftree_file_get_file_size(&file->node);
}

void fs_file_seek(p_file file, int seek_mode, int offset){
    p_fstream stream = &file->stream;
    int currentPos = stream->block_num * BLOCK_FILE_MAX_BYTE_COUNT + stream->offset;
    switch(seek_mode){
        case FILE_SEEK_BEGIN:
            currentPos = 0 + offset;
            break;
        case FILE_SEEK_CURRENT:
            currentPos += offset;
            break;
        case FILE_SEEK_END:
            currentPos = (int) file->node.filesize;
            currentPos += offset;
            break;
        default:
            break;
    }
    fstream_seek_to_pos(stream, currentPos);
}