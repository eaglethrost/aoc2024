#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int part1(void) {
    std::ifstream file{"input.txt"};
    int no_safe = 0;

    for (std::string line; std::getline(file, line); ) {
        bool increasing = true, decreasing = true, safe = true;
        std::istringstream ss(line);
        int prev;
        ss >> prev;

        for (int num; ss >> num;) {
            int diff = num - prev;
            if (increasing && diff >= 1 && diff <= 3) {
                decreasing = false;
            } else if (decreasing && diff <= -1 && diff >= -3) {
                increasing = false;
            } else {
                safe = false;
                break;
            }
            prev = num;
        }
        no_safe += safe;
    }

    return no_safe;
}

int part2(char* input, char* output) {
    int no_safe = 0;

    std::ifstream file{input};    
    for (std::string line; std::getline(file, line); ) {
        std::vector<int> ids;
        std::istringstream ss(line);
        for (int id; ss >> id; ) {
            ids.push_back(id);
        }

        bool safeLine = false;
        auto consider = [&](int j){
            std::vector<int> b = ids;
            b.erase(b.begin() + j);
            bool increasing = true, decreasing = true, safe = true;
            for (int i=0; i<b.size()-1; ++i) {
                int diff = b[i+1] - b[i];
                if (increasing && diff >= 1 && diff <= 3) {
                    decreasing = false;
                } else if (decreasing && diff <= -1 && diff >= -3) {
                    increasing = false;
                } else {
                    safe = false;
                    break;
                }
            }
            if (safe) safeLine |= true;
        };

        consider(0);
        for (int i=0; i<ids.size()-1; ++i) {
            int diff = ids[i+1] - ids[i];
            if (abs(diff) < 1 || abs(diff) > 3){
                consider(i);
                consider(i+1);
                break;
            }
            if (i < ids.size()-2) {
                int diff2 = ids[i+2] - ids[i+1];
                if (diff * diff2 < 0) {
                    consider(i);
                    consider(i+1);
                    consider(i+2);
                    break;
                }
            }
        }
        no_safe += safeLine;
    }

    return no_safe;
}

int main(int argc, char* argv[]) {
    std::cout << "Part 1: " << part1() << "\n";
    std::cout << "Part 2: " << part2(argv[1], argv[2]) << "\n";
    return 0;
}