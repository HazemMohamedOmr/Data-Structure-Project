//
// Created by Hazem on 6/2/2021.
//

#include "BTree.h"
#include "stdio.h"
#include "stdlib.h"

void create(Btree* bt){
    *bt = NULL;
}

int insert(int key, Btree* root) {
    node *newnode;
    int upKey;
    KeyStatus value;
    value = ins(*root, key, &upKey, &newnode);
    if (value == Duplicate)
    {
        printf("Key already available\n");
        return 0;
    }

    if (value == InsertIt) {
        node *uproot = *root;
        *root = (node*)malloc(sizeof(node));
        (*root)->n = 1;
        (*root)->keys[0] = upKey;
        (*root)->p[0] = uproot;
        (*root)->p[1] = newnode;
        return 1;
    }/*End of if */
}/*End of insert()*/

KeyStatus ins(node *ptr, int key, int *upKey, node **newnode) {
    node *newPtr, *lastPtr;
    int pos, i, n, splitPos;
    int newKey, lastKey;
    KeyStatus value;
    if (ptr == NULL) {
        *newnode = NULL;
        *upKey = key;
        return InsertIt;
    }
    n = ptr->n;
    pos = searchPos(key, ptr->keys, n);
    if (pos < n && key == ptr->keys[pos])
        return Duplicate;
    value = ins(ptr->p[pos], key, &newKey, &newPtr);
    if (value != InsertIt)
        return value;
    /*If keys in node is less than M-1 where M is order of B tree*/
    if (n < M - 1) {
        pos = searchPos(newKey, ptr->keys, n);
        /*Shifting the key and pointer right for inserting the new key*/
        for (i = n; i>pos; i--) {
            ptr->keys[i] = ptr->keys[i - 1];
            ptr->p[i + 1] = ptr->p[i];
        }
        /*Key is inserted at exact location*/
        ptr->keys[pos] = newKey;
        ptr->p[pos + 1] = newPtr;
        ++ptr->n; /*incrementing the number of keys in node*/
        return Success;
    }/*End of if */
    /*If keys in nodes are maximum and position of node to be inserted is last*/
    if (pos == M - 1) {
        lastKey = newKey;
        lastPtr = newPtr;
    }
    else { /*If keys in node are maximum and position of node to be inserted is not last*/
        lastKey = ptr->keys[M - 2];
        lastPtr = ptr->p[M - 1];
        for (i = M - 2; i>pos; i--) {
            ptr->keys[i] = ptr->keys[i - 1];
            ptr->p[i + 1] = ptr->p[i];
        }
        ptr->keys[pos] = newKey;
        ptr->p[pos + 1] = newPtr;
    }
    splitPos = (M - 1) / 2;
    (*upKey) = ptr->keys[splitPos];

    (*newnode) = (node*)malloc(sizeof(node));/*Right node after split*/
    ptr->n = splitPos; /*No. of keys for left splitted node*/
    (*newnode)->n = M - 1 - splitPos;/*No. of keys for right splitted node*/
    for (i = 0; i < (*newnode)->n; i++) {
        (*newnode)->p[i] = ptr->p[i + splitPos + 1];
        if (i < (*newnode)->n - 1)
            (*newnode)->keys[i] = ptr->keys[i + splitPos + 1];
        else
            (*newnode)->keys[i] = lastKey;
    }
    (*newnode)->p[(*newnode)->n] = lastPtr;
    return InsertIt;
}/*End of ins()*/

void search(int key, Btree* root) {
    int pos, i, n;
    node *ptr = *root;
    printf("Search path:\n");
    while (ptr) {
        n = ptr->n;
        for (i = 0; i < ptr->n; i++)
            printf(" %d", ptr->keys[i]);
        printf("\n");
        pos = searchPos(key, ptr->keys, n);
        if (pos < n && key == ptr->keys[pos]) {
            printf("Key %d found\n", key);
            return;
        }
        ptr = ptr->p[pos];
    }
    printf("Key %d is not available\n", key);
}/*End of search()*/

int searchPos(int key, int *key_arr, int n) {
    int pos = 0;
    while (pos < n && key > key_arr[pos])
        pos++;
    return pos;
}/*End of searchPos()*/

int DelNode(int key, Btree* root) {
    node *uproot;
    KeyStatus value;
    int willBeDel;
    value = del(*root, key, root);
    switch (value) {
        case SearchFailure:
            printf("Key %d is not available\n", key);
            willBeDel = 0;
            break;
        case LessKeys:
            uproot = *root;
            *root = (*root)->p[0];
            free(uproot);
            willBeDel =1;
            break;
        default:
            willBeDel = 0;
            break;
    }/*End of switch*/
    return willBeDel;
}/*End of delnode()*/

