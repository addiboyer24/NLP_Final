import os
import sys

def is_error(file):

    error = "ERROR:"
    for line in file:
        if(line.find(error) != -1):
            return True


    return False

def main(argv):
    
    # compile .l and .y
    os.system('make -B')

    failed = open('failed.txt','w+')
    passed = open('passed.txt', 'w+')

    num_lines = 0
    
    master = open('outfile.txt', 'r+', encoding='utf-8', errors='ignore').readlines()
    for line in master:
        temp = open('temp.txt', 'w+')
        temp.write(line)
        temp.close()

        
        # make a system call using the current line in temp as input
        os.system('./interpreter.out temp.txt >> output.txt')

        check = open('output.txt')

        error = is_error(check)

        if(error):
            failed.write(line)
        else:
            passed.write(line)

        
        check.close()
        # remove output.txt
        os.remove('output.txt')

        num_lines += 1

        if(num_lines % 500 == 0):
            print("Processed %d lines" % (num_lines))

    passed.close()
    failed.close()

    passed = open('passed.txt').readlines()

    failed = open('failed.txt').readlines()

    print("%d lines passed with current grammar" % len(passed))
    print("%d lines failed with current grammar" % len(failed))
    
    

if(__name__ == '__main__'):
    main(sys.argv[1:])
