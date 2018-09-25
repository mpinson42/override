#!/usr/bin/python
import os

if __name__ == "__main__":
    for x in range(0x1337d00d - 21, 0x1337d00d):
        print("trying with: {}".format(x))
        os.system("echo {} | /home/users/level03/level03".format(x))
