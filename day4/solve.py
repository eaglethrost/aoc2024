def part1():
    file = open("input.txt", "r")
    words = [line.strip("\n") for line in file]
    rows = len(words); cols = len(words[0])
    
    xmas = "XMAS"; samx = "SAMX"
    word_len = len(xmas)
    res = 0

    def match_char(char, word, id):
        nonlocal res
        first_char = 'X' if word == "XMAS" else 'S'
        if char == word[id]:
            id += 1
        elif char == first_char:
            id = 1
        else:
            id = 0
        if id == len(word):
            res += 1
            id = 0
        return id

    for i in range(0, rows):
        xmas_i_row = 0; samx_i_row = 0
        xmas_i_col = 0; samx_i_col = 0
        for j in range(0, cols):

            # match XMAS & SAMX horizontally rightward and vertically downward
            xmas_i_row = match_char(words[i][j], xmas, xmas_i_row)
            samx_i_row = match_char(words[i][j], samx, samx_i_row)
            xmas_i_col = match_char(words[j][i], xmas, xmas_i_col)
            samx_i_col = match_char(words[j][i], samx, samx_i_col)
 
            # match XMAS & SAMX both diagonally
            if i <= rows-word_len and j <= cols-word_len:
                left_diag = "".join(words[i+k][j+k] for k in range(0, word_len))
                right_diag = "".join(words[i+k][cols-1-j-k] for k in range(0, word_len))
                if left_diag == "XMAS" or left_diag == "SAMX":
                    res += 1
                if right_diag == "XMAS" or right_diag == "SAMX":
                    res += 1

    file.close()
    print("Part 1 No of XMAS:", res)

def part2():
    file = open("input.txt")
    words = [line.strip("\n") for line in file]
    res = 0
    for i in range(0, len(words)-2):
        for j in range(0, len(words[i])-2):
            diag1 = words[i][j] + words[i+1][j+1] + words[i+2][j+2]
            diag2 = words[i][j+2] + words[i+1][j+1] + words[i+2][j]
            if (diag1 == "MAS" or diag1 == "SAM") and (diag2 == "MAS" or diag2 == "SAM"):
                res += 1
    file.close()
    print("Part 2 No of XMAS:", res)
    return

if __name__ == "__main__":
    part1()
    part2()
