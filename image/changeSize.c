#include<stdio.h>
#include<stdlib.h>

/*zoom a Grayscale image*/
void zoom(unsigned char** zoomImage, int zoomRow, int zoomColumn,\
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