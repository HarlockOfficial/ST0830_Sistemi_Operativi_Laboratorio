#!/usr/bin/python3
import random
import math
import os
import subprocess
import shutil
import filecmp


def main():
    if os.path.exists("./test/"):
        shutil.rmtree("./test/")
    os.mkdir("./test/")
    input_file_length = 10
    range_len = 8
    for i in range(range_len + 1):
        with open("./test/input_" + str(i) + ".txt", "wb") as f:
            f.write(os.urandom(input_file_length ** i))
        key_length = math.ceil(input_file_length * (random.uniform(0.1, 0.9)))
        with open("./test/key_" + str(i) + ".txt", "wb") as f:
            f.write(os.urandom(key_length ** i))
        print("Running encode of", i)
        p = subprocess.run(
            ['./bvernan', './test/key_' + str(i) + '.txt', './test/input_' + str(i) + '.txt', './test/out_' +
             str(i) + '.txt'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        print(p.stdout.decode())
        print(p.stderr.decode())
        print("Running decode of", i)
        p = subprocess.run(
            ['./bvernan', './test/key_' + str(i) + '.txt', './test/out_' + str(i) + '.txt', './test/decoded_input_' +
             str(i) + '.txt'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        print(p.stdout.decode())
        print(p.stderr.decode())
        result = filecmp.cmp("./test/input_" + str(i) + ".txt", "./test/decoded_input_" + str(i) + ".txt",
                          shallow=False)
        if result:
            print("Files",str(i), "are equal")
            os.remove("./test/input_" + str(i) + ".txt")
            os.remove("./test/decoded_input_" + str(i) + ".txt")
            os.remove("./test/key_" + str(i) + ".txt")
            os.remove("./test/out_" + str(i) + ".txt")
        else:
            print("Files", str(i), "are different")

if __name__ == "__main__":
    main()
