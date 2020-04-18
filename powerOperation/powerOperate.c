#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define row 480
#define column 640
#define L 256

int main(int argc, char** argv)
{
	int i, j;
	char *ifile, *ofile;
	if (argc != 4)
	{
		fprintf(stderr, "usage: %s input output r\n", argv[0]);
		exit(1);
	}
	ifile = argv[1];
	ofile = argv[2];
	double r = atof(argv[3]);
	double c = 1 / pow((L - 1), (r - 1));
	printf("r = %f\n", r);
	printf("c = %f\n", c);

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

	// transform input image
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < column; j++)
		{
			image[i][j] = c * pow(image[i][j], r);
		}
	}
	printf("transform image successfully\n");

	// open output file
	error = fopen_s(&fp, ofile, "wb");
	if (error != 0)
	{
		fprintf(stderr, "error: could not open %s\n", ofile);
		exit(1);
	}
	// write output file
	for (i = 0; i < row; i++)
		fwrite(image[i], 1, column, fp);
	fclose(fp);
	printf("write outfile successfully\n");
	return 0;
}
