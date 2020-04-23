import sys
import string
import re
import numpy as np


def main(argv):
    f = open('../../formatteddata.txt', 'r').readlines()

    remove = string.punctuation
    unique = set()
    pattern = r"[{}]".format(remove)
    for line in f:
        title, quote = line.replace('\n','').split('|')
        quote = re.sub(pattern,'',quote)
        tokens = quote.split()
        for token in tokens:
            unique.add(token.lower())



    f = open('6K adverbs.txt', 'r').readlines()

    final = []
    
    for word in f:
        word = word.replace('\n','').lower()
        if(word in unique):
            final.append(word)

    assert(len(final) == len(np.unique(final)))

    list.sort(final)

    start = "std::vector<std::string> adverbs = {"

    for word in final:
        start += '"%s",' % word

    start = start[0:len(start)-1]
    start += "};"

    # output C++ vector of adverbs for .y file
    print(start)
            
        


if(__name__ == '__main__'):
    main(sys.argv[1:])
