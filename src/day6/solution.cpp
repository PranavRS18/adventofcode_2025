#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

// Part 1 Constant
const bool PART1 = false;

vector<char> getOperators(string &line) {
    vector<char> optrs;
    while(!line.empty()) {
        stringstream ss(line);
        char optr;
        while (ss >> optr) {
            optrs.push_back(optr);
        }
        getline(cin, line);
    }
    
    return optrs;
}

vector<vector<long long>> getNumbers(string &line) {
    vector<vector<long long>> worksheet;
    while(getline(cin, line) && !line.empty()) {
        bool digit = false;
        for(char c : line) {
            if (isdigit(c)) {
                digit = true;
                break;
            }
        }
        if (!digit) break;

        vector<long long> row;
        stringstream ss(line);
        long long num;
        while (ss >> num) row.push_back(num);
        
        if (worksheet.empty()) worksheet.resize(row.size());
        for(int i = 0; i < row.size(); i++) worksheet[i].push_back(row[i]);
    } 
    
    return worksheet;
}

vector<vector<long long>> getCephalopodNumbers(string &line) {
    vector<string> worksheet;
    while(getline(cin, line) && !line.empty()) {
        bool digit = false;
        for(char c : line) {
            if (isdigit(c)) {
                digit = true;
                break;
            }
        }
        if (!digit) break;
        
        if (worksheet.empty()) worksheet.resize(line.size());
        for(int i = 0; i < line.size(); i++) worksheet[i].push_back(line[i]);
    }
    
    vector<vector<long long>> cWorksheet;
    int j = 0;
    for(string col : worksheet) {
        bool isEmpty = true;
        for (char c : col) {
            if(!isspace(c)) {
                isEmpty = false;
                break;
            }
        }
        if (isEmpty) {
            j++;
            continue;
        }
        if (cWorksheet.size() < j + 1) cWorksheet.push_back({});
        cWorksheet[j].push_back(stoll(col));
    }
    
    return cWorksheet;
}

pair<vector<vector<long long>>, vector<char>> getWorksheet() {
    string line;
    vector<vector<long long>> worksheet;
    if (PART1) worksheet = getNumbers(line);
    else worksheet = getCephalopodNumbers(line);
    vector<char> optrs = getOperators(line);

    return {worksheet, optrs};
}

long long solveProblem(vector<long long> &nums, char &optr) {
    long long res = (optr == '+') ? 0 : 1;
    if (optr == '+') for (long long num : nums) res += num;
    else for (long long num : nums) res *= num;

    return res;
}

long long sumResults(pair<vector<vector<long long>>, vector<char>> &worksheet) {
    long long sum = 0;
    for (int i = 0; i < worksheet.first.size(); i++) {
        sum += solveProblem(worksheet.first[i], worksheet.second[i]);
    }
    return sum;
}

void visualiseWorksheet(pair<vector<vector<long long>>, vector<char>> &worksheet) {
    for (int i = 0; i < worksheet.first.size(); i++) {
        for (int num : worksheet.first[i]) {
            cout << num << " ";
        }
        cout << worksheet.second[i];
        cout << endl;
    }
    cout << endl;
}

int main() {
    cout << "BEGIN!" << endl;
    pair<vector<vector<long long>>, vector<char>> worksheet = getWorksheet();
    long long sum = sumResults(worksheet);
    
    // visualiseWorksheet(worksheet);
    cout << "Sum of the Problems : " << sum << endl;
    return 0;
}
