#include <iostream>
#include <string_view>
#include <algorithm>
#include <memory>
#include <fstream>

#include "pricingmath.hpp"
#include "BlackScholesModel.hpp"
#include "hedgingsim.hpp"
#include "calloption.hpp"

void writeData(std::ofstream& out, const size_t i) {
    out << "\n";
}

template<typename ...Data>
void writeData(std::ofstream& out, const size_t i, const std::vector<double>& data, const Data&... args) {
    out << data[i] << " ";
    writeData(out, i, args...);
}

template<typename ...Data>
void writeDataToFile(const std::string& filename, const size_t size, const Data&... args) {
    std::ofstream out(filename, std::ios_base::out);
    if (out.is_open()) {
        for (size_t i = 0; i < size; ++i) {
            writeData(out, i, args...);
        }
    }
    else throw std::runtime_error("Failed to open file " + filename);
}

void generatePricePathData() {
    const OptionPricing::BlackScholesModel bsm(0, 100.0, 0.1, 0.05, 2.0);
    const std::size_t num_steps = 1000;
    const double maturity = 4.0;
    const std::vector<double> path(bsm.generatePricePath(maturity, num_steps));
    const double dt = (maturity - 2.0) / num_steps;
    const std::vector<double> times(PricingMath::createLinearSequence(dt, maturity, num_steps));
    writeDataToFile("../../tests/pricepath.dat", path.size(), path, times);
}

void generateHistogramData() {
    const std::shared_ptr<OptionPricing::BlackScholesModel> bsm(
        std::make_shared<OptionPricing::BlackScholesModel>(
            0.1, 1, 0.2, 0.05, 0
        )
    );
    OptionPricing::HedgingSimulator hedge_sim(
        std::make_shared<OptionPricing::CallOption>(1, 1),
        bsm,
        bsm,
        100
    );
    const std::vector<double> result(hedge_sim.runSimulations(100000));
    writeDataToFile("../../tests/histogram.dat", result.size(), result);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Must call with any of the following optional arguments:\n";
        std::cout << "-PricePath\n" << "-Histogram\n";
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
    if (argExists("-Histogram")) {
        std::cout << "Generating histogram data in histogram.dat..\n";
        generateHistogramData();
        std::cout << "Generated histogram data\n";
    }
    return 0;
}
