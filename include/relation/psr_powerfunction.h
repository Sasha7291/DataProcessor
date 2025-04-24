#pragma once

#include "psr_relation.h"


namespace psr
{

template<class T>
class PowerFunction : public Relation<T>
{

public:
    PowerFunction(T from, T to) noexcept;
    ~PowerFunction() noexcept = default;

    [[nodiscard(R"(Time complexity O(size))")]] std::pair<OutputRange<double>, OutputRange<T>> operator()(std::size_t size, double k, double b) const noexcept;

};

template<class T>
PowerFunction<T>::PowerFunction(T from, T to) noexcept
    : Relation<T>(from, to)
{}

template<class T>
std::pair<OutputRange<double>, OutputRange<T>> PowerFunction<T>::operator()(std::size_t size, double k, double b) const noexcept
{
    return Relation<T>::operator()(size, [k, b](double x) -> T {
        return k * std::pow(x, b);
    });
}

}
