#ifndef _FILTER
#define _FILTER

#include "Image.h"

using namespace std;
using namespace imaging;

namespace filtering
{

	class Filter {

	public:
		virtual Image operator << (const Image & image)=0;

		//default constructor
		Filter();
		//constructor

		//copy constructor
		Filter(const Filter &src);

		//copy assignment operator
		//Filter & operator = (const Filter & right);


		//Filter & operator << (const Filter & right);
		//destructor
		~Filter();

	};
}

#endif
