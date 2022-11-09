#include <iostream>
#include <string>
#include <vector>
#include "MatrixGraph.h"

#define UNVISITED 0

void setAllEdges(Graph* G);
void resetMark(Graph* G);
void findAllPaths(Graph* G, int v1, int v2, std::vector<int>& stack);
void printStack(std::vector<int>& stack);

int main()
{
    const int startVertex = 3, endVertex = 6;

    Graphm matrixGraph(6);
    std::vector<int> stack;

    setAllEdges(&matrixGraph);
    std::cout << "All the paths from vertex " << startVertex << " to vertex "
        << endVertex << " are as follows : " << std::endl << std::endl;
    findAllPaths(&matrixGraph, startVertex - 1, endVertex - 1, stack);

}

void setAllEdges(Graph* G)
{
    G->setEdge(0, 1, 1);
    G->setEdge(1, 3, 1);
    G->setEdge(2, 0, 1);
    G->setEdge(2, 1, 1);
    G->setEdge(2, 4, 1);
    G->setEdge(3, 5, 1);
    G->setEdge(4, 1, 1);
    G->setEdge(4, 3, 1);
    G->setEdge(4, 5, 1);
}

void resetMark(Graph* G)
{
    for (int i = 0; i < G->n(); i++)
        G->setMark(i, 0);
}

void findAllPaths(Graph* G, int v1, int v2, std::vector<int>& stack)
{
    G->setMark(v1, 1);

    for (int w = G->first(v1); w < G->n(); w = G->next(v1, w))
    {
        if (G->getMark(w) == 0)
        {
            stack.push_back(v1);
            G->setMark(w, 1);
            findAllPaths(G, w, v2, stack);
            G->setMark(w, 0);
            if (stack[stack.size() - 1] != v2)
                stack.pop_back();
        }
    }
    if (v1 == v2)
        stack.push_back(v1);

    if (!stack.empty() && stack[stack.size() - 1] == v2)
    {
        printStack(stack);
        stack.pop_back();
    }
    G->setMark(v1, 0);
}

void printStack(std::vector<int>& stack)
{
    for (int i : stack)
    {
        std::cout << i + 1;
        if(i != stack[stack.size()-1])
            std::cout << " -> ";
    }
    std::cout << std::endl;
}

