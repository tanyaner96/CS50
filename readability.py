from cs50 import get_string
import string 

    
text = get_string("Text: ")
    
    #coleman index: 0.0588 * L - 0.296 * S - 15.8
    #L is the average number of letters per 100 words 
    #S is the average number of sentences per 100
    
    #1. get number of letters (separated by spaces)
    #2. get number of sentences (separated by fullstops)
    
text_len = len(text)
space_num = 0
punc_num = 0
sent_num = 0
word_num = 1

for i in range(text_len):
   if text[i] == " ":
       space_num += 1
       word_num += 1

for i in text:
    if i in string.punctuation:
        punc_num += 1

#print("Number of spaces: " + str(space_num))
#print("Number of punctuation: " + str(punc_num))

        
letter_num = text_len - space_num - punc_num
L = (letter_num/word_num) * 100

#print("Number of letters: " + str(letter_num))

sent = ["!", ".", "?"]

for i in text:
    if i in sent:
        sent_num += 1
        
#print("Number of sentences: " + str(sent_num))

S = (sent_num/word_num) * 100

index = 0.0588 * L - 0.296 * S - 15.8

#print("L: " + str(L))
#print("S: " + str(S))
#print("Index: " + str(index))

if index > 15:
    print("Grade 16+")
elif index < 1: 
    print("Before Grade 1")
else:
    print("Grade " + str(round(index)))