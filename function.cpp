#include "stdafx.h"
void readBMP(char *File_Name, BMP &a)
{
	FILE *p = fopen(File_Name, "rb");
	if (p == NULL)
	{
		printf("Can't open file!");

		return;
	}
	else
	{
		fread(&a, sizeof(BMP), 1, p);
	}
	fclose(p);
}
void Get_Inf(BMP a)
{
	if (a.Type[0] != 'B' || a.Type[1] != 'M')
	{
		printf("This is not a BMP file");
	}
	else
	{
		printf("File name: test.bmp\n");
		printf("This is a BMP file\n");
		printf("The size of this file is %lu bytes\n", a.Size);
		printf("The witdth of this image is %lu pixels\n", a.Width);
		printf("The height of this image is %lu pixels\n", a.Height);
		printf("The number of bits per pixels in this image is %u\n", a.BitsPerPixel);
	}

}
void scanBmpPixelLine(FILE *f, Pix *&line, unsigned long length)
{
	if (f == NULL)
		return;
	line = new Pix[length];
	fread(line, sizeof(Pix), length, f);
}
void skipBmpPadding(FILE *f, char count)
{
	if (f == NULL)
		return;
	if (count == 0)
		return;
	char padding[3];
	fread(padding, sizeof(char), count, f);
}
void ReadPixelArray(FILE *f, BMP a, PixelArray &data)
{
	if (f == NULL)
		return;
	data.rowCount = a.Height;
	data.columnCount = a.Width;
	data.pixels = new Pix*[data.rowCount];
	char paddingCount = (4 - (a.Width * (a.BitsPerPixel / 8) % 4)) % 4;
	fseek(f, 54, SEEK_SET);
	for (int i = 0; i < data.rowCount; i++)
	{
		scanBmpPixelLine(f, data.pixels[data.rowCount - i - 1], a.Width);
		skipBmpPadding(f, paddingCount);
	}
}
void draw_BMP_image(BMP a, PixelArray data)
{
	HWND console = GetConsoleWindow();
	HDC hdc = GetDC(console);

	for (int i = 0; i < a.Height; i++)
		for (int j = 0; j < a.Width; j++)
		{
			Pix pixel = data.pixels[i][j];
			SetPixel(hdc, j, i, RGB(pixel.R, pixel.G, pixel.B));
		}

	ReleaseDC(console, hdc);
}

void Free_Pixel_Array(PixelArray data)
{
	for (int i = 0; i < data.rowCount; i++)
		delete[]data.pixels[i];

	delete[]data.pixels;
}