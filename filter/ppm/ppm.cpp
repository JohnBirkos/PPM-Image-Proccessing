#include <iostream>
#include <fstream>
#include <string>

#include "ppm.h"

using namespace std;
using namespace imaging;

float * imaging::ReadPPM(const char * filename, int * w, int * h) {

	string format = "P6";

	ifstream iFileImage(filename, ios::binary); //open file

	if (!iFileImage.is_open()) {
		cerr << "Error open file" << endl;
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	/*!read the header*/
	string format_myImage;
	int	width
		, height
		, pixel_max;

	iFileImage >> format_myImage;//opos sto cin >> diabasma

	if (format_myImage.compare(format) != 0) {
		cerr << "Error image format (must be 'P6')" << endl;
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	iFileImage >> width >> height >> pixel_max;

	char dummy;///gia na diabasei kai to epomeno meta top 255 pou einai to \n
	iFileImage.read(&dummy, 1);

	if (width < 0 || height < 0)
	{
		cerr << "ppm have wrong informations in width or height" << endl;//if give: -1200 750 
		system("PAUSE");
		exit(EXIT_FAILURE);
	}
	if (pixel_max > 255)
	{
		cerr << "the programm use only 24bit,specifically up to 255. OR ppm does not have all informations";//if give: 1200 750 266
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	*w = width;
	*h = height;

	size_t ImageSize = 3 * height * width;

	unsigned char * buffer_CharArrayImg = new unsigned char[ImageSize];

	iFileImage.read((char *)buffer_CharArrayImg, ImageSize);

	iFileImage.close();
	
	typedef float component_t;
	component_t maxSave255 = 1
		, minSave255 = 0;

	component_t * buffer_CompArrayImg = new component_t[ImageSize];

	for (int i = 0; i < ImageSize; i++) {
		//0-255 mapping=> 0-1f (kanonikopoioisi)
		buffer_CompArrayImg[i] = ((component_t)buffer_CharArrayImg[i])* (component_t)maxSave255 / (component_t)pixel_max;//char ginetai cast se int gia na mporoun na ginoun oi pra3eis
	}

	delete[] buffer_CharArrayImg;

	return buffer_CompArrayImg;
}

bool imaging::WritePPM(const float * data, int w, int h, const char * filename) {

	if (data == nullptr) {
		cerr << "data == nullptr" << endl;
		return false;
	}

	ofstream file(filename, ios::binary);
	if (!file.is_open()) {
		cerr << "Cannot open file" << endl;
		return false;
	}

	file << "P6" << endl;
	file << w;
	file << " ";
	file << h;
	file << endl;
	file << "255" << endl;

	size_t size = w * h * 3;

	int * dataFileNegInt = new int[size];
	unsigned char * dataFileNegChar = new unsigned char[size];

	for (int i = 0; i < size; i++) {
		dataFileNegInt[i] =data[i]*255.0f;
		dataFileNegChar[i] = (unsigned char)dataFileNegInt[i];
	}

	file.write((const char *)dataFileNegChar, size);
	file.flush();//gia na pane kateuthean ta dedomaena

	if (file.fail()) {
		cerr << "Could not write data" << endl;
		return false;
	}
	file.close();

	delete[]dataFileNegInt;
	delete[]dataFileNegChar;

	return true;
}