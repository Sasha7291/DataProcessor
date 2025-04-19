#pragma once

#include "psr_average.h"


namespace psr
{

template<class T>
class Variance
{

public:
    explicit Variance(double average) noexcept;
    Variance() noexcept;
    ~Variance() noexcept = default;

    [[nodiscard(R"(Time complexity O(data.size()))")]] double operator()(ConstInputRange<T> data) const noexcept;

private:
    std::optional<double> average_;

};

template<class T>
Variance<T>::Variance(double average) noexcept
    : average_{std::make_optional(average)}
{}

template<class T>
Variance<T>::Variance() noexcept
    : average_{std::nullopt}
{}

template<class T>
double Variance<T>::operator()(ConstInputRange<T> data) const noexcept
{
    OutputRange<T> discrepancy;
    discrepancy.reserve(data.size());

    std::ranges::transform(data, std::back_inserter(discrepancy), [aver = average_.has_value() ? average_.value() : Average<T>{}(data)](T value) -> T {
        return value - aver;
    });

    return Average<T>{}(discrepancy, 2);
}

}
