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
    loop_counter = 0
    error_counter = 0
    while error_counter < 5:
        for i in range(range_len + 1):
            with open("./test/input_" + str(i) + "_" + str(loop_counter) + ".txt", "wb") as f:
                f.write(os.urandom(input_file_length ** i))
            key_length = math.ceil(input_file_length * (random.uniform(0.1, 0.9)))
            with open("./test/key_" + str(i) + "_" + str(loop_counter) + ".txt", "wb") as f:
                f.write(os.urandom(key_length ** i))
            p = subprocess.run(
                ['./bvernan', './test/key_' + str(i) + '_' + str(loop_counter) + '.txt',
                 './test/input_' + str(i) + '_' + str(loop_counter) + '.txt', './test/out_' +
                 str(i) + '_' + str(loop_counter) + '.txt'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            if len(p.stdout.decode().strip()) > 0:
                print(i, loop_counter, p.stdout.decode().strip())
            if len(p.stderr.decode().strip()) > 0:
                print(i, loop_counter, p.stderr.decode().strip())
            p = subprocess.run(
                ['./bvernan', './test/key_' + str(i) + '_' + str(loop_counter) + '.txt', './test/out_' + str(i) + '_' +
                 str(loop_counter) + '.txt', './test/decoded_input_' + str(i) + '_' + str(loop_counter) + '.txt'],
                stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            if len(p.stdout.decode().strip()) > 0:
                print(i, loop_counter, p.stdout.decode().strip())
            if len(p.stderr.decode().strip()) > 0:
                print(i, loop_counter, p.stderr.decode().strip())

            result = filecmp.cmp("./test/input_" + str(i) + "_" + str(loop_counter) + ".txt", "./test/decoded_input_" +
                                 str(i) + "_" + str(loop_counter) + ".txt", shallow=False)
            if result:
                os.remove("./test/input_" + str(i) + "_" + str(loop_counter) + ".txt")
                os.remove("./test/decoded_input_" + str(i) + "_" + str(loop_counter) + ".txt")
                os.remove("./test/key_" + str(i) + "_" + str(loop_counter) + ".txt")
                os.remove("./test/out_" + str(i) + "_" + str(loop_counter) + ".txt")
            else:
                print("Files", i, loop_counter, "are different")
                error_counter += 1
        loop_counter += 1


if __name__ == "__main__":
    main()
