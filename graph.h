/*graph.h*/

#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
using namespace std;
//
class Graph
{
private:
    class Edge
    {
    public:
        int   Src, Dest, Weight;
        Edge *Next;
        int Count;
    };
    
    
    Edge  **Vertices;
    string *Names;
    int     NumVertices;
    int     NumEdges;
    int     Capacity;
   
   
   
    
public:
    Graph(int N);
    ~Graph();
    
    bool AddVertex(string v);
    bool AddEdge(string src, string dest, int weight);
    int  GetNumVertices();
    vector<string> BFS(string v);
    int GetNumEdges();
    bool DoesEdgeExist(string fromID, string toID);
    vector<int>  iNeighbors(int v);
    bool UpdateEdge(string   S, string D, int weight);
    int  getiNeighbors(int v);
    int GetNumTripsTrips(string src, string dest);
    set<string> GetVertices();
    set<string> GetNeighbors(string v);
    vector<int> GetEdgeWeights(string src, string dest);
    void PrintGraph(string title);
};

