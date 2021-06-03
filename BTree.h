//
// Created by Hazem on 6/2/2021.
//

#ifndef BTREE_BTREE_H
#define BTREE_BTREE_H

#define M 5

typedef struct nodeType {
    int    n; //n < M No. of keys in node will always less than order of B tree
    int    keys[M - 1]; //array of keys
    struct nodeType *p[M]; //(n+1 pointers will be in use)
} node;

typedef node * Btree;

typedef enum KeyStatus {
    Duplicate,
    SearchFailure,
    Success,
    InsertIt,
    LessKeys,
} KeyStatus;

void create(Btree* bt);
int insert(int key, Btree* root);
void display(node *ptr, int);
int DelNode(int key, Btree* root);
void search(int key, Btree* root);
KeyStatus ins(node *r, int key, int* y, node** newnode);
int searchPos(int key, int *key_arr, int n);
KeyStatus del(node *r, int key, Btree* root);
void deleteVal(int siz , int vals[] , int k);
void sortPrint(int siz , int vals[]);


#endif //BTREE_BTREE_H
