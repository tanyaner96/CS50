from sys import argv
from sys import exit
import csv


seq = []

if len(argv) < 3:
    print("Error, please input file.") #check if correct number of arguments.
    sys.exit
else:
    with open(argv[1], "r") as file:
        reader = csv.reader(file)
        seq = next(reader)
        seq = seq[1:len(seq)]
    with open(argv[2], "r") as file1:
        word = file1.read()

word_len = len(word)


max_str = []


for target in seq:
    if target in word:
        i = 0
        count = 0
        max_count = 0
        while i < (len(word) - len(target) + 1):
            if word[i:i+len(target)] == target:
                count += 1
                i += len(target)
            else:
                if count > max_count:
                    max_count = count
                count = 0
                i += 1
        max_str.append(str(max_count))



with open(argv[1], "r") as file:
        reader = csv.reader(file)
        next(reader)

        for row in reader:
            if row[1:len(max_str)+1] == max_str:
                print(row[0])
                exit()
                
        print("No Match")
                







