#ifndef _BLUR
#define _BLUR

#include "Filter.h"
#include "Array.h"

using namespace std;

namespace filtering
{
	class FilterBlur : public Array<float>, public Filter {

	protected:
		int N;
		Array<float> f;
	public:
		FilterBlur();

		FilterBlur(int N);

		Image operator << (const Image & image);

		Image applyFilter(Image & image, Array<float> f);

	};
}
#endif
