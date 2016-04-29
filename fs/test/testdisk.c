//
// Created by zaiyangli on 4/22/16.
//

#include "testdisk.h"
#include "../fnode.h"
#include "../fdisk.h"

static bitmap bmap;

void testBitmap(){

    test_case_begin("Bitmap test case for disk allocation");

    bitmap_init(&bmap,0);
    assert_true("initial value of bitmap should be 0 after init",(int) bitmap_get(&bmap, 0) == 0);
    bitmap_set_on(&bmap, 0);
    assert_int_equal("bitmap bit 0 is should be 1 after set on", 1, (int) bitmap_get(&bmap, 0));
    int result;
    for(int i = 0; i < 128; i ++)
        bitmap_set_on(&bmap, i);

    for(int i = 0; i < 128; i++){
        assert_int_equal("bitmap bit 0 is should be 1 after set on", 1, (int) bitmap_get(&bmap, i));
    }
    for(int i = 0; i < 128; i ++)
        bitmap_set_off(&bmap, i);
    for(int i = 0; i < 128; i++){
        assert_int_equal("bitmap bit 0 is should be 1 after set on", 0, (int) bitmap_get(&bmap, i));
    }
    result = bitmap_scan_first_zero(&bmap);
    assert_int_equal("the first bit should be zero after resetting", 0 , result);

    bitmap_set_on(&bmap, 0);
    result = bitmap_scan_first_zero(&bmap);
    assert_int_equal("set bit 0 to be 1, scan first zero should return 1", 1, result);

    for(int i = 0; i < 223; i++){
        bitmap_set_on(&bmap, i);
    }
    result = bitmap_scan_first_zero(&bmap);
    assert_int_equal("set first 223 bits to be 1, scan first zero should return 223", 223, result);
    test_case_end();
    test_case_summary();
}
void testSizes(){
    test_case_begin("File System Structs test cases");
    assert_int_equal("struct fblock size should equal to defined block size constant", BLOCK_SIZE_BYTES, sizeof(fblock));
    assert_int_equal("struct fnode has size equal to  block size", sizeof(fnode), BLOCK_SIZE_BYTES);
    assert_int_equal("allocation table has size equal to block size", sizeof(bitmap), BLOCK_SIZE_BYTES);
    assert_int_equal("disk header has size equal to a block size", sizeof(fdisk_header), BLOCK_SIZE_BYTES);
    test_case_end();
    test_case_summary();
}

void testDiskFormat(){
    test_case_begin("Disk format test case");

    int error=0;
    int files_count = -1;
    disk_format();
    disk_mount(&error);

    p_fnode root= disk_get_root_node();
    fblock block;
    assert_int_equal("newly formatted disk should not have error when mounted", error, DISK_MOUNT_OK);
    assert_true("new formatted root should have id ROOT_NOTE_ID", ROOT_NODE_ID == root->fid);
    assert_int_equal("root node should have a single block", 1, root->block_used_count);

    test_case_end();
    test_case_summary();
}
void testFileManagement(){
    test_case_begin("File management test case");
    int error = 0;
}
void runDiskTest(){
    testBitmap();
    testSizes();
    testDiskFormat();
}

