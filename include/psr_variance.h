#pragma once

#include "psr_average.h"


namespace psr
{

template<class T>
class Variance
{

public:
    explicit Variance(double average);
    Variance();
    ~Variance() = default;

    [[nodiscard(R"(Time complexity O(data.size()))")]] double operator()(ConstInputRange<T> data) const;

private:
    std::optional<double> average_;

};

template<class T>
Variance<T>::Variance(double average)
    : average_{std::make_optional(average)}
{}

template<class T>
Variance<T>::Variance()
    : average_{std::nullopt}
{}

template<class T>
double Variance<T>::operator()(ConstInputRange<T> data) const
{
    OutputRange<T> discrepancy;
    discrepancy.reserve(data.size());

    auto aver = average_.has_value() ? average_.value() : Average<T>{}(data);
    std::ranges::transform(data, std::back_inserter(discrepancy), std::bind(std::minus<>(), std::placeholders::_1, aver));

    return std::pow(Average<T>{}(discrepancy, 2), 2.0);
}

}
