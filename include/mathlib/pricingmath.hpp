#ifndef PRICING_MATH_HPP
#define PRICING_MATH_HPP

#include <vector>
#include <random>
#include <cmath>
#include <cassert>
#include <numeric>

namespace PricingMath {

double vectorMean(const std::vector<double>& vec);
double sampleStandardDeviation(const std::vector<double>& vec);
double populationStandardDeviation(const std::vector<double>& vec);
std::vector<double> getNRandomNumbers(const size_t n);

}
#endif
