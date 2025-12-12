#include <iostream>
#include <vector>
using namespace std;

vector<vector<long>> getManifold() {
    vector<vector<long>> manifold;
    string line;
    while (getline(cin, line) && !line.empty()) {
        vector<long> row;
        for (char c : line) {
            if (c == '.') row.push_back(0);
            else if (c == '^') row.push_back(-1);
            else row.push_back(1);
        }
        manifold.push_back(row);
    }
    return manifold;
}

void visualiseManifold(vector<vector<long>> &manifold) {
    for (vector<long> row : manifold) {
        for (long s : row) {
            if (s == -1) cout << "^";
            else cout << s; 
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int calculateBeam(vector<vector<long>> &manifold, bool visualise) {
    int count = 0;
    for (int i = 1; i < manifold.size(); i++) {
        for (int j = 0; j < manifold[i].size(); j++) {
            if (manifold[i - 1][j] > 0) {
                if (manifold[i][j] == -1) {
                    // Manifolds don't have two splits together
                    manifold[i][j - 1] += manifold[i - 1][j]; // Manifolds don't have split at Start
                    manifold[i][j + 1] += manifold[i - 1][j]; // Manifolds don't have split at End
                    count++;
                }
                else {
                    manifold[i][j] += manifold[i - 1][j];
                }
            }
        }
        if (visualise) visualiseManifold(manifold);
    }
    return count;
}

long calculateTimelines(vector<vector<long>> &manifold) {
    long timelines = 0;
    int lRow = manifold.size() - 1;
    for (int j = 0; j < manifold[lRow].size(); j++) timelines += manifold[lRow][j];
    return timelines;
}

int main() {
    cout << "BEGIN!" << endl;
    vector<vector<long>> manifold = getManifold();
    int count = calculateBeam(manifold, false);
    long timelines = calculateTimelines(manifold);

    // visualiseManifold(manifold);
    cout << "Tachyon Splits : " << count << endl;
    cout << "Beam Timelines : " << timelines << endl;
    return 0;
}