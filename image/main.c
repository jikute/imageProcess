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
	readImage(image, row, column, "triangle.raw");

	// create a buffer to store the operated image
	int outRow = row;
	int outColumn = column;
	unsigned char** outImage = \
		(unsigned char**)malloc(sizeof(unsigned char*) * outRow);
	for (int i = 0; i < outRow; i++)
		outImage[i] = malloc(sizeof(unsigned char) * outColumn);
	filter(outImage, image, gfilter, row, column, rowF, columnF);
	// free the image buffer and filter
	for (int i = 0; i < row; i++)
	{
		free(image[i]);
	}
	free(image);
	writeImage(outImage,outRow,outColumn,"degradedTriangle.raw");
	// free output buffer
	for (int i = 0; i < outRow; i++)
		free(outImage[i]);
	free(outImage);
	return 0;
}