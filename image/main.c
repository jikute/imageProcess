#include<stdio.h>
#include<stdlib.h>
#include"spacialDeal.h"
#include"ImageIO.h"

int main()
{
	int row = 480;
	int column = 640;
	// create a buffer store original image
	unsigned char** image = \
		(unsigned char**)malloc(sizeof(unsigned char*) * row);
	for (int i = 0; i < row; i++)
		image[i] = malloc(sizeof(unsigned char) * column);
	readImage(image, row, column, "cat.raw");
	
	// create a buffer to store the operated image
	unsigned char** outImage = \
		(unsigned char**)malloc(sizeof(unsigned char*) * row);
	for (int i = 0; i < row; i++)
		outImage[i] = malloc(sizeof(unsigned char) * column);
	// create a buffer to store the laplaced image
	unsigned char** laImage = \
		(unsigned char**)malloc(sizeof(unsigned char*) * row);
	for (int i = 0; i < row; i++)
		laImage[i] = malloc(sizeof(unsigned char) * column);

	// operate image
	laplace(laImage, image, row, column);
	subtract(outImage, image, laImage, row, column);
	// free the image buffer and laplaced buffer
	for (int i = 0; i < row; i++)
	{
		free(image[i]);
		free(laImage[i]);
	}
	free(image);
	free(laImage);

	writeImage(outImage,row,column,"sharp.raw");
	// free output buffer
	for (int i = 0; i < row; i++)
		free(outImage[i]);
	free(outImage);
	return 0;
}
