#include <iostream>
using namespace std;

int main() {
    string rule;
    int a = 50, factor = 0, zero_count = 0, count = 0;
    cout << "Give the Rules :" << endl;
    getline(cin, rule);
    while (rule != "") {
        if (rule.size() == 2) {
            rule[3] = rule[1];
            rule[2] = '0';
            rule[1] = '0';
        } 
        else if (rule.size() == 3) {
            rule[3] = rule[2];
            rule[2] = rule[1];
            rule[1] = '0';
        }
        factor = int(rule[1]) * 100 + int(rule[2]) * 10 + int(rule[3]) - 5328;
        rule[0] == 'L' ? factor *= -1 : factor *= 1;
        a += factor;
        if (a < 0 && (a - factor) >= 0) {
            count = (a - factor > 0) ? count + 1 - a / 100 : count - a / 100;
        } 
        else if (a == 0) {
            zero_count++;
        }
        else {
            count += a / 100;
        }
        // cout << count << " " << a << endl;
        a %= 100;
        a = a < 0 ? a + 100 : a;
        getline(cin, rule);
    }
    cout << "The Dial should be " << zero_count + count; // Just Print zero_count for Part 1
    return 0;
}
