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
	
	//create the filter
	int rowF = 41;
	int columnF = 41;
	int** gfilter = \
		(int**)malloc(sizeof(int*) * rowF);
	for (int i = 0; i < rowF; i++)
		gfilter[i] = malloc(sizeof(int) * columnF);
	Gaussian(gfilter,9,20,20,7,7);
	FILE* fp;
	int error = 0;
	error = fopen_s(&fp, "filter.txt", "wb");
	if (error != 0)
	{
		printf("Cannot open outfile\n");
		exit(1);
	}
	for (int x = 0; x < rowF; x++)
		fwrite(gfilter[x], 4, columnF, fp);
	fclose(fp);
	printf("write sucess\n");

	/*
	for (int x = 0; x < rowF; x++)
	{
		for (int y = 0; y < columnF; y++)
		{
			printf("%d ", filter[x][y]);
		}
		printf("\n");
	}
	*/

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
	for (int i = 0; i < rowF; i++)
	{
		free(gfilter[i]);
	}
	free(gfilter);
	writeImage(outImage,outRow,outColumn,"degradedTriangle.raw");
	// free output buffer
	for (int i = 0; i < outRow; i++)
		free(outImage[i]);
	free(outImage);
	return 0;
}
