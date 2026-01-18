from sys import argv

with open(argv[1], "rb") as f:
    print("const unsigned char font_bytes[] = {")
    while byte := f.read(1):
        print("0x" + byte.hex(), end=",")
    print("};")