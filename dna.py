from sys import argv
import csv

    
if len(argv) < 3:
    print("Error, please input file.") #check if correct number of arguments.
    sys.exit
else: 
    with open(argv[1], "r") as file1:
        reader1 = csv.reader(file1)
    
    with open(argv[2], "r") as file2:
        word = file2.read()

#Check AGATC
count_AGATC = 0
most_AGATC = []

i = 0

while i < len(word):
    if i+4 > len(word):
        break
    elif word[i] == "A" and word[i+1] == "G" and word[i+2] == "A" and word[i+3] == "T" and word[i+4] == "C":
        count_AGATC += 1
        i += 5
        most_AGATC.append(count_AGATC)
        #print(i)
        #print(count_AGATC)
    else:
        i += 1
		#print(i)
		
        count_AGATC = 0
		#print(count_AGATC)

#print("AGATC: ", end = "")
#print(most_AGATC)

#Check AATG
count_AATG = 0
most_AATG = []

j = 0

while j < len(word):
    if j+3 > len(word):
        break
    elif word[j] == "A" and word[j+1] == "A" and word[j+2] == "T" and word[j+3] == "G":
        count_AATG += 1
        j += 4
        most_AATG.append(count_AATG)
    else:
        j += 1
        count_AATG = 0
		#print(count_AGATC)

#print("AATG: ", end = "")
#print(most_AATG)
    
#Check TATC
count_TATC = 0
most_TATC = []

k = 0

while k < len(word):
    if k+3 > len(word):
        break
    elif word[k] == "T" and word[k+1] == "A" and word[k+2] == "T" and word[k+3] == "C":
        count_TATC += 1
        k += 4
        most_TATC.append(count_TATC)
    else:
        k += 1
        count_TATC = 0
		#print(count_AGATC)

#print("TATC: ", end = "")
#print(most_TATC)

#find max values of each str and check if the list is empty or not
if not most_AGATC:
    max_AGATC = 0
else: 
    max_AGATC = max(most_AGATC)
    
if not most_AATG:
    max_AATG = 0
else:
    max_AATG = max(most_AATG)

if not most_TATC:
    max_TATC = 0
else:
    max_TATC = max(most_TATC)

dna = [str(max_AGATC), str(max_AATG), str(max_TATC)]
print(dna)

with open(argv[1], "r") as file1:
        reader1 = csv.reader(file1)
        next(reader1)
        
        for row in reader1:
            if row[1] == dna[0] and row[2] == dna[1] and row[3] == dna[2]:
                print(row[0])
            else:
                print("No Match")
                break
                