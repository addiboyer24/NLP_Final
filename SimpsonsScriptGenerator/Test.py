f = open('passed_small.txt', 'r+')

corpus = open('simpsoncorpus.txt', 'w+')

count = 0
for line in f:
    line = line.replace('\n','').split('|')
    #print(line)
    character = line[1]
    if(character == "Homer Simpson"):
        count += 1
    quote = line[2].strip()

    corpus.write("|"+character+"|"+quote+"\n")

print(count)
corpus.close()
    
