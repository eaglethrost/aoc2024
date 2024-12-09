#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int part1(void) {
    std::ifstream file{"input.txt"};
    int no_safe = 0;
    std::string line;

    while(std::getline(file, line)) {
        int i = 0;
        bool increasing = true, safe = true;
        std::istringstream ss(line);
        int num = 0, prev = 0;
        while (ss >> num) {
            if (i > 0) {
                if (num == prev || abs(num - prev) > 3) {
                    safe = false;
                    break;
                } 
                if (i == 1) increasing = num > prev ? true : false;
                else if ((num > prev && !increasing) || num < prev && increasing) {
                    safe = false;
                    break;
                }
            }
            prev = num;
            ++i;
        }
        if (safe) ++no_safe;
    }

    return no_safe;
}

int main(void) {
    std::cout << "Part 1: " << part1() << "\n";

    return 0;
}