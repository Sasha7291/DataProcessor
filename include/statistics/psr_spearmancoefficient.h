#pragma once

#include "psr_covariance.h"
#include "psr_rank.h"
#include "psr_variance.h"


namespace psr
{

template<class T>
class SpearmanCoefficient
{

public:
    SpearmanCoefficient(double averageX, double averageY, double varianceX, double varianceY) noexcept;
    SpearmanCoefficient() noexcept;
    ~SpearmanCoefficient() noexcept = default;

    [[nodiscard(R"(Time complexity O(data.size()))")]] double operator()(ConstInputRange<T> x, ConstInputRange<T> y) const noexcept;

private:
    std::optional<double> averageX_;
    std::optional<double> averageY_;
    std::optional<double> varianceX_;
    std::optional<double> varianceY_;

};

template<class T>
SpearmanCoefficient<T>::SpearmanCoefficient(double averageX, double averageY, double varianceX, double varianceY) noexcept
    : averageX_{std::make_optional(averageX)}
    , averageY_{std::make_optional(averageY)}
    , varianceX_{std::make_optional(varianceX)}
    , varianceY_{std::make_optional(varianceY)}
{}

template<class T>
SpearmanCoefficient<T>::SpearmanCoefficient() noexcept
    : averageX_{std::nullopt}
    , averageY_{std::nullopt}
    , varianceX_{std::nullopt}
    , varianceY_{std::nullopt}
{}

template<class T>
double SpearmanCoefficient<T>::operator()(ConstInputRange<T> x, ConstInputRange<T> y) const noexcept
{
    auto rankX = Rank<T>{}(x);
    auto rankY = Rank<T>{}(y);
    double averX = averageX_.has_value() ? averageX_.value() : Average<double>{}(rankX);
    double averY = averageY_.has_value() ? averageY_.value() : Average<double>{}(rankY);
    double varX = varianceX_.has_value() ? varianceX_.value() : Variance<double>{averX}(rankX);
    double varY = varianceY_.has_value() ? varianceY_.value() : Variance<double>{averY}(rankY);
    double result = Covariance<double>{averX, averY}(rankX, rankY) / (varX * varY);

    return result;
}

}
