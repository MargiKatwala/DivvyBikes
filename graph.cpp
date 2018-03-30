/*graph.cpp*/

#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "graph.h"
#include <queue>


using namespace std;


//
// Constructor:
//
Graph::Graph(int N)
{
    this->NumVertices = 0;
    this->NumEdges = 0;
    this->Capacity = N;
    
    this->Vertices = new Edge*[N];
    this->Names = new string[N];
    
}


//
// Destructor:
//
Graph::~Graph()
{
    //
    // Future work:
    //
}


//
// AddVertex:
//
// Adds the given vertex v to the graph, returning true if
// successful and false if not.  The add fails if (1) the
// graph is full, or (2) the vertex already exists in the
// graph.
//

bool Graph::AddVertex(string v)
{
    //
    // if the graph is "full", i.e. cannot hold more vertices,
    // then return false:
    //
    // TODO #1
    //
    if (this->Capacity == this->NumVertices)
        return false;
    
    
    
    //
    // if the vertex name already exists in the graph,
    // then return false.  To determine, perform a linear
    // search of the Names array; note that in C++ you
    // compare strings using ==, no strcmp needed:
    //
    // TODO #2
    //
    
    int index=0;
    while(index < this->NumVertices)
    {
        if (v == this->Names[index])
        {  return false;
        }
        index++;
    }
    
    
    //
    // there's room to add another vertex, so grab next index
    // and initialize that linked-list to empty, and store
    // vertex's name:
    //
    int i = this->NumVertices;
    
    this->Vertices[i] = nullptr;  // head of LL: null
    this->Names[i] = v;           // copy vertex string:
    
    this->NumVertices++;
    return true;
}


bool Graph::DoesEdgeExist(string fromID, string toID){
    int index = 0;
    int S = -1;
    int j = 0;
    int D = -1;
    //look src vertex
    while( index < this->NumVertices)
    {
        if (this->Names[index] == fromID)
        { S = index;//obtatining the index
        }
        index++;
    }
    //getting the num vertices index of S
    //getting the num vertices index of D
    while( j < this->NumVertices)
    {
        if ( this->Names[j] == toID)
        {  D = j;
        }
        j++;
    }
    //last two checks
    if(S == -1 || D==-1)
        return false;
    Edge *curr;
    
    curr=this->Vertices[S];
    while(curr!=NULL){
        if (curr->Dest==D){
            ++curr->Count;
            
            return true;
        }
        curr=curr->Next;
        
    }
    return false;



}

//
// AddEdge:
//
// Adds an edge from src to dest, with the given weight, returning
// true if successful and false if not.  The add fails if the src
// or dest vertex do not exist.
//
bool Graph::AddEdge(string src, string dest, int weight)
{
    int index = 0;
    int S = -1;
    int j = 0;
    int D = -1;
    //look src vertex
    while( index < this->NumVertices)
    {
        if (this->Names[index] == src)
        { S = index;//obtatining the index
        }
        index++;
    }
    //getting the num vertices index of S
    //getting the num vertices index of D
    while( j < this->NumVertices)
    {
        if ( this->Names[j] == dest)
        {  D = j;
        }
        j++;
    }
    //last two checks
    if(S == -1 || D==-1)
        return false;
    
    Edge *e = new Edge();
    
    e->Dest = D;
    e->Src = S;
    e->Weight = weight;
    Edge *cur  = this->Vertices[S];//assigning the vertices to the current edge
    Edge *prev = nullptr;
    while (cur != nullptr)
    {
        if ((e->Dest == cur->Dest) && (e->Weight <= cur->Weight))
            break;
        else if(e->Dest < cur->Dest)
            break;
        
        
        prev = cur;
        cur  = cur->Next;
    }
    if(prev != nullptr)
        
    {
        prev->Next = e;
        e->Next = cur;
        
    }
    else {
        e->Next = this->Vertices[S];
        this->Vertices[S] = e;
    }
   
    this->NumEdges++;
    return true;
}


//
// PrintGraph:
//
// Prints the graph, typically for debugging purposes.
//
void Graph::PrintGraph(string title)
{
    cout << ">>Graph: " << title << endl;
    cout << "  # of vertices: " << this->NumVertices << endl;
    cout << "  # of edges:    " << this->NumEdges << endl;
    cout << "  Capacity:      " << this->Capacity << endl;
    
    cout << "  Vertices:" << endl;
    
    for (int v = 0; v < this->NumVertices; ++v)
    {
        cout << "    " << v << " (" << this->Names[v] << "): ";
        
        Edge *edge = this->Vertices[v];
        while (edge != nullptr)
        {
            cout << "(" << edge->Src << "," << edge->Dest << "," << edge->Weight << ")";
            
            edge = edge->Next;
            if (edge != nullptr)
                cout << ", ";
        }
        
        cout << endl;
    }
}

