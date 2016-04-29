//
// Created by zaiyangli on 4/23/16.
//

#include "ftree.h"
#include "../libc/iobuffer.h"

int ftree_traverse_from_root(char* path, p_fnode result){
    int found;

    p_fnode root = ftree_get_root_node();
    found = ftree_traverse_from(root, path, result);
    return found;
}
int ftree_refresh_root_node(){
    read_root_dir();
}
p_fnode ftree_get_root_node(){
    return disk_get_root_node();
}
void ftree_get_node_parent(p_fnode node, p_fnode result){
    if(node->parent_id == ROOT_NODE_ID)
        *result = * ftree_get_root_node();
    else
    if( node->parent_id != -1)
        read_fnode(node->parent_id, result);
}
int ftree_traverse_from(p_fnode node, char* path, p_fnode result){

    if(node->type != FNODE_TYPE_DIRECTORY) {
        return NOT_FOUND;
    }

    char* parts[PATH_MAXIMUM_LEVEL];
    int part_count;
    parse_path(path, parts, PATH_MAXIMUM_LEVEL, &part_count);
    return ftree_traverse_path_from(node, parts, part_count, result);
}
int ftree_traverse_path_from(p_fnode node, char** parts, int part_count, p_fnode result){
    int found = NOT_FOUND;
    read_fnode(node->fid, node);
    if(part_count <= 0) {
        *result = *node;
        return FOUND;
    }
    fnode node_buffer;
    fnode current_node = *node;
    fblock block_buffer;
    int dir_levels = part_count - 1;
    for(int i = 0; i < dir_levels; i++){
        if(current_node.type == FNODE_TYPE_DIRECTORY) {
            if(strcmp(CURRENT_DIRECTORY_LABEL, parts[i])==0){

            }else if(strcmp(PARENT_DIRECTORY_LABLE, parts[i])==0){
                ftree_get_node_parent(&current_node, &node_buffer);
                current_node = node_buffer;
            }else {
                if(ftree_find_node_match_name_in_dir(&current_node, parts[i], &node_buffer)){
                    current_node = node_buffer;
                }
            }
        }else {
            found = NOT_FOUND;
            goto ftree_traverse_finally;
        }
    }
    if(ftree_find_node_match_name_in_dir(&current_node, parts[part_count -1], &node_buffer))
        goto ftree_traverse_found;
    else goto ftree_traverse_finally;

    ftree_traverse_found:
    found = FOUND;
    *result = node_buffer;

    ftree_traverse_finally:
    return found;
}
int ftree_traverse_path_from_root( char** parts, int count, p_fnode result){
    p_fnode root = ftree_get_root_node();
    return ftree_traverse_path_from(root, parts, count, result);
}
int ftree_find_node_match_name_in_dir(p_fnode node, char *name, p_fnode result){
    fblock block_buffer;
    fnode node_buffer;
    int found = NOT_FOUND;
    if(name[0] == '\0'){
        return 0;
    }
    if(node->type==FNODE_TYPE_DIRECTORY && node->files_in_dir > 0 && node->block_used_count > 0){
        for(int b = 0; b < node->block_used_count; b ++){
            read_data_block(node->blocks[b], &block_buffer);
            if(block_is_dir_block_empty(&block_buffer) && !found){
                for(int j = 0; j < block_buffer.payload.dir_block.count; j++){
                    read_fnode(block_buffer.payload.dir_block.nodes[j], &node_buffer);
                    if(fnode_name_matches(&node_buffer, name)){
                        found = FOUND;
                        if(result != NULL)
                        *result = node_buffer;
                        break;
                    }
                }
            }
        }
    }
    return found;
}
void ftree_insert_node_at(p_fnode parent, p_fnode leaf){
    fblock block_buffer;
    if(parent->type == FNODE_TYPE_DIRECTORY && parent->fid != leaf->fid){
        if(ftree_node_find_dir_block_with_space(parent, &block_buffer) == FOUND){
            block_dir_add_entry(&block_buffer, leaf);
            write_data_block(&block_buffer);
            leaf -> parent_id = parent->fid;
            write_fnode(leaf);
            parent->files_in_dir++;
            write_fnode(parent);
            if(parent->fid == ROOT_NODE_ID)
                ftree_refresh_root_node();
        }
    }
}
void ftree_delete_node_at(p_fnode node){
    fnode parent;

    if(node->fid == ROOT_NODE_ID) disk_format();

    ftree_get_node_parent(node, &parent);

    if(node->type == FNODE_TYPE_DIRECTORY)
    {
        if(node->files_in_dir > 0)
            return;
        else{
            ftree_node_detach_child(&parent, node);
            ftree_dir_delete(node);
        }
    }
    else if(node->type == FNODE_TYPE_FILE){
        ftree_node_detach_child(&parent, node);
        ftree_file_delete(node);
    }
}

