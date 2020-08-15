#pragma once

class Color
{
public:
	Color();
	Color(float R, float G, float B);
	float R;
	float G;
	float B;
};

Color operator + (const Color& a, const Color& b);
Color operator * (const Color& color,  const float value);
Color operator * (const float value, const Color& color);