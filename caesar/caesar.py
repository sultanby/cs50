import cs50
import sys

if len(sys.argv) != 2:
    exit("Usage: python caesar.py k")
if len(sys.argv) == 2:
    k = int(sys.argv[1])
    p = cs50.get_string("plaintext: ")
    print('ciphertext: ', end="")
    for c in range(len(p)):
        if p[c].isupper():
            print(chr(ord('A')+(ord(p[c])-ord('A')+k) % 26), end="")
        elif p[c].islower():
            print(chr(ord('a')+(ord(p[c])-ord('a')+k) % 26), end="")
        else:
            print(p[c], end="")
print()
