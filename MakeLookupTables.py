import sys
import re
import string


def main(argv):

    f = open('nouns.txt', 'r').readlines()

    words = []
    for word in f:
        word = word.lower().replace('\n','')
        words.append(word)

    f = open('formatteddata.txt', 'r').readlines()
    remove = string.punctuation
    #print(remove)
    pattern = r"[{}]".format(remove)

    final = set()
    for line in f:
        title, quote = line.split('|')
        quote = re.sub(pattern,'',quote)
        tokens = quote.split()
        #print(tokens)
        for token in tokens:
            if(token in words):
                final.add(token)

    actual = []
    for word in final:
        actual.append(word)

    list.sort(actual)
    
    nouns = "std::vector<std::string> nouns = {"
    
    for word in actual:
        word = word.lower().replace('\n','')
        nouns += '"%s",' % word

    nouns = nouns[0:len(nouns)-1]
    nouns += "};"

    print(nouns)
    



if(__name__ == '__main__'):
    main(sys.argv[1:])
