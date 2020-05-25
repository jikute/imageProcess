#pragma once
class Image
{
private:
	int row;
	int column;

public:
	unsigned char** content;
	Image(int row, int column);
	~Image();
	// read image from file
	void readImage(char* infile);
	// write image to a file
	void writeImage(char* outfile);
};