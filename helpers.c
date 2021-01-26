#include "helpers.h"
#include "math.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //For each pixel, calculate average pixel value between red blue and green.
    //Set colour value to the average value (round to nearest integer)


    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            //float red = image[i][j].rgbtRed;
            //float blue = image[i][j].rgbtBlue;
            //float green = image[i][j].rgbtGreen;

            int average = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen)/3.0);




            // if (i == 8 && j == 12) {
            //     printf("red = %i\n", image[i][j].rgbtRed);
            //     printf("blue = %i\n", image[i][j].rgbtBlue);
            //     printf("green = %i\n", image[i][j].rgbtGreen);

            //     printf("average = %i\n",average);
            // }
            image[i][j].rgbtRed = average;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            float red = image[i][j].rgbtRed;
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;

            int sepiaRed = round((0.393 * red) + (0.769 * green) + (0.189 * blue));
            int sepiaGreen = round((0.349 * red) + (0.686 * green) + (0.168 * blue));
            int sepiaBlue = round((0.272 * red) + (0.534 * green) + (0.131 * blue));

            if (sepiaRed > 255) //check if red is more than 255
            {
                image[i][j].rgbtRed = 255;
            }

            else
            {
                image[i][j].rgbtRed = round(sepiaRed);
            }

            if (sepiaGreen > 255) //check if green is more than 255
            {
                image[i][j].rgbtGreen = 255;
            }

            else
            {
                image[i][j].rgbtGreen = round(sepiaGreen);
            }

            if (sepiaBlue > 255) //check if blue is more than 255
            {
                image[i][j].rgbtBlue = 255;
            }

            else
            {
                image[i][j].rgbtBlue = round(sepiaBlue);
            }


        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Swap pixels horizontally on opposite sides
    //if there's an odd number of pixels, the middle number stays the same. if there's an even number of pixels, everyone swaps

    int length = width - 1;

        for (int i = 0; i < height; i++)
    {
            for (int j = 0; j < (width + 1 )/2; j++)
        {
                int new_width = length - j;


                //create a temporary pixel that holds the information of image[i][j]
                // float red_of_ij = image[i][j].rgbtRed;
                // float blue_of_ij = image[i][j].rgbtBlue;
                // float green_of_ij = image[i][j].rgbtGren;


                RGBTRIPLE temp = image[i][j];

                //swap image[i][j] with image[i][new_width]
                //swap image[i][new_width] with temp


                image[i][j] = image[i][new_width];
                image[i][new_width] = temp;
        }

    }



    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    //Calculate the average red/blue/green for the pixel by looking at the surrounding 9 pixels
    // Account for pixels where there isn't 9 pixels around it - edges/corners

    RGBTRIPLE copy[height][width]; //create copy

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float count = 0.0;
            float sumR = 0.0;
            float sumG = 0.0;
            float sumB = 0.0;
            for (int p = -1; p < 2; p++) {
                for (int q = -1; q < 2; q++) {
                    if (i + p < 0 || i + p > height - 1 || j + q < 0 || j + q > width - 1) {
                        continue;
                    }
                    else {
                        sumR += copy[i+p][j+q].rgbtRed;
                        sumG += copy[i+p][j+q].rgbtGreen;
                        sumB += copy[i+p][j+q].rgbtBlue;
                        count += 1.0;
                    }
                }
            }
            image[i][j].rgbtRed = round(sumR/count);
            image[i][j].rgbtGreen = round(sumG/count);
            image[i][j].rgbtBlue = round(sumB/count);
        }
    }

    return;
}
