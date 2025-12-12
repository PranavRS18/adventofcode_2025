#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

// Change Constants here
const int operations = 1000; // Number of Connections

vector<vector<int>> getJunctionBoxes() {
    vector<vector<int>> boxes;
    string line;
    while (getline(cin, line) && !line.empty()) {
        stringstream ss(line);
        int x, y, z;
        char comma;
        ss >> x >> comma >> y >> comma >> z;
        boxes.push_back({x, y, z});
    }

    sort(boxes.begin(), boxes.end());
    return boxes;
}

vector<unordered_set<int>> initialiseCircuits(int size) {
    vector<unordered_set<int>> circuits;
    for (int i = 0; i < size; i++) {
        circuits.push_back({i});
    }
    return circuits;
}

long computeDistance(vector<int> P2, vector<int> P1) {
    long xDist = (long)(P2[0] - P1[0]) * (long)(P2[0] - P1[0]);
    long yDist = (long)(P2[1] - P1[1]) * (long)(P2[1] - P1[1]);
    long zDist = (long)(P2[2] - P1[2]) * (long)(P2[2] - P1[2]);
    return xDist + yDist + zDist;
}

int boxToCircuit(vector<unordered_set<int>> &circuits, int B) {
    for (int i = 0; i < circuits.size(); i++) {
        if (circuits[i].count(B)) return i;
    }
    return -1;
}

bool isSameCircuit(vector<unordered_set<int>> &circuits, int B1, int B2) {
    int C1 = boxToCircuit(circuits, B1);
    int C2 = boxToCircuit(circuits, B2);
    return (C1 == C2);
}

void connectBoxes(vector<unordered_set<int>> &circuits, int B1, int B2) {
    int C1 = boxToCircuit(circuits, B1);
    int C2 = boxToCircuit(circuits, B2);
    if (C1 == C2) return;
    
    circuits[C1].insert(circuits[C2].begin(), circuits[C2].end());
    circuits.erase(circuits.begin() + C2);
}

void createDecoration(vector<vector<int>> &boxes, vector<unordered_set<int>> &circuits, 
    int operations) {
    vector<vector<long>> distances;
    for (int i = 0; i < boxes.size(); i++) {
        for (int j = i + 1; j < boxes.size(); j++) {
            distances.push_back({computeDistance(boxes[j], boxes[i]), i, j});
        }
    }
    sort(distances.begin(), distances.end());
    for (int i = 0; i < operations; i++) {
        if (circuits.size() == 1) {
            cout << "Last Two Junction Boxes' X Coordinates Product : ";
            cout << boxes[distances[i][1]][0] * boxes[distances[i][2]][0] << endl;
            break;
        }
        connectBoxes(circuits, distances[i][1], distances[i][2]);
    }
}

void calcCircuitSizes(vector<unordered_set<int>> &circuits) {
    vector<int> sizes;
    for (unordered_set<int> circuit : circuits) {
        sizes.push_back(circuit.size());
    }
    sort(sizes.rbegin(), sizes.rend());
    cout << "Product of 3 Largest Circuits: " << sizes[0] * sizes[1] * sizes[2] << endl;
}

void visualiseBoxes(vector<vector<int>> &boxes) {
    for (vector<int> box : boxes) {
        cout << "X: " << box[0] << ", ";
        cout << "Y: " << box[1] << ", ";
        cout << "Z: " << box[2] << endl;
    }
}

void visualiseCircuits(vector<unordered_set<int>> &circuits) {
    for (unordered_set<int> circuit : circuits) {
        for (int B : circuit) {
            cout << B << " ";
        }
        cout << endl;
    }
}

int main() {
    cout << "BEGIN!" << endl;

    vector<vector<int>> boxes = getJunctionBoxes();
    vector<unordered_set<int>> circuits = initialiseCircuits(boxes.size());
    createDecoration(boxes, circuits, operations);
    calcCircuitSizes(circuits);

    // visualiseBoxes(boxes);
    // visualiseCircuits(circuits);
    cout << "Operations: " << operations << endl;
    cout << "No. of Circuits: " << circuits.size() << endl;
    return 0;
}