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


typedef struct TreeNode {
    int data;
    struct TreeNode *left_p;
    struct TreeNode *right_p;
    struct TreeNode *parent_p;
} TreeNode;

/*
 * 树的节点的创造函数*/
struct TreeNode *create_tree_node(int data, TreeNode *parent, TreeNode *left, TreeNode *right) {
    TreeNode *node;
    node = (TreeNode *) malloc(sizeof(TreeNode));

    if (node == NULL) {
        return NULL;
    }

    node->data = data;
    node->parent_p = parent;
    node->left_p = left;
    node->right_p = right;

    return node;
}


void pre_print_tree(TreeNode *p) {
    if (p == NULL) {
        return;
    }

    printf("%d", p->data);
    pre_print_tree(p->left_p);
    pre_print_tree(p->right_p);
}