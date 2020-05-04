import os
import sys


def main(argv):
    
    # compile with make -B
    os.system("make -B")

    if(len(argv) == 0):
        # execute the program passing in the corpus of Simpson's Scripts
        os.system("./interpreter.out")
    elif(len(argv) == 3):
        # execute the program passing in the corpus of Simpson's Scripts, numCharacters, and numLines
        fname = argv[0]
        numLines = argv[1]
        numCharacters = argv[2]
        os.system("./interpreter.out {} {} {}".format(fname, numLines, numCharacters))
    else:
        print("Usage SimpsonsSmallTalkGenerator.py <Corpus> <Num Lines> <Num Characters>")


if(__name__ == '__main__'):
    main(sys.argv[1:])

