#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<long>> getRanges() {
    vector<vector<long>> ranges;
    string line;
    while (getline(cin, line) && !line.empty()) {
        stringstream range(line);
        long a, b;
        char dash;
        range >> a >> dash >> b;
        ranges.push_back({a, b});
    }
    sort(ranges.begin(), ranges.end());
    return ranges;
}

// Part 1
int part1(vector<vector<long>> &ranges) {
    vector<long> nums;
    long num;
    cin >> num;
    while (num) {
        nums.push_back(num);
        cin >> num;
    }
    sort(nums.begin(), nums.end());
    
    int i = 0, j = 0;
    int fresh, rotten = 0, ingredients = nums.size();
    while (i < ingredients && j < ranges.size()) {
        if (ranges[j][1] < nums[i]) j++;
        else if (ranges[j][0] > nums[i]) {
            rotten++;
            i++;
        }
        else i++;
    }
    rotten += (ingredients - i);
    fresh = ingredients - rotten;
    return fresh;
}

 // Part 2 (LC 56 : Merge Intervals)
int part2(vector<vector<long>> &ranges) {
    vector<vector<long>> merged_ranges;
    long L = ranges[0][0];
    long R = ranges[0][1];
    for (int i = 1; i < ranges.size(); i++) {
        if (R < ranges[i][0]) {
            merged_ranges.push_back({L, R});
            L = ranges[i][0];
        } 
        R = max(R, ranges[i][1]);
    }
    merged_ranges.push_back({L, R});
    
    long fresh = 0;
    for (vector<long> range : merged_ranges) {
        fresh += (range[1] - range[0]) + 1;
    }
    return fresh;
}

void visualise(vector<vector<long>> &ranges) {
    for (vector<long> range : ranges) {
        cout << "[" << range[0] << ", " << range[1] << "] ";
    }
    cout << endl;
}

int main() {
    cout << "BEGIN!" << endl;
    vector<vector<long>> ranges = getRanges();

    // Part 1
    // int fresh = part1(ranges);

    // Part 2
    int fresh = part2(ranges);
    
    // Visualise Ranges
    // visualise(ranges);
    
    cout << "Fresh Ingredients : " << fresh;
    return 0;
}
