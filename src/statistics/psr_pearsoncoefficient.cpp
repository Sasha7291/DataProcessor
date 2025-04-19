#include "psr_pearsoncoefficient.h"

#include "psr_average.h"
#include "psr_variance.h"


namespace psr
{

PearsonCoefficient::PearsonCoefficient(double averageX, double averageY, double varianceX, double varianceY) noexcept
    : averageX_{std::make_optional(averageX)}
    , averageY_{std::make_optional(averageY)}
    , varianceX_{std::make_optional(varianceX)}
    , varianceY_{std::make_optional(varianceY)}
{}

PearsonCoefficient::PearsonCoefficient() noexcept
    : averageX_{std::nullopt}
    , averageY_{std::nullopt}
    , varianceX_{std::nullopt}
    , varianceY_{std::nullopt}
{}

template<class T>
double PearsonCoefficient::operator()(ConstInputRange<T> x, ConstInputRange<T> y) const noexcept
{
    auto averX = averageX_.has_value() ? averageX_.value() : Average{}(x);
    auto averY = averageY_.has_value() ? averageY_.value() : Average{}(y);

    return std::transform_reduce(x.cbegin(), x.cend(), y.cbegin(), 0.0, std::plus<>(), [averX, averY](T val1, T val2) -> T {
        return (val1 - averX) * (val2 - averY);
    }) / (x.size() * (varianceX_.has_value() ? varianceX_.value() : Variance{averX}(x)) * (varianceY_.has_value() ? varianceY_.value() : Variance{averY}(y)));
}

}
