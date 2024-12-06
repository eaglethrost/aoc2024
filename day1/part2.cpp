#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>

int main(void) {
    std::ifstream file{"input.txt"};
    std::string line{};
    std::unordered_map<int,int> left;
    std::unordered_map<int,int> right;

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string id{};
        int i = 0;
        while (ss >> id) {
            int num = std::stoi(id);
            if (i++ == 0) left[num]++;
            else right[num]++;
        }
    }

    int similarity = 0;
    for (const auto& [num, count] : left) {
        if (right.contains(num)) {
            similarity += (num * count * right[num]);
        }
    }
    std::cout << similarity << "\n";

    return 0;
}