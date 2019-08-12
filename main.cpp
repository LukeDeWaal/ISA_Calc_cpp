#include <iostream>
#include <cmath>
#include <array>
#include <vector>
#include <typeinfo>
#include "Layer.h"


class Atmosphere {

    std::vector<double> T = {288.15, 216.65, 216.65, 228.65, 270.65, 270.65, 214.65, 186.95, 186.95, 201.95, 251.95};
    std::vector<double> H = {0, 11000.0, 20000.0, 32000.0, 47000.0, 51000.0, 71000.0, 84852.0, 90000.0, 100000.0,
                             110000.0};
    std::vector<std::string> N = {"Troposphere", "Tropopause", "Stratosphere", "Stratosphere", "Stratopause",
                                  "Mesosphere", "Mesosphere", "Mesopause", "Thermosphere", "Thermosphere"};
    double p0 = 101325.0, d0 = 1.225;

    std::array<Layer, 10> layers;

    int layer_search(double h) {

        int layer = 0;
        for (int i = 0; i < this->H.size(); i++) {
            if (this->H[i] <= h < this->H[i + 1]) {
                layer = i;
                break;
            } else {
                continue;
            }
        }
        return layer;
    }


public:

    Atmosphere() {
        this->construct();
    }

    std::array<double, 3> calculate(double h) {
        int layer_index = this->layer_search(h);
        return this->layers[layer_index].calculate(h);
    }

    void set_new_atmosphere(
            std::vector<double> T = {},
            std::vector<double> H = {},
            double p0 = 0, double d0 = 0,
            std::vector<std::string> N = {}
    ) {
        if (not T.empty()){
            this->T = T;
        }
        else{
            throw "Empty Temperatures Vector Given!";
        }
        if (not H.empty()){
            this->H = H;
        }
        else{
            throw "Empty Heights Vector Given!";
        }
        if (not N.empty()){
            this->N = N;
        }
        else{
            throw "Empty Name Vector Given!";
        }
        this->p0 = p0;
        this->d0 = d0;

        this->construct();
    }

    void construct() {

        double p;
        double d;

        p = this->p0;
        d = this->d0;

        std::array<double, 3> ceil_vals;

        for (int i = 0; i < this->N.size(); i++) {

            this->layers[i] = Layer(
                    this->H[i],
                    this->H[i + 1],
                    this->T[i],
                    this->T[i + 1],
                    p,
                    d,
                    this->N[i]
            );
            ceil_vals = this->layers[i].get_ceiling_values();
            p = ceil_vals[1];
            d = ceil_vals[2];
        }
    }
};

int main() {

    std::vector<double> T = {218.15, 200.65, 216.65, 228.65, 240.65, 270.65, 214.65, 186.95, 186.95, 201.95, 251.95};
    std::vector<double> H = {0, 11000.0, 20000.0, 32000.0, 47000.0, 49000.0, 71000.0, 84852.0, 90000.0, 100000.0,
                             110000.0};
    std::vector<std::string> N = {"Troposphere", "Tropopause", "Stratosphere", "Stratosphere", "Stratopause",
                                  "Mesosphere", "Mesosphere", "Mesopause", "Thermosphere", "Thermosphere"};
    double p0 = 90000.0, d0 = 1.0;

    Atmosphere Atmos = Atmosphere();
    std::cout << Atmos.calculate(12000.0)[1] << std::endl;
    Atmos.set_new_atmosphere(T, H, p0, d0, N);
    std::cout << Atmos.calculate(12000.0)[1] << std::endl;
    return 0;
}