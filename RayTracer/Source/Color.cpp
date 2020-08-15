#include "Color.h"

#include <algorithm>

Color::Color() : R(1.0f), G(1.0f), B(1.0f){}
Color::Color(float R, float G, float B) : R(R), G(G), B(B){}


Color operator+(const Color& a, const Color& b)
{
	return Color(
		std::clamp(a.R + b.R, 0.0f, 1.0f),
		std::clamp(a.G + b.G, 0.0f, 1.0f),
		std::clamp(a.B + b.B, 0.0f, 1.0f)
	);
}

Color operator*(const Color& color, const float value)
{
	return Color(
		std::clamp(color.R * value, 0.0f, 1.0f),
		std::clamp(color.G * value, 0.0f, 1.0f),
		std::clamp(color.B * value, 0.0f, 1.0f)
	);
}

Color operator*(const float value, const Color& color)
{
	return Color(
		std::clamp(color.R * value, 0.0f, 1.0f),
		std::clamp(color.G * value, 0.0f, 1.0f),
		std::clamp(color.B * value, 0.0f, 1.0f)
	);
}
