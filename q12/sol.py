import networkx

def chToInt(x):
    alpha = "abcdefghijklmnopqrstuvwxyz"
    return alpha.index(x)

grid = [list(ln) for ln in open("input.txt", encoding="utf-8").read().strip().split("\n")]
width = len(grid[0])
height = len(grid)

startX, startY = 0, 0
endX, endY = 0, 0

for y in range(height):
    for x in range(width):
        if grid[y][x] == "S":
            startX, startY = x, y
            grid[y][x] = "a"

        if grid[y][x] == "E":
            endX, endY = x, y
            grid[y][x] = "z"

moves = [(1, 0), (-1, 0), (0, 1), (0, -1)]

G = networkx.DiGraph()

# build graph
for y in range(height):
    for x in range(width):
        for dx, dy in moves:
            nodeX, nodeY = x + dx, y + dy

            # In bounds
            if (0 <= nodeX < width) and (0 <= nodeY < height):
                A = chToInt(grid[y][x])
                B = chToInt(grid[nodeY][nodeX])

                # and not more than 1 higher
                if A + 1 >= B:
                    G.add_edge((x, y), (nodeX, nodeY)) # is part of the graph

# find shortest path
try:
    path = networkx.shortest_path(G, (startX, startY), (endX, endY))
except networkx.exception.NetworkXNoPath:
    # something def went wrong
    path = []

print(len(path) - 1)

minPath = 9999
for y in range(height):
    for x in range(width):

        if grid[y][x] == "a":
            try:
                path = networkx.shortest_path(G, (x, y), (endX, endY))
                minPath = min(minPath, len(path) - 1)
            except:
                pass
            
print(minPath)
