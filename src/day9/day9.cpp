#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

vector<vector<int>> getRedTiles() {
    vector<vector<int>> redTiles;
    string line;
    while (getline(cin, line) && !line.empty()) {
        stringstream ss(line);
        int a, b;
        char comma;
        ss >> a >> comma >> b;
        redTiles.push_back({a, b});
    }
    sort(redTiles.begin(), redTiles.end());
    return redTiles;
}

bool isValidTile(vector<vector<int>> &redTiles, vector<int> tile) {
    bool tl = false, tr = false, bl = false, br = false;
    for (int i = 0; i < redTiles.size(); i++) {
        if (redTiles[i][0] <= tile[0] && redTiles[i][1] <= tile[1]) tl = true;
        if (redTiles[i][0] <= tile[0] && redTiles[i][1] >= tile[1]) bl = true;
        if (redTiles[i][0] >= tile[0] && redTiles[i][1] <= tile[1]) tr = true;
        if (redTiles[i][0] >= tile[0] && redTiles[i][1] >= tile[1]) br = true;
    }
    return (tl && bl && tr && br);
}

long calculateMaxArea(vector<vector<int>> &redTiles) {
    long maxArea = 0;
    for (int i = 0; i < redTiles.size(); i++) {
        for (int j = i + 1; j < redTiles.size(); j++) {
            if (isValidTile(redTiles, {redTiles[i][0], redTiles[j][1]}) 
                && isValidTile(redTiles, {redTiles[j][0], redTiles[i][1]})) {
                long xDist = abs((long)(redTiles[j][0]) - (long)(redTiles[i][0])) + 1;
                long yDist = abs((long)(redTiles[j][1]) - (long)(redTiles[i][1])) + 1;
                maxArea = max(maxArea, xDist * yDist);
            }
        }
    }
    return maxArea;
}

int main() {
    cout << "BEGIN!" << endl;

    vector<vector<int>> redTiles = getRedTiles();
    long area = calculateMaxArea(redTiles);

    cout << "Maximum Area : " << area << endl;
    return 0;
}