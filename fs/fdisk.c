//
// Created by zaiyangli on 4/22/16.
//

#include "fdisk.h"
#include "../libc/string.h"


bitmap node_alloc_table;
bitmap block_alloc_table;
static const char ZERO_BLOCK[BLOCK_SIZE_BYTES];
static fnode root_node;
static fnode node_buffer;
static uint8_t raw_block_buffer[BLOCK_SIZE_BYTES];
static fblock block_buffer;
static fdisk_header disk_header;

void disk_mount(int* error){

    *error = 0;

    read_disk_header(&disk_header);
    verify_partition(&disk_header, error);
    if(*error == 0){
        disk_rd(BITMAP_ALLOC_TABLE_FNODE, (uint8_t *) node_alloc_table.bits, BLOCK_SIZE_BYTES);
        disk_rd(BITMAP_ALLOC_TABLE_DATA, (uint8_t *) block_alloc_table.bits, BLOCK_SIZE_BYTES);

        read_root_dir();
    }else{
        //TODO: handle error or report error

    }
}
void write_alloc_tables(){
    disk_wr(BITMAP_ALLOC_TABLE_FNODE, (uint8_t *) node_alloc_table.bits, BLOCK_SIZE_BYTES);
    disk_wr(BITMAP_ALLOC_TABLE_DATA, (uint8_t *) block_alloc_table.bits, BLOCK_SIZE_BYTES);
}
void write_disk_header(p_fdisk_header header){
    disk_wr(DISK_HEADER_BLOCK_ID, (uint8_t*) header, BLOCK_SIZE_BYTES);
}
void read_root_dir(){
    read_fnode(ROOT_NODE_ID, &root_node);
}
void root_node_create_default(p_fnode node){
    memset(node, sizeof(fnode), 0);
    node->fid = ROOT_NODE_ID;
    node->type = FNODE_TYPE_DIRECTORY;
    node->files_in_dir = 0;
    node->parent_id = node->fid;
    strcpy(node->name, ROOT_DIR_NAME);
}
void zero_out_disk_struct(){
    memset(&disk_header, sizeof(fdisk_header), 0);
    memset(&node_alloc_table, sizeof(node_alloc_table),0);
    memset(&block_alloc_table, sizeof(node_alloc_table),0);
}
void root_node_init(){
    root_node_create_default(&root_node);
    bitmap_set_on(&node_alloc_table, ROOT_NODE_ID);
}
void disk_format(){

    zero_out_disk_struct();

    strcpy(disk_header.magic, FILESYSTEM_MAGIC);
    root_node_init();

    int block_id = disk_allocate_block();

    block_create_type_dir(&block_buffer, (uint32_t) block_id);
    fnode_add_block(&root_node, &block_buffer);
    write_data_block(&block_buffer);
    write_disk_header(&disk_header);
    write_alloc_tables();
    write_fnode(&root_node);
    write_data_block(&block_buffer);
    //commit changes
}

int disk_allocate_block(){
    int bid = bitmap_scan_first_zero(&block_alloc_table);

    if(bid < DATA_BLOCK_LIMIT)
    {
        bitmap_set_on(&block_alloc_table, (uint32_t)bid);
        return bid;
    }
    return -1;
}
int disk_allocate_fnode(){
    int fid = bitmap_scan_first_zero(&node_alloc_table);

    if(fid < FNODE_LIMIT)
    {
        bitmap_set_on(&node_alloc_table, (uint32_t)fid);
        return fid;
    }
    return -1;
}

void disk_free_block(uint32_t index){
    if(index < 0 || index >= DATA_BLOCK_LIMIT)
        return;
    bitmap_set_off(&block_alloc_table, index);
}
void disk_free_fnode(uint32_t index){
    if(index < 0 || index >= DATA_BLOCK_LIMIT)
        return;
    bitmap_set_off(&node_alloc_table, index);
}
void read_fnode(uint32_t id, p_fnode node){
    uint32_t block_addr = FNODE_BLOCK_BEGIN + id/FNODE_PER_BLOCK;
    int offset = FNODE_ALIGN_SIZE * (id % FNODE_PER_BLOCK) ;
    disk_rd(block_addr, raw_block_buffer, BLOCK_SIZE_BYTES);
    *node = *(p_fnode)(raw_block_buffer + offset);
}
void write_fnode(p_fnode node){
    uint32_t block_addr = FNODE_BLOCK_BEGIN + node->fid/FNODE_PER_BLOCK;
    int offset = FNODE_ALIGN_SIZE * (node->fid % FNODE_PER_BLOCK) ;
    disk_rd(block_addr, raw_block_buffer, BLOCK_SIZE_BYTES);
    *(p_fnode)(raw_block_buffer + offset) = *node;
    disk_wr(block_addr, raw_block_buffer, BLOCK_SIZE_BYTES);
}
void write_data_block(p_fblock block){
    uint32_t addr = block->header.id + DATA_BLOCK_BEGIN;
    disk_wr(addr, (uint8_t *)block, BLOCK_SIZE_BYTES);
}
void get_fnode_by_path(const char* path, p_fnode node){

}
void get_fnode_in_dir(p_fnode dir_node ,p_fnode buf[], int size){
    read_fnode(dir_node->fid, &node_buffer);

}
int get_dir_entries_count(p_fnode node){
    if(node->type == FNODE_TYPE_DIRECTORY) {
        return (int) node->files_in_dir;
    }
    return -1;
}
void read_disk_header(p_fdisk_header header){
    disk_rd(DISK_HEADER_BLOCK_ID, (uint8_t*) header, BLOCK_SIZE_BYTES);
}

void verify_partition(p_fdisk_header header, int* error){
    header->magic[8] = '\0';
    if(strcmp(header->magic, FILESYSTEM_MAGIC) != 0){
        *error = error == NULL ? *error : DISK_UNFORMATTED_ERROR;
    }
}

p_fnode disk_get_root_node(){
    return & root_node;
}

void read_data_block (uint32_t id, p_fblock block ){
    if(id < 0 || id >= DATA_BLOCK_LIMIT)
        return;
    disk_rd(DATA_BLOCK_BEGIN + id, (uint8_t*) block, BLOCK_SIZE_BYTES);
}

void disk_data_block_zero_out(int block_id){
    if(block_id < 0 || block_id > DATA_BLOCK_LIMIT)
        return;
    disk_wr(block_id + DATA_BLOCK_BEGIN, (uint8_t*) ZERO_BLOCK, BLOCK_SIZE_BYTES);
}