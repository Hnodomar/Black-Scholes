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
// Moro's algorithm constants
inline static constexpr double a0 = 2.50662823884;
inline static constexpr double a1 = -18.61500062529;
inline static constexpr double a2 = 41.39119773534;
inline static constexpr double a3 = -25.44106049637;
inline static constexpr double b1 = -8.47351093090;
inline static constexpr double b2 = 23.08336743743;
inline static constexpr double b3 = -21.06224101826;
inline static constexpr double b4 = 3.13082909833;
inline static constexpr double c0 = 0.3374754822726147;
inline static constexpr double c1 = 0.9761690190917186;
inline static constexpr double c2 = 0.1607979714918209;
inline static constexpr double c3 = 0.0276438810333863;
inline static constexpr double c4 = 0.0038405729373609;
inline static constexpr double c5 = 0.0003951896511919;
inline static constexpr double c6 = 0.0000321767881768;
inline static constexpr double c7 = 0.0000002888167364;
inline static constexpr double c8 = 0.0000003960315187;

double vectorMean(const std::vector<double>& vec);
double sampleStandardDeviation(const std::vector<double>& vec);
double populationStandardDeviation(const std::vector<double>& vec);
double normCDF(const double x);
double normInverse(const double x);
std::vector<double> getNRandomNumbers(const size_t n);
std::vector<double> createLinearSequence(const double from, const double to, const size_t num_pts);

}
#endif
