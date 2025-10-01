import struct
import matplotlib.pyplot as plt

size = 148
with open("19_v10.W01", "rb") as f:
    f.seek(0x10f)
    load_bytes = f.read(4 * size)

load = struct.unpack("f" * size, load_bytes)

with open("19_v10.W01", "rb") as f:
    f.seek(0x39e)
    stroke_bytes = f.read(4 * size)

stroke = struct.unpack("f" * size, stroke_bytes)

with open("19_v10.W01", "rb") as f:
    f.seek(0x62d)
    command_bytes = f.read(4 * size)

command = struct.unpack("f" * size, command_bytes)

with open("19_v10.W01", "rb") as f:
    f.seek(0x8bc)
    time_bytes = f.read(4 * size)

time = struct.unpack("f" * size, time_bytes)

for i in range(147):
    if abs((time[i] + .0025) - time[i + 1]) > 1e-7:
        print(time[i], time[i + 1])

# for i in range(148):
#     print(load[i] - command[i])

x = range(size)
plt.plot(x, load, color="blue", label="Load")
plt.plot(x, stroke, color="yellow", label="Stroke")
plt.plot(x, command, color="red", label="Command")
plt.plot(x, time, color="green", label="Time")
plt.legend()
plt.show()
