#pragma once

#include "psr_common.h"


namespace psr
{

template<class T>
class Average
{

public:
    Average() noexcept = default;
    ~Average() noexcept = default;


    [[nodiscard(R"(Time omplexity O(data.size()))")]] double operator()(ConstInputRange<T> data) const noexcept;
    [[nodiscard(R"(Time complexity O(data.size()))")]] double operator()(ConstInputRange<T> weights, ConstInputRange<T> data) const noexcept;
    [[nodiscard(R"(Time complexity O(data.size()))")]] double operator()(ConstInputRange<T> data, unsigned n) const noexcept;

};

template<class T>
double Average<T>::operator()(ConstInputRange<T> data) const noexcept
{
    return std::accumulate(data.cbegin(), data.cend(), 0.0) / data.size();
}

template<class T>
double Average<T>::operator()(ConstInputRange<T> weights, ConstInputRange<T> data) const noexcept
{
    return std::transform_reduce(data.cbegin(), data.cend(), weights.cbegin(), 0.0, std::plus<>(), std::multiplies<>())
        / std::accumulate(weights.cbegin(), weights.cend(), 0.0);
}

template<class T>
double Average<T>::operator()(ConstInputRange<T> data, unsigned n) const noexcept
{
    return std::pow(
        std::transform_reduce(data.cbegin(), data.cend(), 0.0, std::plus<>(), std::bind(std::pow<double, int>, std::placeholders::_1, n)) / data.size(),
        1.0 / n
    );
}

}
