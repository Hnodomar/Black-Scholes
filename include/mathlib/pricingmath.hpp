#ifndef PRICING_MATH_HPP
#define PRICING_MATH_HPP

#include <vector>
#include <random>
#include <cmath>
#include <cassert>
#include <numeric>

#define _USE_MATH_DEFINES

namespace PricingMath {

inline static constexpr double ROOT_2_PI = 2.50662827463;

double vectorMean(const std::vector<double>& vec);
double sampleStandardDeviation(const std::vector<double>& vec);
double populationStandardDeviation(const std::vector<double>& vec);
double normCDF(const double x);
std::vector<double> getNRandomNumbers(const size_t n);
std::vector<double> createLinearSequence(const double from, const double to, const size_t num_pts);

}
#endif
