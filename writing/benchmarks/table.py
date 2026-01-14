if __name__ == "__main__":
    with open("input.txt") as f:
        lines = f.readlines()

    index = 1

    for line in lines:
        if line.startswith("samples:"):
            print(f"{index} & 10000 & ", end="")
            index += 1
            continue
        if line.startswith("cycles:"):
            parts = line.split(" ")
            print(f"{parts[1]} & {parts[3]} & ", end="")
            continue
        if line.startswith("ms:"):
            parts = line.split(" ")
            print(f"{parts[1]} & {parts[3]} \\\\\\hline")
            continue