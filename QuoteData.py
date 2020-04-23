import sys
from collections import defaultdict
#http://www.cs.cornell.edu/~cristian/memorability.html
#https://towardsdatascience.com/you-cant-handle-the-truth-transfer-learning-to-detect-memorable-movie-quotes-d2b5305062cd


def main(argv):
    file = open('YouHadMeAtHelloData/moviequotes.memorable_nonmemorable_pairs.txt', 'r').readlines()
    f = open('formatteddata.txt', 'w')
    
    movie_to_quotes = defaultdict(list)

    for x in range(0, len(file), 5):
        
        movie = file[x].replace('\n','').lower()
        memorable_quote = file[x+1].strip().replace('"','').lower()
        #other_quote = file[x+3][6:].strip()

        movie_to_quotes[movie].append(memorable_quote)


    for movie, quotes in sorted(movie_to_quotes.items(), key = lambda x: x[0]):
        
        for quote in quotes:
            f.write(movie + "|" + quote + "\n")

    f.close()


if(__name__ == '__main__'):
    main(sys.argv[1:])





