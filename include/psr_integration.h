#pragma once

#include "psr_common.h"


namespace psr
{

template<class T>
class Integration
{

public:
    Integration() = default;
    ~Integration() = default;

    [[nodiscard(R"(Time complexity O(data.size()))")]] double operator()(ConstInputRange<T> x, ConstInputRange<T> y) const;

};

template<class T>
double Integration<T>::operator()(ConstInputRange<T> x, ConstInputRange<T> y) const
{
    double result = 0.0;

    for (auto i = 1; i < x.size() - 1; ++i)
        result += 0.5 * (y[i] + y[i + 1]) * (x[i + 1] - x[i]);

    return result;
}

}
