#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#define UNVISITED 0

void Assert(bool print, std::string message);

class Graph
{
private:
    void operator =(const Graph&) {} // Protect assignment
    Graph(const Graph&) {} // Protect copy constructor
public:
    Graph() {} // Default constructor
    virtual ~Graph() {} // Base destructor
    // Return the number of vertices in the graph
    virtual int n() = 0;
    // Return the current number of edges in the graph
    virtual int e() = 0;
    // Store an edge from "v1" to "v2" with weight "wgt"
    virtual void setEdge(int v1, int v2, int wgt) = 0;
    // Delete the edge going from "v1" to "v2"
    virtual void delEdge(int v1, int v2) = 0;
    // Return weight of the edge from "v1" to "v2".
    // Return 0 if no such edge exists.
    virtual int weight(int v1, int v2) = 0;
    // Get the mark value for vertex "v"
    virtual int getMark(int v) = 0;
    // Set the mark value for vertex "v" to be "val"
    virtual void setMark(int v, int val) = 0;
    // Return the index of the first neighbor for vertex "v"
    virtual int first(int v) = 0;
    // Return the index of the next neighbor
    // (after "v2") for vertex "v1"
    virtual int next(int v1, int v2) = 0;
};

class Graphm : public Graph
{
private:
    int numVertex, numEdge;
    int** matrix;
    int* mark;
public:
    Graphm(int numVert)
    {
        int i;
        numVertex = numVert;
        numEdge = 0;
        mark = new int[numVert];
        for (i = 0; i < numVertex; i++)
            mark[i] = UNVISITED;
        matrix = (int**) new int* [numVertex];
        for (i = 0; i < numVertex; i++)
            matrix[i] = new int[numVertex];
        for (i = 0; i < numVertex; i++)
            for (int j = 0; j < numVertex; j++)
                matrix[i][j] = 0;
    }

    ~Graphm()
    {
        delete[] mark;
        for (int i = 0; i < numVertex; i++)
            delete[] matrix[i];
        delete[] matrix;
    }

    int n() { return numVertex; }
    int e() { return numEdge; }

    void setEdge(int v1, int v2, int wgt)
    {
        Assert(wgt > 0, "Illegal weight value");
        if (matrix[v1][v2] == 0)
            numEdge++;
        matrix[v1][v2] = wgt;
    }

    void delEdge(int v1, int v2)
    {
        if (matrix[v1][v2] != 0) numEdge--;
        matrix[v1][v2] = 0;
    }

    int weight(int v1, int v2) { return matrix[v1][v2]; }
    int getMark(int v) { return mark[v]; }
    void setMark(int v, int val) { mark[v] = val; }

    int first(int v)
    {
        for (int i = 0; i < numVertex; i++)
            if (matrix[v][i] != 0)
                return i;
        return numVertex;
    }

    int next(int v1, int v2)
    {
        for (int i = v2 + 1; i < numVertex; i++)
            if (matrix[v1][i] != 0)
                return i;
        return numVertex;
    }

};

void printAdjacencyMatrix(Graph* G)
{
    std::cout << std::left;
    std::cout << std::setw(5) << " ";
    for (int i = 0; i < G->n(); i++)
        std::cout << std::setw(2) << i + 1;
    std::cout << std::endl;
    std::cout << "    ----------------" << std::endl;

    for (int i = 0; i < G->n(); i++)
    {
        std::cout << " " << i + 1 << " | ";
        for (int j = 0; j < G->n(); j++)
        {
            if (G->weight(i, j) == UNVISITED)
                std::cout << std::setw(2) << " ";
            else
                std::cout << std::setw(2) << G->weight(i, j);
        }
        std::cout << std::endl;
    }
}

void printAdjacencyList(Graph* G)
{

    for (int i = 0; i < G->n(); i++)
    {
        std::cout << " " << i + 1 << " |";
        for (int j = 0; j < G->n(); j++)
        {
            if (G->weight(i, j) != UNVISITED)
                std::cout << " -> | " << j + 1 << " |";
        }
        std::cout << std::endl;
    }
}

void Assert(bool print, std::string message)
{
    if (!print)
        throw message;
}

#endif