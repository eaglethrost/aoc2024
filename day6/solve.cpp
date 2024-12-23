#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

void part1(const char* input) {
    /**
     * - find the ^ index
     * - create a 4 directions array of up,right,down,left
     * - keep track of new unvisited spots
     * 
     * 1. parse the grid state and find the no of height & width using a char array
     * 2. while current spot is not out of grid
     *       next = cur + dir
     *       if next is out of bounds, break
     *       else if cur + dir is blocked
     *          change to next direction
     *       else
     *          cur = cur + dir
     *          if cur is unvisited
     *              add ans
     *              mark cur as visited
     * #..
     * ^.#
     * #..
     * .#.
     * 
     * 
     */
    vector<pair<int,int>> directions = {{-1,0},{0,1},{1,0},{0,-1}};
    int uniquePos = 1, row = 0, col = 0, dir = 0;

    // parse board state
    vector<string> board;
    ifstream file{input};
    int height = 0, width = 0;
    for (string line; getline(file, line); ) {
        string boardLine{};
        for (size_t j=0; j<line.length(); ++j) {
            if (line[j] == '^') {
                row = height; col = j;
                line[j] = 'X';
            }
            boardLine.push_back(line[j]);
        }
        ++height;
        board.emplace_back(boardLine);
    }
    width = board[0].size();
 
    // travel along the board
    while (true) {
        int drow = row + directions[dir].first, dcol = col + directions[dir].second;
        if (drow >= height || drow < 0 || dcol >= width || dcol < 0) break;
        else if (board[drow][dcol] == '#') dir = (dir + 1) % 4;
        else {
            row = drow; col = dcol;
            if (board[row][col] == '.') {
                ++uniquePos;
                board[row][col] = 'X';
            }
        }
    }

    cout << "Part 1 ans: " << uniquePos << "\n";
    return;
}

void part2(const char* input) {
    /**
     * isLoop: if we're going along a row/col in the same direction as previous
     * 
     * create a 2d of board size to store if given point i,j answers if there is a block on right/up/down/left of it
     * 
     * while not out of bounds
     *  travel along the board from the start
     *  update row & cols direction movement
     *  at a pos, if there is a block somewhere on the right, explore that branch
     * 
     * explore:
     *  travel along the new board while not out of bounds
     *  if at any point isLoop is true, return true
     */
}

int main(int argc, char* argv[]) {
    part1(argv[1]);
    return 0;
}