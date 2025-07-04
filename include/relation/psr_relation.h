#pragma once

#include "psr_common.h"

#include <QDebug>


namespace psr
{

template<class T>
class Relation
{

public:
    Relation(T from, T to);
    Relation(T fromX, T toX, T fromY, T toY);
    virtual ~Relation() = default;

    [[nodiscard(R"(Time complexity O(size))")]] std::pair<OutputRange<double>, OutputRange<T>> operator()(std::size_t size, const std::function<double(double)> &func) const;
    [[nodiscard(R"(Time complexity O(size))")]] std::tuple<OutputRange<double>, OutputRange<double>, OutputRange<T>> operator()(
        std::size_t sizeX,
        std::size_t sizeY,
        const std::function<double(double,double)> &func
    ) const;

private:
    std::pair<T, T> rangeX_;
    std::pair<T, T> rangeY_;

};

template<class T>
Relation<T>::Relation(T from, T to)
    : rangeX_(std::make_pair(from, to - from))
{}

template<class T>
Relation<T>::Relation(T fromX, T toX, T fromY, T toY)
    : rangeX_(std::make_pair(fromX, toX - fromX))
    , rangeY_(std::make_pair(fromY, toY - fromY))
{}

template<class T>
std::pair<OutputRange<double>, OutputRange<T>> Relation<T>::operator()(std::size_t size, const std::function<double(double)> &func) const
{
    OutputRange<double> resultX(size);
    std::ranges::generate(resultX, [this, size, i = 0]() mutable -> double {
        return i++ * rangeX_.second / static_cast<double>(size) + rangeX_.first;
    });

    OutputRange<T> resultY;
    resultY.reserve(size);
    std::ranges::transform(resultX, std::back_inserter(resultY), func);

    return std::make_pair(resultX, resultY);
}

template<class T>
std::tuple<OutputRange<double>, OutputRange<double>, OutputRange<T>> Relation<T>::operator()(
    std::size_t sizeX,
    std::size_t sizeY,
    const std::function<double(double,double)> &func
) const
{
    OutputRange<double> x(sizeX);

    std::ranges::generate(x, [this, sizeX, i = 0]() mutable -> double {
        return i++ * rangeX_.second / static_cast<double>(sizeX) + rangeX_.first;
    });

    OutputRange<double> resultX;
    resultX.reserve(sizeX * sizeY);
    for (std::size_t i = 0; i < sizeY; ++i)
        std::ranges::copy(x, std::back_inserter(resultX));

    OutputRange<double> resultY;
    resultY.reserve(sizeX * sizeY);
    for (std::size_t i = 0; i < sizeX; ++i)
        std::ranges::copy(
            OutputRange<double>(sizeY, i * rangeY_.second / static_cast<double>(sizeY) + rangeY_.first),
            std::back_inserter(resultY)
        );

    OutputRange<T> resultZ;
    resultZ.reserve(sizeX * sizeY);
    for (std::size_t i = 0; i < sizeY; ++i)
        for (std::size_t j = 0; j < sizeX; ++j)
            resultZ.push_back(func(x[j], resultY[i * sizeX + j]));

    return std::make_tuple(resultX, resultY, resultZ);
}

}
