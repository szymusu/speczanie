with open("regression.md") as f:
    lines = f.readlines()


MODE_NONE = 0
MODE_CYCLES = 1
MODE_MS = 2

mode = MODE_NONE

data = []

for line in lines:
    if mode == MODE_NONE:
        if line.startswith("samples:"):
            parts = line.split(" ")
            assert len(parts) == 2
            mode = MODE_CYCLES
            continue
    elif mode == MODE_CYCLES:
        assert line.startswith("cycles:")
        parts = line.split(" ")
        assert len(parts) == 5
        assert parts[2] == "avg"
        assert parts[4] == "best\n"
        sample = {"cycles": (int(parts[1]), int(parts[3]))}
        data.append(sample)
        mode = MODE_MS
        continue
    elif mode == MODE_MS:
        assert line.startswith("ms:")
        parts = line.split(" ")
        assert len(parts) == 5
        assert parts[2] == "avg"
        assert parts[4] == "best\n"
        sample = data[-1]
        assert "ms" not in sample
        sample["ms"] = (float(parts[1]), float(parts[3]))
        mode = MODE_NONE
        continue

for d in data:
    avg_ratio = d["cycles"][0] / d["ms"][0]
    if d["ms"][1] == 0:
        best_ratio = -1
    else:
        best_ratio = d["cycles"][1] / d["ms"][1]
    print(avg_ratio, best_ratio)
