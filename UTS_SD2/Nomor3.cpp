#include <iostream>
#include <vector>
#include <queue>

using namespace std;
class Graph {
private:
    int numVertices;
    vector<vector<int>> adjMatrix;

public:
    Graph(int V) {
        numVertices = V;
        adjMatrix.resize(numVertices, vector<int>(numVertices, 0));
    }

    void addEdge(int i, int j, int weight) {
        if (i >= 0 && i < numVertices && j >= 0 && j < numVertices) {
            adjMatrix[i][j] = weight;
            adjMatrix[j][i] = weight;
        } else {
            cout << "Indeks tidak valid." << endl;
        }
    }

    void dfsUtil(int u, vector<bool>& visited, const vector<char>& vertexChar) {
        visited[u] = true;
        cout << vertexChar[u]; 

        for (int v = numVertices - 1; v >= 0; v--) {
            if (adjMatrix[u][v] > 0 && !visited[v]) {
                cout << " -> ";
                dfsUtil(v, visited, vertexChar);
            }
        }
    }

    // Fungsi utama
    void dfs(int startVertex, const vector<char>& vertexChar) {
        vector<bool> visited(numVertices, false);
        cout << "PENJELAJAHAN PARUL (DFS dari A):" << endl;
        dfsUtil(startVertex, visited, vertexChar);
        cout << endl;
    }

    void bfs(int startVertex, int endVertex, const vector<char>& vertexChar, const vector<string>& vertexNames) {
        vector<bool> visited(numVertices, false);
        queue<int> q;
        vector<int> parent(numVertices, -1); 
        vector<int> edgeCount(numVertices, 0); 

        visited[startVertex] = true;
        q.push(startVertex);

        cout << "JALUR TERCEPAT PARUL (BFS):" << endl;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (u == endVertex) break; 

            for (int v = numVertices - 1; v >= 0; v--) {
                if (adjMatrix[u][v] > 0 && !visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    edgeCount[v] = edgeCount[u] + 1; 
                    q.push(v);
                }
            }
        }   
        // Bangun Jalur dari endVertex ke startVertex
        vector<int> path;
        int curr = endVertex;
        while (curr != -1) {
            path.push_back(curr);
            curr = parent[curr];
        }
        // Balik urutan jalur
        int left = 0;
        int right = path.size() - 1;
        while (left < right) {
            int temp = path[left];
            path[left] = path[right];
            path[right] = temp;
            left++;
            right--;
        }

        int totalJarak = 0;
        vector<char> pathString;

        for (int i = 0; i < path.size(); ++i) {
            int nodeIndex = path[i];
            char nodeChar = vertexChar[nodeIndex];
            string nodeName = vertexNames[nodeIndex];

            cout << nodeName << " (" << nodeChar << ")" << endl;

            pathString.push_back(nodeChar);

            if (i < path.size() - 1) {
                int u = path[i];
                int v = path[i + 1];
                int jarak = adjMatrix[u][v];
                totalJarak += jarak;
                cout << jarak << "m" << endl;
            }
        }

        cout << "\nJalur terpendek: ";
        for (int i = 0; i < pathString.size(); ++i) {
            cout << pathString[i];
            if (i < pathString.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
        cout << "Total langkah: " << edgeCount[endVertex] << " edge" << endl;
        cout << "Total jarak: " << totalJarak << " meter" << endl;
    }
};

int main() {
    int V = 5;
    Graph g(V);

    vector<char> vertexChar;
    vertexChar.push_back('A');
    vertexChar.push_back('B');
    vertexChar.push_back('C');
    vertexChar.push_back('D');
    vertexChar.push_back('E');
    
    vector<string> vertexNames;
    vertexNames.push_back("Warung Kopi Pak Harry");
    vertexNames.push_back("Kedai Coding IKLC");
    vertexNames.push_back("Catfe Alya");
    vertexNames.push_back("Studio Fasilkom-TI");
    vertexNames.push_back("Wi-Fi Gratis Sejagat (tujuan Parul)");

    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 3, 3);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 5); 

    g.dfs(0, vertexChar); 

    cout << endl;

    g.bfs(0, 4, vertexChar, vertexNames);
}