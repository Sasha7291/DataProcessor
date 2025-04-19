#pragma once

#include "psr_rank.h"


namespace psr
{

template<class T>
class SpearmanCoefficient
{

public:
    SpearmanCoefficient(ConstInputRange<unsigned> rankedX, ConstInputRange<unsigned> rankedY) noexcept;
    SpearmanCoefficient() noexcept;
    ~SpearmanCoefficient() noexcept = default;

    [[nodiscard(R"(Time complexity O(data.size()))")]] double operator()(ConstInputRange<T> x, ConstInputRange<T> y) const noexcept;

private:
    std::optional<OutputRange<unsigned>> rankedX_;
    std::optional<OutputRange<unsigned>> rankedY_;

};

template<class T>
SpearmanCoefficient<T>::SpearmanCoefficient(ConstInputRange<unsigned> rankedX, ConstInputRange<unsigned> rankedY) noexcept
    : rankedX_{std::make_optional<OutputRange<unsigned>>({rankedX.cbegin(), rankedX.cend()})}
    , rankedY_{std::make_optional<OutputRange<unsigned>>({rankedY.cbegin(), rankedY.cend()})}
{}

template<class T>
SpearmanCoefficient<T>::SpearmanCoefficient() noexcept
    : rankedX_{std::nullopt}
    , rankedY_{std::nullopt}
{}

template<class T>
double SpearmanCoefficient<T>::operator()(ConstInputRange<T> x, ConstInputRange<T> y) const noexcept
{
    ConstInputRange<unsigned> rankX = rankedX_.has_value() ? rankedX_.value() : Rank<T>{}(x);
    ConstInputRange<unsigned> rankY = rankedY_.has_value() ? rankedY_.value() : Rank<T>{}(y);

    return 1.0 - 6.0 * std::transform_reduce(rankX.cbegin(), rankX.cend(), rankY.cbegin(), 0.0, std::plus<>(), [](unsigned rank1, unsigned rank2) -> unsigned {
        return (rank1 - rank2) * (rank1 - rank2);
    }) / (x.size() * (x.size() * x.size() - 1));
}

}
