#include<stdio.h>
#include<stdlib.h>
#include"Image.h"

// construct function of class Image
Image::Image(int row, int column)
{
	this->row = row;
	this->column = column;
	this->content = (unsigned char**)malloc(sizeof(unsigned char*) * row);
	for (int x = 0; x < row; x++)
	{
		content[row] = \
			(unsigned char*)malloc(sizeof(unsigned char) * column);
	}
}

// desctructor of class Image
Image::~Image()
{
	for (int x = 0; x < row; x++)
	{
		free(this->content[x]);
		this->content[x] = NULL;
	}
	free(this->content);
	this->content = NULL;
}

// read image from a input file
void Image::readImage(char* infile)
{
	FILE* fp;
	int error = 0;
	error = fopen_s(&fp, infile, "rb");
	if (error != 0)
	{
		printf("Cannot open infile\n");
		exit(1);
	}
	for (int x = 0; x < this->row; x++)
		if (fread(this->content[x], 1, column, fp) != column)
		{
			fprintf(stderr, "error: couldn't read enough stuff\n");
			exit(1);
		}
	fclose(fp);
	printf("read input file sucess\n");
}

// write image to a file
void Image::writeImage(char* outfile)
{
	FILE* fp;
	int error = 0;
	error = fopen_s(&fp, outfile, "wb");
	if (error != 0)
	{
		printf("Cannot open outfile\n");
		exit(1);
	}
	for (int x = 0; x < row; x++)
		fwrite(this->content[x], 1, column, fp);
	fclose(fp);
	printf("write sucess\n");
}