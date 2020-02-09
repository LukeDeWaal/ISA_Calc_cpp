//
// Created by lucky on 12/09/2019.
//

#ifndef ISACPP_LAYER_H
#define ISACPP_LAYER_H

#include <iostream>
#include <cmath>
#include <array>

class Layer {
private:

    // Define constants and se up all other important variables
    double g0 = 9.80665;
    double R = 287.0;
    double gamma = 1.4;
    double h0, h1, T0, T1, p0, d0, L;

    std::string name;

    // Helper Methods
    double lapserate() {
        return (this->T1 - this->T0) / (this->h1 - this->h0);
    }

    double temperature(double h) {
        if (this->L == 0) {
            return this->T0;
        } else {
            return this->T0 + this->L * (h - this->h0);
        }
    }

public:
    // Constructors
    Layer(double h0, double h1, double T0, double T1, double p0, double d0, std::string name = "Unnamed") {

        this->name = std::move(name);

        this->h0 = h0;
        this->h1 = h1;
        this->d0 = d0;
        this->p0 = p0;
        this->T0 = T0;
        this->T1 = T1;
        this->L = this->lapserate();

    }

    Layer() = default;

    // Main function to calculate Temperature, Pressure and Density within a layer
    std::array<double, 3> calculate(double h) {
        double T, p, d;

        if (this->L == 0) {
            T = this->T0;
            p = this->p0 * exp(-this->g0 / (this->R * this->T0) * (h - this->h0));
            d = this->d0 * exp(-this->g0 / (this->R * this->T0) * (h - this->h0));
        } else {
            double C = -this->g0 / (this->L * this->R);
            T = this->temperature(h);
            p = this->p0 * pow((T / this->T0), C);
            d = this->d0 * pow((T / this->T0), C - 1);
        }
        std::array<double, 3> values = {T, p, d};
        return values;
    }

    // Method to return the floor values of the layer
    std::array<double, 3> get_floor_values() {
        std::array<double, 3> floor_vals = {this->T0, this->p0, this->d0};
        return floor_vals;
    }

    // Method to return the ceiling values of the layer
    std::array<double, 3> get_ceiling_values() {
        std::array<double, 3> ceil_values = this->calculate(this->h1);
        return ceil_values;
    }

    // Method to return the total height of the layer
    std::array<double, 2> get_layer_heights() {
        std::array<double, 2> heights = {this->h0, this->h1};
        return heights;
    }

    // Method to return the name of the layer
    std::string get_name() {
        return this->name;
    }

    // Method to set the name of the layer
    void set_name(std::string &name) {
        this->name = name;
    }

};

#endif //ISACPP_LAYER_H
