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