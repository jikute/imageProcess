#pragma once
/*zoom a Grayscale image*/
void zoom(unsigned char** zoomImage, int zoomRow, int zoomColumn, \
	unsigned char** image, int row, int column);
/* shrink a Grayscale image*/
void shrink(unsigned char** sImage, int sRow, int sColumn, \
	unsigned char** image, int row, int column);
/* arithmetric meam filter*/
void amf(unsigned char** out, unsigned char** image,\
	int row, int column, int size);
/* geometric mean filter*/
void gmf(unsigned char** out, unsigned char** image, \
	int row, int column, int size);
/* harmonic mean filter*/
void hmf(unsigned char** out, unsigned char** image, \
	int row, int column, int size);
/*contraharmonic mean filter with Q = 1*/
void chmf(unsigned char** out, unsigned char** image, \
	int row, int column, int size, double Q);
/*max filter*/
void maxf(unsigned char** out, unsigned char** image, \
	int row, int column, int size);
/*min filter*/
void minf(unsigned char** out, unsigned char** image, \
	int row, int column, int size);
/*midpoint filter*/
void midpointf(unsigned char** out, unsigned char** image, \
	int row, int column, int size);
/*median filter*/
void medianf(unsigned char** out, unsigned char** image, \
	int row, int column, int size);
/* power law of gray scale image*/
void power(unsigned char** out, unsigned char** image, \
	int row, int column, double exponent);
/* get the gray level histogram of input image*/
void getHistogram(int* pr, unsigned char** image, \
	int row, int column);
/*histogram equalization*/
void histogramEqualizate(unsigned char** out, \
	unsigned char** image, int row, int column);
/*laplace transform of a image, center value is -8*/
void laplace(unsigned char** out, \
	unsigned char** image, int row, int column);
/*using image1 substract image2 */
void subtract(unsigned char** out, \
	unsigned char** image1, unsigned char** image2, \
	int row, int column);
/* convolution of image1 and image2 */
void convolution(unsigned char** out, \
	unsigned char** image1, unsigned char** image2, \
	int row1, int column1, int row2, int column2);

/*generate a spacial Gaussian filter*/
void Gaussian(int** out, double A, \
	int meanx, int meany, int sigmax, int sigmay);

/* convolution of image1 and filter */
void filter(unsigned char** out, \
	unsigned char** image1, int** filter, \
	int row1, int column1, int row2, int column2);