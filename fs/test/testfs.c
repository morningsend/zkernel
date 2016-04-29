//
// Created by zaiyangli on 4/24/16.
//

#include "testfs.h"

void test_init(){
    disk_format();
    fs_init();
}

void testFTree(){
    int error = 0;
    fs_init();
    fnode node;
    int found;
    char path[128] = "/home";
    p_fnode root_node = ftree_get_root_node();
    test_case_begin("FTree fnode tree structure functions test");
    error = ftree_create_dir_at(root_node, "home", 1, NULL);
    assert_int_equal("create a new dir at root should be OK", OK, error);
    ftree_traverse_from_root(path, &node);
    assert_string_equal("path /home should get the fnode for home directory", node.name, "home");
    assert_int_equal("/home directory should have root node as parent", root_node->fid, node.parent_id);
    assert_int_equal("root node should have one file in dir", 1, root_node->files_in_dir);
    assert_int_equal("home should have zero files in dir", 0, node.files_in_dir);
    ftree_create_file_at(root_node, "hello.txt", 0, NULL);
    ftree_traverse_from_root("hello.txt", &node);
    assert_string_equal("traversing root after creating hello.txt will produce valid node", "hello.txt",node.name);
    assert_int_equal("hello.txt should have file size of 0 bytes", node.filesize, 0);
    strcpy(path,"/hello.txt/me");
    found = ftree_traverse_from_root(path, &node);
    assert_int_equal("traverse from non-dir file as dir name will fail", NOT_FOUND, found);
    strcpy(path, "hello");
    found = ftree_find_node_match_name_in_dir(root_node, path, &node);
    assert_int_equal("nonexistend file/dir names in dir should not be matched", NOT_FOUND, found);

    strcpy(path, "home");

    ftree_traverse_from_root("home", &node);
    assert_string_equal("traverse file system by path will return a node with the same name","home" , node.name);



    ftree_delete_node_at(&node);
    strcpy(path, "/home");
    found = ftree_find_node_match_name_in_dir(root_node, path, &node);

    assert_int_equal("after deleting, /home dir should NOT be found by traversing dir tree", NOT_FOUND, found);
    found = ftree_traverse_from_root("home", &node);
    assert_int_equal("traversing deleted 'home' dir will return not found", NOT_FOUND, found);
    test_case_end();
    test_case_summary();
}

void testPathParser(){
    int count;
    char* parts[PATH_MAXIMUM_LEVEL];
    test_case_begin("Path parser test case");
    char path[128] = "/home/dir/abc.txt";
    parse_path(path, parts, PATH_MAXIMUM_LEVEL, &count);
    assert_int_equal("/home/dir/abc.txt should be parsed to 3 parts", 3, count);
    assert_string_equal("part 1 should be home", "home", parts[0]);
    assert_string_equal("part 2 should be dir", "dir", parts[1]);
    assert_string_equal("part 3 should be abc.txt", "abc.txt", parts[2]);

    strcpy(path, "/home/dir/ccc/");
    parse_path(path, parts, PATH_MAXIMUM_LEVEL, &count);
    assert_int_equal("path with trailing slash is will be parsed as normal, e.g. /home/dir/ccc/", 3, count);
    assert_string_equal("dir with trailing slash will be parsed to name without slash", "ccc", parts[2]);

    strcpy(path, "home");
    parse_path(path, parts, PATH_MAXIMUM_LEVEL, &count);
    assert_int_equal("path with no slashes should parsed as one file", 1, count);
    assert_string_equal("parsing 'home' should produce 'home'", "home", parts[0]);
    test_case_end();
    test_case_summary();
}
void testFTreeWrite(){
    read_root_dir();
    p_fnode root_node = ftree_get_root_node();
    char path[32] = "test.txt";
    int error = 0;
    char data[] = "hello world";
    fnode node_txt_file;

    test_case_begin("File writing test case");
    ftree_create_file_at(root_node, path, 1,&node_txt_file );

    ftree_file_write_bytes(&node_txt_file, data, strlen(data));
    read_fnode(node_txt_file.fid, &node_txt_file);

    assert_int_equal("Writing 'hello world' to file will change file size to strlen(hello world)",strlen(data), node_txt_file.filesize );
    assert_int_equal("test.txt will need 1 block to store 'hello world'", 1, node_txt_file.block_used_count);
    int fid = node_txt_file.fid;
    int bid = node_txt_file.blocks[0];
    ftree_delete_node_at(&node_txt_file);

    assert_int_equal("deleting file should free allocated file node", 0, disk_get_fnode_alloc_status(fid));
    assert_int_equal("deleting file should free allocated data blocks", 0, disk_get_data_block_alloc_status(bid));

    test_case_end();
    test_case_summary();
}

