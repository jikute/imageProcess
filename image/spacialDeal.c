#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*zoom a Grayscale image*/
void zoom(unsigned char** zoomImage, int zoomRow, int zoomColumn, \
	unsigned char** image, int row, int column)
{
	double rm = ((double)zoomRow - 1) / ((double)row - 1);
	double cm = ((double)zoomColumn - 1) / ((double)column - 1);
	// nearest neighbor interpolation
	for (int x = 0; x < zoomRow; x++)
	{
		for (int y = 0; y < zoomColumn; y++)
		{
			if (x / rm - (int)(x / rm) <= 0.5)
			{
				if (y / cm - (int)(y / cm) <= 0.5)
				{
					zoomImage[x][y] = image[(int)(x / rm)][(int)(y / cm)];
				}
				else
				{
					zoomImage[x][y] = image[(int)(x / rm)][(int)(y / cm) + 1];
				}
			}
			else
			{
				if (y / cm - (int)(y / cm) <= 0.5)
				{
					zoomImage[x][y] = image[(int)(x / rm) + 1][(int)(y / cm)];
				}
				else
				{
					zoomImage[x][y] = image[(int)(x / rm) + 1][(int)(y / cm) + 1];
				}
			}
		}
	}
	printf("zoom by neighbor interpolate success\n");
}

/* shrink a Grayscale image*/
void shrink(unsigned char** sImage, int sRow, int sColumn, \
	unsigned char** image, int row, int column)
{
	// compute row shrink multiple
	double rm = ((double)row - 1) / ((double)sRow - 1);
	//compute column shrink multiple
	double cm = ((double)column - 1) / ((double)sColumn - 1);
	// interpolating the input file by nearest neighbor way
	for (int x = 0; x < sRow; x++)
	{
		for (int y = 0; y < sColumn; y++)
		{
			if (x * rm - (int)(x * rm) <= 0.5)
			{
				if (y * cm - (int)(y * cm) <= 0.5)
				{
					sImage[x][y] = image[(int)(x * rm)][(int)(y * cm)];
				}
				else
				{
					sImage[x][y] = image[(int)(x * rm)][(int)(y * cm) + 1];
				}
			}
			else
			{
				if (y * cm - (int)(y * cm) <= 0.5)
				{
					sImage[x][y] = image[(int)(x * rm) + 1][(int)(y * cm)];
				}
				else
				{
					sImage[x][y] = image[(int)(x * rm) + 1][(int)(y * cm) + 1];
				}
			}
		}
	}
	printf("shrink the image success\n");
}

/* arithmetric mean filter*/
/* variables: output image, input image,
              row of image, colum of image, size of mask*/
void amf(unsigned char**out, unsigned char** image,\
	int row, int column, int size)
{
	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y < column; y++)
		{
			if (x < size / 2 || x >= column - size / 2)
			{
				out[x][y] = image[x][y];
				continue;
			}
			if (y < size / 2 || y >= column - size / 2)
			{
				out[x][y] = image[x][y];
				continue;
			}
			int sum = 0;
			for (int i = -size / 2; i <= size / 2; i++)
			{
				for (int j = -size / 2; j <= size / 2; j++)
				{
					sum = sum + image[x + i][y + j];
				}
			}
			out[x][y] = sum / (size * size);
		}
	}
	printf("%d arithmetric mean filter success\n",size);
}

/* geometric mean filter*/
void gmf(unsigned char** out, unsigned char** image, \
	int row, int column, int size)
{
	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y < column; y++)
		{
			if (x < size / 2 || x >= column - size / 2)
			{
				out[x][y] = image[x][y];
				continue;
			}
			if (y < size / 2 || y >= column - size / 2)
			{
				out[x][y] = image[x][y];
				continue;
			}
			double product = 1;
			for (int i = -size / 2; i <= size / 2; i++)
			{
				for (int j = -size / 2; j <= size / 2; j++)
				{
					product = product * pow(image[x + i][y + j],\
						1/ ((double)size * (double)size));
				}
			}
			out[x][y] = (unsigned char)product;
		}
	}
	printf("%d geometric mean filter success\n", size);
}

/* harmonic mean filter*/
void hmf(unsigned char** out, unsigned char** image, \
	int row, int column, int size)
{
	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y < column; y++)
		{
			if (x < size / 2 || x >= column - size / 2)
			{
				out[x][y] = image[x][y];
				continue;
			}
			if (y < size / 2 || y >= column - size / 2)
			{
				out[x][y] = image[x][y];
				continue;
			}
			double sum = 0;
			for (int i = -size / 2; i <= size / 2; i++)
			{
				for (int j = -size / 2; j <= size / 2; j++)
				{
					sum = sum + 1 / (double)image[x + i][y + j];
				}
			}
			out[x][y] = (unsigned char)((double)size * (double)size / sum);
		}
	}
	printf("%d harmonic mean filter success\n", size);
}

