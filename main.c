#include<stdio.h>
#include<stdlib.h>
#include"treaps.h"



int main()
{
    int size;

    getSize("marks.txt",&size);

    studentNode* array = (studentNode*) malloc(sizeof(studentNode)*size);

    int count = fillArray("marks.txt",array);
    
    treapNode* root = NULL;
    
    printf("Making treap from given text file ...\n");
    for(int i=0 ; i< size;i++){
        root = insert(root,array[i].mis,array[i].priority,array[i].marks);
    }

    FILE *fptr;
    fptr = fopen("sortedResult.txt","w");

    if (fptr == NULL)
    {
        printf("Not able to openfile\n");
        exit(1);
    }
    

    printf("Printing mis wise order in file ...\n");
    char strings[70];
    sprintf(strings,"\n\n\n--- TRAVERSAL ACCORDING TO BINARY TREE PROPERTY ---\n\n\n");
    fprintf(fptr,"%s",strings);
    inOrder(root,count,fptr);

    printf("Printing max heap wise order in file ...\n");
    sprintf(strings,"\n\n\n--- TRAVERSAL ACCORDING TO MAX-HEAP PROPERTY ---\n\n\n");
    fprintf(fptr,"%s",strings);
    printLevelOrder(root,count,fptr);

    printf("\nPOSTORDER => \n\n");
    printPostorder(root);

    printf("\nPREORDER => \n\n");
    printPreorder(root);

    return 0;
}

