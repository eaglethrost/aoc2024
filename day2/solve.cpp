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
            if (increasing && (num >= prev + 1 && num <= prev + 3)) {
                decreasing = false;
            } else if (decreasing && (num <= prev - 1 && num >= prev - 3)) {
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
    auto inRange = [](int a, int b) -> bool {
        if (abs(b-a) >= 1 && abs(b-a) <= 3) return true;
        return false;
    };
    auto isIncreasing = [](int a, int b) -> bool {
        return b - a >= 0 ? true : false;
    };
    auto validSeq = [](int a, int b, int c) -> bool {
        if (b - a > 0) return c >= b + 1 && c <= b + 3;
        return c <= b - 1 && c >= b - 3;
    };
    auto followsMonoticity = [](bool increasing, int a, int b) -> bool {
        if (increasing) return b - a > 0;
        return b - a < 0;
    };
    auto validCur = [](bool increasing, int prev, int cur) -> bool {
        if (increasing) return cur >= prev + 1 && cur <= prev + 3;
        return cur <= prev - 1 && cur >= prev - 3;
    };

    int no_safe = 0;
    std::ifstream file{input};
    std::ofstream outFile{output};

    int no_line = 0;
    for (std::string line; std::getline(file, line); ) {
        int errors = 0, len = 0;

        // get first 3 ids
        int firstThree[3];
        std::istringstream ss(line);
        for (; len<3, !ss.eof(); ++len) {
            ss >> firstThree[len];
        }
        if (len < 3) {
            ++no_safe;
            continue;
        }

        // get the target monoticity of the sequence which can be decided from the first 3 or 4 ids
        bool increasing = true;
        int a = firstThree[0], b = firstThree[1], c = firstThree[2];
        int prev2 = b, prev = c;
        if (!inRange(a,b) && !inRange(a,c) && !inRange(b,c)) continue;
        else if (isIncreasing(a,b) == isIncreasing(b,c)){
            if (!isIncreasing(a,b)) increasing = false;
            if (!inRange(a,b)) {
                prev2 = b; prev = c;
                ++errors;
            }
            if (!inRange(b,c)) {
                prev2 = a; prev = b;
                ++errors;
            }
        } else if (!ss.eof()) {
            ++errors;
            int cur = 0;
            ss >> cur;
            if (inRange(a,b) && validSeq(a,b,cur)) {
                increasing = b - a > 0 ? true : false;    
                prev2 = b;
            } else if (inRange(a,c) && validSeq(a,c,cur)) {
                increasing = c - a > 0 ? true : false;
                prev2 = c;
            } else if (inRange(b,c) && validSeq(b,c,cur)) {
                increasing = c - b > 0 ? true : false;
                prev2 = c;
            } else {
                ++errors;
            }
            prev = cur;
        } 

        // for each new id, use the 2nd prev & prev ids to determine if the new id fits the monoticity
        // edge case: if c goes the opposite trend but we can still connect the 2nd prev to c
        while (errors <= 1 && ss >> c) {
            if (validCur(increasing, prev, c)) {
                prev2 = prev;
                prev = c;
            } else if (prev != c && !followsMonoticity(increasing,prev,c) && validCur(increasing,prev2,c)) {
                prev = prev2;
                prev = c;
                ++errors;
            } else {
                ++errors;
            }
        }

        if (errors <= 1) {
            std::cout << no_line << " is safe\n"; 
            ++no_safe;
        } 
        ++no_line;
    }

    return no_safe;
}

int main(int argc, char* argv[]) {
    std::cout << "Part 1: " << part1() << "\n";
    // std::cout << "Part 2: " << part2(argv[1], argv[2]) << "\n";
    return 0;
}