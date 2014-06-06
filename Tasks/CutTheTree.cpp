#include "CutTheTree.h"


std::string CutTheTreeDataMock()
{
    std::string input =
        "6\n"
        "100 200 100 500 100 600\n"
        "1 2\n"
        "2 3\n"
        "2 5\n"
        "4 5\n"
        "5 6\n";

    return input;
}

void CutTheTreePreparer(std::istream &input, GraphType *verts)
{
    size_t intemsCount = 0;
    input >> intemsCount;
    input.ignore();

    if (intemsCount < 1)
        return;

    verts->resize(intemsCount);
    for (size_t i = 0; i < intemsCount; i++)
    {
        int w;
        input >> w;
        (*verts)[i].iWeight = w;
        (*verts)[i].subTreeSum = 0;
    }

    for (size_t i = 0; i < intemsCount - 1; i++)
    {
        int from, to;
        input >> from >> to;
        input.ignore();

        (*verts)[from - 1].conn.push_back(to - 1);
        (*verts)[to - 1].conn.push_back(from - 1);
    }
}

int TreeTraverseNaive(const GraphType &verts, const std::pair<size_t, size_t> &cutEdge, size_t startNode, std::vector<int> &visited)
{
    if (verts.size() == 0)
        return 0;

    if (verts.size() < startNode)
        return 0;

    int treeSum = 0;

    std::stack<size_t> traverseStack;
    traverseStack.push(startNode);

    while (!traverseStack.empty())
    {
        size_t vertex = traverseStack.top();
        traverseStack.pop();

        // count the 
        visited[vertex] = true;
        treeSum += verts[vertex].iWeight;

        for (auto v : verts[vertex].conn)
        {
            if (visited[v] ||
                (vertex == cutEdge.first && v == cutEdge.second) ||
                (vertex == cutEdge.second && v == cutEdge.first)
                )
                continue; // don't go through the edge, which cut

            traverseStack.push(v);
        }
    }


    return treeSum;
}

int TreeTraverseOptimized(const GraphType &verts, size_t startNode, std::vector<int> &visited, std::vector<int> &subTreeSum)
{
    if (visited[startNode])
        return subTreeSum[startNode];

    visited[startNode] = 1;
    int subSum = verts[startNode].iWeight;

    for (auto v : verts[startNode].conn)
    {
        subSum += TreeTraverseOptimized(verts, v, visited, subTreeSum);
    }
    
    subTreeSum[startNode] = subSum;

    return subSum;
}

int CutTheTreeSolverNaive(const GraphType &verts)
{
    // Calculate tree sum for the initial tree
    std::vector<int> visited(verts.size());
    int treeDiff = TreeTraverseNaive(verts, std::make_pair(0, 0), 0, visited);

    for (size_t i = 0; i < verts.size(); i++)
    {
        for (auto v : verts[i].conn)
        {
            std::fill_n(visited.begin(), verts.size(), 0);

            // always start from 0th
            int F1 = TreeTraverseNaive(verts, std::make_pair(i, v), 0, visited);

            // find the first not visited
            size_t idx = 0;
            while (idx < visited.size() && visited[idx] != 0) { idx++; };

            // continue from anyone, which has not been visited
            int F2 = TreeTraverseNaive(verts, std::make_pair(i, v), idx, visited);

            treeDiff = std::min(treeDiff, abs(F1 - F2));
        }
    }

    return treeDiff;
}

int CutTheTreeSolverOptimized(const GraphType &verts)
{
    // Calculate tree sum for the initial tree
    std::vector<int> visited(verts.size());
    std::vector<int> subTreeSum(verts.size());
    int fullTreeSum = TreeTraverseOptimized(verts, 0, visited, subTreeSum);

    std::vector<int> diffs(verts.size());

    for (size_t i = 0; i < verts.size(); i++)
    {
        diffs[i] = abs(fullTreeSum - 2 * subTreeSum[i]);
    }

    int iRes = *std::min_element(diffs.begin(), diffs.end());

    return iRes;
}

int CutTheTreeSolver(const GraphType &verts)
{
    return false ? CutTheTreeSolverNaive(verts) : CutTheTreeSolverOptimized(verts);
}

void CutTheTree()
{
    auto start = std::chrono::system_clock::now();
    GraphType verts;

    std::string strData = CutTheTreeDataMock();
    std::istringstream inStr(strData);

    //std::istream &dataStream = std::cin;
    std::istream &dataStream = inStr;

    //int iRes = sln2(dataStream);

    CutTheTreePreparer(dataStream, &verts);
    int iRes = CutTheTreeSolver(verts);

    auto end = std::chrono::system_clock::now();

    auto duration = (end - start);
    auto mSec = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

    //std::cout << iRes << "(time: " << mSec << ")" << std::endl;
    std::cout << iRes << std::endl;
}



using namespace std;


int visited[100009];
vector<int> edges[100009];
int val_node[100009];
int val[100009];


int diff(int val, int sum)
{
    return abs(sum - 2 * val);
}


int dfs(int node)
{
    if (visited[node] == 1)
        return val_node[node];

    visited[node] = 1;
    int c = val[node];
    for (auto k : edges[node])
    {
        c += dfs(k);
    }
    val_node[node] = c;
    return val_node[node];
}

int sln2(std::istream &input)
{
    int N, root, i;
    input >> N;
    int s = 0;
    for (i = 1; i <= N; i++)
    {
        input >> val[i];
        s = s + val[i];
    }

    for (i = 0; i< N - 1; i++)
    {
        int a, b;
        input >> a;
        input >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }


    for (i = 1; i <= N; i++)
    {
        if (edges[i].size() > 1)
        {
            root = i;
            break;
        }
    }

    for (i = 1; i <= N; i++)
        val_node[i] = visited[i] = 0;

    int c = dfs(root);

    for (i = 1; i <= N; i++)
        val_node[i - 1] = diff(val_node[i], s);

    sort(val_node, val_node + N);

    return val_node[0];
}