void ftree_node_detach_child(p_fnode parent, p_fnode child){
    fblock block_buffer;
    if( child-> parent_id != parent->fid) return;
    if(parent->type == FNODE_TYPE_DIRECTORY && parent->files_in_dir > 0){
        for(int i = 0; i < parent->block_used_count; i++){
            read_data_block(parent->blocks[i], &block_buffer);
            if(block_buffer.header.type == BLOCK_TYPE_DIRECTORY_ENTRY){
                for(int j = 0; j< block_buffer.payload.dir_block.count; j ++){
                    if(block_buffer.payload.dir_block.nodes[j] == child->fid){
                        block_dir_remove_entry(&block_buffer, child);
                        parent->files_in_dir = parent->files_in_dir - 1;
                        child->parent_id = 0xffffffff;
                        write_data_block(&block_buffer);
                        write_fnode(parent);
                        write_fnode(child);
                        goto finish;
                    }
                }
            }
        }
    }
    finish:
        return;
}

void ftree_move_node(p_fnode node, p_fnode new_parent) {
    fnode old_parent;
    read_fnode(node->parent_id, &old_parent);
    ftree_node_detach_child(&old_parent, node);
    ftree_insert_node_at(new_parent, node);
}
int ftree_node_find_dir_block_with_space(p_fnode node, p_fblock block){
    fblock block_buffer;
    for(int i = 0; i < node->block_used_count; i ++){
        read_data_block(node->blocks[i], &block_buffer);
        if( block_buffer.payload.dir_block.count < BLOCK_DIRECTORY_ENTRY_MAX_COUNT) {
            *block = block_buffer;
            return FOUND;
        }
    }
    return NOT_FOUND;
};

int ftree_preallocate_block(int type, p_fnode node, int n){
    int allocate_count = 0;
    if(n > FNODE_MAX_BLOCK_CAPACITY) n = FNODE_MAX_BLOCK_CAPACITY;
    fblock block;
    int bid = -1;
    for(int i = 0; i < n ; i++){
        bid = disk_allocate_block();
        if(bid > -1){
            allocate_count++;
            node->blocks[i] =(uint32_t) bid;
            if(type == BLOCK_TYPE_DATA)
                block_create_type_data(&block, bid, NULL, 0);
            else if(type == BLOCK_TYPE_DIRECTORY_ENTRY)
                block_create_type_dir(&block, bid);
            write_data_block(&block);
        }else {
            break;
        }
    }
    node->block_capacity = (uint32_t) allocate_count;
    if(allocate_count > 0) {
        write_alloc_tables();
        write_fnode(node);
    }
    return allocate_count;
}

int ftree_create_dir_at(p_fnode parent, char *name, int preallocate, p_fnode out){

    fnode node;
    int error = 0;
    if(parent->type == FNODE_TYPE_DIRECTORY){
        int fid = disk_allocate_fnode();
        if(fid > -1){
            fnode_create_dir(&node, fid, parent->fid, name);
            write_fnode(&node);
            ftree_insert_node_at(parent, &node);
            ftree_preallocate_block(BLOCK_TYPE_DIRECTORY_ENTRY, &node, preallocate);
            error = OK;
            if(out != NULL){
                *out = node;
            }
        }else {
            error = ERROR_CANNOT_ALLOCATE_FNODE;
        }
    }
    return error;
}
int ftree_create_file_at(p_fnode parent, char* name, int preallocate, p_fnode out){
    fnode node;
    int error = 0;
    if(parent->type == FNODE_TYPE_DIRECTORY){
        int fid = disk_allocate_fnode();
        if(fid > -1){
            fnode_create_file(&node, fid, parent->fid, name);
            write_fnode(&node);
            ftree_insert_node_at(parent, &node);
            ftree_preallocate_block(BLOCK_TYPE_DATA, &node, preallocate);
            if(out != NULL){
                *out = node;
            }
            error = OK;
        }else {
            error = ERROR_CANNOT_ALLOCATE_FNODE;
        }
    }
    return error;
}
int ftree_dir_get_file_count(p_fnode node){
    if(node->type == FNODE_TYPE_DIRECTORY){
        return (int) node->files_in_dir;
    }else {
        return -1;
    }
}
int ftree_file_get_file_size(p_fnode node){
    if(node->type == FNODE_TYPE_FILE){
        return (int) node->filesize;
    }
    else {
        return -1;
    }
}
void ftree_file_write_bytes(p_fnode node, char* bytes, uint32_t size){
    if(node->type != FNODE_TYPE_FILE || size > FILE_SIZE_MAX ) return;

    int remainder = size % BLOCK_FILE_MAX_BYTE_COUNT;
    int blocks_needed = size / BLOCK_FILE_MAX_BYTE_COUNT + (remainder == 0 ? 0 : 1);
    fblock block_buffer;
    int bid = -1;
    int more_blocks = blocks_needed - node->block_used_count;
    int i;
    int written = 0;
    if(more_blocks < 0){

        for( i = blocks_needed; i < node->block_used_count; i++){
            disk_free_fnode(node->blocks[i]);
            node->blocks[i] = 0;
        }
        node->block_used_count = (uint32_t) blocks_needed;
    }else
    if(blocks_needed > node->block_used_count){

        for( i = node->block_used_count; i < blocks_needed ; i++){
            bid = disk_allocate_block();
            if(bid != -1){
                node->blocks[i] = bid;
            }else {
                //TODO: handle case when there are not more blocks that can be allocated on the disk.
                break;
            }
        }
        node->block_used_count = (uint32_t) blocks_needed;
    }

    int whole_blocks = node->block_used_count - 1;
    for (int i = 0; i < whole_blocks; i++) {
        block_create_type_data(&block_buffer, node->blocks[i], bytes + written, BLOCK_FILE_MAX_BYTE_COUNT);
        written += BLOCK_FILE_MAX_BYTE_COUNT;
        write_data_block(&block_buffer);
    }
    remainder = remainder == 0 ? BLOCK_FILE_MAX_BYTE_COUNT : remainder;
    block_create_type_data(&block_buffer, node->blocks[whole_blocks], bytes+written, remainder);
    write_data_block(&block_buffer);
    written += remainder;
    node->filesize = (uint32_t) written;
    write_alloc_tables();
    write_fnode(node);
}

