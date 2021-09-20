//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2017 - 2018
//
//

#ifndef _ARRAY
#define _ARRAY

#include <iostream>
#include <vector>
#include <string>
#include "../ppm/ppm.h"
#include "Vec3.h"

	using namespace std;
	namespace math
	{
		template <typename T>
		class Array
		{

		protected:
			vector<T> buffer;                              //! Holds the image data.

			unsigned int width, height;

		public:
			Array() {
				width = 0;
				height = 0;
				buffer = vector<T>(0);
			}

			Array(unsigned int width, unsigned int height) {
				this->width = width;
				this->height = height;
				this->buffer = vector<T>(width*height);
			}

			Array(const Array &src) {

				//Array(src.getWidth(), src.getHeight(), src.buffer);
				width = src.width;
				height = src.height;
				buffer = src.getRawDataPtr();
				
			}

			Array & operator = (const Array<T> & right) {

				//an paei na antigrapsei ton eauto tou ston eauto tou,agnoise kai min kaneis tipota
				//theory: sugkrinoume tis dieu8inseis ton 2 antikeimenon
				//theory:An einai idies,prokeite gia auto-anauesi,opote den kanoume tipota
				if (&right == this) {
					return *this;
				}

				width = right.width;
				height = right.height;
				buffer = src.getRawDataPtr();
				
				return *this;//dereference//gia na min einai pleon pointer//8eloume Image & //this=to diko mou stigmiotipo
			}

			T & operator () (int x, int y) {//gt oxi unsigned int

				if ((x <= width) && (y <= height) && (x >= 0) && (y >= 0)) {
					return buffer[y*width + x];//briskoume to synoliko with-row mias seiras kai prs8etoume to height,x-1=mia 8esi tou pinaka poio pano //kai stin idia seira tou width,bazoume to width pou mas erxetai kai y-1,gt o pinakas c++ start from 0 and no 1//(WithAll*RowHeiht-1)+ColumnWidth
				}
				else {
					cerr << "out of bounds." << endl;
					system("PAUSE");
					exit(1);
				}
			}

			Array(unsigned int width, unsigned int height, const vector<T> data_ptr) {
				this->width = width;
				this->height = height;
				setData(data_ptr);
			}

			virtual ~Array() {
				//delete[] buffer;
				vector<T> tempvector;
				buffer.swap(tempvector);
			}

			/*! Returns the width of the image
			*/
			const unsigned int getWidth() const { return width; }

			/*! Returns the height of the image
			*/
			const unsigned int getHeight() const { return height; }

			vector<T> getRawDataPtr() const{
				return buffer;
			}

			T getElement(unsigned int x, unsigned int y) const {

				if ((x <= width) && (y <= height) && (x >= 0) && (y >= 0)) {
					return buffer[y*width + x];
				}
				else {
					cout << "ERROR AT GET_ELEMENT!!!" << endl;
					system("PAUSE");
				}

			}

			void setElement(unsigned int x, unsigned int y, T & value) {
				if ((x <= width) && (y <= height) && (x >= 0) && (y >= 0)) {
					buffer[y*width + x] = value;
				}
				else {
					cout << "Width or heigth out of bounds!" << endl;
					system("PAUSE");
				}
			}

			//exo kanei desmesei enos pinaka toy sostoy megethous sto esoteriko tis eikonas mou kai tote exo tin dinatotita
			//toe mporo na paro apo to e3oteriko=data_ptr kai na ta balo mesa
			//antigrafi ,den 8a poume isi,oxi bffer_ptr=data_ptr,8eloume depcopie,oxi stin idia mnimi

			
			void setData(const vector<T> & data_ptr) {
				//If the image buffer is not allocated or the
				//*  width or height of the image are 0, the method should exit immediately.!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				if (width == 0 || height == 0) {//|| data_ptr == nullptr DE DOULEUEI!!!
					return;
				}

				int sizeArrayColor = width * height;

				buffer = vector<Color>(sizeArrayColor);

				for (int i = 0; i < sizeArrayColor; i++) {
					buffer[i] = data_ptr[i];
				}
			}
		};
	}
#endif