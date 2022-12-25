from parse import parse

with open("input.txt", "r") as f:
    v = [[int(j) for j in list(parse("Sensor at x={}, y={}: closest beacon is at x={}, y={}\n", l))] for l in f.readlines()]

# generate list of ranges that cannot contain beacon
def listOfNotBeacon(tgt):
    rgs = []
    # generate separate range for each beacon
    for i in v:
        d = abs(i[2] - i[0]) + abs(i[3] - i[1])
        if abs(tgt - i[1]) < d:
            k = d - abs(tgt - i[1])
            rgs.append([i[0] - k, i[0] + k])


    # combine overlapping
    rgs.sort()
    i = 0
    while(i < len(rgs) - 1):
        if rgs[i][1] + 1 >= rgs[i + 1][0]:
            rgs[i][1] = max(rgs[i + 1][1], rgs[i][1])
            rgs.pop(i + 1)
            continue
        i += 1

    print (rgs)
    return rgs


# Part 1
print(sum(i[1] - i[0] for i in listOfNotBeacon(2000000)))

print(listOfNotBeacon(2000000))

# Part 2
for i in range(4000000):
    rgs = listOfNotBeacon(i)
    for j in rgs:
        if j[0] <= 0 and j[1] >= 4000000:
            break
        for j in rgs:
            if j[0] <= 0 and j[1] >= 0:
                print((j[1] + 1) * 4000000 + i)
