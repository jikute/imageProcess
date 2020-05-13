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
	
	int* pr = (int*)malloc(sizeof(int) * 256);
	getHistogram(pr, image, row, column);
	for (int i = 0; i < 256; i++)
	{
		printf("level=%d,pr=%d\n",i,pr[i]);
	}
	//shrink the Image
	/*
	// create a buffer to store the operated image
	int oRow = row;
	int oColumn = column;
	unsigned char** outImage = \
		(unsigned char**)malloc(sizeof(unsigned char*) * oRow);
	for (int i = 0; i < oRow; i++)
		outImage[i] = malloc(sizeof(unsigned char) * oColumn);

	// zoom image
	power(outImage, image, row, column, 4.1);
	// free the image buffer
	for (int i = 0; i < row; i++)
		free(image[i]);
	free(image);
	writeImage(outImage,oRow,oColumn,"power.raw");
	// free output buffer
	for (int i = 0; i < row; i++)
		free(outImage[i]);
	free(outImage);
	*/
	return 0;
}