int Graph::GetNumEdges()
{
    return this->NumEdges;
}
set<string> Graph::GetVertices() {
    set<string> vertices;
    
    for (int i=0; i<this->NumVertices; ++i){
        vertices.insert(this->Names[i]);
    }
    return vertices;
}
// GetNeighbors:
//
// Returns a set containing all the vertices adjacent to v.
// If v does not exist in the graph, the returned set is
// empty.
//
set<string> Graph::GetNeighbors(string v) {
    set<string> verices ;
    
    int S = -1;
    int index=0;
    while( index < this->NumVertices)
    {
        if (this->Names[index] == v)
        { S = index;//obtatining the index
        }
        index++;
    }
    Edge *cur  = this->Vertices[S];//assigning the vertices to the current edge
    while (cur != nullptr)
    {
        verices.insert(this->Names[cur->Dest]);
        cur  = cur->Next;
    }
    
    return verices;
}

vector<int> Graph::GetEdgeWeights(string src, string dest) {
    vector<int>  result;
    int index = 0;
    int S = -1;
    int j = 0;
    int D = -1;
    //look src vertex
    while( index < this->NumVertices)
    {
        if (this->Names[index] == src)
        { S = index;//obtatining the index
        }
        index++;
    }
    //getting the num vertices index of S
    //getting the num vertices index of D
    while( j < this->NumVertices)
    {
        if ( this->Names[j] == dest)
        {  D = j;
        }
        j++;
    }
    
    int i=0;
    while(i<this->NumVertices){
        Edge *cur= this->Vertices[i];
        while(cur!=nullptr)
        {
            if((S==cur->Src) &&(D==cur->Dest))
                
            {
                result.push_back(cur->Weight);
                
            }
            
            cur=cur->Next;
        }
        i++;
    }
    return result;
}

int  Graph::GetNumVertices() {
    set<string> vertices;
    int index=0;
    for (int i=0; i<this->NumVertices; ++i){
        vertices.insert(this->Names[i]);
        index++;
    }
    return index;
}

bool Graph::UpdateEdge(string src, string  dest, int weight)
{
    int index = 0;
    int S = -1;
    int j = 0;
    int D = -1;
    //look src vertex
    while( index < this->NumVertices)
    {
        if (this->Names[index] == src)
        { S = index;//obtatining the index
        }
        index++;
    }
    //getting the num vertices index of S
    //getting the num vertices index of D
    while( j < this->NumVertices)
    {
        if ( this->Names[j] == dest)
        {  D = j;
        }
        j++;
    }
    Edge *e = new Edge();
    e->Dest = D;
    e->Src = S;
    e->Weight = weight;
    Edge *cur  = this->Vertices[S];//assigning the vertices to the current edge
    Edge *prev = nullptr;
    while (cur != nullptr)
    {
         if (e->Dest == cur->Dest)
        {   cur->Weight++;
            return true;
    
        }
        else if(e->Dest < cur->Dest)
            break;
      
        
        prev = cur;
        cur  = cur->Next;
       
       
    }
    if(prev != nullptr)
        
    {
        prev->Next = e;
        e->Next = cur;
        
    }
    else {
        e->Next = this->Vertices[S];
        this->Vertices[S] = e;
         
    }
    
    this->NumEdges++;
    return true;
}

vector<int>  Graph:: iNeighbors(int v){
    vector<int> V;
        Edge *cur = this->Vertices[v];
        while(cur!=nullptr)
        {
            V.push_back(cur->Dest);
            cur= cur->Next;
        }
    
    return  V;
}
int  Graph:: getiNeighbors(int v){
    vector<int> V;
    int index=0;
    Edge *cur = this->Vertices[v];
    while(cur!=nullptr)
    {
        V.push_back(cur->Dest);
        cur= cur->Next;
        index++;
    }
    
    return  index;
}
vector<string> Graph:: BFS(string v){
    vector<string> visited;
    queue<int> frontierQueue;
    set<int> discoveredSet;
    int index = 0;
    int S = -1;
    while( index < this->NumVertices)
    {
        if (this->Names[index] == v)
        { S = index;//obtatining the index
            break;
        }
        index++;
    }
    if(S<0){ return visited;}
    frontierQueue.push(S);
    discoveredSet.insert(S);
    while(!(frontierQueue.empty())){
    
        int cur=frontierQueue.front();
        frontierQueue.pop();
        visited.push_back(this->Names[cur]);
        vector<int> V = iNeighbors(cur);
        for( auto adjV : V){
        
        if(discoveredSet.find(adjV)== discoveredSet.end())
        {
            frontierQueue.push(adjV);
            discoveredSet.insert(adjV);
        }
        }
    }
    return visited;
}

int Graph::GetNumTripsTrips(string  src, string  dest) {
  
    
    int index = 0;
    int S = -1;
    int j = 0;
    int D = -1;
    while( index < this->NumVertices)
    {
        if (this->Names[index] == src)
        { S = index;//obtatining the index
        }
        index++;
    }
    //getting the num vertices index of S
    //getting the num vertices index of D
    while( j < this->NumVertices)
    {
        if ( this->Names[j] == dest)
        {  D = j;
        }
        j++;
    }
    
    int i=0;
    while(i<this->NumVertices){
        Edge *cur= this->Vertices[i];
        while(cur!=nullptr)
        {
            if((S==cur->Src) &&(D==cur->Dest))
                
            {
              //  result.push_back(cur->Weight);
                return cur->Weight;
                
            }
            
            cur=cur->Next;
        }
        i++;
    }
  
    
    return 0;
}
