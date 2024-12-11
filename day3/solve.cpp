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
    char c = file.get();
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
                c = file.get();
            }
            else if (preID == 0) c = file.get();
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
                c = file.get();
            }
            // has to end with ,
            findFirstDigit = false;
            if (c == ',') {
                findSecondDigit = true;
                c = file.get();
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
                c = file.get();
            }
            findSecondDigit = false;
            // std::cout << "got number " << secondDigit << "\n";
            if (c == ')') {
                foundExpr = true;
                c = file.get();
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

int main(void) {
    std::cout << "Part 1: " << part1() << "\n";
    return 0;
}