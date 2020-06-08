from cs50 import get_string
from sys import argv


def main():
    if len(argv) != 2:
        exit("Usage: python bleep.py dictionary")

    file = open(argv[1], "r")
    # print(file.read())
    banned, message = [], []
    # message = []
    for line in file:
        line = line.strip()
        banned.append(line)
    # print(banned)
    print("What message would you like to censor?")
    f = get_string("")
    message = f.split(" ")
    # print(message)
    for k in message:
        if k.lower() in banned:
            print("*" * len(k), end="")
            print(" ", end="")
        else:
            print(k, end="")
            print(" ", end="")
    print()


if __name__ == "__main__":
    main()