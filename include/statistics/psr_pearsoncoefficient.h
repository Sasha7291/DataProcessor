#pragma once

#include "psr_average.h"
#include "psr_variance.h"


namespace psr
{

template<class T>
class PearsonCoefficient
{

public:
    PearsonCoefficient(double averageX, double averageY, double varianceX, double varianceY) noexcept;
    PearsonCoefficient() noexcept;
    ~PearsonCoefficient() noexcept = default;

    [[nodiscard(R"(Time complexity O(x.size()))")]] double operator()(ConstInputRange<T> x, ConstInputRange<T> y) const noexcept;

private:
    std::optional<double> averageX_;
    std::optional<double> averageY_;
    std::optional<double> varianceX_;
    std::optional<double> varianceY_;

};

template<class T>
PearsonCoefficient<T>::PearsonCoefficient(double averageX, double averageY, double varianceX, double varianceY) noexcept
    : averageX_{std::make_optional(averageX)}
    , averageY_{std::make_optional(averageY)}
    , varianceX_{std::make_optional(varianceX)}
    , varianceY_{std::make_optional(varianceY)}
{}

template<class T>
PearsonCoefficient<T>::PearsonCoefficient() noexcept
    : averageX_{std::nullopt}
    , averageY_{std::nullopt}
    , varianceX_{std::nullopt}
    , varianceY_{std::nullopt}
{}

template<class T>
double PearsonCoefficient<T>::operator()(ConstInputRange<T> x, ConstInputRange<T> y) const noexcept
{
    auto averX = averageX_.has_value() ? averageX_.value() : Average<T>{}(x);
    auto averY = averageY_.has_value() ? averageY_.value() : Average<T>{}(y);

    return std::transform_reduce(x.cbegin(), x.cend(), y.cbegin(), 0.0, std::plus<>(), [averX, averY](T val1, T val2) -> T {
        return (val1 - averX) * (val2 - averY);
    }) / (x.size() * (varianceX_.has_value() ? varianceX_.value() : Variance<T>{averX}(x)) * (varianceY_.has_value() ? varianceY_.value() : Variance<T>{averY}(y)));
}

}
