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

static inline double hornerFunction(double, double a1) {
    return a1;
}

template<typename ...Args>
static inline double hornerFunction(double x, double a0, Args&&... args) {
    return a0 + x * hornerFunction(x, std::forward<double>(args)...);
}

double normCDF(const double x) { // normalised cumulative density function
    if (x > 0) return 1 - normCDF(-x);
    const double k = 1 / (1 + 0.2316419 * x);
    const double k_polynomial = hornerFunction(
        k,
        0.0,
        0.319381530,
        -0.356563782,
        1.781477937,
        -1.821255978,
        1.330274429
    );
    const double approximation = 1.0 - 1.0 / ROOT_2_PI * exp(-0.5*x*x) * k_polynomial;
    return approximation;
}

std::vector<double> getNRandomNumbers(const size_t n) {
    static std::random_device dev;
    static std::mt19937 rng(dev());
    static std::uniform_real_distribution<double> dist(-1, 1);
    std::vector<double> ret(n);
    for (size_t i = 0; i < n; ++i) {
        ret[i] = dist(rng);
    }
    return ret;
}

std::vector<double> createLinearSequence(const double from, const double to, const size_t num_pts) {
    assert(num_pts > 2 && "Cannot create linear sequence from less than 3 points");
    std::vector<double> ret(num_pts);
    const double step = (to - from) / (num_pts - 1);
    double curr = from;
    for (size_t i = 0; i < num_pts; ++i) {
        ret[i] = curr;
        curr += step;
    }
    return ret;
}

}
