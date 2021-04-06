from cs50 import get_int

def main():


    height = get_int("Height: ")

    while height > 8 or height < 1:
        height = get_int("Height: ")
        
    mario(height)
    
def mario(height):    
    
    row = 1  
    
    #left side
    for i in range(height):
        space = height - row
        print((" " * space)+("#" * row)+(" ")+("#" * row))
        row = row + 1 
main()