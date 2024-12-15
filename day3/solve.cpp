#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

long long part1() {
    /**
     * States:
     * 1. String match for mult(
     * 2. Reading first num sequence
     * 3. ,
     * 4. Reading second num sequence
     * 5. )
     * 
     * Options:
     * 1. Use KMP, Rabin-Karp to search for mult( instances
     * 
     * 
    */
    std::ifstream file{"input.txt"};
    char c;
    file >> c;
    long long res = 0;

    // states
    std::string prefix = "mul(";
    int preID = 0;
    bool findPrefix = true;

    bool findFirstDigit = false;
    int firstDigit = 0;
    bool findSecondDigit = false;
    int secondDigit = 0;
    bool foundExpr = false;

    while (!file.eof()){
        if (findPrefix) {
            if (c == prefix[preID]) {
                // std::cout << "matched " << c << " at " << file.tellg() << "\n";
                ++preID;
                file >> c;
            }
            else if (preID == 0) file >> c;
            else preID = 0;
            if (preID >= prefix.length()){
                // std::cout << "found prefix at " << file.tellg() << "\n";
                findPrefix = false;
                findFirstDigit = true;
                preID = 0;
            }
        } else if (findFirstDigit) {
            // find run of digits
            // std::cout << "finding first digit at " << file.tellg() << " of " << c << "\n";
            while (isdigit(c)) {
                // std::cout << "add digit " << c << "\n";
                firstDigit = firstDigit * 10 + (c-'0');
                file >> c;
            }
            // has to end with ,
            findFirstDigit = false;
            if (c == ',') {
                findSecondDigit = true;
                file >> c;
                // std::cout << "got number " << firstDigit << " next char is " << c << "\n";
            } else {
                findPrefix = true;
                firstDigit = 0;
            }
        } else if (findSecondDigit) {
            // find run of digits
            // std::cout << "finding second digit at " << file.tellg() << " of " << c << "\n";
            while (isdigit(c)) {
                // std::cout << "add digit " << c << "\n";
                secondDigit = secondDigit * 10 + (c-'0');
                file >> c;
            }
            findSecondDigit = false;
            // std::cout << "got number " << secondDigit << "\n";
            if (c == ')') {
                foundExpr = true;
                file >> c;
            } else {
                findPrefix = true;
                firstDigit = 0;
                secondDigit = 0;
            }
        }

        if (foundExpr) {
            std::cout << "multiply " << firstDigit << " and " << secondDigit << "\n";
            res += (firstDigit * secondDigit);
            firstDigit = 0;
            secondDigit = 0;
            findPrefix = true;
            foundExpr = false;
        }
    }
    return res;
}

long long part2() {
    std::ifstream file{"input.txt"};
    char c;
    file >> c;
    long long res = 0;

    // states
    std::string prefix = "mul(", enable = "do()", disable = "don't()";
    int preID = 0, enableID = 0, disableID = 0;
    bool findPrefix = true;

    bool findFirstDigit = false;
    int firstDigit = 0;
    bool findSecondDigit = false;
    int secondDigit = 0;
    bool foundExpr = false;

    bool enabled = true;
    bool disabled = false;

    while (!file.eof()){
        // update enabled and disabled states
        if (enabled) {
            // look for don't()
            if (c == disable[disableID]) {
                // std::cout << "found disable char " << c << "\n";
                ++disableID;
                file >> c;
                if (disableID == disable.length()) {
                    // std::cout << "found don't() at " << file.tellg() << "\n"; 
                    disableID = 0;
                    disabled = true;
                    enabled = false;
                    findPrefix = false;
                    findFirstDigit = false;
                    findSecondDigit = false;
                }
                continue;
            }
            else if (disableID > 0) disableID = 0;
        } 

        if (disabled) {
            // look for do()
            if (c == enable[enableID]) ++enableID;
            else if (enableID > 0) enableID = 0;
            if (enableID == enable.length()) {
                enableID = 0;
                enabled = true;
                disabled = false;
                findPrefix = true;
            }
            file >> c;
        } else if (findPrefix) {
            if (c == prefix[preID]) {
                ++preID;
                file >> c;
            }
            else if (preID == 0) file >> c;
            else preID = 0;
            if (preID >= prefix.length()){
                findPrefix = false;
                findFirstDigit = true;
                preID = 0;
            }
        } else if (findFirstDigit) {
            // find run of digits
            while (isdigit(c)) {
                firstDigit = firstDigit * 10 + (c-'0');
                file >> c;
            }
            // has to end with ,
            findFirstDigit = false;
            if (c == ',') {
                findSecondDigit = true;
                file >> c;
            } else {
                findPrefix = true;
                firstDigit = 0;
            }
        } else if (findSecondDigit) {
            // find run of digits
            while (isdigit(c)) {
                secondDigit = secondDigit * 10 + (c-'0');
                file >> c;
            }
            findSecondDigit = false;
            if (c == ')') {
                foundExpr = true;
                file >> c;
            } else {
                findPrefix = true;
                firstDigit = 0;
                secondDigit = 0;
            }
        }

        if (foundExpr) {
            // std::cout << "multiply " << firstDigit << " and " << secondDigit << "\n";
            res += (firstDigit * secondDigit);
            firstDigit = 0;
            secondDigit = 0;
            findPrefix = true;
            foundExpr = false;
        }
    }
    return res;
}

int main(void) {
    // std::cout << "Part 1: " << part1() << "\n";
    std::cout << "Part 2: " << part2() << "\n";
    return 0;
}