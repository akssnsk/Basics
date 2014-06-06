#pragma once

#include "Tasks.h"

struct GraphNode
{
    int iWeight;
    std::list<int> conn;
    int subTreeSum;
};
typedef std::vector<GraphNode> GraphType;

void CutTheTreePreparer(std::istream &input, GraphType *edges);
int CutTheTreeSolver(const GraphType &nodes);
int TreeTraverseNaive(const GraphType &verts, const std::pair<size_t, size_t> &cutEdge, size_t startNode, std::vector<int> &visited);
void CutTheTree();

int sln2(std::istream &input);
