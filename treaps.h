
typedef struct treapNode
{
    int mis;
    float priority;
    float marks;
    struct treapNode *left,*right;
} treapNode;

typedef struct studentNode
{
    int mis;
    float marks;
    float priority;
    struct studentNode* next;
}studentNode;


struct sNode
{
  treapNode *t;
  struct sNode *next;
};
treapNode *insert(treapNode *root, int mis, float priority, float marks);
void getSize(char *filename1, int *sizePointer);
int fillArray(char *filename1, studentNode *arrayHeadPointer);
void inOrder(treapNode *root, int groupSize, FILE *fptr);
void printLevelOrder(treapNode *root, int groupSize, FILE *fptr);
void printPostorder(treapNode *node);
void printPreorder(treapNode *node);