/*contraharmonic mean filter*/
void chmf(unsigned char** out, unsigned char** image, \
	int row, int column, int size, double Q)
{
	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y < column; y++)
		{
			if (x < size / 2 || x >= column - size / 2)
			{
				out[x][y] = image[x][y];
				continue;
			}
			if (y < size / 2 || y >= column - size / 2)
			{
				out[x][y] = image[x][y];
				continue;
			}
			double numerator = 0;
			double denominator = 0;
			for (int i = -size / 2; i <= size / 2; i++)
			{
				for (int j = -size / 2; j <= size / 2; j++)
				{
					numerator = numerator + pow(image[x + i][y + j], Q + 1);
					denominator = denominator + pow(image[x + i][y + j], Q);
				}
			}
			out[x][y] = (unsigned char)(numerator / denominator);
		}
	}
	printf("Q= %f, %d contraharmonic mean filter success\n", Q, size);
}

/*max filter*/
void maxf(unsigned char** out, unsigned char** image, \
	int row, int column, int size)
{
	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y < column; y++)
		{
			if (x < size / 2 || x >= column - size / 2)
			{
				out[x][y] = image[x][y];
				continue;
			}
			if (y < size / 2 || y >= column - size / 2)
			{
				out[x][y] = image[x][y];
				continue;
			}
			unsigned char max = image[x][y];
			for (int i = -size / 2; i <= size / 2; i++)
			{
				for (int j = -size / 2; j <= size / 2; j++)
				{
					if (image[x + i][y + j] > max)
					{
						max = image[x + i][y + j];
					}
					else
						continue;
				}
			}
			out[x][y] = max;
		}
	}
	printf("%d max filter success\n", size);
}

/*min filter*/
void minf(unsigned char** out, unsigned char** image, \
	int row, int column, int size)
{
	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y < column; y++)
		{
			if (x < size / 2 || x >= column - size / 2)
			{
				out[x][y] = image[x][y];
				continue;
			}
			if (y < size / 2 || y >= column - size / 2)
			{
				out[x][y] = image[x][y];
				continue;
			}
			unsigned char min = image[x][y];
			for (int i = -size / 2; i <= size / 2; i++)
			{
				for (int j = -size / 2; j <= size / 2; j++)
				{
					if (image[x + i][y + j] < min)
					{
						min = image[x + i][y + j];
					}
					else
						continue;
				}
			}
			out[x][y] = min;
		}
	}
	printf("%d min filter success\n", size);
}

/*midpoint filter*/
void midpointf(unsigned char** out, unsigned char** image, \
	int row, int column, int size)
{
	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y < column; y++)
		{
			if (x < size / 2 || x >= column - size / 2)
			{
				out[x][y] = image[x][y];
				continue;
			}
			if (y < size / 2 || y >= column - size / 2)
			{
				out[x][y] = image[x][y];
				continue;
			}
			unsigned char min = image[x][y];
			unsigned char max = image[x][y];
			for (int i = -size / 2; i <= size / 2; i++)
			{
				for (int j = -size / 2; j <= size / 2; j++)
				{
					if (image[x + i][y + j] < min)
					{
						min = image[x + i][y + j];
					}
					if (image[x + i][y + j] > max)
					{
						max = image[x + i][y + j];
					}
				}
			}
			out[x][y] = (min + max) / 2;
		}
	}
	printf("%d midpoint filter success\n", size);
}

/*median filter*/
void medianf(unsigned char** out, unsigned char** image, \
	int row, int column, int size)
{
	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y < column; y++)
		{
			if (x < size / 2 || x >= column - size / 2)
			{
				out[x][y] = image[x][y];
				continue;
			}
			if (y < size / 2 || y >= column - size / 2)
			{
				out[x][y] = image[x][y];
				continue;
			}
			unsigned char* buffer = (unsigned char*)malloc(sizeof(unsigned char) * size * size);
			int k = 0;
			for (int i = -size / 2; i <= size / 2; i++)
			{
				for (int j = -size / 2; j <= size / 2; j++)
				{
					buffer[k] = image[x + i][y + j];
					k = k + 1;
				}
			}
			// sort the elements in buffer
			for (int front = 0; front < size * size; front++)
			{
				for (int back = front + 1; back < size * size; back++)
				{
					if (buffer[back] < buffer[front])
					{
						unsigned char a = buffer[front];
						buffer[front] = buffer[back];
						buffer[back] = a;
					}
				}
			}
			out[x][y]=buffer[size*size/2];
		}
	}
	printf("%d median filter success\n", size);
}

/* power law of gray scale image*/
void power(unsigned char** out, unsigned char** image,\
	int row, int column, double exponent)
{
	double c = 1 / pow(255, exponent - 1);
	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y < column; y++)
		{
			out[x][y] = (unsigned char)(c * pow(image[x][y], exponent));
		}
	}
	printf("power image success, exponent=%f\n",exponent);
}

/* get the gray level histogram of input image*/
void getHistogram(int* pr, unsigned char** image,\
	int row, int column)
{
	for (int i = 0; i < 256; i++)
	{
		pr[i] = 0;
	}
	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y < column; y++)
		{
			for (int level = 0; level < 256; level++)
			{
				if (image[x][y] == level)
				{
					pr[level] = pr[level] + 1;
					break;
				}
			}
		}
	}
	printf("get histogram success\n");
}