KeyStatus del(node *ptr, int key, Btree* root) {
    int pos, i, pivot, n, min;
    int *key_arr;
    KeyStatus value;
    node **p, *lptr, *rptr;

    if (ptr == NULL)
        return SearchFailure;
    /*Assigns values of node*/
    n = ptr->n;
    key_arr = ptr->keys;
    p = ptr->p;
    min = (M - 1) / 2;/*Minimum number of keys*/

    //Search for key to delete
    pos = searchPos(key, key_arr, n);
    // p is a leaf
    if (p[0] == NULL) {
        if (pos == n || key < key_arr[pos])
            return SearchFailure;
        /*Shift keys and pointers left*/
        for (i = pos + 1; i < n; i++)
        {
            key_arr[i - 1] = key_arr[i];
            p[i] = p[i + 1];
        }
        return --ptr->n >= (ptr == *root ? 1 : min) ? Success : LessKeys;
    }/*End of if */

    //if found key but p is not a leaf
    if (pos < n && key == key_arr[pos]) {
        node *qp = p[pos], *qp1;
        int nkey;
        while (1) {
            nkey = qp->n;
            qp1 = qp->p[nkey];
            if (qp1 == NULL)
                break;
            qp = qp1;
        }/*End of while*/
        key_arr[pos] = qp->keys[nkey - 1];
        qp->keys[nkey - 1] = key;
    }/*End of if */
    value = del(p[pos], key, root);
    if (value != LessKeys)
        return value;

    if (pos > 0 && p[pos - 1]->n > min) {
        pivot = pos - 1; /*pivot for left and right node*/
        lptr = p[pivot];
        rptr = p[pos];
        /*Assigns values for right node*/
        rptr->p[rptr->n + 1] = rptr->p[rptr->n];
        for (i = rptr->n; i>0; i--) {
            rptr->keys[i] = rptr->keys[i - 1];
            rptr->p[i] = rptr->p[i - 1];
        }
        rptr->n++;
        rptr->keys[0] = key_arr[pivot];
        rptr->p[0] = lptr->p[lptr->n];
        key_arr[pivot] = lptr->keys[--lptr->n];
        return Success;
    }/*End of if */
    //if (posn > min)
    if (pos < n && p[pos + 1]->n > min) {
        pivot = pos; /*pivot for left and right node*/
        lptr = p[pivot];
        rptr = p[pivot + 1];
        /*Assigns values for left node*/
        lptr->keys[lptr->n] = key_arr[pivot];
        lptr->p[lptr->n + 1] = rptr->p[0];
        key_arr[pivot] = rptr->keys[0];
        lptr->n++;
        rptr->n--;
        for (i = 0; i < rptr->n; i++) {
            rptr->keys[i] = rptr->keys[i + 1];
            rptr->p[i] = rptr->p[i + 1];
        }/*End of for*/
        rptr->p[rptr->n] = rptr->p[rptr->n + 1];
        return Success;
    }/*End of if */

    if (pos == n)
        pivot = pos - 1;
    else
        pivot = pos;

    lptr = p[pivot];
    rptr = p[pivot + 1];
    /*merge right node with left node*/
    lptr->keys[lptr->n] = key_arr[pivot];
    lptr->p[lptr->n + 1] = rptr->p[0];
    for (i = 0; i < rptr->n; i++) {
        lptr->keys[lptr->n + 1 + i] = rptr->keys[i];
        lptr->p[lptr->n + 2 + i] = rptr->p[i + 1];
    }
    lptr->n = lptr->n + rptr->n + 1;
    free(rptr); /*Remove right node*/
    for (i = pos + 1; i < n; i++) {
        key_arr[i - 1] = key_arr[i];
        p[i] = p[i + 1];
    }
    return --ptr->n >= (ptr == *root ? 1 : min) ? Success : LessKeys;
}/*End of del()*/


void deleteVal(int siz , int vals[] , int k)
{
    int pos = 0;
    for(int i=0 ; i<siz ; i++)
    {
        if(vals[i] == k)
        {
            pos = i;
            break;
        }
    }
    for(int j=pos ; j<siz ; j++)
    {
        vals[j] = vals[j+1];
    }

}

void sortPrint(int siz , int vals[])
{
    int pass , temp , i;
    for(pass=0 ; pass<siz ; pass++)
    {
        for(i=0 ; i<siz-pass-1 ; i++)
        {
            if(vals[i]>vals[i+1])
            {
                temp = vals[i];
                vals[i] = vals[i+1];
                vals[i+1] = temp;
            }
        }
    }
}

void display(node *ptr, int blanks) {
    if (ptr) {
        int i;
        for (i = 1; i <= blanks; i++)
            printf(" ");

        for (int j = 0; j < 16; ++j){
            if(j == 0){
                printf(" ");
                continue;
            }
            printf("-");
        }


        printf("\n");
        for (i = 1; i <= blanks; i++)
            printf(" ");
        printf("|");

        for (i = 0; i < ptr->n; i++)
            printf(" %d |", ptr->keys[i]);
        for (i = 0; i < (M-1)-ptr->n; i++)
            printf("   |");

        printf("\n");
        for (i = 1; i <= blanks; i++)
            printf(" ");
        for (int j = 0; j < 16; ++j){
            if(j == 0){
                printf(" ");
                continue;
            }
            printf("-");
        }

        printf("\n");
        if(ptr->p[0])
            printf("\n");


        for (i = 0; i <= ptr->n; i++)
            display(ptr->p[i], blanks + 4);
    }/*End of if*/
}