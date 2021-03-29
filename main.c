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
	{
		image[i] = malloc(sizeof(unsigned char) * column);
	}
	// read the original image
	readImage(image, row, column, "triangle.raw");
	return 0;
}