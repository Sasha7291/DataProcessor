#pragma once

#include "psr_average.h"


namespace psr
{

template<class T>
class Covariance
{

public:
    Covariance(double averageX, double averageY);
    Covariance();
    ~Covariance() = default;

    [[nodiscard(R"(Time complexity O(x.size()))")]] T operator()(ConstInputRange<T> x, ConstInputRange<T> y) const;

private:
    std::optional<double> averageX_;
    std::optional<double> averageY_;

};

template<class T>
Covariance<T>::Covariance(double averageX, double averageY)
    : averageX_{std::make_optional(averageX)}
    , averageY_{std::make_optional(averageY)}
{}

template<class T>
Covariance<T>::Covariance()
    : averageX_{std::nullopt}
    , averageY_{std::nullopt}
{}

template<class T>
T Covariance<T>::operator()(ConstInputRange<T> x, ConstInputRange<T> y) const
{
    auto averX = averageX_.has_value() ? averageX_.value() : Average<T>{}(x);
    auto averY = averageY_.has_value() ? averageY_.value() : Average<T>{}(y);

    return std::transform_reduce(x.cbegin(), x.cend(), y.cbegin(), 0.0, std::plus<>(), [averX, averY](T val1, T val2) -> T {
        return (val1 - averX) * (val2 - averY);
    }) / x.size();
}

}
