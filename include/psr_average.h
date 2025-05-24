#pragma once

#include "psr_common.h"


namespace psr
{

template<class T>
class Average
{

public:
    Average() = default;
    ~Average() = default;

    [[nodiscard(R"(Time omplexity O(data.size()))")]] double operator()(ConstInputRange<T> data) const;
    [[nodiscard(R"(Time complexity O(data.size()))")]] double operator()(ConstInputRange<T> weights, ConstInputRange<T> data) const;
    [[nodiscard(R"(Time complexity O(data.size()))")]] double operator()(ConstInputRange<T> data, int n) const;

};

template<class T>
double Average<T>::operator()(ConstInputRange<T> data) const
{
    return std::accumulate(data.cbegin(), data.cend(), 0.0) / data.size();
}

template<class T>
double Average<T>::operator()(ConstInputRange<T> weights, ConstInputRange<T> data) const
{
    return std::transform_reduce(data.cbegin(), data.cend(), weights.cbegin(), 0.0, std::plus<>(), std::multiplies<>())
        / std::accumulate(weights.cbegin(), weights.cend(), 0.0);
}

template<class T>
double Average<T>::operator()(ConstInputRange<T> data, int n) const
{
    return std::pow(
        std::transform_reduce(data.cbegin(), data.cend(), 0.0, std::plus<>(), std::bind(static_cast<double(*)(double, int)>(std::pow), std::placeholders::_1, n)) / data.size(),
        1.0 / n
    );
}

}
