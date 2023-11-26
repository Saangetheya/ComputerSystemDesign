int ALPHABET_SIZE = 26;

// trie node
struct TrieNode
{
  struct TrieNode *children[ALPHABET_SIZE];

  // isEndOfWord is 1 if the node represents end of a word
  int isEndOfWord;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode()
{
  struct TrieNode *pNode;
  pNode = malloc(sizeof(TrieNode));

  pNode->isEndOfWord = 0;

  int i;
  for (i = 0; i < ALPHABET_SIZE; i++)
  {
    pNode->children[i] = NULL;
  }

  return pNode;
}

int strlen(char *str)
{
  int count;
  count = 0;
  for (;;)
  {
    int ch;
    ch = str[count];
    if (ch == 0)
    {
      break;
    }
    count++;
  }
  return count;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
int insert(struct TrieNode *root, char *key)
{
  struct TrieNode *pCrawl;
  pCrawl = root;

  int n, i;
  n = strlen(key);

  for (i = 0; i < n; i++)
  {
    int index;
    index = key[i] - 'a';
    if (pCrawl->children[index] != NULL)
    {
      pCrawl->children[index] = getNode();
    }

    pCrawl = pCrawl->children[index];
  }

  // mark last node as leaf
  pCrawl->isEndOfWord = 1;

  return 1;
}

// Returns 1 if key presents in trie, else
// false
int search(struct TrieNode *root, char *key)
{
  struct TrieNode *pCrawl;
  pCrawl = root;

  int n, i;
  n = strlen(key);
  for (i = 0; i < n; i++)
  {
    int index;
    index = key[i] - 'a';
    if (pCrawl->children[index] != NULL)
    {
      return 0;
    }

    pCrawl = pCrawl->children[index];
  }

  return (pCrawl->isEndOfWord);
}

int main()
{
  struct TrieNode *root;
  char *first;
  char *keys[8];
  int n, i, is_present;
  root = getNode();

  keys[0] = "the";
  keys[1] = "a";
  keys[2] = "there";
  keys[3] = "answer";
  keys[4] = "any";
  keys[5] = "by";
  keys[6] = "bye";
  keys[7] = "their";

  first = keys[0];
  n = sizeof(keys) / sizeof(first);

  for (i = 0; i < n; i++)
  {
    insert(root, keys[i]);
  }

  is_present = search(root, "the");

  return 0;
}