//
// Created by root on 29.05.2019.
//

#include <cstdio>
#include <cstdint>
#include "Bitmap.h"

void
Bitmap::saveImage(
	byte_t* image,
	imageDimension_t height,
	imageDimension_t width,
	const std::string& imageFileName) {

	byte_t   padding[3]  = {0, 0, 0};
	uint16_t paddingSize = ( 4 - ( width * BYTES_PER_PIXEL ) % 4 ) % 4;

	byte_t* fileHeader = createBitmapFileHeader(height, width, paddingSize);
	byte_t* infoHeader = createBitmapInfoHeader(height, width);

	FILE* imageFile = fopen(imageFileName.c_str(), "wb");

	fwrite(fileHeader, 1, fileHeaderSize, imageFile);
	fwrite(infoHeader, 1, infoHeaderSize, imageFile);

	int i;
	for (i = 0; i < height; i++) {
		fwrite(image + ( i * width * BYTES_PER_PIXEL ), BYTES_PER_PIXEL, width, imageFile);
		fwrite(padding, 1, paddingSize, imageFile);
	}

	fclose(imageFile);
}

uint8_t*
Bitmap::createBitmapFileHeader(
		uint16_t height,
		uint16_t width,
		uint16_t paddingSize) {
	uint16_t fileSize = fileHeaderSize + infoHeaderSize + ( BYTES_PER_PIXEL * width + paddingSize ) * height;

	static uint8_t fileHeader[] = {
			0, 0, /// signature
			0, 0, 0, 0, /// image file size in bytes
			0, 0, 0, 0, /// reserved
			0, 0, 0, 0, /// start of pixel array
	};

	fileHeader[0]  = (uint8_t) ( 'B' );
	fileHeader[1]  = (uint8_t) ( 'M' );
	fileHeader[2]  = (uint8_t) ( fileSize );
	fileHeader[3]  = (uint8_t) ( fileSize >> 8u );
	fileHeader[4]  = (uint8_t) ( fileSize >> 16u );
	fileHeader[5]  = (uint8_t) ( fileSize >> 24u );
	fileHeader[10] = (uint8_t) ( fileHeaderSize + infoHeaderSize );

	return fileHeader;
}

uint8_t*
Bitmap::createBitmapInfoHeader(
		uint16_t height,
		uint16_t width) {
	static uint8_t infoHeader[] = {
			0, 0, 0, 0, /// header size
			0, 0, 0, 0, /// image width
			0, 0, 0, 0, /// image height
			0, 0, /// number of color planes
			0, 0, /// bits per pixel
			0, 0, 0, 0, /// compression
			0, 0, 0, 0, /// image size
			0, 0, 0, 0, /// horizontal resolution
			0, 0, 0, 0, /// vertical resolution
			0, 0, 0, 0, /// colors in color table
			0, 0, 0, 0, /// important color count
	};

	infoHeader[0]  = (uint8_t) ( infoHeaderSize );
	infoHeader[4]  = (uint8_t) ( width );
	infoHeader[5]  = (uint8_t) ( width >> 8u );
	infoHeader[6]  = (uint8_t) ( width >> 16u );
	infoHeader[7]  = (uint8_t) ( width >> 24u );
	infoHeader[8]  = (uint8_t) ( height );
	infoHeader[9]  = (uint8_t) ( height >> 8u );
	infoHeader[10] = (uint8_t) ( height >> 16u );
	infoHeader[11] = (uint8_t) ( height >> 24u );
	infoHeader[12] = (uint8_t) ( 1 );
	infoHeader[14] = (uint8_t) ( BYTES_PER_PIXEL * 8 );

	return infoHeader;
}
