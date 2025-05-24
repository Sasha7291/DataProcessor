#pragma once

#include "psr_average.h"


namespace psr
{

template<class T>
class RmsRoughness
{

public:
    RmsRoughness() = default;
    ~RmsRoughness() = default;

    [[nodiscard]] double operator()(ConstInputRange<T> y1, ConstInputRange<T> y2) const;

};

template<class T>
double RmsRoughness<T>::operator()(ConstInputRange<T> y1, ConstInputRange<T> y2) const
{
    OutputRange<T> difference;
    difference.reserve(y1.size());
    std::ranges::transform(y1, y2, std::back_inserter(difference), [](double val1, double val2) -> double {
        return std::pow(val1 - val2, 2);
    });

    return Average{}(difference, 2);
}

}
