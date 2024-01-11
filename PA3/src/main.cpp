#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class disjointSet{
    int* parent;
    int* rank;
    public:

    // Constructor
    disjointSet(int n){
        parent = new int[n];
        rank = new int[n];
        for (int i=0; i<n; i++){
            parent[i] = i;
            rank[i] = 1;
        }
    }

    // Find-set
    int findSet(int u){
        if (parent[u] != u) parent[u] = findSet(parent[u]);
        return parent[u];
    }

    // Union
    void Union(int u, int v){
        int r1 = findSet(u);
        int r2 = findSet(v);
        if (r1 != r2){
            if (rank[r1] > rank[r2]) parent[r2] = r1;
            else if (rank[r2] > rank[r1]) parent[r1] = r2;
            else {
                parent[r2] = parent[r1];
                rank[r1]++;
            }
        }
        else return;
    }

};
// Disjoint-set implementation reference: https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/

class edge{
    public:
    int w;
    int u,v;
};


int main(int argc, char* argv[])
{
    if (argc < 3){
        cout << "Wrong command formant!" << endl;
        return 1;
    }
    // Input
    fstream ifile;
    ifile.open(argv[1], ios::in);
    if (!ifile){
        cout << "Input file cannot be opened!" << endl;;
        return 1;
    }
    // Output
    fstream ofile;
    ofile.open(argv[2], ios::out);
    if (!ofile){
        cout << "Output file cannot be opened!" << endl;
        return 1;
    }

    char graph;
    int edgeNum;
    int n;
    ifile >> graph;
    ifile >> n >> edgeNum;
    edge* edges_unsorted = NULL;
    edges_unsorted = new edge [edgeNum];

    for (int i=0; i<edgeNum; i++){
        ifile >> edges_unsorted[i].u >> edges_unsorted[i].v >> edges_unsorted[i].w;
    }

    // Sort edges in "descending" order
    /// Counting sort, add 100 to weight values so that all weights are positive or zero
    int range = 201;
    int *count = NULL;
    count = new int [range];

    edge* edges = NULL;
    edges = new edge[edgeNum];
    
    for (int i=0; i<range; i++){
        count[i] = 0;
    }
    for (int i=0; i<edgeNum; i++){
        count[edges_unsorted[i].w + 100] = count[edges_unsorted[i].w + 100] + 1;
    }

    // // Debug:
    // for (int i=0; i<range; i++) {
    //     if (count[i] != 0) cout << i-100 << ":" << count[i] << " " ;
    // }
    // cout << endl;
    for (int i=0; i<range; i++){
        count[i] = count[i] + count[i-1];
    }
    for (int i=edgeNum-1; i>=0; i--){
        edges[ edgeNum+1 - count[edges_unsorted[i].w+100] -1] = edges_unsorted[i];
        count[edges_unsorted[i].w+100]--;
    }

    // // Debug:
    // for (int i=0; i<range; i++) {
    //     if (count[i] != 0) cout << i-100 << ":" << count[i] << " " ;
    // }
    // cout << endl;
    // for (int i=0; i<edgeNum; i++){
    //     cout << edges[i].u << " " << edges[i].v << " " << edges[i].w << endl;
    // }

    // Kruskal's Algorithm
    int cutW = 0;
    disjointSet vertices(n);
    vector<edge> removedEdges; 

    /// Undirected graph
    if ( graph == 'u'){
        int chosen = 0;
        for (int i=0; i<edgeNum; i++){
            if (chosen == n-1){
                cutW += edges[i].w;
                removedEdges.push_back(edges[i]);
                continue;
            }
            if ( vertices.findSet(edges[i].u) != vertices.findSet(edges[i].v) ){
                vertices.Union(edges[i].u, edges[i].v);
                chosen++;
            } 
            else{
                cutW += edges[i].w;
                removedEdges.push_back(edges[i]);
            }

        }
    }
    
    /// Directed graph
    else if ( graph == 'd'){
        // Transitive closure for the directed MST
        bool** t = NULL;
        t = new bool*[n];
        for (int i=0; i<n; i++) t[i] = new bool[n];
        for (int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                if (i == j) t[i][j] = true;
                else t[i][j] = false;
            }
        }


        disjointSet veritces(n);
        for (int i=0; i<edgeNum; i++){
            bool exist_path = false;
            for (int x=0; x<n; x++){
                if (t[edges[i].v][x] == true && t[x][edges[i].u] == true) {
                    exist_path = true; // cycle would be formed
                    break;
                }
            }
            
            if (exist_path == true){
                // cout << "(" << edges[i].u << "," << edges[i].v << ")" << endl;
                removedEdges.push_back(edges[i]);
                cutW += edges[i].w;
            }
            else {
                // Do not add negative edges if u and v are already in the MST
                if ( edges[i].w < 0 && vertices.findSet(edges[i].u) == vertices.findSet(edges[i].v) ){
                    // cout << "(" << edges[i].u << "," << edges[i].v << ")" << endl;
                    removedEdges.push_back(edges[i]);
                    cutW += edges[i].w;
                }
                else { 
                    vertices.Union(edges[i].u, edges[i].v);
                    // Update transitive closure table
                    t[edges[i].u][edges[i].v] = true;
                    for (int x=0; x<n; x++){
                        if (t[x][edges[i].u] == true){
                            t[x][edges[i].v] = true;
                            for (int y=0; y<n; y++){
                                if (t[edges[i].v][y] == true) {
                                    t[x][y] = true;
                                    t[edges[i].u][y] = true;
                                }
                            }
                        }
                    }
                }
            }   
        }
    }
    // Output
    ofile << cutW << endl;
    for (int i=0; i<removedEdges.size(); i++){
        ofile << removedEdges[i].u << " " << removedEdges[i].v << " " << removedEdges[i].w << endl;
    }
    return 0;
}