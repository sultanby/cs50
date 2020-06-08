from cs50 import get_float

while True:
    n = get_float("Owed:")
    if n > 0:
        break
pennies, dimes, nickels, quarters = 0, 0, 0, 0
cents = int(n*100)
quarters = cents//25
remain1 = cents - (quarters*25)
if remain1 > 0:
    dimes = remain1//10
    remain2 = remain1 - (dimes*10)
    if remain2 > 0:
        nickels = remain2//5
        remain3 = remain2 - (nickels*5)
        if remain3 > 0:
            pennies = remain3
print(quarters+dimes+nickels+pennies)