#include "stdio.h"
#include "stdlib.h"

#define M 5

typedef struct nodeType {
    int    n; //n < M No. of keys in node will always less than order of B tree
    int    keys[M - 1]; //array of keys
    struct nodeType *p[M]; //(n+1 pointers will be in use)
} node;

//node *root = NULL;

typedef node * Btree;
//Btree root = NULL;


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

int main() {
    Btree root = NULL;
    create(&root);

    int key , vals[100] , sizeTree=0;
    int choice;
    printf("Creation of B tree for M=%d\n", M);
    while (1) {
        printf("1.Insert\n");
        printf("2.Delete\n");
        printf("3.Search\n");
        printf("4.Display\n");
        printf("5.Quit\n");
        printf("6.Print tree sorted\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter the key : ");
                scanf("%d", &key);
                if(insert(key, &root))
                {
                    vals[sizeTree] = key;
                    sizeTree++;
                }

                break;
            case 2:
                printf("\nEnter the key : ");
                scanf("%d", &key);
                if(DelNode(key, &root))
                {
                    deleteVal(sizeTree , vals , key);
                    sizeTree--;
                }
                break;
            case 3:
                printf("\nEnter the key : ");
                scanf("%d", &key);
                search(key, &root);
                break;
            case 4:
                printf("\n\nBtree is :\n");
                display(root, 0);
                printf("\n\n");
                break;
            case 5:
                return 0;
            case 6:
                printf("\nBtree in sorted order is:\n");
                sortPrint(sizeTree , vals);
                for(int j=0 ; j<sizeTree ; j++)
                    printf("%d " , vals[j]);
                printf("\n\n");
                break;
            default:
                printf("\nWrong choice\n");
                break;
        }/*End of switch*/
    }/*End of while*/
}/*End of main()*/

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
            printf("Key %d found in position %d of last dispalyed node\n", key, i);
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
    int pos;
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
        for (i = 0; i < ptr->n; i++)
            printf("%d ", ptr->keys[i]);
        if(1)
        {
            printf("\n");
        }
        else
            printf("\t");
        for (i = 0; i <= ptr->n; i++)
            display(ptr->p[i], blanks + 10);
    }/*End of if*/
}
