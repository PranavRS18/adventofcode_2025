#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Part 1 Constant
const bool PART1 = false;

vector<vector<int>> getPapers() {
    vector<vector<int>> papers;
    string rowS;
    getline(cin, rowS);
    while (rowS != "") {
        vector<int> row;
        for (char pos : rowS) {
            if (pos == '@') {
                row.push_back(1);
            }
            else {
                row.push_back(0);
            }
        }
        papers.push_back(row);
        getline(cin, rowS);
    }
    return papers;
}

int countPapers(vector<vector<int>> &papers, int i, int j, int row_size, int col_size) {
    int count = 0;
    if (i - 1 >= 0) {
        if (j - 1 >= 0 && papers[i - 1][j - 1]) count++;
        if (papers[i - 1][j]) count++;
        if (j + 1 < col_size && papers[i - 1][j + 1]) count++;
    }
    if (j - 1 >= 0 && papers[i][j - 1]) count++;
    if (j + 1 < col_size && papers[i][j + 1]) count++;
    if (i + 1 < row_size) {
        if (j - 1 >= 0 && papers[i + 1][j - 1]) count++;
        if (papers[i + 1][j]) count++;
        if (j + 1 < col_size && papers[i + 1][j + 1]) count++;
    }
    
    return count;
}

vector<vector<int>> calculateAdjP(vector<vector<int>> &papers){
    vector<vector<int>> adjP;
    int row_size = papers.size();
    int col_size = papers[0].size();
    for (int i = 0; i < row_size; i++) {
        vector<int> adjPRow;
        for (int j = 0; j < col_size; j++) {
            if (papers[i][j]) {
                adjPRow.push_back(countPapers(papers, i, j, row_size, col_size));
            }
            else {
                adjPRow.push_back(0);
            }
        }
        adjP.push_back(adjPRow);
    }
    return adjP;
}

void removePapers(vector<vector<int>> &papers, vector<vector<int>> &adjP, int i, int j, int row_size, int col_size) {
    if (i - 1 >= 0) {
        if (j - 1 >= 0 && papers[i - 1][j - 1]) adjP[i - 1][j - 1]--;
        if (papers[i - 1][j]) adjP[i - 1][j]--;
        if (j + 1 < col_size && papers[i - 1][j + 1]) adjP[i - 1][j + 1]--;
    }
    if (j - 1 >= 0 && papers[i][j - 1]) adjP[i][j - 1]--;
    if (j + 1 < col_size && papers[i][j + 1]) adjP[i][j + 1]--;
    if (i + 1 < row_size) {
        if (j - 1 >= 0 && papers[i + 1][j - 1]) adjP[i + 1][j - 1]--;
        if (papers[i + 1][j]) adjP[i + 1][j]--;
        if (j + 1 < col_size && papers[i + 1][j + 1]) adjP[i + 1][j + 1]--;
    }
}

int countForkLifted(vector<vector<int>> &papers, vector<vector<int>> &adjP, bool part1 = false) {
    int count = 0;
    int row_size = papers.size();
    int col_size = papers[0].size();
    bool isLift = true;
    while (isLift) {
        isLift = false;
        for (int k = 0; k < row_size * col_size; k++) {
            int i = k / col_size, j = k % col_size;
            if (papers[i][j] && adjP[i][j] < 4) {
                papers[i][j] = 0;
                count++;

                if (!part1) {
                    removePapers(papers, adjP, i, j, row_size, col_size);
                    isLift = true;
                }
            }
        }
    }
    return count;
}

void visualise(vector<vector<int>> &papers) {
    for (vector<int> row : papers) {
        for (int paper : row) {
            cout << paper << " ";
        }
        cout << endl;
    }
}

int main() {
    cout << "BEGIN!" << endl;
    // Puzzle Input
    vector<vector<int>> papers = getPapers();
    vector<vector<int>> adjP = calculateAdjP(papers);
    int count = countForkLifted(papers, adjP, PART1);

    // Visualise Grid
    // visualise(papers);
    
    cout << "Papers ForkLifted : " << count << endl;
    return 0;
}
