#include <stdio.h>
#include <stdlib.h>
#include "treaps.h"

treapNode *rightRotate(treapNode *y)
{
    treapNode *x = y->left;
    treapNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

treapNode *leftRotate(treapNode *x)
{
    treapNode *y = x->right;
    treapNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}

treapNode *newNode(int mis, float priority, float marks)
{
    treapNode *temp = (treapNode *)malloc(sizeof(treapNode));
    temp->mis = mis;
    temp->priority = priority;
    temp->marks = marks;
    temp->left = temp->right = NULL;
    return temp;
}

treapNode *search(treapNode *root, int mis)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->mis == mis)
        return root;

    // Key is greater than root's key
    if (root->mis < mis)
        return search(root->right, mis);

    // Key is smaller than root's key
    return search(root->left, mis);
}

treapNode *insert(treapNode *root, int mis, float priority, float marks)
{
    // If root is NULL, create a new node and return it
    if (!root)
        return newNode(mis, priority, marks);

    // If key is smaller than root
    if (mis <= root->mis)
    {
        // Insert in left subtree
        root->left = insert(root->left, mis, priority, marks);

        // Fix Heap property if it is violated
        if (root->left->priority > root->priority)
            root = rightRotate(root);
    }
    else // If key is greater
    {
        // Insert in right subtree
        root->right = insert(root->right, mis, priority, marks);

        // Fix Heap property if it is violated
        if (root->right->priority > root->priority)
            root = leftRotate(root);
    }
    return root;
}

void inorder(treapNode *root)
{
    if (root)
    {
        inorder(root->left);
        printf("mis : %d | priority : %f\n", root->mis, root->priority);
        inorder(root->right);
    }
}

void getSize(char *filename1, int *sizePointer)
{ // we are getting the graph  input in form of file
    int x;
    FILE *fp;
    int i, j;
    fp = fopen(filename1, "r");
    if (fp == NULL) // if we are unable to open the file
    {
        printf("UNABLE TO OPEN THE FILE\n");
        return;
    }

    // scanf the number of students
    fscanf(fp, "%d", &x);
    *sizePointer = x;
    return;
}

int fillArray(char *filename1, studentNode *arrayHeadPointer)
{ // we are getting the graph  input in form of file
    int groupSize;
    printf("Enter the group size => ");
    scanf("%d", &groupSize);
    int x;
    FILE *fp;
    int i, j;
    fp = fopen(filename1, "r");
    if (fp == NULL) // if we are unable to open the file
    {
        printf("UNABLE TO OPEN THE FILE\n");
        return 0;
    }

    // scanf the number of vertices
    fscanf(fp, "%d", &x);

    // scanf the all vertices of 2d matrix nxn
    for (int i = 0; i < x; i++)
    {
        int mis;
        float marks;
        fscanf(fp, "%d %f", &mis, &marks);
        arrayHeadPointer[i].marks = marks;
        arrayHeadPointer[i].mis = mis;

        float priority = ((100 - marks) / 100) * (groupSize);
        arrayHeadPointer[i].priority = priority;
        // printf("%d %f %f\n",arrayHeadPointer[i].mis,arrayHeadPointer[i].marks,arrayHeadPointer[i].priority);
    }
    return groupSize;
}

void printArray(studentNode *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d => %f & %f\n", arr[i].mis, arr[i].marks, arr[i].priority);
    }
    printf("\n");
}

void push(struct sNode **top_ref, treapNode *t)
{
    /* allocate tNode */
    struct sNode *new_tNode =
        (struct sNode *)malloc(sizeof(struct sNode));

    if (new_tNode == NULL)
    {
        printf("Stack Overflow \n");
        getchar();
        exit(0);
    }

    /* put in the data  */
    new_tNode->t = t;

    /* link the old list off the new tNode */
    new_tNode->next = (*top_ref);

    /* move the head to point to the new tNode */
    (*top_ref) = new_tNode;
}

int isEmpty(struct sNode *top)
{
    return (top == NULL) ? 1 : 0;
}

treapNode *pop(struct sNode **top_ref)
{
    treapNode *res;
    struct sNode *top;

    /*If sNode is empty then error */
    if (isEmpty(*top_ref))
    {
        printf("Stack Underflow \n");
        getchar();
        exit(0);
    }
    else
    {
        top = *top_ref;
        res = top->t;
        *top_ref = top->next;
        free(top);
        return res;
    }
}

void inOrder(treapNode *root, int groupSize, FILE *fptr)
{
    /* set current to root of binary tree */
    treapNode *current = root;
    struct sNode *s = NULL; /* Initialize stack s */
    int done = 0;

    int count = 0;
    studentNode *roott = NULL;
    while (!done)
    {
        /* Reach the left most tNode of the current tNode */
        if (current != NULL)
        {
            /* place pointer to a tree node on the stack before traversing
              the node's left subtree */
            push(&s, current);
            current = current->left;
        }

        else
        {
            if (!isEmpty(s))
            {
                current = pop(&s);
                char strings[70];
                sprintf(strings, "| MIS : %d |MARKS : %f | PRIORITY : %f |\n", current->mis, current->marks, current->priority);
                fprintf(fptr, "%s", strings);
                count++;
                if (count == groupSize)
                {
                    count = 0;
                    char strings[70];
                    sprintf(strings, "\n-----------------------------------------\n");
                    fprintf(fptr, "%s", strings);
                }
                current = current->right;
            }
            else
                done = 1;
        }
    }
}

void printCurrentLevel(treapNode *root, int level, int *count, int groupSize, FILE *fptr)
{
    if (root == NULL)
        return;
    if (level == 1)
    {
        char strings[70];
        sprintf(strings, "| MIS : %d | PRIORITY : %f | MARKS : %f |\n", root->mis, root->priority, root->marks);
        fprintf(fptr, "%s", strings);
        *count = *count + 1;
        if (*count == groupSize)
        {
            char strings[70];
            sprintf(strings, "\n-----------------------------------------\n");
            fprintf(fptr, "%s", strings);
            *count = 0;
        }
    }
    else if (level > 1)
    {
        printCurrentLevel(root->left, level - 1, count, groupSize, fptr);
        printCurrentLevel(root->right, level - 1, count, groupSize, fptr);
    }
}

int height(treapNode *node)
{
    if (node == NULL)
        return 0;
    else
    {
        /* compute the height of each subtree */
        int lheight = height(node->left);
        int rheight = height(node->right);

        /* use the larger one */
        if (lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}

void printLevelOrder(treapNode *root, int groupSize, FILE *fptr)
{
    int h = height(root);
    int i;
    int count = 0;
    for (i = 1; i <= h; i++)
    {
        printCurrentLevel(root, i, &count, groupSize, fptr);
    }
}

void printPostorder(treapNode *node)
{
    if (node == NULL)
        return;

    // first recur on left subtree
    printPostorder(node->left);

    // then recur on right subtree
    printPostorder(node->right);

    // now deal with the node
    printf("| MIS : %d |MARKS : %f | PRIORITY : %f |\n", node->mis, node->marks, node->priority);
}

void printPreorder(treapNode *node)
{
    if (node == NULL)
        return;

    /* first print data of node */
    printf("| MIS : %d |MARKS : %f | PRIORITY : %f |\n", node->mis, node->marks, node->priority);

    /* then recur on left subtree */
    printPreorder(node->left);

    /* now recur on right subtree */
    printPreorder(node->right);
}
