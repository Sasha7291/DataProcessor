#pragma once

#include "psr_common.h"


namespace psr
{

template<class T>
class Relation
{

public:
    Relation(T from, T to) noexcept;
    virtual ~Relation() noexcept = default;

    [[nodiscard(R"(Time complexity O(size))")]] std::pair<OutputRange<double>, OutputRange<T>> operator ()(std::size_t size, const std::function<double(double)> &func) const noexcept;

private:
    std::pair<T, T> range_;

};

template<class T>
Relation<T>::Relation(T from, T to) noexcept
    : range_(std::make_pair(from, to - from))
{}

template<class T>
std::pair<OutputRange<double>, OutputRange<T>> Relation<T>::operator()(std::size_t size, const std::function<double(double)> &func) const noexcept
{
    OutputRange<double> resultX(size);
    std::ranges::generate(resultX, [this, size, i = 0]() mutable -> double {
        return i++ * range_.second / static_cast<double>(size) + range_.first;
    });

    OutputRange<T> resultY;
    resultY.reserve(size);
    std::ranges::transform(resultX, std::back_inserter(resultY), func);

    return std::make_pair(resultX, resultY);
}

}
