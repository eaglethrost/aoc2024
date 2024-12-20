def part1():
    file = open("input.txt", "r")
    words = [line.strip("\n") for line in file]
    rows = len(words); cols = len(words[0])
    
    xmas = "XMAS"; samx = "SAMX"
    res = 0

    def check_xmas(char, id):
        nonlocal res
        if char == xmas[id]:
            id += 1
        elif char == 'X':
            id = 1
        else:
            id = 0
        if id == len(xmas):
            res += 1
            id = 0
        return id
    def check_samx(char, id):
        nonlocal res
        if char == samx[id]:
            id += 1
        elif char == 'S':
            id = 1
        else:
            id = 0
        if id == len(samx):
            res += 1
            id = 0
        return id

    for i in range(0, rows):
        xmas_i_row = 0; samx_i_row = 0
        xmas_i_col = 0; samx_i_col = 0
        for j in range(0, cols):

            # match XMAS & SAMX horizontally rightward and vertically downward
            xmas_i_row = check_xmas(words[i][j], xmas_i_row)
            samx_i_row = check_samx(words[i][j], samx_i_row)
            xmas_i_col = check_xmas(words[j][i], xmas_i_col)
            samx_i_col = check_samx(words[j][i], samx_i_col)
 
            # match XMAS & SAMX both diagonally
            if i <= rows-len(xmas) and j <= cols-len(xmas):
                left_diag = "".join(words[i+k][j+k] for k in range(0, 4))
                right_diag = "".join(words[i+k][cols-1-j-k] for k in range(0, 4))
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
