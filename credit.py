from cs50 import get_int
from cs50 import get_string

def main():

    number = get_string("Number: ")
    
    odd_total = 0
    even_total = 0
    
    if number[0] == str(3):
        if number[1] == str(4) or number[1] == str(7):
            card_type = "AMEX"
    elif number[0] == str(5):
        if number[1] == str(1) or number[1] == str(2) or number[1] == str(3) or number[1] == str(4) or number[1] == str(5):
            card_type ="MASTERCARD"
    elif number[0] == str(4):
        card_type = "VISA"
    

    start = len(number) - 2

    for i in range(start, -1, -2):
        x = int(number[i]) * 2
        if len(str(x)) > 1:
                x = str(x)
                first_digit = int(x[0])
                second_digit = int(x[1])
                x = first_digit + second_digit
        
        odd_total = odd_total + x
    
    #print("Odd total: " + str(odd_total))
    
    for i in range(start+1 , -1 , -2):
        y = int(number[i])
        even_total = even_total + int(number[i])
    
    
    #print("Even total: " + str(even_total))
    
    total = odd_total + even_total
    #print("Total: " + str(total))
    
    #get number of digits in total
    total_len = len(str(total))
    
    #check if the last digit is 0 or not
    if (str(total))[total_len - 1] != str(0):
        print("INVALID")
    else:
        print(card_type)

main()
            
        