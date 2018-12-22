#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Tree.c"
#include "avltree.c"
#include <stdio.h>
#include "BRtree.c"


int main() {

//    TreeNode *t1;
//    TreeNode *t2;
//    TreeNode *t3;
//    TreeNode *t4;
//    TreeNode *t5;
//    TreeNode *t6;
//    TreeNode *t7;
//
//    t1 = create_tree_node(1, NULL, NULL, NULL);
//    t2 = create_tree_node(2, NULL, NULL, NULL);
//    t3 = create_tree_node(3, NULL, NULL, NULL);
//    t4 = create_tree_node(4, NULL, NULL, NULL);
//    t5 = create_tree_node(5, NULL, NULL, NULL);
//    t6 = create_tree_node(6, NULL, NULL, NULL);
//    t7 = create_tree_node(7, NULL, NULL, NULL);
//
//    t3->left_p = t1;
//    t3->right_p = t5;
//    t1->right_p = t2;
//    t5->left_p = t4;
//    t5->right_p = t6;
//
//    pre_print_tree(t3);
    test_br_tree();
    return 0;
}
