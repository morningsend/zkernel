//
// Created by zaiyangli on 4/23/16.
//

#include "ftree.h"
#define CURRENT_DIRECTORY_LABEL "."
#define PARENT_DIRECTORY_LABLE ".."
#define NOT_FOUND 0
#define FOUND 1
int ftree_traverse_from_root(char* path, p_fnode result){
    int found;
    p_fnode root = disk_get_root_node();
    found = ftree_traverse_from(root, path, result);
    return found;
}
void ftree_get_dir_node_parent(p_fnode node, p_fnode result){
    if( node->parent_id != -1)
        read_fnode(node->parent_id, result);
}
int ftree_traverse_from(p_fnode node, char* path, p_fnode result){

    if(node->type != FNODE_TYPE_DIRECTORY) {
        return NOT_FOUND;
    }

    fnode node_buffer;
    fnode current_node = *node;
    fblock block_buffer;
    char* parts[PATH_MAXIMUM_LEVEL];
    int part_count;
    parse_path(path, parts, PATH_MAXIMUM_LEVEL, &part_count);
    for(int i = 0; i < part_count; i++){
        if(current_node.type == FNODE_TYPE_DIRECTORY) {
            if(strcmp(CURRENT_DIRECTORY_LABEL, parts[i])==0){

            }else if(strcmp(PARENT_DIRECTORY_LABLE, parts[i])==0){
                ftree_get_dir_node_parent(&current_node, &node_buffer);
                current_node = node_buffer;
            }else {
                if(ftree_find_node_match_name_in_dir(&current_node, parts[i], &node_buffer)){
                    current_node = node_buffer;
                }
            }
        }else {

        }
    }

    *result = node_buffer;
    return FOUND;
}
int ftree_find_node_match_name_in_dir(p_fnode node, char *name, p_fnode result){
    fblock block_buffer;
    fnode node_buffer;
    int found = NOT_FOUND;
    if(name[0] == '\0'){
        return 0;
    }
    if(node->type==FNODE_TYPE_DIRECTORY && node->block_count > 0){
        for(int b = 0; b < node->block_count; b ++){
            read_data_block(node->blocks[b], &block_buffer);
            if(block_is_dir_block_empty(&block_buffer) && !found){
                for(int j = 0; j < block_buffer.payload.dir_block.count; j++){
                    read_fnode(block_buffer.payload.dir_block.nodes[j], & node_buffer);
                    if(fnode_name_matches(&node_buffer, name)){
                        found = FOUND;
                        *result = node_buffer;
                        break;
                    }
                }
            }
        }
    }
    return found;
}
void ftree_insert_node_at(p_fnode node, p_fnode leaf){
    fblock block_buffer;
    if(node->type == FNODE_TYPE_DIRECTORY && node->fid != leaf->fid){
        if(ftree_node_find_dir_block_with_space(node, &block_buffer) == FOUND){
            block_dir_add_entry(&block_buffer, leaf);
            write_data_block(&block_buffer);
            leaf -> parent_id = node->fid;
            write_fnode(leaf);
            node->files_in_dir++;
            write_fnode(node);
        }
    }
}
void ftree_delete_node_at(p_fnode node){
    if(node->fid == ROOT_NODE_ID) disk_format();
}
void ftree_delete_recursive(p_fnode node){
    if(node->fid == ROOT_NODE_ID) disk_format();
}
void ftree_move_node(p_fnode node_from, p_fnode node_to, p_fnode node) {

}
int ftree_node_find_dir_block_with_space(p_fnode node, p_fblock block){
    fblock block_buffer;
    for(int i = 0; i < node->block_count; i ++){
        read_data_block(node->blocks[i], &block_buffer);
        if( block_buffer.payload.dir_block.count < BLOCK_DIRECTORY_ENTRY_MAX_COUNT) {
            *block = block_buffer;
            return FOUND;
        }
    }
    return NOT_FOUND;
};

int ftree_preallocate_block(p_fnode node, int n){
    int allocate_count = 0;
    if(n > FNODE_MAX_BLOCK_COUNT) n = FNODE_MAX_BLOCK_COUNT;
    int bid = -1;
    for(int i = 0; i < n ; i++){
        bid = disk_allocate_block();
        if(bid > -1){
            allocate_count++;
            node->blocks[i] =(uint32_t) bid;
        }else {
            break;
        }
    }
    node->block_count = allocate_count;
    if(allocate_count > 0) {
        write_alloc_tables();
        write_fnode(node);
    }
    return allocate_count;
}

void ftree_create_dir_at(p_fnode parent, char *name, int preallocate, int* error){

    fnode node;
    memset(&node, sizeof(fnode), 0);
    if(parent->type == FNODE_TYPE_DIRECTORY){
        int fid = disk_allocate_fnode();
        if(fid > -1){
            fnode_create_dir(&node, fid, parent->fid, name);
            write_fnode(&node);
            ftree_insert_node_at(parent, &node);
            ftree_preallocate_block(&node, preallocate);
        }else {
            *error = ERROR_CANNOT_ALLOCATE_FNODE;
            return;
        }
    }
}
void ftree_create_file_at(p_fnode parent, char* name, int preallocate, int *error){
    fnode node;
    memset(&node, sizeof(fnode), 0);
    if(parent->type == FNODE_TYPE_DIRECTORY){
        int fid = disk_allocate_fnode();
        if(fid > -1){
            fnode_create_file(&node, fid, parent->fid, name);
            write_fnode(&node);
            ftree_insert_node_at(parent, &node);
            ftree_preallocate_block(&node, preallocate);
        }else {
            *error = ERROR_CANNOT_ALLOCATE_FNODE;
            return;
        }
    }
}