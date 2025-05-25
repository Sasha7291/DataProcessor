#pragma once

#include "psr_average.h"


namespace psr
{

template<class T>
class AverageRoughness
{

public:
    AverageRoughness() = default;
    ~AverageRoughness() = default;

    [[nodiscard]] double operator()(ConstInputRange<T> y1, ConstInputRange<T> y2) const;

};

template<class T>
double AverageRoughness<T>::operator()(ConstInputRange<T> y1, ConstInputRange<T> y2) const
{
    OutputRange<T> difference;
    difference.reserve(y1.size());
    std::ranges::transform(y1, y2, std::back_inserter(difference), [](double value1, double value2) -> double {
        return std::abs(value1 - value2);
    });

    return Average<T>{}(difference);
}

}
