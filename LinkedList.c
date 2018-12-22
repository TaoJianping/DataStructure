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


typedef struct SinglyLinkedListNode SinglyLinkedListNode;
typedef struct SinglyLinkedList SinglyLinkedList;


struct SinglyLinkedListNode {
    int data;
    struct SinglyLinkedListNode *next;
};


void print_SinglyLinkedList(SinglyLinkedListNode *head_node) {
    printf("start \n");
    for (; head_node!=NULL; head_node=head_node->next) {
        printf("%d \n", head_node->data);
    }
    printf("end \n");
}


SinglyLinkedListNode* init_SinglyLinkedList (int number) {
    struct SinglyLinkedListNode *ans;
    ans = (struct SinglyLinkedListNode *) malloc(sizeof(struct SinglyLinkedListNode));
    ans->data = number;
    ans->next = NULL;
    return ans;
}

/*
 * add a node to the tail of a other node
 * */
void add_ans_node(struct SinglyLinkedListNode *answer_head, struct SinglyLinkedListNode *node) {
    for (; answer_head!=NULL; answer_head=answer_head->next) {
        if (answer_head->next == NULL) {
            answer_head->next = node;
            break;
        }
    }
}


/*
 * merge two sorted list
 * */
SinglyLinkedListNode* mergeLists(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {
    struct SinglyLinkedListNode *tmp1 = head1;
    struct SinglyLinkedListNode *tmp2 = head2;
    struct SinglyLinkedListNode *tmp;
    struct SinglyLinkedListNode *answer_head;
    answer_head = (struct SinglyLinkedListNode *) malloc(sizeof(struct SinglyLinkedListNode));
    answer_head->next = NULL;
    answer_head->data = 0;

    while (1) {
        if (tmp1 == NULL && tmp2 != NULL) {
            add_ans_node(answer_head, tmp2);
            tmp2 = NULL;
        }

        if (tmp1 != NULL && tmp2 == NULL) {
            add_ans_node(answer_head, tmp1);
            tmp1 = NULL;
        }

        if (tmp1 != NULL && tmp2 != NULL) {
            if (tmp1->data < tmp2->data) {
                add_ans_node(answer_head, tmp1);
                tmp = tmp1;
                tmp1 = tmp1->next;
                tmp->next = NULL;
            } else {
                add_ans_node(answer_head, tmp2);
                tmp = tmp2;
                tmp2 = tmp2->next;
                tmp->next = NULL;
            }
        }

        if (tmp1 == NULL && tmp2 == NULL) {
            answer_head = answer_head->next;
            return answer_head;
        }
    }
}


/*
 * reverse a linked list
 * */
SinglyLinkedListNode * reverse_linked_list(SinglyLinkedListNode* head) {
    SinglyLinkedListNode *tmp1;
    SinglyLinkedListNode *tmp2;
    tmp1 = NULL;
    tmp2 = NULL;
    // TODO 待优化
    while (1) {
        // tmp1 是前一个节点，tmp2 是后一个节点
        tmp2 = head->next;

        if (tmp1 == NULL) {
            // 第一个节点挂载到tmp2
            head->next = NULL;
        } else {
            head->next = tmp1;
        }
        // 注意这里要改变一下tmp1的值
        tmp1 = head;
        if (tmp2 == NULL) {
            return head;
        } else {
            head = tmp2;
        }
    }
}


/*
 * get the value of the node from the tail of a list
 * */
int getNode(SinglyLinkedListNode* head, int positionFromTail) {
    int count = 0;
    if (NULL == head) { return 0; }
    SinglyLinkedListNode *reversed_linked_list;
    reversed_linked_list = reverse_linked_list(head);

    while (1) {
        for (; reversed_linked_list!=NULL; reversed_linked_list=reversed_linked_list->next) {
            if (count == positionFromTail) {
                return reversed_linked_list->data;
            } else {
                ++count;
            }
        }

    }
}


/*
 * delete duplicate-value nodes from a sorted linked list
 * */
SinglyLinkedListNode* removeDuplicates(SinglyLinkedListNode* head) {
    SinglyLinkedListNode* ans;
    ans = head;
    while(1) {
        if (head->next == NULL) {
            break;
        }

        if (head->data == head->next->data) {
            head->next = head->next->next;
        } else {
            if (head->next == NULL) {
                break;
            }
            head = head->next;
        }

    }

    return ans;
}


/*
 * detect Cycle linked list */
bool has_cycle(SinglyLinkedListNode* head) {

    SinglyLinkedListNode *tmp;
    SinglyLinkedListNode *last;
    last = (SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));

    while (true) {
        if (head->next == NULL) {
            return false;
        } else if (head->next == last) {
            return true;
        }
        tmp = head->next;
        head->next = last;
        head = tmp;
    }
}


//int main() {
////    struct SinglyLinkedListNode *node1;
////    node1 = (struct SinglyLinkedListNode *) malloc(sizeof(struct SinglyLinkedListNode));
////    node1->data = 0;
////    node1->next = NULL;
////
////
////    struct SinglyLinkedListNode *node2;
////    node2 = (struct SinglyLinkedListNode *) malloc(sizeof(struct SinglyLinkedListNode));
////    node2->data = 10000;
////    node2->next = NULL;
////
////    add_ans_node(node1, node2);
////
////    printf("%d \n", node1->next->data);
//
////    struct SinglyLinkedListNode *node1;
////    struct SinglyLinkedListNode *node2;
////    struct SinglyLinkedListNode *node3;
////    struct SinglyLinkedListNode *node4;
////    struct SinglyLinkedListNode *node5;
////    struct SinglyLinkedListNode *node10;
////    struct SinglyLinkedListNode *answer;
////
////    node1 = init_SinglyLinkedList(1);
////    node2 = init_SinglyLinkedList(2);
////    node3 = init_SinglyLinkedList(5);
////    node4 = init_SinglyLinkedList(3);
////    node5 = init_SinglyLinkedList(7);
////    node10 = init_SinglyLinkedList(10);
////
////    add_ans_node(node1, node2);
////    add_ans_node(node1, node3);
////    add_ans_node(node1, node5);
////    add_ans_node(node1, node10);
////    node10->next = node3;
//
////    add_ans_node(node4, node5);
////    add_ans_node(node5, node10);
//
////    add_ans_node(node1, node4);
////    mergeLists(node1, node4);
////    print_SinglyLinkedList(node1);
////    answer = reverse_linked_list(node4);
////    print_SinglyLinkedList(answer);
//
////    bool ans = has_cycle(node1);
//
//
//}

