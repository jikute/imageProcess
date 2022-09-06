#include<stdio.h>
#include<stdlib.h>

/* read the image file*/
void readImage(unsigned char** image, \
	int row, int column, char* infile)
{
	FILE* fp;
	int error = 0;
	error = fopen_s(&fp, infile, "rb");
	if (error != 0)
	{
		printf("Cannot open infile\n");
		exit(1);
	}
	for (int x = 0; x < row; x++)
		if (fread(image[x], 1, column, fp) != column)
		{
			fprintf(stderr, "error: couldn't read enough stuff\n");
			exit(1);
		}
	fclose(fp);
	printf("read input file sucess\n");
}

/* write the image file*/
void writeImage(unsigned char** image, \
	int row, int column, char* outfile)
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
		fwrite(image[x], 1, column, fp);
	fclose(fp);
	printf("write sucess\n");
}