#include "pricingmath.hpp"
#include <iostream>

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
    return sqrt(calculateTotalMeanDeviation(vec) / (vec.size() - 1));
}

double populationStandardDeviation(const std::vector<double>& vec) {
    return sqrt(calculateTotalMeanDeviation(vec) / vec.size());
}

static inline double hornerFunction(const double, const double a1) {
    return a1;
}

template<typename ...Args>
static inline double hornerFunction(const double x, const double a0, Args&&... args) {
    return a0 + x * hornerFunction(x, std::forward<const double>(args)...);
}

double normCDF(const double x) { // normalised cumulative density function
    if (x < 0) return 1 - normCDF(-x);
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

double normInverse(const double x) {
    const double y = x - 0.5;
    if (y < 0.42 && y > -0.42) {
        const double r = y * y;
        return y * hornerFunction(r, a0, a1, a2, a3) / hornerFunction(r, 1.0, b1, b2, b3, b4);
    }
    else {
        const double r = y < 0.0 ? x : 1.0 - x;
        const double s = log(-log(r));
        const double t = hornerFunction(s, c0, c1, c2, c3, c4, c5, c6, c7, c8);
        return x > 0.5 ? t : -t;
    }
}

std::vector<double> getNRandomNumbers(const size_t n) {
    static std::random_device dev;
    static std::mt19937 rng(dev());
    //static std::uniform_real_distribution<double> dist(-1, 1);
    std::vector<double> ret(n);
    for (size_t i = 0; i < n; ++i) {
        const double rnum = (rng()+0.5)/ (rng.max()+1.0);
        ret[i] = normInverse(rnum);
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
