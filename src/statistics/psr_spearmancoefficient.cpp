#include "psr_spearmancoefficient.h"

#include "psr_rank.h"


namespace psr
{

SpearmanCoefficient::SpearmanCoefficient(ConstInputRange<unsigned> rankedX, ConstInputRange<unsigned> rankedY) noexcept
    : rankedX_{std::make_optional<OutputRange<unsigned>>({rankedX.cbegin(), rankedX.cend()})}
    , rankedY_{std::make_optional<OutputRange<unsigned>>({rankedY.cbegin(), rankedY.cend()})}
{}

SpearmanCoefficient::SpearmanCoefficient() noexcept
    : rankedX_{std::nullopt}
    , rankedY_{std::nullopt}
{}

template<class T>
double SpearmanCoefficient::operator()(ConstInputRange<T> x, ConstInputRange<T> y) const noexcept
{
    ConstInputRange<T> rankX = rankedX_.has_value() ? rankedX_.value() : Rank{}(x);
    ConstInputRange<T> rankY = rankedY_.has_value() ? rankedY_.value() : Rank{}(y);

    return 1.0 - 6.0 * std::transform_reduce(rankX.cbegin(), rankX.cend(), rankY.cbegin(), 0.0, std::plus<>(), [](unsigned rank1, unsigned rank2) -> unsigned {
        return (rank1 - rank2) * (rank1 - rank2);
    }) / (x.size() * (x.size() * x.size() - 1));
}

}
