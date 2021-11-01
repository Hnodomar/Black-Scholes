#include <iostream>
#include <string_view>
#include <algorithm>
#include <fstream>

#include "pricingmath.hpp"
#include "BlackScholesModel.hpp"

void generatePricePathData() {
    const BlackScholesModel bsm(0, 100.0, 0.1, 0.05, 2.0);
    const std::size_t num_steps = 1000;
    const double maturity = 4.0;
    const std::vector<double> path(bsm.generatePricePath(maturity, num_steps));
    const double dt = (maturity - 2.0) / num_steps;
    const std::vector<double> times(PricingMath::createLinearSequence(dt, maturity, num_steps));
    std::ofstream out("../../tests/pricepath.dat", std::ios_base::out);
    if (out.is_open()) {
        for (size_t i = 0; i < path.size(); ++i) {
            out << path[i] << " " << times[i] << "\n";
        }
    }
    else 
        throw std::runtime_error("Failed to open file pricepath.dat");
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Must call with any of the following optional arguments:\n";
        std::cout << "-PricePath\n";
        return 1;
    }
    const auto argExists = [&](const std::string_view& arg) {
        return std::find(argv, argv + argc, arg) != argv + argc;
    };
    if (argExists("-PricePath")) {
        std::cout << "Generating price path data in file pricepath.dat..\n";
        generatePricePathData();
        std::cout << "Generated price path data\n";
    }
    return 0;
}
