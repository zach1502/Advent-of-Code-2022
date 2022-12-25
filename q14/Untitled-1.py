floor_base = 0

grid = {}
for ln in IN.split("\n"):
    places = ln.split(" -> ")
    places = [tuple(map(int, x.split(","))) for x in places]

    x, y = places[0]
    floor_base = max(floor_base, y)
    grid[x, y] = "#"
    for nx, ny in places[1:]:
        while x != nx or y != ny:
            dx = (nx > x) - (x > nx)
            dy = (ny > y) - (y > ny)
            x = x + dx
            y = y + dy
            grid[x, y] = "#"
            floor_base = max(floor_base, y)
        
        assert x == nx
        assert y == ny

for y in range(10):
    for x in range(490, 505):
        print("#" if (x, y) in grid else ".", end="")
    print()
print()

floor_base = floor_base + 2

for x in range(-1000, 1000):
    grid[x, floor_base] = "#"

# now pour
t = 0
is_over = False
while True:
    # release sand
    sx, sy = 500, 0

    if grid.get((sx, sy)) == "o":
        break

    while True:
        # try down
        if grid.get((sx, sy + 1), None) is None:
            sy = sy + 1
            t = t + 1
            continue

        # try left
        elif grid.get((sx - 1, sy + 1), None) is None:
            sx = sx - 1
            sy = sy + 1
            t = t + 1
            continue

        # try right
        elif grid.get((sx + 1, sy + 1), None) is None:
            sx = sx + 1
            sy = sy + 1
            t = t + 1
            continue

        else:
            grid[sx, sy] = "o"
            break

    if is_over:
        break

print(sum(1 for k, v in grid.items() if v == "o"))
