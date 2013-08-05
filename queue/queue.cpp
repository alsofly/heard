#include <iostream>

using namespace std;

struct Node {
   int val;
   Node *next;
   Node(const int v): val(v), next(NULL) {}
};

class Queue {
public:
   Queue():head(NULL), tail(NULL) {}
   void enqueue(const int val)
   {
      Node *curr = new Node(val);
      if ( head == NULL )
      {
         head = curr;
         tail = curr;
      }
      else
      {
         tail->next = curr;
         tail = curr;
      }
   }

   void dequeue()
   {
      if ( head == NULL ) return;
      Node *curr = head;
      head = head->next;
      delete curr;
      curr = NULL;
   }

   Node *front()
   {
      return head;
   }

   Node *back()
   {
      return tail;
   }

private:
   Node *head;
   Node *tail;
};

int main()
{
   Queue q;
   q.enqueue(1);
   q.enqueue(2);
   q.enqueue(3);
   q.dequeue();

   Node *curr = q.front();
   while ( curr != NULL )
   {
      cout << curr->val << endl;
      curr = curr->next;
   }
   return 0;
}
