#pragma once
class Image
{
public:
	int row;
	int column;
	unsigned char** content;
	Image(int row, int column);
	~Image();
	// read image from file
	void readImage(const char* infile);
	// write image to a file
	void writeImage(const char* outfile);
	// interpolate an image
	void interpolate(Image* image, const char* way);
};