#include "psr_average.h"

#include <cmath>
#include <functional>
#include <numeric>


namespace psr
{

template<class T>
double Average::operator()(ConstInputRange<T> data) const noexcept
{
    return std::accumulate(data.cbegin(), data.cend(), 0.0) / data.size();
}

template<class T>
double Average::operator()(ConstInputRange<T> weights, ConstInputRange<T> data) const noexcept
{
    return std::transform_reduce(data.cbegin(), data.cend(), weights.cbegin(), 0.0, std::plus<>(), std::multiplies<>())
        / std::accumulate(weights.cbegin(), weights.cend(), 0.0);
}

template<class T>
double Average::operator()(ConstInputRange<T> data, unsigned n) const noexcept
{
    return std::pow(
        std::transform_reduce(data.cbegin(), data.cend(), 0.0, std::plus<>(), std::bind(std::pow<double, int>, std::placeholders::_1, n)) / data.size(),
        1.0 / n
    );
}

}

