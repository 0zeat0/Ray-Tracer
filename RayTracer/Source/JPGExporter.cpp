#include "JPGExporter.h"

#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

#include "toojpeg.h"

JPGExporter::JPGExporter() : isRGB(true), quality(100), downsample(false) {}
JPGExporter::JPGExporter(bool isRGB, unsigned int quality, bool downsample) : isRGB(isRGB), quality(quality), downsample(downsample) {}

std::ofstream jpgfile;

//Writes bytes into a file
void WriteByte(unsigned char byte)
{
	jpgfile << byte;
}


//Exports image into a jpg file
void JPGExporter::Export(unsigned char* image, unsigned int width, unsigned int height, const char* filename)
{
	jpgfile = std::ofstream(filename, std::ios_base::out | std::ios_base::binary);
	TooJpeg::writeJpeg(WriteByte, image, width, height, isRGB, quality, downsample);

	std::cout << "The result was saved in " + std::filesystem::current_path().string() << " as " << static_cast<std::string>(filename) << "\n";
}
