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
    ftree_create_file_at(root_node, path, 0,&node_txt_file );

    ftree_file_write_bytes(&node_txt_file, data, strlen(data));
    read_fnode(node_txt_file.fid, &node_txt_file);

    assert_int_equal("Writing 'hello world' to file will change file size to strlen(hello world)",strlen(data), node_txt_file.filesize );
    assert_int_equal("test.txt will need 1 block to store 'hello world'", 1, node_txt_file.block_count);

    test_case_end();
    test_case_summary();
}
void testFnode(){

}
void testFBlock(){

}
void runFileTests(){
    test_init();
    testPathParser();
    testFTree();
    testFTreeWrite();
}