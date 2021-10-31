#include "pricingmath.hpp"

namespace PricingMath {

double vectorMean(const std::vector<double>& vec) {
    return std::reduce(vec.begin(), vec.end()) / vec.size();
}

double calculateTotalMeanDeviation(const std::vector<double>& vec) {
    double total = 0.0;
    double total_sq = 0.0;
    for (const auto& num : vec) {
        total += num;
        total_sq += num * num;
    }
    return total_sq - total * total / vec.size();
}

double sampleStandardDeviation(const std::vector<double>& vec) {
    assert(vec.size() > 1 && "Cannot calculate sample std deviation with vector size less than 1");
    return sqrt(calculateTotalMeanDeviation(vec) / vec.size() - 1);
}

double populationStandardDeviation(const std::vector<double>& vec) {
    return sqrt(calculateTotalMeanDeviation(vec) / vec.size());
}

std::vector<double> getNRandomNumbers(const size_t n) {
    static std::random_device dev;
    static std::mt19937 rng(dev());
    static std::uniform_int_distribution<std::mt19937::result_type> dist;
    std::vector<double> ret(n);
    for (size_t i = 0; i < n; ++i) {
        ret[i] = dist(rng);
    }
    return ret;
}

}
