#pragma once

#include "psr_relation.h"


namespace psr
{

template<class T>
class Plane : public Relation<T>
{

public:
    Plane(T fromX, T toX, T fromY, T toY);
    ~Plane() = default;

    [[nodiscard(R"(Time complexity O(size))")]] std::tuple<OutputRange<double>, OutputRange<double>, OutputRange<T>> operator()(
        std::size_t sizeX,
        std::size_t sizeY,
        double k1,
        double k2,
        double b
    ) const;

};

template<class T>
std::tuple<OutputRange<double>, OutputRange<double>, OutputRange<T>> Plane<T>::operator()(
    std::size_t sizeX,
    std::size_t sizeY,
    double k1,
    double k2,
    double b
) const
{
    return Relation<T>::operator()(sizeX, sizeY, [k1, k2, b](double x, double y) -> T {
        return k1 * x + k2 * y + b;
    });
}

}
