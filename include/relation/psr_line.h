#pragma once

#include "psr_relation.h"


namespace psr
{

template<class T>
class Line : public Relation<T>
{

public:
    Line(T from, T to);
    ~Line() = default;

    [[nodiscard(R"(Time complexity O(size))")]] std::pair<OutputRange<double>, OutputRange<T>> operator()(
        std::size_t size,
        double k,
        double b
    ) const;

};

template<class T>
Line<T>::Line(T from, T to)
    : Relation<T>{from, to}
{}

template<class T>
std::pair<OutputRange<double>, OutputRange<T>> Line<T>::operator()(
    std::size_t size,
    double k,
    double b
) const
{
    return Relation<T>::operator()(size, [k, b](double x) -> T {
        return k * x + b;
    });
}

}
