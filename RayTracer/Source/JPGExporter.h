#pragma once
class JPGExporter
{
public:
	JPGExporter();
	JPGExporter(bool isRGB, unsigned int quality, bool downsample);
	void Export(unsigned char* image, unsigned int width, unsigned int height, const char* filename);
	bool isRGB;
	unsigned int quality;
	bool downsample; 
};


