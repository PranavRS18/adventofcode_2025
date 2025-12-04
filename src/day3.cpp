#include <iostream>
using namespace std;

int main() {
    long best = 0;
    int num_batteries = 12; // Set num_batteries = 2 for Part 1
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

    cout << "Max Joltage Possible : " << best << endl;
    return 0;
}
