#!/usr/bin/python3.9
import filecmp
import math
import os
import random
import shutil
import struct
import subprocess
import time


def main():
    if os.path.exists("./test/"):
        shutil.rmtree("./test/")
    os.mkdir("./test/")
    input_file_length = 10
    range_len = 8
    loop_counter = 0
    error_counter = 0
    csv = open("data.csv", "w")
    csv.write("input_size;loop_counter;key_size;encode_millis;decode_millis;equal_encode;equal_decode\n")
    try:
        while error_counter < 5:
            for i in range(1, range_len + 1):
                csv_line = str(input_file_length ** i)+";"+str(loop_counter)+";"

                with open("./test/input_" + str(i) + "_" + str(loop_counter) + ".txt", "wb") as f:
                    f.write(random.randbytes(input_file_length ** i))
                key_length = math.ceil(input_file_length * (random.uniform(0.1, 0.9)))

                csv_line += str(key_length ** i)+";"

                with open("./test/key_" + str(i) + "_" + str(loop_counter) + ".txt", "wb") as f:
                    f.write(random.randbytes(key_length ** i))

                time_encode_start = time.time()
                p = subprocess.run(
                    ['./bvernan', './test/key_' + str(i) + '_' + str(loop_counter) + '.txt',
                     './test/input_' + str(i) + '_' + str(loop_counter) + '.txt', './test/out_' +
                     str(i) + '_' + str(loop_counter) + '.txt'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)

                csv_line += str(time.time()-time_encode_start)+";"

                if len(p.stdout.decode().strip()) > 0:
                    print(i, loop_counter, p.stdout.decode().strip())
                if len(p.stderr.decode().strip()) > 0:
                    print(i, loop_counter, p.stderr.decode().strip())

                time_decode_start = time.time()
                p = subprocess.run(
                    ['./bvernan', './test/key_' + str(i) + '_' + str(loop_counter) + '.txt', './test/out_' + str(i) + '_' +
                     str(loop_counter) + '.txt', './test/decoded_input_' + str(i) + '_' + str(loop_counter) + '.txt'],
                    stdout=subprocess.PIPE, stderr=subprocess.PIPE)

                csv_line += str(time.time()-time_decode_start)+";"

                if len(p.stdout.decode().strip()) > 0:
                    print(i, loop_counter, p.stdout.decode().strip())
                if len(p.stderr.decode().strip()) > 0:
                    print(i, loop_counter, p.stderr.decode().strip())

                with open('./test/generated_out_' + str(i) + "_" + str(loop_counter) + '.txt', 'wb') as out:
                    key = open('./test/key_' + str(i) + '_' + str(loop_counter) + '.txt', 'rb')
                    input_file = open('./test/input_' + str(i) + '_' + str(loop_counter) + '.txt', 'rb')

                    key.seek(0, os.SEEK_END)
                    block_length = key.tell()
                    key.seek(0, os.SEEK_SET)

                    input_file.seek(0, os.SEEK_END)
                    input_length = input_file.tell()
                    input_file.seek(0, os.SEEK_SET)

                    block_quantity = input_length // block_length
                    if input_length % block_length != 0:
                        block_quantity += 1

                    for block_index in range(block_quantity):
                        for byte_index in range(block_length):
                            input_file.seek(byte_index+block_index*block_length, os.SEEK_SET)
                            x = input_file.read(1)
                            if x == b'':
                                break
                            d, = struct.unpack('B', x)
                            key.seek((byte_index+block_index) % block_length, os.SEEK_SET)
                            b, = struct.unpack('B', key.read(1))
                            _d = d ^ b
                            out.write(struct.pack('B', _d))

                    input_file.close()
                    key.close()

                result_test = filecmp.cmp('./test/out_' + str(i) + '_' + str(loop_counter) + '.txt',
                                          './test/generated_out_' + str(i) + "_" + str(loop_counter) + '.txt',
                                          shallow=False)

                result = filecmp.cmp("./test/input_" + str(i) + "_" + str(loop_counter) + ".txt", "./test/decoded_input_" +
                                     str(i) + "_" + str(loop_counter) + ".txt", shallow=False)

                csv_line += str(result_test) + ";" + str(result)

                if result and result_test:
                    print("Files", i, loop_counter, "are equals")
                    os.remove("./test/input_" + str(i) + "_" + str(loop_counter) + ".txt")
                    os.remove("./test/decoded_input_" + str(i) + "_" + str(loop_counter) + ".txt")
                    os.remove("./test/key_" + str(i) + "_" + str(loop_counter) + ".txt")
                    os.remove("./test/out_" + str(i) + "_" + str(loop_counter) + ".txt")
                    os.remove("./test/generated_out_" + str(i) + "_" + str(loop_counter) + ".txt")
                else:
                    print("\t\t\t\t\tFiles", i, loop_counter, "are DIFFERENT", result, result_test)
                    error_counter += 1

                csv.write(csv_line+"\n")
            loop_counter += 1
    except KeyboardInterrupt as k:
        csv.close()


if __name__ == "__main__":
    main()
