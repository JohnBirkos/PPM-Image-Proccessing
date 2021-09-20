#include <fstream>
#include <string>
#include <sstream>

#include "../ppm/ppm.h"
#include "Image.h"

#include "Vec3.h"
#include "Array.h"

#include <iostream>

using namespace std;

using namespace math;
using namespace imaging;

	Image::Image() {
		Array();
	}

	Image::Image(unsigned int width, unsigned int height) {
		Array(width, height);
	}

	Image::Image(const Image &src) {
		width = src.width;
		height = src.height;
		buffer = src.getRawDataPtr();
	}

	Image & Image::operator = (const Image & right) {

		//an paei na antigrapsei ton eauto tou ston eauto tou,agnoise kai min kaneis tipota
		//theory: sugkrinoume tis dieu8inseis ton 2 antikeimenon
		//theory:An einai idies,prokeite gia auto-anauesi,opote den kanoume tipota
		if (&right == this) {
			return *this;
		}

		width = right.width;
		height = right.height;
		buffer = right.getRawDataPtr();

		return *this;//dereference//gia na min einai pleon pointer//8eloume Image & //this=to diko mou stigmiotipo
	}

	Image::Image(unsigned int width, unsigned int height, const vector<Color> data_ptr) {
		this->width = width;
		this->height = height;
		setData(data_ptr);
	}
	
	Image::~Image() {
		
	}


	vector<Color> Image::getRawDataPtr() const{
		return buffer;
	}

	Color Image::getPixel(unsigned int x, unsigned int y) const {

		Color c(0, 0, 0);
		
		if ((x <= width) && (y <= height) && (x >= 0) && (y >= 0)) {
			return buffer[y*width + x];
		}
		else {
			cout << "ERROR AT GET_ELEMENT!!!" << endl;
			system("PAUSE");
			return c;
		}
	}

	void Image::setPixel(unsigned int x, unsigned int y, Color & value) {
		
		if ((x <= width) && (y <= height) && (x >= 0) && (y >= 0)) { // && (buffer != nullptr)  DE DOULEUEI!!!
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

	void Image::setData(const vector<Color> & data_ptr) {
		//If the image buffer is not allocated or the
		//*  width or height of the image are 0, the method should exit immediately.!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		if (width == 0 || height == 0) {
			return;
		}
		int sizeArrayColor = width * height;

		buffer = vector<Color>(sizeArrayColor);
		for (int i = 0; i < sizeArrayColor; i++) {
			buffer[i] = data_ptr[i];
		}
	}

	bool Image::load(const std::string & filename, const std::string & format) {

		string myFormat= filename.substr(filename.find(".") + 1, std::string::npos);
		
		if (myFormat != format) {
			return false;
		}

		component_t* fbuff = ReadPPM(filename.c_str(), (int*)&width, (int*)&height);
		
		vector<Color> mybuffer = vector<Color>(width*height);

		int countArray = 0;
	
		for (int i = 0; i < width * height * 3; i = i + 3) {
			
			Color c(fbuff[i], fbuff[i+1], fbuff[i+2]);
			mybuffer[countArray] = c;
			countArray++;

		}

		const vector<Color> mybuffer1 = mybuffer;

		setData(mybuffer1);

		delete[]fbuff;
		//mybuffer.clear();

		return true;
	}

	bool Image::save(const std::string & filename, const std::string & format) {

		string myFormat = filename.substr(filename.find(".") + 1, std::string::npos);

		if (myFormat != format) {
			return false;
		}

		component_t* fbuff = new component_t[width * height * 3];
		
		int count = 0;
		Color col(1, 1, 1);
		for (int i = 0; i < width*height*3; i+=3) {
			Color c = buffer[count];
			fbuff[i] = c[0];
			fbuff[i + 1] = c[1];
			fbuff[i + 2] = c[2];
			count++;
		}
		
		bool flag = WritePPM(fbuff, (int)width, (int)height, filename.c_str());

		delete[]fbuff;

		return flag;
	}

	

