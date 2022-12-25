#!/usr/bin/env python3
from functools import cmp_to_key

packets = []
data = open("input.txt", encoding="utf-8").read().strip()
lines = [x for x in data.split('\n')]

def isInRightOrder(firstPair, secondPair):
    # firstPair [[1],[2,3,4]]
    # secondPair [[1],4]

    # -1 if firstPair is smaller secondPair
    # 0 if firstPair is equal to secondPair
    # 1 if firstPair is bigger secondPair

    if(type(firstPair) == int and type(secondPair) == int):
        if(firstPair < secondPair):
            return -1
        elif(firstPair > secondPair):
            return 1
        return 0
    elif(type(firstPair) == list and type(secondPair) == list):
        smaller = len(firstPair) if len(firstPair) < len(secondPair) else len(secondPair)
        for i in range(0, smaller):
            cmp = isInRightOrder(firstPair[i], secondPair[i])
            if(cmp != 0):
                return cmp
        
        if(len(firstPair) < len(secondPair)):
            return -1
        elif(len(firstPair) > len(secondPair)):
            return 1
        
        return 0
    
    elif(type(firstPair) == int and type(secondPair) == list):
        return isInRightOrder([firstPair], secondPair)
    else:
        return isInRightOrder(firstPair, [secondPair])


pt1 = 0
for i, group in enumerate(data.split('\n\n')):
    p1,p2 = group.split('\n')
    p1 = eval(p1)
    p2 = eval(p2)

    packets.append(p1)
    packets.append(p2)

    if isInRightOrder(p1, p2) == -1:
        pt1 += 1+i
print(pt1)


# pt2
packets.append([[2]])
packets.append([[6]])

packets = sorted(packets, key=cmp_to_key(lambda p1,p2: isInRightOrder(p1,p2)))
pt2 = 1
for i, pkt in enumerate(packets):
    if pkt == [[2]] or pkt == [[6]]:
        pt2 *= i+1
print(pt2)
