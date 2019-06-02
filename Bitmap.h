//
// Created by root on 29.05.2019.
//

#ifndef RAYTRACING_BITMAP_H
#define RAYTRACING_BITMAP_H

#include <iostream>
#include "generic/defines.h"

class Bitmap {
public:
	static
	void
	saveImage(
			uint8_t*,
			imageDimension_t height,
			imageDimension_t width,
			const std::string& imageFileName);

	static constexpr uint8_t BYTES_PER_PIXEL = 3; /// red, green, blue
	static constexpr uint8_t RED             = 2;
	static constexpr uint8_t GREEN           = 1;
	static constexpr uint8_t BLUE            = 0;

protected:
	static constexpr int fileHeaderSize = 14;
	static constexpr int infoHeaderSize = 40;

	static uint8_t*
	createBitmapFileHeader(
			uint16_t height,
			uint16_t width,
			uint16_t paddingSize);

	static uint8_t*
	createBitmapInfoHeader(
			uint16_t height,
			uint16_t width);
};


#endif //RAYTRACING_BITMAP_H
