#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <climits>
using namespace std;

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

int boxToCircuit(vector<unordered_set<int>> &circuits, int B) {
    int C;
    for (int i = 0; i < circuits.size(); i++) {
        if (circuits[i].count(B)) C = i;
    }
    return C;
}

bool isSameCircuit(vector<unordered_set<int>> &circuits, int B1, int B2) {
    int C1 = boxToCircuit(circuits, B1);
    int C2 = boxToCircuit(circuits, B2);
    return (C1 == C2);
}

void connectBoxes(vector<unordered_set<int>> &circuits, int B1, int B2) {
    int C1 = boxToCircuit(circuits, B1);
    int C2 = boxToCircuit(circuits, B2);
    circuits[C1].insert(circuits[C2].begin(), circuits[C2].end());
    circuits.erase(circuits.begin() + C2);
}

long computeDistance(vector<int> P2, vector<int> P1) {
    long xDist = (P2[0] - P1[0]) * (P2[0] - P1[0]);
    long yDist = (P2[1] - P1[1]) * (P2[1] - P1[1]);
    long zDist = (P2[2] - P1[2]) * (P2[2] - P1[2]);
    return xDist + yDist + zDist;
}

void stripDistance(vector<vector<int>> &boxes, vector<unordered_set<int>> &circuits, 
    long &dist, int &B1, int &B2, int left, int right) {
    for (int i = left; i < right; i++) {
        for (int j = i + 1; j <= right; j++) {
            if (abs(boxes[j][1] - boxes[i][1]) > dist) break;
            else if (abs(boxes[j][2] - boxes[i][2]) > dist) continue;
            long cDist = computeDistance(boxes[j], boxes[i]);
            if (dist > cDist && !isSameCircuit(circuits, i, j)) {
                B1 = i;
                B2 = j;
                dist = cDist;
            } 
        }
    }
}

void minDistance(vector<vector<int>> &boxes, vector<unordered_set<int>> &circuits, 
    long &dist, int &B1, int &B2, int left, int right) {
    if (right - left < 2) {
        if (left == right) return;
        long cDist = computeDistance(boxes[right], boxes[left]);
        if (dist > cDist && !isSameCircuit(circuits, left, right)) {
            B1 = left;
            B2 = right;
            dist = cDist;
        }
    }

    int mid = (left + right) / 2;
    minDistance(boxes, circuits, dist, B1, B2, left, mid); // Left Side
    minDistance(boxes, circuits, dist, B1, B2, mid + 1, right); // Right Side

    // Strip Across
    int j = mid, k = mid;
    for (int i = left; i <= right; i++) {
        if (abs(boxes[mid][0] - boxes[i][0]) <= dist) {
            j = min(i, j);
            k = max(i, k);
        }
    }
    stripDistance(boxes, circuits, dist, B1, B2, j, k);
}

void createDecoration(vector<vector<int>> &boxes, vector<unordered_set<int>> &circuits, int operations) {
    for (int i = 0; i < operations; i++) {
        int B1, B2;
        long dist = LONG_MAX;
        minDistance(boxes, circuits, dist, B1, B2, 0, boxes.size() - 1);
        connectBoxes(circuits, B1, B2);
    }
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
    createDecoration(boxes, circuits, 3);

    // visualiseBoxes(boxes);
    visualiseCircuits(circuits);
    return 0;
}