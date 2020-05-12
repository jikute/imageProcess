#include<stdio.h>
#include<stdlib.h>
#include"changeSize.h"
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

	//zoom the Image
	// create a buffer to store the operated image
	int zoomRow = row * 2;
	int zoomColumn = column * 1;
	unsigned char** outImage = \
		(unsigned char**)malloc(sizeof(unsigned char*) * zoomRow);
	for (int i = 0; i < zoomRow; i++)
		outImage[i] = malloc(sizeof(unsigned char) * zoomColumn);
	// zoom image
	zoom(outImage, zoomRow, zoomColumn, image, row, column);
	// free the image buffer
	for (int i = 0; i < row; i++)
		free(image[i]);
	free(image);
	writeImage(outImage,zoomRow,zoomColumn,"multiple.raw");
	// free output buffer
	for (int i = 0; i < row; i++)
		free(outImage[i]);
	free(outImage);
}
