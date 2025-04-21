#pragma once

#include "psr_common.h"

#include <QDebug>


namespace psr
{

template<class T>
class Gauss
{

public:
    Gauss(unsigned width) noexcept;
    Gauss() noexcept;
    ~Gauss() noexcept = default;

    [[nodiscard(R"(Time complexity O(data.size()))")]] T operator()(ConstInputRange<T> data) const noexcept;

private:
    [[nodiscard(R"(Time complexity O(data.size()))")]] OutputRange<double> kernel(int width) const noexcept;

    std::optional<OutputRange<double>> kernel_;

};

template<class T>
Gauss<T>::Gauss(unsigned width) noexcept
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
OutputRange<double> Gauss<T>::kernel(int width) const noexcept
{
    const double sigma2 = 2 * std::pow((width - 1) / 6.0, 2);
    OutputRange<double> result;
    result.reserve(width);

    for (int i = -width / 2; i <= width / 2; ++i)
        result.push_back(std::exp(-std::pow(i, 2) / sigma2));

    std::ranges::transform(result, result.begin(), [sum = std::accumulate(result.cbegin(), result.cend(), 0.0)](double value) -> double {
        return value / sum;
    });

    return result;
}

}