/*histogram equalization*/
void histogramEqualizate(unsigned char** out, \
	unsigned char** image, int row, int column)
{
	int L = 256;
	// get the gray level distribution of original picture
	int* pro = (int*)malloc(sizeof(int*) * L);
	for (int i = 0; i < L; i++)
	{
		pro[i] = 0;
	}
	getHistogram(pro,image,row,column);

	// get the cumulative distribution of original picture
	int* cuo = (int*)malloc(sizeof(int*) * L);
	cuo[0] = pro[0];
	for (int i = 1; i < L; i++)
	{
		cuo[i] = cuo[i - 1] + pro[i];
	}
	free(pro);

	// construct desired cumulative distribution
	int* cud = (int*)malloc(sizeof(int*) * L);
	cud[0] = row * column / L;
	for (int i = 1; i < L; i++)
	{
		cud[i] = cud[i - 1] + cud[0];
	}

	// get mro (ouput versus input)
	unsigned char* mro = (unsigned char*)malloc(sizeof(char*) * L);
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < L; j++)
		{
			if (j == 255)
			{
				mro[i] = j;
				break;
			}
			int a = cuo[i] - cud[j];
			int b = cuo[i] - cud[j + 1];
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
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			for (int level = 0; level < L; level++)
			{
				if (image[i][j] == level)
				{
					out[i][j] = mro[level];
					break;
				}
			}
		}
	}
	free(mro);
	printf("image histogram equlization success\n");
}

/*laplace transform of a image, center value is -8*/
/*variables: output image, input image, row of image, column of image
*/
void laplace(unsigned char** out, \
	unsigned char** image, int row, int column)
{
	// create a buffer
	int** buffer = (int**)malloc(sizeof(int*) * row);
	for (int i = 0; i < row; i++)
		buffer[i] = malloc(sizeof(int) * column);

	// laplace transform and send the transformed value to buffer 
	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y < column; y++)
		{
			if (x - 1 < 0 || x + 1 >= row)
			{
				buffer[x][y] = image[x][y];
				continue;
			}
			if (y - 1 < 0 || y + 1 >= column)
			{
				buffer[x][y] = image[x][y];
				continue;
			}
			int sum = 0;
			for (int i = x - 1; i <= x + 1; i++)
			{
				for (int j = y - 1; j <= y + 1; j++)
				{
					if (i == x && j == y)
						sum = sum - 8 * image[i][j];
					else
						sum = sum + image[i][j];
				}
			}
			buffer[x][y] = sum;
		}
	}
	// find the smallest value in buffer
	int smallestNumber = buffer[0][0];
	int largestNumber = buffer[0][0];
	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y < column; y++)
		{
			if (buffer[x][y] < smallestNumber)
			{
				smallestNumber = buffer[x][y];
			}
			if (buffer[x][y] > largestNumber)
			{
				largestNumber = buffer[x][y];
			}
			else
				continue;
		}
	}
	int constant;
	if (smallestNumber < 0)
	{
		constant = 0 - smallestNumber;
	}
	else
	{
		constant = 0;
	}
	double scale;
	if (largestNumber + constant > 255)
	{
		scale = 255 / ((double)largestNumber + (double)constant);
	}
	else
	{
		scale = 1;
	}
	// scale the buffer
	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y < column; y++)
		{
			out[x][y] = (unsigned char)(scale * ((double)buffer[x][y] + (double)constant));
		}
	}
	printf("laplace transform success\n");
	// free buffer
	for (int i = 0; i < row; i++)
		free(buffer[i]);
	free(buffer);
}

/*using image1 substract image2 */
/*variables: out image, the minus, the substracted,
             row of images, row of columns*/
void subtract(unsigned char** out,\
	unsigned char** image1, unsigned char** image2, \
	int row, int column)
{
	// create a buffer
	int** buffer = (int**)malloc(sizeof(int*) * row);
	for (int i = 0; i < row; i++)
		buffer[i] = malloc(sizeof(int) * column);
	// substract
	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y < column; y++)
		{
			buffer[x][y] = image1[x][y] - image2[x][y];
		}
	}
	// find the smallest value in buffer
	int smallestNumber = buffer[0][0];
	int largestNumber = buffer[0][0];
	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y < column; y++)
		{
			if (buffer[x][y] < smallestNumber)
			{
				smallestNumber = buffer[x][y];
			}
			if (buffer[x][y] > largestNumber)
			{
				largestNumber = buffer[x][y];
			}
			else
				continue;
		}
	}
	int constant;
	if (smallestNumber < 0)
	{
		constant = 0 - smallestNumber;
	}
	else
	{
		constant = 0;
	}
	double scale;
	if (largestNumber + constant > 255)
	{
		scale = 255 / ((double)largestNumber + (double)constant);
	}
	else
	{
		scale = 1;
	}
	// scale the buffer
	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y < column; y++)
		{
			out[x][y] = (unsigned char)(scale * ((double)buffer[x][y] + (double)constant));
		}
	}
	printf("substract success\n");
	// free buffer
	for (int i = 0; i < row; i++)
		free(buffer[i]);
	free(buffer);
}