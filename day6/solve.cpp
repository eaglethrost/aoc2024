#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

vector<string> parseBoard(const char* input, int& row, int& col) {
    vector<string> board;
    ifstream file{input};
    int height = 0;
    for (string line; getline(file, line); ) {
        string boardLine{};
        for (size_t j=0; j<line.length(); ++j) {
            if (line[j] == '^') {
                row = height; col = j;
                board[row][j] = '.';
            }
            boardLine.push_back(line[j]);
        }
        ++height;
        board.emplace_back(boardLine);
    }
    return board;
}

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
     */
    vector<pair<int,int>> directions = {{-1,0},{0,1},{1,0},{0,-1}};
    int uniquePos = 1, row = 0, col = 0, dir = 0;
    vector<string> board = parseBoard(input, row, col);
    int height = board.size(), width = board[0].size();
 
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

// given position i,j , answers if there is a block on the right [0], down [1], left [2], up [3] 
struct NextBlock {
    NextBlock(){
        for (int i=0; i<4; ++i)
            hasBlock[i] = false;
    };
    bool hasBlock[4];
};

// create a 2d of board size to store if given point i,j answers if there is a block on right/up/down/left of it
vector<vector<NextBlock>> createBlockExistsTable(int height, int width, const vector<string>& board) {
    vector<vector<NextBlock>> blockExists(height, vector<NextBlock>(width));
    for (int i=0; i<height; ++i) {
        for (int j=0; j<width; ++j) {
            if (board[i][j] != '#') blockExists[i][j].hasBlock[2] = false;
            else break; 
        }
    }
    for (int i=0; i<height; ++i) {
        for (int j=width-1; j>=0; --j) {
            if (board[i][j] != '#') blockExists[i][j].hasBlock[0] = false;
            else break; 
        }
    }
    for (int j=0; j<width; ++j) {
        for (int i=0; i<height; ++i) {
            if (board[i][j] != '#') blockExists[i][j].hasBlock[3] = false;
            else break; 
        }
    }
    for (int j=0; j<width; ++j) {
        for (int i=height-1; i>=0; --i) {
            if (board[i][j] != '#') blockExists[i][j].hasBlock[1] = false;
            else break; 
        }
    }
    return blockExists;
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
     *  at a pos, if there is a block somewhere on the right, explore that branch if there isnt a block ahead yet
     * 
     * explore:
     *  travel along the new board while not out of bounds
     *  if at any point isLoop is true, return true
     */
    vector<pair<int,int>> directions = {{-1,0},{0,1},{1,0},{0,-1}};
    int dir = 0, startRow = 0, startCol = 0;

    vector<string> board = parseBoard(input, startRow, startCol);
    int height = board.size(), width = board[0].size();
    vector<vector<NextBlock>> blockExistsTable = createBlockExistsTable(height, width, board);

    // travel along the board
    char dirSymbols[4] = {'^','>','|','<'};
    vector<vector<bool>> visited(height, vector<bool>(width));

    auto explore = [&](vector<string> copyBoard) -> bool {
        vector<vector<NextBlock>> visited(height, vector<NextBlock>(width));
        int dir = 0, row = startRow, col = startCol;
        while (true) {
            if (visited[row][col].hasBlock[dir]) return true;
            visited[row][col].hasBlock[dir] = true;
            int drow = row + directions[dir].first, dcol = col + directions[dir].second;
            if (drow >= height || drow < 0 || dcol >= width || dcol < 0) return false;
            else if (copyBoard[drow][dcol] == '#') dir = (dir + 1) % 4;
            else {
                row = drow; col = dcol;
            }
        }
        return false;
    };

    int possibleObstructions = 0;
    int i = startRow, j = startCol;
    while (true) {
        visited[i][j] = true;
        int drow = i + directions[dir].first, dcol = j + directions[dir].second;
        if (drow >= height || drow < 0 || dcol >= width || dcol < 0) break;
        else if (board[drow][dcol] == '#') dir = (dir + 1) % 4;
        else {
            if (!(drow == startRow && dcol == startCol) && !visited[drow][dcol]) {
                auto copy = board;
                copy[drow][dcol] = '#';
                possibleObstructions += explore(copy);
            }
            i = drow; j = dcol;
        }
    }

    // for (int i=0; i<height; ++i) {
    //     for (int j=0; j<width; ++j) {
    //         if (board[i][j] == '.' && !(i == startRow && j == startCol)) {
    //             board[i][j] = '#';
    //             possibleObstructions += explore(board);
    //             board[i][j] = '.';
    //         }
    //     }
    // }

    cout << "Part 2: " << possibleObstructions << "\n";
    return;
}

int main(int argc, char* argv[]) {
    // part1(argv[1]);
    part2(argv[1]);
    return 0;
}