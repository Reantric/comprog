# cant be arsed to figure out how many squares needed efficiently using logs
# if you do that then you can skip squaring repeatedly and just raise to the right power
# straight away.
# tho theres probably a way w/out needing to actually exponentiate. ever.

# returns -1 on failure
def my_solution(l: list[int]) -> int:
    # how many squares needed
    count = 0

    # how many elements we have seen
    # if we go right to left and square elem i then we will also need to square i+1, i+2, ...
    # so keeping a count allows us to see how many needed to square
    # w/out needing to actually square them
    k = 1

    # will never need to square the first element so ignore it.
    for i in reversed(range(1, len(l))):
        # if there is a 1 in the middle of the list then impossible
        if l[i] == 1:
            return -1

        # square till we get l[i] > l[i-1]
        # each time add k for l[i], l[i+1], ..., l[i+k-1] all *needing* to be squared
        while l[i] < l[i - 1]:
            l[i] *= l[i]
            count += k

        k += 1

    print(l)
    return count


def main():
    import sys
    input = '''
    7
3
1 2 3
2
3 2
3
3 1 5
4
1 1 2 3
3
4 3 2
9
16 2 4 2 256 2 4 2 8
11
10010 10009 10008 10007 10006 10005 10004 10003 10002 10001 10000
    '''
    data = input.split()

    t = int(data[0])
    index = 1
    results = []

    for _ in range(t):
        n = int(data[index])
        array = list(map(int, data[index + 1: index + 1 + n]))
        result = my_solution(array)
        results.append(result)
        index += n + 1

    for result in results:
        print(result)


if __name__ == "__main__":
    main()
