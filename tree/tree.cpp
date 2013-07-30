#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <stack>

using namespace std;

struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode(const int v)
      : val(v)
      , left(NULL)
      , right(NULL)
   {}
};

int str2i(const string& s)
{
   istringstream iss(s);
   int rtn;
   iss >> rtn;
   return rtn;
}

void visit(TreeNode *node)
{
   cout << node->val << endl;
}

// pre-order recursive
void preorder_recur(TreeNode *head)
{
   if ( NULL == head ) return;
   visit(head);
   preorder_recur(head->left);
   preorder_recur(head->right);
}

// pre-order iterative
void preorder_iter(TreeNode *head)
{
   stack<TreeNode *> s;
   TreeNode *curr = head;
   while ( !s.empty() || curr != NULL )
   {
      if ( curr != NULL )
      {
         visit(curr);
         s.push(curr->right);
         curr = curr->left;
      }
      else
      {
         curr = s.top();
         s.pop();
      }
   }
}

// post-order recursive
void postorder_recur(TreeNode *head)
{
   if ( NULL == head ) return;
   postorder_recur(head->left);
   postorder_recur(head->right);
   visit(head);
}

// in-order recursive
void inorder_recur(TreeNode *head)
{
   if ( NULL == head ) return;
   inorder_recur(head->left);
   visit(head);
   inorder_recur(head->right);
}

// in-order recursive
void inorder_iter(TreeNode *head)
{
   stack<TreeNode *> s;
   TreeNode *curr = head;
   while ( !s.empty() || curr != NULL )
   {
      if ( curr != NULL )
      {
         s.push(curr);
         curr = curr->left;
      }
      else
      {
         curr = s.top();
         s.pop();
         visit(curr);
         curr = curr->right;
      }
   }
}

// BFS
void bfs(TreeNode *head)
{
   if ( head == NULL ) return;
   queue<TreeNode *> que;
   que.push(head);
   while ( !que.empty() )
   {
      TreeNode *curr = que.front();
      que.pop();
      visit(curr);

      if ( curr->left != NULL ) que.push(curr->left);
      if ( curr->right != NULL ) que.push(curr->right);
   }
}

TreeNode* fromArray(const vector<string>& input)
{
   queue<TreeNode *> que;
   int p(0);
   TreeNode *head = new TreeNode(str2i(input[p++]));
   que.push(head);
   while ( !que.empty() && p < input.size() )
   {
      TreeNode *curr = que.front();
      que.pop();
      if ( input[p] != "#" )
      {
         TreeNode *left = new TreeNode(str2i(input[p]));
         curr->left = left;
         que.push(left);
      }
      ++p;
      if ( p < input.size() && input[p] != "#" )
      {
         TreeNode *right = new TreeNode(str2i(input[p]));
         curr->right = right;
         que.push(right);
      }
      ++p;
   }
   return head;
}

std::ostream& operator<<(std::ostream& os, TreeNode *head)
{
   os << "[";
   if ( NULL == head )
   {
      os << "[#]";
      return os;
   }

   std::queue<TreeNode *> que;
   os << head->val << ",";
   que.push(head);
   while ( que.size() > 0 )
   {
      TreeNode *curr = que.front();
      que.pop();

      if ( curr->left != NULL )
      {
         que.push(curr->left);
         os << curr->left->val << ",";
      }
      else
      {
         os << "#,";
      }

      if ( curr->right != NULL )
      {
         que.push(curr->right);
         os << curr->right->val << ",";
      }
      else
      {
         os << "#,";
      }
   }
   os << "]";
   return os;
}

template <typename T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& strVec)
{
   os << "[";
   for ( size_t j = 0; j < strVec.size(); ++j )
   {
      os << strVec[j] << (j == strVec.size() - 1 ? "" : ",");
   }
   os << "]";
   return os;
}

int main()
{
   // read tree from std::cin
   vector<string> tree;
   string input;
   while ( getline(cin, input) )
   {
      tree.push_back(input);
   }
   cout << tree << endl;
   
   // convert input to tree structure
   TreeNode *head = fromArray(tree);
   cout << head << endl;

   // pre-order recursive
   cout << "\nPre-order recursively" << endl;
   preorder_recur(head);

   // pre-order iterative
   cout << "\nPre-order iteratively" << endl;
   preorder_iter(head);

   // in-order recursive
   cout << "\nIn-order recursively" << endl;
   inorder_recur(head);

   // in-order iterative
   cout << "\nIn-order iteratively" << endl;
   inorder_iter(head);

   // post-order recursive
   cout << "\nPost-order recursively" << endl;
   postorder_recur(head);
   
   // BFS
   cout << "\nBFS" << endl;
   bfs(head);

   return 0;
}
