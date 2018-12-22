#include <stdio.h>
#include <stdlib.h>

#define Red 1
#define Black 0
#define True 1
#define False 0

typedef int Bool;
//
// Created by tjp56 on 2018/12/20.
//

//每个结点要么是红的要么是黑的。
//根结点是黑的。
//每个叶结点（叶结点即指树尾端NIL指针或NULL结点）都是黑的。
//如果一个结点是红的，那么它的两个儿子都是黑的。
//对于任意结点而言，其到叶结点树尾端NIL指针的每条路径都包含相同数目的黑结点。


// 插入
// 第一种情况：插入的时候是根节点，不用管
// 第二种情况：插入之后父节点是黑色的，也不用管

typedef struct BRTreeNode {
    int key;
    int color;
    struct BRTreeNode *left_child;
    struct BRTreeNode *right_child;
    struct BRTreeNode *parent;
} BRNode;

struct BRTree {
    struct BRTreeNode *root;
};

void insert_case1(BRNode *n);

void insert_case2(BRNode *n);

void balance_case3(BRNode *, BRNode *);

void balance_case4(BRNode *, BRNode *);

void balance_case5(BRNode *, BRNode *);

void re_balance_tree_node(BRNode *root, BRNode *node);


struct BRTreeNode *get_grandfather(BRNode *node) {
    if (node->parent == NULL) {
        return NULL;
    } else {
        return node->parent->parent;
    }
}


struct BRTreeNode *get_uncle(BRNode *node) {
    if (node->parent == NULL) {
        return NULL;
    }
    if (node->parent->parent == NULL) {
        return NULL;
    }

    if (node->parent == node->parent->parent->left_child) {
        return node->parent->parent->right_child;
    } else {
        return node->parent->parent->left_child;
    }

}


Bool is_root_node(BRNode *root, BRNode *node) {
    if (node->key == root->key) {
        return True;
    } else {
        return False;
    }
}


Bool is_left_child(BRNode *parent, BRNode *node) {
    if (node == NULL || parent == NULL) {
        return False;
    }

    if (node == parent->left_child) {
        return True;
    }

    return False;
}


Bool is_right_child(BRNode *parent, BRNode *node) {
    if (node == NULL || parent == NULL) {
        return False;
    }

    if (node == parent->right_child) {
        return True;
    }

    return False;
}


Bool is_uncle_red(BRNode *node) {
    BRNode *uncle = get_uncle(node);
    Bool is_uncle_red = False;

    if (uncle != NULL) {
        if (uncle->color == Red) {
            is_uncle_red = True;
        }
    }
    return is_uncle_red;
}


Bool is_case_1(BRNode *root, BRNode *node) {
    if (node->parent->key == root->key) {
        return True;
    } else {
        return False;
    }
}


Bool is_case_2(BRNode *root, BRNode *node) {
    if (node->parent->color == Black) {
        return True;
    } else {
        return False;
    }
}


Bool is_case_3(BRNode *root, BRNode *node) {
    if (node->parent->color == Red && is_uncle_red(node)) {
        return True;
    } else {
        return False;
    }
}


Bool is_case_4(BRNode *root, BRNode *node) {
    BRNode *parent = node->parent;
    BRNode *grand_father = get_grandfather(node);
    BRNode *uncle = get_uncle(node);

    if (parent->color == Red && is_uncle_red(uncle) == False && is_right_child(parent, node) &&
        is_left_child(parent, grand_father)) {
        return True;
    }

    return False;
}


Bool is_case_5(BRNode *root, BRNode *node) {
    BRNode *parent = node->parent;
    BRNode *grand_father = get_grandfather(node);

    if (parent == NULL || grand_father == NULL) {
        return False;
    }

    if (parent->color == Red && is_uncle_red(node) == False && is_left_child(parent, node) &&
        is_left_child(parent, grand_father)) {
        return True;
    } else if (parent->color == Red && is_uncle_red(node) == False && is_right_child(parent, node) &&
            is_right_child(parent, grand_father)) {
        return True;
    } else {
        return False;
    }
}


/*
 * 左旋转
 * LEFT-ROTATE(T, x)
 * y ← right[x]            // 前提：这里假设x的右孩子为y。下面开始正式操作
 * right[x] ← left[y]      // 将 “y的左孩子” 设为 “x的右孩子”，即 将β设为x的右孩子
 * p[left[y]] ← x          // 将 “x” 设为 “y的左孩子的父亲”，即 将β的父亲设为x
 * p[y] ← p[x]             // 将 “x的父亲” 设为 “y的父亲”
 * if p[x] = nil[T]
 * then root[T] ← y                 // 情况1：如果 “x的父亲” 是空节点，则将y设为根节点
 * else if x = left[p[x]]
 *           then left[p[x]] ← y    // 情况2：如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
 *           else right[p[x]] ← y   // 情况3：(x是它父节点的右孩子) 将y设为“x的父节点的右孩子”
 * left[y] ← x             // 将 “x” 设为 “y的左孩子”   p[x] ← y                // 将 “x的父节点” 设为 “y”
 * */
