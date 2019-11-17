//
// Created by lucky on 12/09/2019.
//

#ifndef ISACPP_ATMOSPHERE_H
#define ISACPP_ATMOSPHERE_H

#include <vector>
#include <string>
#include "Layer.h"

class Atmosphere{
private:
    int n_layers = 0;
    double height_range[2] = {0, 0};
    std::vector<double> T;
    std::vector<double> H;
    std::vector<std::string> N;
    double p0, d0;

    std::vector<Layer> layers;

    unsigned int layer_search(double h) {

        unsigned int layer = 0;
        for (unsigned int i = 0; i < this->H.size(); i++) {
            if (this->H[i] <= h && h < this->H[i + 1]) {
                layer = i;
                break;
            } else {
                continue;
            }
        }
        return layer;
    }

public:
    // Constructors
    Atmosphere(){ // Default Constructor
        this->T = {288.15, 216.65, 216.65, 228.65, 270.65, 270.65, 214.65, 186.95, 186.95, 201.95, 251.95};
        this->H = {0, 11000.0, 20000.0, 32000.0, 47000.0, 51000.0, 71000.0, 84852.0, 90000.0, 100000.0, 110000.0};
        this->N = {"Troposphere", "Tropopause", "Stratosphere", "Stratosphere", "Stratopause",
                   "Mesosphere", "Mesosphere", "Mesopause", "Thermosphere", "Thermosphere"};
        this->p0 = 101325.0, this->d0 = 1.225;
        this->construct();
    }

    Atmosphere(std::vector<double>& h, std::vector<double>& T, double p0, double d0){
        this->T = T;
        this->H = h;
        this->p0 = p0;
        this->d0 = d0;

        for(unsigned int i = 0; i < this->T.size(); i++){
            this->N.emplace_back("Layer_"+std::to_string(i));
        }

        this->construct();
    }

    Atmosphere(std::vector<double>& h, std::vector<double>& T, double p0, double d0, std::vector<std::string>& n){
        this->T = T;
        this->H = h;
        this->N = n;
        this->p0 = p0;
        this->d0 = d0;
        this->construct();
    }

    // Method to calculate at a specified height h
    std::array<double, 3> calculate(double h) {
        unsigned int layer_index = this->layer_search(h);
        return this->layers[layer_index].calculate(h);
    }

    // Method to be called when initalizing the atmosphere
    void construct() {

        double p;
        double d;

        p = this->p0;
        d = this->d0;

        std::array<double, 3> ceil_vals{};

        for (unsigned int i = 0; i < this->N.size(); i++) {

            this->layers.emplace_back(Layer(
                    this->H[i],
                    this->H[i + 1],
                    this->T[i],
                    this->T[i + 1],
                    p,
                    d,
                    this->N[i]
            ));
            ceil_vals = this->layers[i].get_ceiling_values();
            p = ceil_vals[1];
            d = ceil_vals[2];
            this->n_layers += 1;
        }
        this->height_range[0] = this->layers[0].get_layer_heights()[0];
        this->height_range[1] = this->layers.back().get_layer_heights()[1];
    }
};

#endif //ISACPP_ATMOSPHERE_H
