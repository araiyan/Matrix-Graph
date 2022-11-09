#include <iostream>
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

void Assert(bool print, std::string message)
{
    if (!print)
        throw message;
}