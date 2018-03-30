/*main.cpp*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include "graph.h"

using namespace std;

#define _CRT_SECURE_NO_WARNINGS  // ignore C-related security warnings in Visual Studio:
class Station
{
public:
    string Name;
    int    ID;
    double Latitude;
    double Longitude;
    int    Capacity;
    Station(string name, int id, double latitude, double longitude, int capacity)
    {
        Name = name;
        ID = id;
        Latitude = latitude;
        Longitude = longitude;
        Capacity = capacity;
    }
    string getName()
    {
        return Name;
    }
    
    int getID()
    {
        return ID;
    }
    double getlatitude()
    {
        return Latitude;
    }
    
    double getlongitude(){ return Longitude;}
    int getCapacity(){return Capacity;}
};
//Getting the station ID for the BFS function
//Paramets are the vector and the string and return the ID
int stationName(string v,vector<Station>stations){
    int i;
    for (i = 0; i < stations.size(); i++)
    {
        if (stations[i].Name == v)
        {
            return  stations[i].ID;
        }
    }
    return -1;
}


// Inputs the stations from the given file, adding each station name as a
// vertex to the graph, and storing a new Station object into the vector.
// The graph is passed by reference --- note the & --- so that the changes
// made by the function are returned back.  The vector of Station objects is
// returned by the function.
//
vector<Station> InputStations(Graph& G, string filename)
{
    string line;
    vector<Station> V;
    
    ifstream input(filename);
    if (!input.good())  // failed to open:
        return V;
    
    getline(input, line);  // skip first line: column headers
    getline(input, line);  // first line of real data
    
    while (!input.eof())  // for each line of input:
    {
        stringstream  ss(line);
        
        // format:
        //   id,name,latitude,longitude,dpcapacity,online_date
        //   456,2112 W Peterson Ave,41.991178,-87.683593,15,5/12/2015
        //   101,63rd St Beach,41.78101637,-87.57611976,23,4/20/2015
        //
        string  stationID, name, latitude, longitude,   capacity;
        
        //
        // parse the line:
        //
        getline(ss, stationID, ',');
        getline(ss, name, ',');
        getline(ss, latitude, ',');
        getline(ss, longitude, ',');
        getline(ss, capacity, ',');
        
        
        // Create a new station object:
        Station S(name,stoi(stationID),stod(latitude),stod(longitude),stoi(capacity));
        V.push_back(S);//1 add station object to the vector
        G.AddVertex(name);//2 add vertex to the graph
        
        
        getline(input, line);
    }
    
    return V;
}


//
// Inputs the trips, adding / updating the edges in the graph.  The graph is
// passed by reference --- note the & --- so that the changes made by the
// function are returned back.  The vector of stations is needed so that
// station ids can be mapped to names; it is passed by reference only for
// efficiency (so that a copy is not made).
//
void ProcessTrips(string filename, Graph& G, vector<Station>& stations)
{
    string line;
    
    ifstream input(filename);
    if (!input.good())  // failed to open:
        return;
    
    getline(input, line);  // skip first line: column headers
    getline(input, line);  // first line of real data
    
    while (!input.eof())  // for each line of input:
    {
        stringstream  ss(line);
        
        // format:
        //   trip_id,starttime,stoptime,bikeid,tripduration,from_station_id,from_station_name,to_station_id,to_station_name,usertype,gender,birthyear
        //   10426561,6/30/2016 23:35,7/1/2016 0:02,5229,1620,329,Lake Shore Dr & Diversey Pkwy,307,Southport Ave & Clybourn Ave,Subscriber,Male,1968
        //
        string  tripID, fromID, toID, skip;
        
        //
        // parse the input line:
        //
        getline(ss, tripID, ',');
        getline(ss, skip, ',');
        getline(ss, skip, ',');
        getline(ss, skip, ',');
        getline(ss, skip, ',');
        getline(ss, fromID, ',');
        getline(ss, skip, ',');
        getline(ss, toID, ',');
        getline(ss, skip, ',');
        int weight = 1;
        string s,d;
        unsigned int i=0;
        //getting the station Name
        while ( i < stations.size())
        {
            if (stations[i].ID == stoi(fromID))
            {
                s= stations[i].Name;
            }
            i++;
        }
        //getting the station ID
        for ( i = 0; i < stations.size(); i++)
        {
            if (stations[i].ID == stoi(toID))
            {
                d= stations[i].Name;
            }
        }
        
        
        /// if exits 1 increment weight
        if(G.DoesEdgeExist(s,d)==1){
            G.UpdateEdge(s , d, weight);
        }
        else
        { G.AddEdge(s, d, 1);
        }
        
        
        getline(input, line);
    }
}

//stations-t2.csv
//
// getFileName:
//
// Inputs a filename from the keyboard, checks that the file can be
// opened, and returns the filename if so.  If the file cannot be
// opened, an error message is output and the program is exited.
//
string getFileName()
{
    string filename;
    
    // input filename from the keyboard:
    getline(cin, filename);
    
    // make sure filename exists and can be opened:
    ifstream file(filename);
    if (!file.good())
    {
        cout << "**Error: unable to open '" << filename << "'" << endl << endl;
        std::terminate();
    }
    
    return filename;
}


int main()
{
    int    N = 1000;
    Graph  DivvyGraph(N);
    
    cout << "** Divvy Graph Analysis **" << endl;
    
    string stationsFilename = getFileName();
    string tripsFilename = getFileName();
    
    vector<Station> stations = InputStations(DivvyGraph, stationsFilename);
    ProcessTrips(tripsFilename, DivvyGraph, stations);
    
    
    
    cout << ">> Graph:" << endl;
    cout << "   # of vertices: " << DivvyGraph.GetNumVertices() << endl;
    cout << "   # of edges:    " << DivvyGraph.GetNumEdges() << endl;
    cout << ">> Ready:" << endl;
    
    string cmd;
    int    fromID, toID;
    
    cout << ">> ";
    cin >> cmd;
    
    
    
    while (cmd != "exit")
    {
        if (cmd == "info")
        {
            cin >> fromID;
            //iter finds the name from id in the station graph
            auto iter= find_if(stations.begin(),stations.end(),[=] (Station s){
                if(s.ID== fromID)
                    return true;
                else
                    return  false;
                
                
            });
            if(iter==stations.end())
            {   //if not found
                cout<<"** No such station..."<<endl;
                cout<<">>"<<endl;
            }
            else
            {
                //Printing the info part
                cout << iter->Name<< endl;
                cout << "("<< iter->getlatitude()<<","<< iter->getlongitude()<<")"<<endl;
                cout<<"Capacity: "<<iter->getCapacity()<<endl;
                set<string> vertices = DivvyGraph.GetVertices();
                set<string> neighbors = DivvyGraph.GetNeighbors(iter->Name);
                cout<<"# of destination stations: "<< neighbors.size()<<endl;
                int count = 0;
                
                for (auto n : neighbors)
                {
                    vector<int> PrintWeight = DivvyGraph.GetEdgeWeights(iter->Name, n);
                    for (auto i : PrintWeight)
                    {
                        count+=i;
                    }
                }
                cout << "# of trips to those stations: " << count << endl;
                cout << "Station: trips" << endl;
                int A = 0;
                int i;
                // getting the ID  from the neighbors
                for (string s : neighbors)
                    
                {   for (i = 0; i < stations.size(); i++)
                {
                    if (stations[i].Name == s)
                    {
                        A= stations[i].ID;
                    }
                }
                    
                    int destID = A;
                    cout << "   " << s << " (" << destID << "): ";
                    vector<int> weights = DivvyGraph.GetEdgeWeights(iter->Name, s);
                    for (int j : weights)
                    {
                        cout << j << endl;
                    }
                }
                cout<<">>"<<endl;
            }
        }
        else if (cmd == "trips")
        {
            cin >> fromID;
            cin >> toID;
            int  i;
            string A, B;
            for ( i = 0; i < stations.size(); i++)
            {
                if (stations[i].ID == fromID)
                {
                    A=  stations[i].Name;
                }
                
            }
            for ( i = 0; i < stations.size(); i++)
            {
                if (stations[i].ID == toID)
                {
                    B=  stations[i].Name;
                }
                
            }
            //iter finds to and fromID
            auto iter= find_if(stations.begin(),stations.end(),[=] (Station s){
                if(s.ID== fromID)
                    return true;
                else
                    return  false;
                
                
            });
            auto iter2= find_if(stations.begin(),stations.end(),[=] (Station s){
                if(s.ID== toID)
                    return true;
                else
                    return  false;
                
                
            });
            
            if(iter==stations.end() || iter2 == stations.end())
            {
                cout<<"** One of those stations doesn't exist..."<<endl;
                cout<<">>"<<endl;
            }
            else
                
            {
                cout << iter->Name<<"->"<<iter2->Name<< endl;
                int weight = DivvyGraph.GetNumTripsTrips(A, B);
                cout<<"# of trips:"<<weight<<endl;
                cout<<">>"<<endl;
                
            }
        
            
        }
        else if (cmd == "bfs")
        {
            
            cin >> fromID;
            string fromId;
            
            auto iter= find_if(stations.begin(),stations.end(),[=] (Station s){
                if(s.ID== fromID)
                    return true;
                else
                    return  false;
                
                
            });
            if(iter==stations.end())
            {
                cout<<"** No such station..."<<endl;
                cout<<">>"<<endl;
                
            }
            else {
                
                int i ;
                for ( i = 0; i < stations.size(); i++)
                {
                    if (stations[i].ID == fromID)
                    {
                        fromId=  stations[i].Name;
                        //cout<<fromId<<endl;
                        break;
                    }
                    
                }
                vector<string> visited = DivvyGraph.BFS(fromId);
                int id=0;
                cout<< "# of stations: "<<visited.size()<<endl;
                
                for(int j=0;j<visited.size();j++){
                    
                    id=stationName(visited[j],stations);
                    
                    cout<<id<<",";
                }
                cout<<"#"<<endl;
                cout<<">>"<<endl;
                
            }
        }
        else if (cmd == "debug")
        {
            DivvyGraph.PrintGraph("Divvy Graph");
        }
        else
        {
            cout << "**Invalid command, try again..." << endl;
            cout<<">>"<<endl;
        }
        
    
        cin >> cmd;
    }
    
    cout << "**Done**" << endl;
    return 0;
}
