#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

long long part1() {
    /**
     * States:
     * 1. String match for mult(
     * 2. Parse (num,num)
    */
    std::ifstream file{"input.txt"};
    long long res = 0;
    std::string prefix = "mul(";
    int preID = 0;

    char c;
    auto parseMul = [&](){
        while (preID < prefix.length() && file >> c){
            if (c == prefix[preID]) ++preID;
            else if (c == 'm') preID = 1;
            else preID = 0;
        }
        preID = 0;
    };
    auto parseNumbers = [&]() -> long long {
        long long firstNum = 0, secondNum = 0;
        while (file >> c && isdigit(c)){
            firstNum = firstNum * 10 + (c-'0');
        }
        if (c != ',') {
            if (!file.eof()) file.unget();
            return 0;
        }
        while (file >> c && isdigit(c)){
            secondNum = secondNum * 10 + (c-'0');
        }
        if (c != ')') {
            if (!file.eof()) file.unget();
            return 0;
        }
        std::cout << "multiplying " << firstNum << " and " << secondNum << "\n";
        return firstNum * secondNum;
    };

    while (!file.eof()){
        parseMul();
        res += parseNumbers();
    }

    return res;
}

long long part2() {
    std::ifstream file{"input.txt"};
    long long res = 0;

    // states
    std::string prefix = "mul(", enable = "do()", disable = "don't()";
    int preID = 0, enableID = 0, disableID = 0;
    bool enabled = true;

    char c;
    file >> c;
    while (!file.eof()){
        // update which state we're at
        if (enabled) {
            if (c == prefix[preID]) ++preID;
            else if (c == 'm') preID = 1;
            else preID = 0;

            if (c == disable[disableID]) ++disableID;
            else if (c == 'd') disableID = 1;
            else disableID = 0;
        }
        if (c == enable[enableID]) ++enableID;
        else if (c == 'd') enableID = 1;
        else enableID = 0;

        file >> c;
        if (enableID == enable.length()){
            enabled = true;
            enableID = 0;
        } else if (disableID == disable.length()){
            enabled = false;
            disableID = 0;
        } else if (preID == prefix.length()){
            // read numbers in
            preID = 0;
            long long firstNum = 0, secondNum = 0;
            file.unget();
            while (file >> c && isdigit(c)){
                firstNum = firstNum * 10 + (c-'0');
            }
            if (c != ',') {
                if (!file.eof()) file.unget();
                continue;
            }
            while (file >> c && isdigit(c)){
                secondNum = secondNum * 10 + (c-'0');
            }
            if (c != ')') {
                if (!file.eof()) file.unget();
                continue;
            }
            std::cout << "multiplying " << firstNum << " and " << secondNum << "\n";
            res += firstNum * secondNum;
        }
    }
    return res;
}

int main(void) {
    // std::cout << "Part 1: " << part1() << "\n";
    std::cout << "Part 2: " << part2() << "\n";
    return 0;
}