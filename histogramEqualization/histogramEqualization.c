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
	int *pro = (int*)malloc(sizeof(int*) * L);
	for (i = 0; i < L; i++)
	{
		pro[i] = 0;
	}
	getHistogram(image, pro);
	
	// get the cumulative distribution of original picture
	int* cuo = (int*)malloc(sizeof(int*) * L);
	cuo[0] = pro[0];
	for (i = 1; i < L; i++)
	{
		cuo[i] = cuo[i - 1] + pro[i];
	}
	free(pro);

	// construct desired cumulative distribution
	int* cud = (int*)malloc(sizeof(int*) * L);
	cud[0] = row * column / L;
	for (i = 1; i < L; i++)
	{
		cud[i] = cud[i - 1] + cud[0];
	}
	
	// get mro(ouput versus input)
	unsigned char *mro = (unsigned char*)malloc(sizeof(char*) * L);
	for (i = 0; i < L; i++)
	{
		for (j = 0; j < L; j++)
		{
			if (j == 255)
			{
				mro[i] = j;
				break;
			}
			int a = cuo[i] - cud[j];
			int b = cuo[i] - cud[j+1];
			if (abs(a) <= abs(b))
			{
				mro[i] = j;
				break;
			}
		}
	}
	free(cuo);
	free(cud);

	// transform image with mro
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < column; j++)
		{
			for (int level = 0; level < L; level++)
			{
				if (image[i][j]==level)
				{
					image[i][j] = mro[level];
					break;
				}
			}
		}
	}
	printf("transform image successfully\n");

	// write mrofile
	char* mrofile = "mrofile.txt";
	error = fopen_s(&fp, mrofile, "wb");
	if (error != 0)
	{
		fprintf(stderr, "error: could not open %s\n", ofile);
		exit(1);
	}
	fwrite(mro, 1, L, fp);
	fclose(fp);
	free(mro);

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