#include "../ppm/ppm.h"
#include "Image.h"

#include "Filter.h"

#include "Vec3.h"

#include "FilterLinear.h"

using namespace std;
using namespace filtering;
using namespace imaging;

Image FilterLinear::operator << (const Image & image) {

	Image newImage(image);

	Color pixel;
	
	for (int i = 0; i < newImage.getWidth(); i++) {
		for (int j = 0; j < newImage.getHeight(); j++) {
			
			pixel = newImage.getPixel(i, j);
		
			pixel = a_parameter * pixel + c_parameter;
			
			pixel = pixel.clampToLowerBound(0.0f);
			
			pixel = pixel.clampToUpperBound(1.0f);
			
			newImage.setPixel(i, j, pixel);
		}
	}

	return newImage;

}

FilterLinear::FilterLinear(Color a_parameter, Color c_parameter) {
	this->a_parameter = a_parameter;
	this->c_parameter = c_parameter;
}

FilterLinear::~FilterLinear() {}