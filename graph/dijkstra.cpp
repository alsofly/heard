#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Connect
{
   int key;
   int weight;
   Connect(int k, int w):key(k), weight(w){}
};

struct comp {
   bool operator() (const Connect &a, const Connect &b)
   {
      return a.weight > b.weight;
   }
};

const int MAX = 1000;
vector<Connect> graph[MAX];
int             dist[MAX];
bool            visited[MAX];
priority_queue<Connect, vector<Connect>, comp> que;

int main()
{
   int nodes, edges, start;
   cin >> nodes >> edges >> start;
   for ( int i = 0; i < edges; ++i )
   {
      int u, v, w;
      cin >> u >> v >> w;
      graph[u].push_back(Connect(v, w));
      graph[v].push_back(Connect(u, w));
   }

   for ( int i = 0; i < nodes; ++i )
   {
      dist[i] = INT_MAX;
      visited[i] = false;
   }
  
   dist[start] = 0;
   que.push(Connect(start, 0));

   while ( !que.empty() )
   {
      Connect curr = que.top();
      que.pop();
      if ( visited[curr.key] || dist[curr.key] == INT_MAX ) continue;

      int len = graph[curr.key].size();
      for ( int i = 0; i < len; ++i )
      {
         Connect& adj = graph[curr.key][i];
         if ( !visited[adj.key] 
           && dist[curr.key] + adj.weight < dist[adj.key] )
         {
            dist[adj.key] = dist[curr.key] + adj.weight;
            que.push(Connect(adj.key, dist[adj.key]));
         }
      }
      visited[curr.key] = true;
   }

   for ( int i = 0; i < nodes; ++i )
   {
      cout << "Node [" << i << "]: " << dist[i] << endl;
   }

   return 0;
}
