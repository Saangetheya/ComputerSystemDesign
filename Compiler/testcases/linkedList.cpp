// #include <bits/stdc++.h>
// using namespace std;

struct Node
{
  int data;
  struct Node *next;
};

int insert(struct Node *head1, struct Node *head2, int k)
{
  int count;

  // traverse the first linked list until k-th point is reached int count = 1;
  struct Node *curr;
  curr = head1;
  for (count = 1; count < k; count++)
  {
    curr = curr->next;
  }

  // backup next node of the k-th point
  struct Node *temp;
  temp = curr->next;

  // join second linked list at the kth point
  curr->next = head2;

  // traverse the second linked list till end
  for (; head2->next != NULL;)
  {
    head2 = head2->next;
  }

  // join the second part of the linked list
  // to the end
  head2->next = temp;
}

int main()
{

  return 0;
}