from cs50 import get_int

h = get_int("Height:")
while h < 1 or h > 8:
    h = get_int("Height:")
for i in range(1, h+1):
    for k in range(h-i):
        print(" ", end="")
        continue
    for l in range(1, i+1):
        print("#", end="")
    print("  ", end="")
    for l in range(1, i+1):
        print("#", end="")
    print('')
    continue