#include <iostream>
#include <string>
using namespace std;

// Part 1 Constant
const bool PART1 = false;

void calculateRule(int &a, string &rule, int &zero_count, int &count) {
    int factor = stoi(rule.substr(1));
    rule[0] == 'L' ? factor *= -1 : factor *= 1;
    a += factor;
    if (a < 0 && (a - factor) >= 0) {
        count -= a / 100;
        if (a - factor > 0) count++;
    } 
    else if (a == 0) {
        count++;
        zero_count++;
    }
    else {
        count += a / 100;
    }
    a %= 100;
    a = a < 0 ? a + 100 : a;
}

int main() {
    cout << "BEGIN!" << endl;
    
    // Initial Configuration
    int a = 50;
    
    string rule;
    int zero_count = 0, count = 0;
    while (getline(cin, rule) && !rule.empty()) calculateRule(a, rule, zero_count, count);

    cout << "The Dial should be " << (PART1 ? zero_count : count);
    return 0;
}
