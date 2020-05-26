#include"Image.h"

int main()
{
	Image* originalImage = new Image(480,640);
	originalImage->readImage("cat.raw");
	Image* newImage = new Image(900,700);
	originalImage->interpolate(newImage,"nearestNeighbor");
	delete(originalImage);
	newImage->writeImage("newCat.raw");
	delete(newImage);
	return 0;
}
