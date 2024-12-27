def solve():
    file = open("input-7.txt")

    def operate(nums, target):
        if len(nums) == 1:
            return nums[0] == target
        add = nums.copy(); mul = nums.copy(); cali = nums.copy()
        add.insert(0, add.pop(0) + add.pop(0))
        mul.insert(0, mul.pop(0) * mul.pop(0))
        cali.insert(0, int(str(cali.pop(0)) + str(cali.pop(0))))
        return operate(add,target) or operate(mul,target) or operate(cali,target)

    res = 0
    for line in file:
        val, nums = line.split(':')
        nums = list(map(int, nums.split()))
        if operate(nums, int(val)):
            res += int(val)
    print("Answer:", res)

if __name__ == "__main__":
    solve()