void testMoveFile(){
    read_root_dir();
    p_fnode root_node = ftree_get_root_node();
    char dir1_name[32] = "dir1";
    char dir2_name[32] = "dir2";
    char file_name[32] = "file.txt";
    fnode node1;
    fnode node2;
    int file_count = (int) root_node->files_in_dir;
    ftree_create_dir_at(root_node, dir1_name, 1, NULL);
    ftree_create_dir_at(root_node, dir2_name, 1, NULL);
    ftree_create_file_at(root_node, file_name,1, NULL);
    read_root_dir();
    test_case_begin("ftree file moving test case");
    assert_int_equal("root node has 3 files",file_count+3,root_node->files_in_dir );
    ftree_traverse_from_root("/dir1", &node1);
    ftree_traverse_from_root("file.txt", &node2);
    ftree_move_node(&node2, &node1);
    ftree_refresh_root_node();
    root_node = ftree_get_root_node();
    assert_int_equal("root node have 1 less file", file_count + 2, root_node->files_in_dir);
    test_case_end();
    test_case_summary();
}
void testFnode(){
    fnode node;
    fblock block;

    fnode_create_file(&node, 1,0,"hello");
    block_create_type_data(&block, 33, "world", 5);
    test_case_begin("FNode test case");
    assert_string_equal("node should have name hello", "hello", node.name);
    fnode_add_block(&node, &block);
    assert_int_equal("node should have one block", 1, node.block_used_count);
    assert_int_equal("node should have block with id 33", 33, node.blocks[0]);
    assert_int_equal("node should have capacity of 1", 1, node.block_capacity);
    fnode_remove_block(&node, &block);
    assert_int_equal("after remove block, node should have capacity of 0", 0, node.block_capacity);
    assert_int_equal("after remove block, node should have one block used", 0, node.block_used_count);
    test_case_end();
    test_case_summary();
}
void testGeneratedBitmap(){
    bitmap_64 bmap;
    bitmap_init_64(&bmap);
    test_case_begin("Macro Generated Bitmap Test Case");
    assert_int_equal("bitmap_64 should equal to 0", 0, (int) bmap.bits[0]);
    assert_int_equal("bitmap_64 should have size equal to 8 bytes", 8, sizeof(bitmap_64));
    bitmap_set_on_64(&bmap, 33);
    assert_int_equal("bitmap_64 should support set bit position", 2, bmap.bits[1] );
    assert_int_equal("bitmap_64 should support get bit operation", 1, bitmap_get_64(&bmap,33));
    test_case_end();
    test_case_summary();
}
void testFileReadWrite(){
    disk_format();
    fs_init();
    char buffer[20] = "0123456789";
    char fname[] = "/hello2.txt";
    int len = strlen(buffer);
    test_case_begin("File Open Read Write Close function test case");
    p_file fp = _fopen(fname, FILE_WRITE_ONLY | FILE_CREATE);
    assert_true("file pointer fp should not be null", fp != NULL);
    assert_int_equal("file will have size 0", 0, _fsize(fp));
    assert_int_equal("file cursor is at position 0", 0, _ftell(fp));
    _fwrite(fp, buffer, len);
    assert_int_equal("file cursor is at position 10", len, _ftell(fp));
    _fclose(fp);
    strcpy(fname, "/hello2.txt");
    fp = _fopen(fname, FILE_READ_ONLY);
    assert_true("hello2.txt exist on the file system, fp != null", fp != NULL);

    memset(buffer, 20, 0);
    int chars_read = _fread(fp, buffer, 20);

    buffer[chars_read] = '\0';
    _fclose(fp);
    assert_int_equal("file size of hello2.txt should equal to length of string written", len, _fsize(fp));
    assert_int_equal("chars read equals to length of string written", len, chars_read);
    assert_string_equal("written 0123456789, should get back 0123456789", "0123456789", buffer);
    test_case_end();
    test_case_summary();
}
void runFileTests(){
    testFnode();
    test_init();
    testPathParser();
    testFTree();
    testFTreeWrite();
    testMoveFile();
    testGeneratedBitmap();
    testFileReadWrite();
}