void left_rotate(BRNode *node) {
    BRNode *rn = node->right_child;
    BRNode *np = node->parent;

    node->right_child = rn->left_child;
    rn->left_child = node;
    node->parent = rn;
    if (np != NULL) {
        if (node->key == np->left_child->key) {
            np->left_child = rn;
        } else {
            np->right_child = rn;
        }
    }
}


/*
 * 右旋：
 *      1. node节点下沉到右边
 *      2. node节点->左节点->右节点 变成node节点的左节点
 *      3. node节点->原左节点 变成node节点的父节点
 *      4. node节点的父节点的子节点变成 node节点->原左节点
 *
 * RIGHT-ROTATE(T, y)
 * x ← left[y]             // 前提：这里假设y的左孩子为x。下面开始正式操作
 * left[y] ← right[x]      // 将 “x的右孩子” 设为 “y的左孩子”，即 将β设为y的左孩子
 * p[right[x]] ← y         // 将 “y” 设为 “x的右孩子的父亲”，即 将β的父亲设为y
 * p[x] ← p[y]             // 将 “y的父亲” 设为 “x的父亲”
 * if p[y] = nil[T]
 * then root[T] ← x                 // 情况1：如果 “y的父亲” 是空节点，则将x设为根节点
 * else if y = right[p[y]]
 *           then right[p[y]] ← x   // 情况2：如果 y是它父节点的右孩子，则将x设为“y的父节点的左孩子”
 *           else left[p[y]] ← x    // 情况3：(y是它父节点的左孩子) 将x设为“y的父节点的左孩子”
 * right[x] ← y            // 将 “y” 设为 “x的右孩子”
 * p[y] ← x                // 将 “y的父节点” 设为 “x”
 * */
void right_rotate(BRNode *node) {
    BRNode *ln = node->left_child;
    BRNode *np = node->parent;

    node->left_child = ln->right_child;
    node->parent = ln;
    ln->right_child = node;

    if (np != NULL) {
        if (node->key == np->left_child->key) {
            np->left_child = ln;
        } else {
            np->right_child = ln;
        }
    }
}


void balance_case5(BRNode *root, BRNode *node) {
    BRNode *parent = node->parent;
    BRNode *grand_father = get_grandfather(node);

    parent->color = Black;
    grand_father->color = Red;

    if (is_left_child(parent, node)) {
        right_rotate(grand_father);
    } else {
        left_rotate(grand_father);
    }

    root = parent;
}


void balance_case4(BRNode *root, BRNode *node) {
    left_rotate(node->parent);
    balance_case5(root, node);
}


void balance_case3(BRNode *root, BRNode *node) {
    BRNode *uncle = get_uncle(node);
    BRNode *grand_father = get_grandfather(node);

    node->parent->color = Black;
    uncle->color = Black;
    if (grand_father->key != root->key) {
        grand_father->color = Red;
        balance_case3(root, grand_father);
    }

}


void re_balance_tree_node(BRNode *root, BRNode *node) {

    if (is_case_1(root, node)) {
        return;
    }

    if (is_case_2(root, node)) {
        return;
    }

    if (is_case_3(root, node)) {
        balance_case3(root, node);
    }

    if (is_case_4(root, node)) {
        balance_case4(root, node);
    }

    if (is_case_5(root, node)) {
        balance_case5(root, node);
    }
}


struct BRTreeNode *create_br_tree_node(int key) {
    struct BRTreeNode *node;
    node = (struct BRTreeNode *) malloc(sizeof(struct BRTreeNode));

    node->key = key;
    node->color = Red;
    node->right_child = NULL;
    node->left_child = NULL;
    node->parent = NULL;

    return node;
}


struct BRTree *create_br_tree() {
    struct BRTreeNode *node;
    node = (struct BRTreeNode *) malloc(sizeof(struct BRTreeNode));

    struct BRTree *tree;
    tree = (struct BRTree *) malloc(sizeof(struct BRTree));

    node->color = Black;
    node->right_child = NULL;
    node->left_child = NULL;
    node->parent = NULL;

    tree->root = node;
    return tree;
}


void insert_br_tree_node(BRNode *root, BRNode *node) {
    if (root->parent == NULL) {
        root = node;
    }

    if (root->key > node->key) {
        if (root->left_child == NULL) {
            root->left_child = node;
            node->parent = root;
        } else {
            insert_br_tree_node(root->left_child, node);
        }
    } else {
        if (root->right_child == NULL) {
            root->right_child = node;
            node->parent = root;
        } else {
            insert_br_tree_node(root->right_child, node);
        }
    }
}


void insert_br_tree(struct BRTree *tree, BRNode *node) {
    BRNode *root = tree->root;
    insert_br_tree_node(root, node);
    re_balance_tree_node(root, node);
}


int test_br_tree() {

    struct BRTree *tree = create_br_tree();

    struct BRTreeNode *node1 = create_br_tree_node(2);
    struct BRTreeNode *node2 = create_br_tree_node(3);

    insert_br_tree(tree, node1);
    insert_br_tree(tree, node2);

    printf("%d \n", tree->root->right_child->key);
    printf("%d", tree->root->right_child->right_child->key);

    return 0;
}

