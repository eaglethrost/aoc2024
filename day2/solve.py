def valid_sequence(ids):
    increasing = True; decreasing = True; safe = True
    for i in range(1, len(ids)):
        if increasing and ids[i] >= ids[i-1]+1 and ids[i] <= ids[i-1]+3:
            decreasing = False
        elif decreasing and ids[i] <= ids[i-1]-1 and ids[i] >= ids[i-1]-3:
            increasing = False
        else:
            safe = False
            break
    return safe

def part1():
    file = open("input.txt")
    safe_ids = 0
    for line in file:
        ids = list(map(int, line.split()))
        safe_ids += valid_sequence(ids)
    print("Safe reports:", safe_ids)

def part2():
    file = open("input.txt")
    safe_ids = 0
    for line in file:
        ids = list(map(int, line.split()))
        if not valid_sequence(ids):
            for i in range(0, len(ids)):
                new_ids = [ids[j] for j in range(0, len(ids)) if i != j]
                if valid_sequence(new_ids):
                    safe_ids += 1
                    break
        else:
            safe_ids += 1
    print("Safe reports with 1 replacement: ", safe_ids)

if __name__ == "__main__":
    part1()
    part2()