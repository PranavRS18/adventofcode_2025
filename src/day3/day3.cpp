#include <iostream>
using namespace std;

// Part 1 Constant
const bool PART1 = false;

long max_joltage(int num_batteries) {
    cout << "BEGIN!" << endl;
    long best = 0;
    string nums;
    getline(cin, nums);

    while (nums != "") {
        long sum = 0, max = 0;
        for (int b = 0; b < num_batteries; b++) {
            sum *= 10;
            for (int i = max; i < nums.size() - (num_batteries - b - 1); i++) {
                if (nums[i] > nums[max]) max = i;
            }
            sum += int(nums[max]) - 48;
            max++;
        }
        best += sum;
        getline(cin, nums);
    }
    return best;
}

int main() {
    long best = 0;
    best = max_joltage(PART1 ? 2 : 12);
    cout << "Max Joltage Possible : " << best << endl;
    return 0;
}
