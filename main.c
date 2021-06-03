#include "stdio.h"
#include "stdlib.h"
#include "BTree.h"

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