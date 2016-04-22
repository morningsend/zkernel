//
// Created by zaiyangli on 4/22/16.
//

#include "testdisk.h"

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
void testBlock(){
    test_case_begin("FBlock test case for allocating files");
    assert_int_equal("struct fblock size should equal to defined block size constant", BLOCK_SIZE_BYTES, sizeof(fblock));
    test_case_end();
    test_case_summary();
}
void runDiskTest(){
    testBitmap();
    testBlock();
}

