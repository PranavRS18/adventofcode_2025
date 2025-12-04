#include <iostream>
#include <sstream>
using namespace std;

bool is_repetition(long long x) {
    string str = to_string(x);
    int n = str.size();
    for (int i = 1; i <= n / 2; i++) { // Set initial i to n / 2 for Part 1
        if (n % i != 0) continue;
        string block = str.substr(0, i), r = "";
        int times = n / i;
        for (int j = 0; j < times; j++) r += block;
        if (r == str) return true;
    }
    return false;
}

int main() {
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
            if (is_repetition(i)) sum += i;
    }

    cout << "Sum of Invalid IDs : " << sum << endl;
}

