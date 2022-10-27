#include <queue>
#include <vector>

using namespace std;

#define MAX_VERTEXES 200005

class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        vector<vector<int> > connections(n + 1);
        for (vector<int> edge : edges) {
            connections[edge[0]].push_back(edge[1]);
            connections[edge[1]].push_back(edge[0]);
        }
        
        bool visited[MAX_VERTEXES] = { false };
        queue<int> pending;
        pending.push(source);
        
        while (!pending.empty()) {
            int current = pending.front();
            visited[current] = true;
            
            if (current == destination) 
                return true;
            
            vector<int> adjacents = connections[current];
            for (int vertex : adjacents) {
                if (!visited[vertex])
                    pending.push(vertex);
            }
            pending.pop();
        }
        return false;
    }
};
