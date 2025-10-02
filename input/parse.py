import os
import struct

from matplotlib import pyplot as plt


def read_int(file):
    return struct.unpack("i", file.read(4))[0]

def read_floats(file, size):
    return struct.unpack("f" * size, file.read(4 * size))

def read_string(file):
    out = b''
    while True:
        byte = file.read(1)
        if byte == b'\x00':
            return out
        out += byte

def read_column(file, row_count):
    pre_data = read_int(file)
    print("pre_data", pre_data)
    label = file.read(59)
    print("label", label)
    data = read_floats(file, row_count)
    print("data", data)
    return data

def parse(filename):
    print(f"\n\nParsing {filename}\n")
    with open(filename, "rb") as f:
        magic = f.read(4)
        print("magic", magic)
        assert magic == b"ff\x86?"

        v1 = read_int(f)
        assert v1 == 1

        size = read_int(f)
        os_size = os.path.getsize(filename)
        print("size + 1 =", size)
        assert size == os_size + 1

        assert read_int(f) == 0
        name = f.read(8)
        print("name", name)

        size_m_16 = read_int(f)
        print("size - 16 =", size_m_16)
        assert size_m_16 + 16 == os_size

        row_count = read_int(f)
        print("row_count", row_count)

        column_count = read_int(f)
        print("column_count", column_count)
        assert column_count == 4

        assert read_int(f) == 1
        assert read_int(f) == 1

        timestamp = f.read(18)
        print("timestamp", timestamp)

        f.seek(0x68)
        program = read_string(f)
        print("program", program)

        f.seek(0xd0)
        load = read_column(f, row_count)
        stroke = read_column(f, row_count)
        command = read_column(f, row_count)
        time = read_column(f, row_count)
        x = range(row_count)
        plt.plot(x, load, color="blue", label="Load")
        plt.plot(x, stroke, color="yellow", label="Stroke")
        plt.plot(x, command, color="red", label="Command")
        plt.plot(x, time, color="green", label="Time")
        plt.legend()
        plt.show()


if __name__ == "__main__":
    parse("19_v10.W01")
    parse("20_v50.W01")
