#ifndef _FILTERLINEAR
#define _FILTERLINEAR

#include "Image.h"
#include "Filter.h"

using namespace std;

namespace filtering
{
	class FilterLinear : public Filter{
		
	protected:
		Color a_parameter;
		Color c_parameter;
	public:
		
		FilterLinear(Color a_parameter, Color c_parameter);

		~FilterLinear();

		Image operator << (const Image & image);
	};
}
#endif
