/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
	Color original = image->image[row][col];
	int last_digit = original.B & 1;
	Color *color = malloc(sizeof(Color));

	if (color == NULL) {
		return NULL;
	}
	if (last_digit) {
		color->B = 0;
		color->G = 0;
		color->R = 0;
	} else {
		color->B = 255;
		color->G = 255;
		color->R = 255;
	}
	return color;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	Color **color = malloc(sizeof(Color *) * image->rows);
	if (color == NULL) {
		return NULL;
	}
	for (int i = 0; i < image->rows; ++i) {
		color[i] = malloc(sizeof(Color) * image->cols);
		for (int j = 0; j < image->cols; ++j) {
			Color *p = evaluateOnePixel(image, i, j);
			color[i][j] = *p;
		}
	}
	Image *new_img = malloc(sizeof(Image));
	if (new_img == NULL) {
		return NULL;
	}
    new_img->rows = image->rows;
    new_img->cols = image->cols;
	new_img->image = color;
	return new_img;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if (argc == 1) {
		return -1;
	}

	char *filename = argv[1];
	Image *img = readData(filename);
	if (img == NULL) {
		return -1;
	}
	Image *st_img = steganography(img);
	freeImage(img);
	if (st_img == NULL) {
		return -1;
	}
	writeData(st_img);
	freeImage(st_img);
	return 0;
}
