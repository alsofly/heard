#include <iostream>

using namespace std;

struct Node {
   int val;
   Node *next;
   Node (const int v) : val(v), next(NULL) {}
};

class Stack {
public:
   Stack() : head(NULL) {}

   void push(const int val)
   {
      Node *curr = new Node(val);
      if ( head == NULL )
      {
         head = curr;
      }
      else
      {
         curr->next = head;
         head = curr;
      }
   }

   void pop()
   {
      if ( head == NULL ) return;
      Node *curr = head;
      head = head->next;
      delete curr;
      curr = NULL;
   }

   Node *top()
   {
      return head;
   }

private:
   Node *head;

};

int main()
{
   Stack s;
   s.push(1);
   s.push(3);
   s.push(2);

   Node *head = s.top();
   while ( head != NULL )
   {
      cout << head->val << endl;
      head = head->next;
   }

   s.pop();
   head = s.top();
   while ( head != NULL )
   {
      cout << head->val << endl;
      head = head->next;
   }
   

   return 0;
}
