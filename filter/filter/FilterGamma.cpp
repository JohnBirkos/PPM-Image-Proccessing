#include "../ppm/ppm.h"
#include "Image.h"

#include "Filter.h"

#include "Vec3.h"

#include "FilterGamma.h"

#include <cmath>

using namespace std;
using namespace filtering;
using namespace imaging;

Image FilterGamma::operator << (const Image & image) {

	Image newImage(image);

	Color pixel;
	
	
	for (int i = 0; i < newImage.getWidth(); i++) {
		for (int j = 0; j < newImage.getHeight(); j++) {
			
			pixel = newImage.getPixel(i, j);
			
			pixel = power(pixel, g_parameter);
			
			pixel = pixel.clampToLowerBound(0);
			
			pixel = pixel.clampToUpperBound(1);
			
			newImage.setPixel(i, j, pixel);
		}
	}

	return newImage;

}

Color FilterGamma::power(Color c, double y) {
	c.r = pow(c.r, y);
	c.g = pow(c.g, y);
	c.b = pow(c.b, y);
	return c;
}

FilterGamma::FilterGamma(double g_parameter) {
	this->g_parameter = g_parameter;
}

FilterGamma::~FilterGamma() {}