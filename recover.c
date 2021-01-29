#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


const int size = 512;
 
int main(int argc, char *argv[])
{
    //check if input is a file
    if (argc != 2)
    {
        printf("Usage ./recover image \n");
        return 1;
    }
    
    
    FILE *file = fopen(argv[1], "r");
    FILE *output = NULL; 
    
    uint8_t buffer[size]; //create a new type to store a byte of data
    
    int count = 0; //count number of jpegs
    
    char filename[8];
    
    while (fread(&buffer, size, 1, file)) //read samples
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            printf("  This is a jpeg!\n");
            count = count + 1;
            sprintf(filename, "%03i.jpg", count);
        }
    }
    
    
}