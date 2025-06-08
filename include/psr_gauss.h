#pragma once

#include "psr_common.h"


namespace psr
{

template<class T>
class Gauss
{

public:
    Gauss(std::size_t width) noexcept;
    Gauss() noexcept;
    ~Gauss() noexcept = default;

    [[nodiscard(R"(Time complexity O(data.size()))")]] T operator()(ConstInputRange<T> data) const noexcept;

private:
    [[nodiscard(R"(Time complexity O(data.size()))")]] OutputRange<double> kernel(std::size_t width) const noexcept;

    std::optional<OutputRange<double>> kernel_;

};

template<class T>
Gauss<T>::Gauss(std::size_t width) noexcept
    : kernel_{std::make_optional(kernel(width))}
{}

template<class T>
Gauss<T>::Gauss() noexcept
    : kernel_{std::nullopt}
{}

template<class T>
T Gauss<T>::operator()(ConstInputRange<T> data) const noexcept
{
    return std::transform_reduce(data.cbegin(), data.cend(), kernel_.has_value() ? kernel_.value().cbegin() : kernel(data.size()).cbegin(), 0.0, std::plus<>(), std::multiplies<>());
}

template<class T>
OutputRange<double> Gauss<T>::kernel(std::size_t width) const noexcept
{
    const double sigma2 = 2 * std::pow((width - 1) / 6.0, 2);
    OutputRange<double> result;
    result.reserve(width);

    for (long long i = -static_cast<long long>(width / 2); i <= static_cast<long long>(width / 2); ++i)
        result.push_back(std::exp(-std::pow(i, 2) / sigma2));

    const auto sum = std::accumulate(result.cbegin(), result.cend(), 0.0);
    std::ranges::transform(result, result.begin(), std::bind(std::divides<>(), std::placeholders::_1, sum));

    return result;
}

}
