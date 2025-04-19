#include "psr_gauss.h"

namespace psr
{

Gauss::Gauss(unsigned width) noexcept
    : kernel_{std::make_optional(kernel(width))}
{}

Gauss::Gauss() noexcept
    : kernel_{std::nullopt}
{}

template<class T>
T Gauss::operator()(ConstInputRange<T> data) const noexcept
{
    return std::transform_reduce(data.cbegin(), data.cend(), kernel_.has_value() ? kernel_.value().cbegin() : kernel(data.size()).cbegin(), 0.0, std::plus<>(), std::multiplies<>());
}

OutputRange<double> Gauss::kernel(unsigned width) const noexcept
{
    const unsigned center = width / 2;
    const double sigma2 = 2 * std::pow((width - 1) / 6.0, 2);
    OutputRange<double> result;
    result.reserve(width);

    for (auto i = -width / 2; i < width / 2; ++i)
        result.push_back(std::exp(-std::pow(i - center, 2) / sigma2));

    std::ranges::transform(result, result.begin(), [sum = std::accumulate(result.cbegin(), result.cend(), 0.0)](double value) -> double {
        return value / sum;
    });

    return result;
}

}
