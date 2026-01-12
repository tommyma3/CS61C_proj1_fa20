/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	FILE *fp = fopen(filename, "r");
	char form[5];
	int row, col, scale;
	fscanf(fp, "%s %d %d %d", form, &col, &row, &scale);
	Color **color = malloc(sizeof(Color *) * row);

	for (int i = 0; i < row; ++i) {
		color[i] = malloc(sizeof(Color) * col);
		for (int j = 0; j < col; ++j) {
			int r, g, b;
			fscanf(fp, "%d %d %d", &r, &g, &b);
			color[i][j].R = r;
			color[i][j].G = g;
			color[i][j].B = b;
		}
	}

	Image *image = malloc(sizeof(Image));
	image->rows = row;
	image->cols = col;
	image->image = color;

	fclose(fp);
	return image;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	printf("P3\n%d %d\n255\n", image->cols, image->rows);
	for (int i = 0; i < image->rows; ++i) {
		for (int j = 0; j < image->cols; ++j) {
			Color p = image->image[i][j];

            printf("%3d %3d %3d", p.R, p.G, p.B);
			if (j != image->cols - 1) {
				printf("   ");
			}
		}
		printf("\n");
	}
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	if (image == NULL) {
		return;
	}

	for (int i = 0; i < image->rows; ++i) {
		free(image->image[i]);
	}

	free(image->image);
	free(image);
}