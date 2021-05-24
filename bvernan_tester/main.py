#!/usr/bin/python3
import random
import string
import math
import os
import subprocess


def main():
    if not os.path.exists("./test/"):
        os.mkdir("./test/")
    input_file_length = 10
    range_len = 9
    for i in range(range_len):
        print("Creating", i)
        with open("./test/input_"+str(i)+".txt", "wb") as f:
            f.write(("".join([random.choice(string.printable) for _ in range(input_file_length**i)])).encode())
        key_length = math.ceil(input_file_length*(random.uniform(0.1, 1.0)))
        with open("./test/key_"+str(i)+".txt", "wb") as f:
            f.write(("".join([random.choice(string.printable) for _ in range(key_length**i)])).encode())
        print("Testing encode of", i)
        subprocess.run(['./bvernan', './test/key_'+str(i)+'.txt', './test/input_'+str(i)+'.txt', './test/out_' +
                        str(i)+'.txt'], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        print("Testing decode of", i)
        subprocess.run(['./bvernan', './test/key_'+str(i)+'.txt', './test/out_'+str(i)+'.txt', './test/decoded_input_' +
                        str(i)+'.txt'], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    print("Verifying")
    for i in range(range_len):
        print("Checking", i)
        out = open("./test/out_"+str(i)+".txt", "rb")
        input_file = open("./test/input_"+str(i)+".txt", "rb")
        key = open("./test/key_"+str(i)+".txt", "rb")
        decoded_input = open("./test/decoded_input_"+str(i)+".txt", "rb")
        input_byte = input_file.read(1)
        while input_byte:
            encoded = out.read(1)
            key_value = key.read(1)
            if not key_value:
                key.seek(0)
                key_value = key.read(1)
#            if not (ord(encoded.decode())^ord(key_value.decode()) == ord(input_byte.decode())):
#                print("error encode for i=", i, "val1: ",ord(encoded.decode()), "val2:", ord(key_value.decode()),"xor:", ord(encoded.decode())^ord(key_value.decode()), "input:", ord(input_byte.decode()))
            decoded = decoded_input.read(1)
            if not (decoded == input_byte):
                print("error decode for i=", i)
            input_byte = input_file.read(1)
        print("Verification completed of", i)
        out.close()
        input_file.close()
        key.close()


if __name__ == "__main__":
    main()
