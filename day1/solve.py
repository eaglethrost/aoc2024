from collections import Counter

def part1():
    file = open("input.txt")
    left_ids, right_ids = map(sorted, map(list, zip(*(map(lambda line: map(int, line.split()), file)))))  
    diffs = sum(abs(left_ids[i] - right_ids[i]) for i in range(len(left_ids)))
    print("Part 1:", diffs)

def part2():
    file = open("input.txt")
    left_counts = Counter(line[0] for line in (map(int, line.split()) for line in file))
    right_counts = Counter(line[1] for line in (map(int, line.split()) for line in file))
    similarity = sum(id * left_counts[id] * right_counts[id] if id in right_counts else 0 for id in left_counts)
    print("Part 2:", similarity)

if __name__ == "__main__":
    part1()
    part2()