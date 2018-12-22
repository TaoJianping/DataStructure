#include <stdio.h>
#include <stdlib.h>


typedef struct AvlTreeNode {
    int data;
    int height;
    struct AvlTreeNode *left_child;
    struct AvlTreeNode *right_child;
} Node, *avl_tree;

/*
 * 制造第一个根节点*/
static Node *create_avl_node(int data, Node *left, Node *right) {
    Node *node = (Node *) (malloc(sizeof(Node)));

    if (node == NULL) {
        return NULL;
    }

    node->data = data;
    node->left_child = left;
    node->right_child = right;
    node->height = 0;

    return node;
}

/*
 * 递归求节点的高度*/
int calculate_root_height(Node *root) {

    if (root == NULL) {
        return 0;
    }

    int left_height = calculate_root_height(root->left_child);
    int right_height = calculate_root_height(root->right_child);

    return (left_height > right_height) ? (left_height + 1) : (right_height + 1);
}


/*
 * 左左旋转*/
static void left_left_rotation(Node *root) {
    root->left_child = root->left_child->right_child;
    root->left_child->right_child = root;
    root = root->left_child;

}
