import re

def part1():
    with open("input.txt", "r") as file:
        data = file.read()
    matches = re.findall(r"mul\((\d{1,3}),(\d{1,3})\)", data)
    mults = [tuple(map(int,match)) for match in matches]
    res = sum(map(lambda ops: ops[0] * ops[1], mults))
    print("Part 1 Sum:", res)

def part2():
    with open("input.txt", "r") as file:
        data = file.read()
    matches = re.findall(r"do\(\)|don't\(\)|mul\(\d{1,3},\d{1,3}\)", data)

    def multiply(ops):
        nums = re.findall(r"(\d{1,3}),(\d{1,3})", ops)[0]
        return int(nums[0]) * int(nums[1])
    
    process = True
    res = 0
    for match in matches:
        if match == "do()":
            process = True
        elif match == "don't()":
            process = False
        elif process:
            res += multiply(match)
    print("Part 2 Sum:", res)

if __name__ == "__main__":
    part1()
    part2()