#ifndef _LAPLACE
#define _LAPLACE

#include "../ppm/ppm.h"
#include "Image.h"

#include "FilterBlur.h"

#include "Vec3.h"

using namespace std;
//using namespace filtering;
using namespace imaging;

using namespace std;

namespace filtering
{
	class FilterLaplace : public FilterBlur {

	protected:

	public:
		FilterLaplace() {
		}

		Image operator << (const Image & image) {

			Image newImage(image);
			int N = 3;
			Array<float> f(N, N);

			f(0, 0) = 0;
			f(0, 1) = 1;
			f(0, 2) = 0;
			f(1, 0) = 1;
			f(1, 1) = -4;
			f(1, 2) = 1;
			f(2, 0) = 0;
			f(2, 1) = 1;
			f(2, 2) = 0;
			
			FilterBlur b(3);

			return newImage = b.applyFilter(newImage, f);
		}

	};
}

#endif