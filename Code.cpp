#include <iostream>
#include <fstream>
#include <map>
#include <climits>
#include <sstream> 
using namespace std;
#define INF 10000000000000000000
map<string, string> vertexMap; // mapping array declaration
const int MAX_VERTICES = 100; // declaring max size of adjacency matrix
int graph[MAX_VERTICES][MAX_VERTICES]; // declaring the adjacency matrix
int num_vertices; // total number of vertices in the graph
int e,r; // start and destination vertex
string mapping (const map<string, string>&map, const string& vertexx){
    // function to match building/intersection character code to the vertex number
    for (auto it = map.begin(); it != map.end(); ++it)
    {
        if (it->second == vertexx)
        {
            return it->first;
        }
    }   
    return "";
}
int minDistance(int dist[], bool sptSet[])
{
    // function returns the index of the vertex with the minimum distance value among the set of vertices not yet included in the shortest path tree
    int min = INT_MAX, min_index;
    for (int v = 0; v < num_vertices; v++){ if (sptSet[v] == false && dist[v] <= min){
        min = dist[v]; min_index = v;}
    }
    return min_index;
}
void printSolution(int dist[], int parent[])
{
    // function to print the shortest distance and the path taken 
    printf("Distance from Source to Destination is : ");
    for (int i = 0; i < num_vertices; i++)
    {
        if (i == r) {
            printf("%s %d\n", mapping(vertexMap, mapping(vertexMap, to_string(i)).substr(0, 2)).c_str(), dist[i]);
            printf("And the Shortest Path is :\n");
            int curr = i;
            string path = "";
            while (curr != e) {
                path = to_string(curr) + " -> " + path;
                curr = parent[curr];
            }
            path = to_string(e) + " -> " + path;
            cout << path << endl;
        }
    }
}
void dijkstra(int src)
{
    // function representing the dijkstra's algorithm
    int dist[num_vertices]; // The output array. dist[i] will hold the shortest
    int parent[num_vertices]; // parent[i] will hold the parent of vertex i in the shortest path
    bool sptSet[num_vertices]; // sptSet[i] will be true if vertex i is included in shortest
    for (int i = 0; i < num_vertices; i++)
        {dist[i] = INT_MAX; sptSet[i] = false;}

    dist[src] = 0;
    parent[src] = -1;

    for (int count = 0; count < (num_vertices - 1); count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < num_vertices; v++){
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]){
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }
    printSolution(dist, parent);
}
int main() 
{
    fstream newfile;
    fstream mapfile; // files to read the two text files
    int y; // number of buildings in map
    string start_building, dest_building;
    string startvertex,destvertex;
    stringstream ss1,ss2;
    newfile.open("graph.txt",ios::in);
    if (newfile.is_open())
    {
        // the if function reads contents from graph text file and stores the values into adjacency matrix "graph"
        newfile >> num_vertices;
        for (int i = 0; i < num_vertices; i++) {
            for (int j = 0; j < num_vertices; j++) {
                graph[i][j] = 0;}
        }
        int u, v, w;
        while (newfile >> u >> v >> w) {
            graph[u][v] = w;
            graph[v][u] = w; } // assuming undirected graph // the graph text file contains 2 way directions for all edges too
        cout<<"The adjacency-matrix is : "<<"\n";
        for (int i = 0; i < num_vertices; i++) {
            for (int j = 0; j < num_vertices; j++) {
                cout << graph[i][j] <<" "; } // printing adjacency matrix
        newfile.close();}
    }
    mapfile.open("map.txt",ios::in);
    if (mapfile.is_open())
    {
        // the if function reads contents from map text file and stores the values into array "vertexMap"
        mapfile >> y;
        string code;
        string vertex;
        while (mapfile >> code >> vertex) {
            vertexMap[code] =  vertex;}
        mapfile.close();
    }
    cout<<"\n"<<"The mapping array is : "<<"\n";
    for (auto it = vertexMap.begin(); it != vertexMap.end(); ++it) {
        // printing vertexMap array
        cout << "Vertex " << it->first << " maps to building/intersection : " << it->second << endl;
    }
    cout<<"Enter start building/intersection : ";
    cin>>start_building;
    cout<<"Enter destination building/intersection : ";
    cin>>dest_building;  
    startvertex=mapping (vertexMap, start_building);
    destvertex=mapping (vertexMap, dest_building);
    cout << "Building/intersection " << start_building << " matches to vertex: " << startvertex << "\n";
    cout << "Building/intersection " << dest_building << " matches to vertex: " << destvertex << "\n";
    ss1<<startvertex;
    ss1>>e;
    ss2<<destvertex;
    ss2>>r;
    dijkstra(e);
    return 0;
}