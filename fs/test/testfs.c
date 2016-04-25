//
// Created by zaiyangli on 4/24/16.
//

#include "testfs.h"


void testFsInit(){
    int error = 0;
    fs_init();

}
void testFTree(){
    int error = 0;
    fs_init();
    fnode node;
    p_fnode root_node = ftree_get_root_node();
    test_case_begin("FTree fnode tree structure functions test");
    ftree_create_dir_at(root_node, "home", 1, &error);
    assert_int_equal("create a new dir at root should be OK", OK, error);
    ftree_find_node_match_name_in_dir(root_node, "home", &node);
    //ftree_traverse_from_root("/home", &node);
    assert_true("path /home should get the fnode for home directory", strcmp(node.name, "home")==0);
    assert_int_equal("/home directory should have root node as parent", root_node->fid, node.parent_id);
    assert_int_equal("root node should have one file in dir", 1, root_node->files_in_dir);
    assert_int_equal("home should have zero files in dir", 0, node.files_in_dir);
    ftree_traverse_from_root("home", &node);
    assert_true("traverse file system by path will return a node with the same name", strcmp(node.name,"home")==0);
    ftree_delete_node_at(&node);
    read_root_dir();
    root_node = ftree_get_root_node();
    assert_int_equal("after delete home dir, root node should have 0 file in dir", 0, root_node->files_in_dir);
    ftree_create_file_at(root_node, "hello.txt", 0, &error);
    ftree_traverse_from_root("hello.txt", &node);
    assert_string_equal("traversing root after creating hello.txt will produce valid node", "hello.txt",node.name);
    assert_int_equal("hello.txt should have file size of 0 bytes", node.filesize, 0);

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

    test_case_end();
    test_case_summary();
}
void testFnode(){

}
void testFBlock(){

}
void runFileTests(){
    testPathParser();
    testFTree();
}