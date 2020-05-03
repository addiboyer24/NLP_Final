import os
import sys


def main(argv):
    
    # compile with make -B
    os.system("make -B")

    if(len(argv) == 0):
        # execute the program passing in the corpus of Simpson's Scripts
        os.system("./interpreter.out")
    elif(len(argv) == 1):
        # execute the program passing in the corpus of Simpson's Scripts
        os.system("./interpreter.out {}".format(argv[0]))
    else:
        print("Usage SimpsonsSmallTalkGenerator.py <Corpus Filename>(optional)")


if(__name__ == '__main__'):
    main(sys.argv[1:])

