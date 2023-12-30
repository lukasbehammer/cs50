#include "helpers.h"
#include <math.h>

int cap(int input);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int val = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = val;
            image[i][j].rgbtGreen = val;
            image[i][j].rgbtBlue = val;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img_reflected[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            img_reflected[i][j] = image[i][width - (j + 1)];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = img_reflected[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img_blurred[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sumRed = 0.0;
            float sumGreen = 0.0;
            float sumBlue = 0.0;

            int up = -1;
            int down = 2;
            int left = -1;
            int right = 2;

            float counter = 0.0;

            if (i == 0)
            {
                up = 0;
            }
            if (i == height - 1)
            {
                down = 1;
            }
            if (j == 0)
            {
                left = 0;
            }
            if (j == width - 1)
            {
                right = 1;
            }
            for (int k = up; k < down; k++)
            {
                for (int l = left; l < right; l++)
                {
                    sumRed += image[i + k][j + l].rgbtRed;
                    sumGreen += image[i + k][j + l].rgbtGreen;
                    sumBlue += image[i + k][j + l].rgbtBlue;
                    counter++;
                }
            }
            img_blurred[i][j].rgbtRed = round(sumRed / counter);
            img_blurred[i][j].rgbtGreen = round(sumGreen / counter);
            img_blurred[i][j].rgbtBlue = round(sumBlue / counter);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = img_blurred[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Sobel_x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Sobel_y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    RGBTRIPLE img_edge[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sumRed_x = 0.0;
            float sumGreen_x = 0.0;
            float sumBlue_x = 0.0;

            float sumRed_y = 0.0;
            float sumGreen_y = 0.0;
            float sumBlue_y = 0.0;

            int up = -1;
            int down = 2;
            int left = -1;
            int right = 2;

            if (i == 0)
            {
                up = 0;
            }
            if (i == height - 1)
            {
                down = 1;
            }
            if (j == 0)
            {
                left = 0;
            }
            if (j == width - 1)
            {
                right = 1;
            }
            for (int k = up; k < down; k++)
            {
                for (int l = left; l < right; l++)
                {
                    sumRed_x += (image[i + k][j + l].rgbtRed * Sobel_x[1 + k][1 + l]);
                    sumGreen_x += (image[i + k][j + l].rgbtGreen * Sobel_x[1 + k][1 + l]);
                    sumBlue_x += (image[i + k][j + l].rgbtBlue * Sobel_x[1 + k][1 + l]);

                    sumRed_y += (image[i + k][j + l].rgbtRed * Sobel_y[1 + k][1 + l]);
                    sumGreen_y += (image[i + k][j + l].rgbtGreen * Sobel_y[1 + k][1 + l]);
                    sumBlue_y += (image[i + k][j + l].rgbtBlue * Sobel_y[1 + k][1 + l]);
                }
            }
            img_edge[i][j].rgbtRed = cap(round(sqrt(pow(sumRed_x, 2) + pow(sumRed_y, 2))));
            img_edge[i][j].rgbtGreen = cap(round(sqrt(pow(sumGreen_x, 2) + pow(sumGreen_y, 2))));
            img_edge[i][j].rgbtBlue = cap(round(sqrt(pow(sumBlue_x, 2) + pow(sumBlue_y, 2))));
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = img_edge[i][j];
        }
    }
    return;
}

int cap(int input)
{
    int output;
    if (input > 255)
    {
        output = 255;
    }
    else
    {
        output = input;
    }
    return output;
}
