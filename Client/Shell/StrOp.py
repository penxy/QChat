import sys

str = sys.argv[1]
split_char = sys.argv[2]

ADDR = str.split(split_char)

for i in ADDR:
    print(i)