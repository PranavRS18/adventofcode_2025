#include <iostream>
#include <sstream>
using namespace std;

bool is_repetition(long long x, bool part1 = false) {
    string str = to_string(x);
    int n = str.size();
    for (int i = 1; i <= n / 2; i++) {
        if (n % i != 0) continue;
        string block = str.substr(0, i), r = "";
        int times = part1 ? 2 : (n / i);
        for (int j = 0; j < times; j++) r += block;
        if (r == str) return true;
    }
    return false;
}

long long sumInvalidIDs(){
    cout << "BEGIN!" << endl;
    string input;
    getline(cin, input);

    stringstream ss(input);
    string range;
    long long sum = 0;

    while (getline(ss, range, ',')) {
        stringstream part(range);
        string Ls, Rs;
        getline(part, Ls, '-');
        getline(part, Rs, '-');
        long long L = stoll(Ls), R = stoll(Rs);
        for (long long i = L; i <= R; i++)
            if (is_repetition(i, false)) sum += i; // Set False to True for Part 1
    }

    return sum;
}

int main() {
    long long sum = 0;
    sum = sumInvalidIDs();
    cout << "Sum of Invalid IDs : " << sum << endl;
}
