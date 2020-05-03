import sys

def get_cleaned_line(line, to_replace):

    for token in to_replace:
        line = line.replace(token, '')

    return line
def main(argv):

    f = open('errors.txt', 'r+')
    to_replace = set()
    
    for line in f:
        line = line.split()
        for token in line:
            to_replace.add(token)

    f = open('passed.txt')

    cleaned_passed = open('clean_passed.txt', 'w+')
    
    for line in f:
        
        cleaned_line = get_cleaned_line(line, to_replace)
        cleaned_passed.write(cleaned_line)


    cleaned_passed.close()
    print("Done cleaning corpus")
    


if(__name__ == '__main__'):
    main(sys.argv[1:])
