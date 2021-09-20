#ifndef _FILTERGAMMA
#define _FILTERGAMMA

#include "Image.h"
#include "Filter.h"

using namespace std;

namespace filtering
{
	class FilterGamma : public Filter {
		
	protected:
		float g_parameter;
	public:
		
		Color power(Color c, double y);

		FilterGamma(double g_parameter);

		~FilterGamma();

		Image operator << (const Image & image);
	};
}
#endif
