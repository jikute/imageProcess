#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define row 480
#define column 640
#define L 256

void getHistogram(unsigned char *image,int *pr)
{
	for (int i = 0; i < row * column; i++)
	{
		for (int z = 0; z < L; z++)
		{
			if (image[i] == z)
			{
				pr[z] = pr[z] + 1;
				break;
			}
		}
	}
}

int main(int argc, char** argv)
{
	int i, j;
	char *ifile, *ofile;
	if (argc != 3)
	{
		fprintf(stderr, "usage: %s input output r\n", argv[0]);
		exit(1);
	}
	ifile = argv[1];
	ofile = argv[2];

	//open input file
	int error;
	FILE* fp;
	error = fopen_s(&fp, ifile, "rb");
	if (error != 0)
	{
		fprintf(stderr, "error: couldn't open %s\n", ifile);
		exit(1);
	}

	// read input file
	unsigned char image[row][column];
	for (i = 0; i < row; i++)
		if (fread(image[i], 1, column, fp) != column)
		{
			fprintf(stderr, "error: couldn't read enough stuff\n");
			exit(1);
		}
	fclose(fp);
	printf("read infile successfully\n");

	// get the gray level distribution of original picture
	int *pr = (int*)malloc(sizeof(int*) * L);
	for (i = 0; i < L; i++)
	{
		pr[i] = 0;
	}
	getHistogram(image, pr);
	
	// write profile
	error = fopen_s(&fp, ofile, "wb");
	if (error != 0)
	{
		fprintf(stderr, "error: could not open %s\n", ofile);
		exit(1);
	}
	fwrite(pr, 4, L, fp);
	fclose(fp);
}