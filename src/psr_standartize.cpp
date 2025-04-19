#include "psr_standartize.h"

#include "psr_average.h"
#include "psr_variance.h"


namespace psr
{

Standartize::Standartize(double average, double variance) noexcept
    : average_{std::make_optional(average)}
    , variance_{std::make_optional(variance)}
{}

Standartize::Standartize() noexcept
    : average_{std::nullopt}
    , variance_{std::nullopt}
{}

template<class T>
OutputRange<T> Standartize::operator()(ConstInputRange<T> data) const noexcept
{
    OutputRange<T> result;
    result.reserve(data.size());

    auto aver = average_.has_value() ? average_.value() : Average{}(data);
    auto var = variance_.has_value() ? variance_.value() : Variance{aver}(data);
    std::ranges::transform(data, std::back_inserter(result), [aver, var](T value) -> T {
        return static_cast<T>((value - aver) / var);
    });

    return result;
}



}
