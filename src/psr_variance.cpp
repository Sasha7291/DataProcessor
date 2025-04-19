#include "psr_variance.h"

#include "psr_average.h"


namespace psr
{

Variance::Variance(double average) noexcept
    : average_{std::make_optional(average)}
{}

Variance::Variance() noexcept
    : average_{std::nullopt}
{}

template<class T>
double Variance::operator()(ConstInputRange<T> data) const noexcept
{
    OutputRange<T> discrepancy;
    discrepancy.reserve(data.size());

    std::ranges::transform(data, std::back_inserter(discrepancy), [aver = average_.has_value() ? average_.value() : Average{}(data)](T value) -> T {
        return value - aver;
    });

    return Average{}(discrepancy, 2);
}

}
