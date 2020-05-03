import os
import sys


def main(argv):
    # compile with make -B
    os.system("make -B")

    # execute the program passing in the corpus of Simpson's Scripts
    os.system("./interpreter.out cleaned_passed.txt")


if(__name__ == '__main__'):
    main(sys.argv[1:])

