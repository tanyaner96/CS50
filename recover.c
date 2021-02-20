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
    //initialising
    FILE *output = NULL;
    char filename[8];

    uint8_t buffer[size]; //create a new type to store a byte of data

    int count = 0; //count number of jpegs

    int writingFlag = 0;

    while ((fread(&buffer, size, 1, file)) == 1) //read samples
    {
        printf("reading\n");
        if ((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) && writingFlag == 1)
        {
            printf("case1\n");
            //CLOSE and write NEW
            fclose(output);

            printf("  This is a jpeg!\n");

            sprintf(filename, "%03i.jpg", count); //jpeg name
            printf("%i\n", count);
            fopen(filename, "w"); //jpeg file

            count = count + 1;
            output = fopen(filename, "w");
            fwrite(&buffer, size, 1, output);
            writingFlag = 1;
        }
        else if ((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) && writingFlag == 0)
        {
            printf("case2\n");
            //JUST write NEW
            printf("  This is a jpeg!\n");

            sprintf(filename, "%03i.jpg", count); //jpeg name
            printf("%i\n", count);
            fopen(filename, "w"); //jpeg file

            count = count + 1;
            output = fopen(filename, "w");
            fwrite(&buffer, size, 1, output);
            writingFlag = 1;
        }

        else if (writingFlag == 1)
        {
            printf("case3\n");
            fwrite(&buffer, size, 1, output);
        }
        else
        {
            printf("case4\n");
        }

    }

    fclose(file);
    fclose(output);

}