#include"Image.h"
#include<stdio.h>

int main()
{
	//draw the 16*16 image with gray level 61 in every pixels
	Image* image = new Image(16,16);
	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			image->content[x][y] = 61;
			printf("%d ",image->content[x][y]);
		}
		printf("\n");
	}

	// do the error duffusion

	return 0;
}
