#include "Graph.h"

#include <vector>
#include <stack>
#include <queue>
#include <algorithm>




int N; // number of vertices 
std::vector<std::vector<int>> W; // graph 
std::vector<int> V; // V is a visited flag 

void dfs_recurse(int i) {
    if (!V[i]) {
        // check for termination condition(have we reached the node we want to ? )

        // mark top as visited;
        V[i] = true;

        // call dfs for all of top's neighbors 
        std::for_each(W[i].begin(), W[i].end(), dfs_recurse);
    }
}

void dfs(int i) {
    std::stack<int> s;
    s.push(i);
    while (!s.empty()) {
        int top = s.top();
        s.pop();

        if (!V[i]) {
            // check for termination condition(have we reached the node we want to ? )

            // mark top as visited;
            V[i] = true;

            // add all of top's neighbors to the stack
            std::for_each(W[i].begin(), W[i].end(), [&](int n){ s.push(n); });
        }
    }
}

void bfs(int i) {
    std::queue<int> q;
    q.push(i);
    while (!q.empty()) {
        int top = q.front();
        q.pop();

        if (!V[i]) {
            // check for termination condition(have we reached the node we want to ? )

            // mark top as visited;
            V[i] = true;

            // add all of top's neighbors to the stack
            std::for_each(W[i].begin(), W[i].end(), [&](int n){ q.push(n); });
        }
    }
}

bool check_graph_connected_dfs() {
    int start_vertex = 0;
    V = std::vector<int>(N, false);
    
    dfs(start_vertex);


    return (std::find(V.begin(), V.end(), 0) == V.end());
}

bool check_graph_connected_bfs() {
    int start_vertex = 0;
    std::vector<int> V(N, false);
    std::queue<int> Q;
    Q.push(start_vertex);
    V[start_vertex] = true;
    while (!Q.empty()) {
        int i = Q.front();
        
        // get the tail element from queue
        Q.pop();
        
        for (auto it = W[i].begin(); it != W[i].end(); ++it) {
            if (!V[*it]) {
                V[*it] = true;
                Q.push(*it);
            }
        }
    }

    return (std::find(V.begin(), V.end(), 0) == V.end());
}


void GraphAlgorithmsRun()
{
    std::vector<std::vector<int>> initVect = 
    {
        { 3, 7, 15 },
        { 10, 17, 35},
        { 5, 25, 53 }
    };

    W = initVect;


}