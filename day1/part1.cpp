/***
 * algorithm:
 * - the sum of absolute difference between each line is the same as the sum of absolute difference of pairs in sorted order
 * 
 */


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

// METHOD 1 : Sorting
uint32_t solve1(std::ifstream& file) {
    uint32_t diffSum = 0;
    std::string line{};
    std::vector<int> left{}, right{};

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string id;
        int i = 0;
        while (ss >> id) {
            int num = std::stoi(id);
            if (i++ == 0) left.emplace_back(num);
            else right.emplace_back(num);
        }
    }

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    for (int i=0; i<left.size(); ++i) {
        diffSum += abs(left[i] - right[i]);
    }
    return diffSum;
}

// METHOD 2 : Use array to store values
uint32_t solve2(std::ifstream& file) {
    uint32_t diffSum = 0;
    std::string line{};
    const int maxID = 100000;

    std::array<int, maxID> left{}, right{};
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string id;
        int i = 0;
        while (ss >> id) {
            int num = std::stoi(id);
            if (i++ == 0) ++left[num];
            else ++right[num];
        }
    }

    int l = 0, r = 0;
    while (l < maxID) {
        while (l < maxID && left[l] == 0) ++l;
        while (r < maxID && right[r] == 0) ++r;
        if (l < maxID && r < maxID) {
            int diff = std::max(l,r) - std::min(l,r);
            auto minCount = std::min(left[l], right[r]);
            diffSum += (diff * minCount);
            left[l] -= minCount;
            right[r] -= minCount;
        } 
    }
    return diffSum;
}


int main(void) {
    std::ifstream file{"input.txt"};

    auto ans1 = solve1(file);
    std::cout << "method 1 ans: " << ans1 << "\n";

    file.clear();
    file.seekg(0);

    auto ans2 = solve2(file);
    std::cout << "method 2 ans: " << ans2 << "\n";
    return 0;
}