#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int getCorrectMid(unordered_map<int,unordered_set<int>>& rules, vector<int>& nums) {
    int targetVal = nums.size()/2;
    for (const auto& a : nums) {
        int numsAhead = 0;
        for (const auto& b : nums) {
            if (a != b && rules[a].contains(b)) ++numsAhead;
        }
        if (numsAhead == targetVal) return a;
    }
    return 0;
}

void printQueue() {
    /**
     * - use hash map to store order rules (before : hash set of afters)
     * - read each input line UNTIL an empty line, signalling the end of the rules
     * - for each update, split values by comma and put values in a vector
     * 
     * 1. BRUTE FORCE - O(n^2)
     * - for each pair of numbers (l,r) from left to right, if r exists in map[l], the order is valid
     * - stop processing line once an r doesn't exist in map[l] or if l is found in map[r]
     * - if valid, get the middle number of line
     * - optimize: store result validitiy of (l,r) so that in the next line we don't need to check again
     * 
     * 
     * 
     * O = 97,75,47,61,53
     * 
     * I = 61,97,53,47,75
     * 
     * 97,61,53,47,75
     * 97,47,53,61,75
     * 97,75,53,61,47
     */

    // parse order rules
    ifstream file{"input.txt"};
    unordered_map<int,unordered_set<int>> rules{};
    for (string line; getline(file, line), line != ""; ) {
        // get numbers separated by |
        int before = stoi(line.substr(0, line.find('|')));
        int after = stoi(line.substr(line.find('|')+1));
        rules[before].insert(after);
    }

    auto isValidSeq = [&](int before, int after) -> bool{
        if (rules[before].contains(after)) return true;
        return false;
    };

    int correctUpdateMidSum = 0, wrongUpdateMidSum = 0;
    // read each update 
    for (string line; getline(file, line), line != ""; ) {
        // get numbers separated by ,
        vector<int> nums;
        istringstream ss(line);
        for (string num; getline(ss, num, ',');) {
            nums.emplace_back(stoi(num));
        }
        auto len = nums.size();

        // evaluate each pair's validity
        bool valid = true;
        for (size_t i=0; i<len; ++i) {
            for (size_t j=i+1; j<len; ++j) {
                if (!isValidSeq(nums[i],nums[j])) {
                    valid = false;
                    break;
                }
            }
            if (!valid) break;
        }
        if (valid) correctUpdateMidSum += nums[len/2];
        else wrongUpdateMidSum += getCorrectMid(rules, nums);
    }

    std::cout << "Part 1 answer: " << correctUpdateMidSum << "\n";
    std::cout << "Part 2 answer: " << wrongUpdateMidSum << "\n";
}

int main(void) {
    printQueue();
    return 0;
}