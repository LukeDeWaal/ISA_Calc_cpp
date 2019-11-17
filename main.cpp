#include <iostream>
#include <string>
#include "src/Atmosphere.h"

int main(int argc, char* argv[]) {

	double hmin, hmax, hstep;

	if(argc == 4){
		hmin = std::stod(argv[1]);
		hmax = std::stod(argv[2]);
		hstep = std::stod(argv[3]);
	}
	else{
		hmin = 0;
		hmax = 80000.0; 
		hstep = 100.0;
	}

    Atmosphere A = Atmosphere();
    std::array<double, 3> result;
    std::cout << "Height [m] - Temperature [K] - Pressure [Pa] - Density [kg/m^3]" << std::endl;

    for(float h = hmin; h <= hmax; h+=hstep){
        result = A.calculate(h);
        std::cout << h << " - " << result[0] << " - " << result[1] << " - " << result[2] << "\n";
    }

    // Just to keep console window open
    std::cout << "\nPress Enter to Exit" << std::endl;
    std::cin.ignore();


    return 0;
}
