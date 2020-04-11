#include<stdio.h>
#include<stdlib.h>

#define row 480
#define column 640

int main(int argc, char** argv)
{
	int i,j;
	int	threshold;
	char *ifile, *ofile;
	if (argc != 4)
	{
		fprintf(stderr, "usage: %s input output threshold\n", argv[0]);
		exit(1);
	}
	ifile = argv[1];
	ofile = argv[2];
	threshold = atoi(argv[3]);
	printf("threshold=%d\n", threshold);

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

	// create a buffer to store samples
	int samRow = row / threshold;
	int samColumn = column / threshold;
	char** samImage = (char**)malloc(sizeof(char*) * samRow);
	for (i = 0; i < samRow; i++)
		samImage[i] = malloc(sizeof(char) * samColumn);
	// subsampling the input file
	for (i = 0; i < samRow; i++)
	{
		for (j = 0; j < samColumn; j++)
		{
			samImage[i][j] = image[i * threshold][j * threshold];
		}
	}
	printf("subsample successfully\n");

	// open output file
	error = fopen_s(&fp, ofile, "wb");
	if (error != 0)
	{
		fprintf(stderr, "error: could not open %s\n", ofile);
		exit(1);
	}
	// write output file
	for (i = 0; i < samRow; i++)
		fwrite(samImage[i], 1, samColumn, fp);
	fclose(fp);
	printf("write outfile sucessfully");
	free(samImage);
	return 0;
}
