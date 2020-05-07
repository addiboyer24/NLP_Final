import os
import sys


def main(argv):
    
    # compile with make -B
    path = 'interpreter.out'
    if(os.path.isfile(path)):
        pass
    else:
        # compile the .l, and .y files
        os.system("make -B")

    if(len(argv) == 0):
        # execute the program passing in the corpus of Simpson's Scripts
        os.system("./interpreter.out")
    elif(len(argv) == 4):
        # execute the program passing in the corpus of Simpson's Scripts, numCharacters, and numLines
        fname = argv[0]
        numLines = argv[1]
        numCharacters = argv[2]
        isStochastic = argv[3]
        os.system("./interpreter.out {} {} {} {}".format(fname, numLines, numCharacters, isStochastic))
    else:
        print("Usage: SimpsonsSmallTalkGenerator.py <corpus> <num_lines> <num_characters> <is_stochastic?>")


if(__name__ == '__main__'):
    main(sys.argv[1:])

