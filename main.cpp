#include <iostream>
#include "src/Atmosphere.h"

int main() {
    Atmosphere A = Atmosphere();
    std::cout << A.calculate(20000)[2] << std::endl;
    return 0;
}
