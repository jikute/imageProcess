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
	
	//create the filter
	int rowF = 480;
	int columnF = 640;
	unsigned char** filter = \
		(unsigned char**)malloc(sizeof(unsigned char*) * rowF);
	for (int i = 0; i < rowF; i++)
		filter[i] = malloc(sizeof(unsigned char) * columnF);
	readImage(filter, rowF, columnF, "cat.raw");
	// create a buffer to store the operated image
	int outRow = row + rowF - 1;
	int outColumn = column + columnF - 1;
	unsigned char** outImage = \
		(unsigned char**)malloc(sizeof(unsigned char*) * outRow);
	for (int i = 0; i < outRow; i++)
		outImage[i] = malloc(sizeof(unsigned char) * outColumn);
	convolution(outImage, image, filter, row, column, rowF, columnF);
	// free the image buffer and filter
	for (int i = 0; i < row; i++)
	{
		free(image[i]);
	}
	free(image);
	for (int i = 0; i < 3; i++)
	{
		free(filter[i]);
	}
	free(filter);
	writeImage(outImage,outRow,outColumn,"Laplace.raw");
	// free output buffer
	for (int i = 0; i < outRow; i++)
		free(outImage[i]);
	free(outImage);
	return 0;
}
