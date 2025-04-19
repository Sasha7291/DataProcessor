#include "psr_relation.h"


namespace psr
{

template<class T>
Relation<T>::Relation(T from, T to) noexcept
    : range_(std::make_pair(from, to - from))
{}

template<class T>
std::pair<OutputRange<T>, OutputRange<double>> Relation<T>::operator()(std::size_t size, const std::function<double (double)> &func)
{
    OutputRange<double> resultX;
    resultX.reserve(size);
    std::ranges::generate(std::back_inserter(resultX), [this, size, i = 0]() mutable -> double {
        return static_cast<T>(i++ * range_.second / static_cast<double>(size) + range_.first);
    });

    OutputRange<T> resultY;
    resultY.reserve(size);
    std::ranges::transform(resultX, std::back_inserter(resultY), func);

    return std::make_pair(resultX, resultY);
}

}
