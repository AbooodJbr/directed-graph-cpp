#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

template <typename T>
class Graph {
private:
    unordered_map<T, unordered_set<T>> adjacencyList;

public:
    void insertVertex(const T& val) {
        adjacencyList[val]; 
    }

    bool removeVertex(const T& val) {
        if (adjacencyList.find(val) != adjacencyList.end()) {
            // Remove the vertex from all adjacency lists
            for (auto& vertex : adjacencyList) {
                vertex.second.erase(val);
                
            }
            // Remove the vertex itself
            adjacencyList.erase(val);
            return true;
        }
        return false;
    }

    bool isAdjacent(const T& u, const T& v) const {
        auto src = adjacencyList.find(u);
        if (src != adjacencyList.end()) {
            return src->second.find(v) != src->second.end();
        }
        return false;
    }

    void insertEdge(const T& u, const T& v) {
        insertVertex(u);
        insertVertex(v);
        if (!isAdjacent(u, v)) {
            adjacencyList[u].insert(v);
        }
    }

    bool removeEdge(const T& u, const T& v) {
        if (isAdjacent(u, v)) {
            adjacencyList[u].erase(v);
            return true;
        }
        return false;
    }

    void print() const {
        for (const auto& entry : adjacencyList) {
            cout << "( " << entry.first << " ) : [  ";
            for (const auto& neighbor : entry.second) {
                cout << neighbor << "  ";
            }
            cout << "]" << endl;
        }
    }

};

int main() {
    // Create a graph instance
    Graph<int> g;

    // Insert vertices
    cout << "Inserting vertices 1, 2, 3, and 4...\n";
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);

    // Print the graph
    cout << "Graph after inserting vertices:\n";
    g.print();

    // Insert edges
    cout << "Inserting edges (1->2), (2->3), (3->4), (4->1)...\n";
    g.insertEdge(1, 2);
    g.insertEdge(2, 3);
    g.insertEdge(3, 4);
    g.insertEdge(4, 1);

    // Print the graph
    cout << "Graph after inserting edges:\n";
    g.print();

    // Check adjacency
    cout << "Checking adjacency (1, 2): " << (g.isAdjacent(1, 2) ? "Yes" : "No") << endl;
    cout << "Checking adjacency (2, 4): " << (g.isAdjacent(2, 4) ? "Yes" : "No") << endl;

    // Remove an edge
    cout << "Removing edge (2->3)...\n";
    if (g.removeEdge(2, 3)) {
        cout << "Edge removed successfully.\n";
    }
    else {
        cout << "Edge not found.\n";
    }

    // Print the graph
    cout << "Graph after removing edge (2->3):\n";
    g.print();

    // Remove a vertex
    cout << "Removing vertex 3...\n";
    if (g.removeVertex(3)) {
        cout << "Vertex removed successfully.\n";
    }
    else {
        cout << "Vertex not found.\n";
    }

    // Print the graph
    cout << "Graph after removing vertex 3:\n";
    g.print();

    // Test edge removal for a non-existent edge
    cout << "Removing edge (4->1) which does not exist...\n";
    if (g.removeEdge(4, 1)) {
        cout << "Edge removed successfully.\n";
    }
    else {
        cout << "Edge not found.\n";
    }

    // Print the graph
    cout << "Graph after attempting to remove non-existent edge (4->1):\n";
    g.print();

    return 0;
}
