#include <iostream>
#include <string>
#include "src/Atmosphere.h"

int main(int argc, char *argv[]) {

    double hmin, hmax, hstep;

    if (argc == 4) {
        hmin = std::stod(argv[1]);
        hmax = std::stod(argv[2]);
        hstep = std::stod(argv[3]);
    } else {
        hmin = 0;
        hmax = 80000.0;
        hstep = 100.0;
    }

    Atmosphere A = Atmosphere();
    A.print_tabular(hmin, hmax, hstep);

    // Just to keep console window open
    std::cout << "\nPress Enter to Exit" << std::endl;
    std::cin.ignore();

    return 0;
}
