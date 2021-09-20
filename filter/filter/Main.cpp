#include <regex>

#include "Array.h"
#include "Image.h"
#include "FilterLinear.h"
#include "FilterGamma.h"
#include "FilterBlur.h"
#include "Filter.h"
#include "FilterLaplace.h"

#include "../ppm/ppm.h"

#include <fstream>
#include <string>
#include <iostream>
using namespace std;

using namespace math;
using namespace imaging;
using namespace filtering;

bool checkFloat(string str);

int main(int argc, char* argv[]){
	string format = "ppm";
	string image = "";
	Image am;

	if (argc < 4) {// only name of application.
		cerr << "Not enough arguments." << endl;
		system("PAUSE");
		return 1;
	}
	else {
		
		image = argv[argc - 1];

		Image *im = new Image();
		bool error;
		error = im->load(image, format);
		
		if (error == false) {
			cerr << "Incompatible format, only the ppm extension is supported for now!!!" << endl;
			system("PAUSE");
		}
		else {
			cout << "Image dimension are: " << im->getHeight() << "x" << im->getWidth() << endl;
			system("PAUSE");
		}

		am = *im;

		int i = 1;

		while (image != argv[i]) {
			
			if (static_cast<string>(argv[i]) == "-f") {
				i++;
				if (static_cast<string>(argv[i]) == "linear") {
					i++;
					float linear_parameters[6];
					for (int j = 0;j < 6;j++) {
						if (checkFloat(argv[i])) {
							float par=stof(argv[i]);
							linear_parameters[j] = par;
							i++;
						}
						else {
							cerr << "Linear filter parameters must be float\nProgram is terminated";
							system("PAUSE");
							return -1;
						}
					}
					//linear filter application
					Color a(linear_parameters[0], linear_parameters[1], linear_parameters[2]);
					Color c(linear_parameters[3], linear_parameters[4], linear_parameters[5]);
					FilterLinear k(a, c);
					am = k.FilterLinear::operator<<(am);
				}
				else if (static_cast<string>(argv[i]) == "gamma") {
					i++;
					float y;
					float parg;

					if (checkFloat(static_cast<string>(argv[i]))) {
						parg = stof(argv[i]);
						if (parg < 0.5 || parg > 2.0) {
							cout << "Typical value for gamma filter parameter is between 0.5 and 2.0" << endl;
							cout << "If you wish to exit the program press 0. Else press any other button to continue" << endl;
							int answer;
							cin >> answer;
							if (answer == 0) {
								return -1;
							}
							else {
								i++;
							}
						}
						else {
							i++;
						}
					}
					else {
						cerr << "Gamma filter parametes must be float\nProgram is terminated";
						system("PAUSE");
						return -1;
					}
					FilterGamma g(parg);
					am = g.FilterGamma::operator<<(am);
				}
				else if (static_cast<string>(argv[i]) == "blur") {
					i++;
					int N;

					if (checkFloat(static_cast<string>(argv[i]))) {
						N = stoi(argv[i]);
						if (N % 2 == 0) {
							cout << "N is Even Number. The pixel is not in center of array" << endl;
							cout << "If you wish to exit the program press 0. Else press any other button to continue" << endl;
							int answer;
							cin >> answer;
							if (answer == 0) {
								return -1;
							}
							else {
								i++;
							}
						}
						else {
							i++; 
						}
					}
					else {
						cerr << "Blur filter parameter must be an integer\nProgram is terminated" << endl;
						system("PAUSE");
						return -1;
					}
					FilterBlur b(N);
					am = b.FilterBlur::operator<<(am);
				}
				else if (static_cast<string>(argv[i]) == "laplace") {
					i++;
					FilterLaplace la;
					am = la.FilterLaplace::operator<<(am);
				}
				else {
					cerr << "String must be equal to a filter name\nProgram is terminated";
					system("PAUSE");
					return -1;
				}
			}
			else {
				cerr << "Filter must begin with -f\nProgram is terminated";
				system("PAUSE");
				return -1;
			}
		}
	}
	string name = "filtered_" + image;
	
	bool flag = am.save(name, format);

	if (flag) {
		cout << "Image is written" << endl;
		system("PAUSE");
	}
	else {
		cout << "Error writing image" << endl;
		system("PAUSE");
	}
}

bool checkFloat(string str) {
	//c++11 regular expression
	//^ = begin of string
	//$ = end of string

	regex reg("^[-+]?[0-9]+(\\.[0-9]+)?$");

	return regex_match(str, reg);
}