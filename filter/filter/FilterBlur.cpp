#include "../ppm/ppm.h"
#include "Image.h"

#include "Filter.h"

#include "Vec3.h"

#include "FilterBlur.h"

using namespace std;
using namespace filtering;
using namespace imaging;

Image FilterBlur::operator << (const Image & image) {

	Image newImage(image);
	Array<float> f(N, N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			f(i, j) = 1 / pow(N, 2);
		}
	}

	return newImage = applyFilter(newImage, f);
}

Image FilterBlur::applyFilter(Image & newImage, Array<float> f) {
	//diaperasi eikonas
	for (int i = 0; i < newImage.getWidth(); i++) {
		for (int j = 0; j < newImage.getHeight(); j++) {
			Color sum(0, 0, 0);
			//efarmogi filtrou ana pixel
			for (int m = 0; m <N; m++) {
				for (int n = 0; n < N; n++) {
					if (i + m >= 0 && i + m < newImage.getWidth() && j + n >= 0 && j + n < newImage.getHeight()) {
						//cout << "COUNT: " << count << endl;
						sum += newImage.getPixel(i + m, j + n) * f(m, n);
					}
				}
			}
			sum = sum.clampToLowerBound(0);
			sum = sum.clampToUpperBound(1);
			newImage.setPixel(i, j, sum);
		}
	}
	return newImage;
}

FilterBlur::FilterBlur(int N) {
	this->N = N;
}

FilterBlur::FilterBlur(){}