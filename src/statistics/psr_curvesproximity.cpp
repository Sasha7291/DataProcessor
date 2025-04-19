#include "psr_curvesproximity.h"

#include "psr_integration.h"


namespace psr
{

template<class T>
CurvesProximity<T>::CurvesProximity(ConstInputRange<T> difference) noexcept
    : difference_{std::make_optional<OutputRange<T>>({difference.cbegin(), difference.cend()})}
{}

template<class T>
CurvesProximity<T>::CurvesProximity() noexcept
    : difference_{std::nullopt}
{}

template<class T>
double CurvesProximity<T>::operator()(ConstInputRange<T> x, ConstInputRange<T> y1, ConstInputRange<T> y2) const noexcept
{
    if (!difference_.has_value())
    {
        difference_ = std::make_optional<OutputRange<T>>();
        difference_.value().reserve(y1.size());

        std::ranges::transform(y1, y2, std::back_inserter(difference_.value()), [](T val1, T val2) -> T {
            return (val1 - val2) * (val1 - val2);
        });
    }

    return std::sqrt(Integration{}(x, difference_.value()) / (x.back() - x.front()));
}

template<class T>
double CurvesProximity<T>::operator()(ConstInputRange<T> y1, ConstInputRange<T> y2) const noexcept
{
    if (!difference_.has_value())
    {
        difference_ = std::make_optional<OutputRange<T>>();
        difference_.value().reserve(y1.size());

        std::ranges::transform(y1, y2, std::back_inserter(difference_.value()), [](T val1, T val2) -> T {
            return std::abs(val1 - val2);
        });
    }

    return *std::ranges::max_element(difference_.value());
}

}
