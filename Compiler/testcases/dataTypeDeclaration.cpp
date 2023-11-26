int CHILDREN_SIZE = 26;
int N = 64;
int M = 32;

struct LLNode
{
  char value;
  struct LLNode *next;
};

struct Node
{
  int Hash[N][M];
  struct Node *children[CHILDREN_SIZE];
  struct LLNode values;
  int isLeaf;
};