void ftree_file_delete_data(p_fnode node, int zero_out){
    if(node->type != FNODE_TYPE_FILE ) return;
    for(int i = 0; i < node->block_capacity; i++){
        disk_free_block(node->blocks[i]);
    }
    if(zero_out){
        for(int i = 0; i < node->block_capacity; i++) {
            disk_data_block_zero_out(node->blocks[i]);
        }
    }
}
void ftree_file_delete_dir_data(p_fnode node){
    if(node->type != FNODE_TYPE_FILE ) return;
    for(int i = 0; i < node->block_capacity; i++){
        disk_free_block(node->blocks[i]);
    }
}
void ftree_file_delete(p_fnode node){
    if(node->type != FNODE_TYPE_FILE) return;
    ftree_file_delete_data(node, 0);
    disk_free_fnode(node->fid);
    write_alloc_tables();
}

void ftree_dir_delete(p_fnode node){
    if(node->type != FNODE_TYPE_DIRECTORY) return;
    if(node->files_in_dir == 0){
        ftree_file_delete_dir_data(node);
        disk_free_fnode(node->fid);
        write_alloc_tables();
    }
}
void ftree_file_expand(){

}
void ftree_dir_delete_recursive(p_fnode node){
    if(node->fid == ROOT_NODE_ID) disk_format();
}
void ftree_node_commit(p_fnode node){
    write_fnode(node);
}
void ftree_block_commit(p_fblock block){
    write_data_block(block);
}

void ftree_block_read(uint32_t block_id, p_fblock block){
    read_data_block(block_id, block);
}

int ftree_file_get_data_capacity(p_fnode node){
    return ftree_node_get_block_capacity(node) * BLOCK_FILE_MAX_BYTE_COUNT;
}
int ftree_dir_get_capacity(p_fnode node){
    return ftree_node_get_block_capacity(node) * BLOCK_DIRECTORY_ENTRY_MAX_COUNT;
}
int ftree_node_get_block_capacity(p_fnode node){
    return (int) node->block_capacity;
}
int ftree_node_expand_block_capacity(p_fnode node, int capacity){
    if(capacity < node->block_capacity || capacity < 1)
        return (int) node->block_capacity;
    if(capacity > FNODE_MAX_BLOCK_CAPACITY ) capacity = FNODE_MAX_BLOCK_CAPACITY;
    int allocated = 0;
    int block_id = -1;
    fblock block;
    for(int i = (int) node->block_capacity; i < capacity; i++){
        block_id = disk_allocate_block();
        if(block_id > 0){
            allocated ++;
            switch(node->type){
                case FNODE_TYPE_DIRECTORY:
                    block_create_type_dir(&block, (uint32_t) block_id);
                    break;
                case FNODE_TYPE_FILE:
                    block_create_type_data(&block, (uint32_t) block_id, NULL, 0);
                    break;
                default:
                    block_create_type_data(&block, (uint32_t) block_id, NULL, 0);
                    break;
            }
            node->blocks[i] = (uint32_t) block_id;
            ftree_block_commit(&block);
        }else {
            break;
        }
    }
    node->block_capacity += allocated;
    write_alloc_tables();
    ftree_node_commit(node);
    return (int) node->block_capacity;
}
int ftree_node_shrink_block_capacity(p_fnode node, int capacity){
    if(capacity > node->block_capacity || capacity < 1)
        return 0;
    for(int i = (int) node->block_capacity - 1; i >= capacity; i++){
        disk_free_block(node->blocks[i]);
    }
    node->block_capacity = (uint32_t) capacity;
    if(node->block_used_count > capacity)
        node->block_used_count = (uint32_t) capacity;
    write_alloc_tables();
    ftree_node_commit(node);
    return 0;
}