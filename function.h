#pragma once
#include "stdafx.h"
#pragma pack(1)
struct BMP
{
	char Type[2];           //File type. Set to "BM".
	int32_t Size;     //Size in BYTES of the file.
	int16_t Reserved1;      //Reserved. Set to zero.
	int16_t Reserved2;      //Reserved. Set to zero.
	int32_t OffSet;   //Offset to the data.
	int32_t headsize; //Size of rest of header. Set to 40.
	int32_t Width;     //Width of bitmap in pixels.
	int32_t Height;     //  Height of bitmap in pixels.
	int16_t Planes;    //Number of Planes. Set to 1.
	int16_t BitsPerPixel;       //Number of Bits per pixels.
	int32_t Compression;   //Compression. Usually set to 0.
	int32_t SizeImage;  //Size in bytes of the bitmap.
	int32_t XPixelsPreMeter;     //Horizontal pixels per meter.
	int32_t YPixelsPreMeter;     //Vertical pixels per meter.
	int32_t ColorsUsed;   //Number of colors used.
	int32_t ColorsImportant;  //Number of "important" colors.
};
struct Pix
{
	unsigned char B;
	unsigned char G;
	unsigned char R;

};
struct ColorTable
{
	Pix	 *colors;
	unsigned long length;
};

struct PixelArray
{
	Pix	 **pixels;
	unsigned long rowCount;
	unsigned long columnCount;
};
void readBMP(char *File_Name, BMP &a);
void Get_Inf(BMP a);
void scanBmpPixelLine(FILE *f, Pix *&line, unsigned long length);
void skipBmpPadding(FILE *f, char count);
void ReadPixelArray(FILE *f, BMP a, PixelArray &data);
void draw_BMP_image(BMP a, PixelArray data);
void Free_Pixel_Array(PixelArray data);