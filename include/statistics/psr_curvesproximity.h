#pragma once

#include "psr_average.h"
#include "psr_integration.h"


namespace psr
{

template<class T>
class CurvesProximity
{

public:
    CurvesProximity(ConstInputRange<T> difference) noexcept;
    CurvesProximity() noexcept;
    ~CurvesProximity() noexcept = default;

    [[nodiscard(R"(Time complexity O(y.size()))")]] double operator()(ConstInputRange<T> x, ConstInputRange<T> y1, ConstInputRange<T> y2) const noexcept;
    [[nodiscard(R"(Time complexity O(y.size()))")]] double operator()(ConstInputRange<T> y1, ConstInputRange<T> y2) const noexcept;

private:
    std::optional<OutputRange<T>> difference_;

};

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
    OutputRange<T> difference = difference_.value_or(OutputRange<T>{});
    if (!difference_.has_value())
    {
        difference.reserve(y1.size());

        std::ranges::transform(y1, y2, std::back_inserter(difference), [](T val1, T val2) -> T {
            return (val1 - val2) * (val1 - val2);
        });
    }

    return std::sqrt(Integration<T>{}(x, difference) / (x.back() - x.front()));
}

template<class T>
double CurvesProximity<T>::operator()(ConstInputRange<T> y1, ConstInputRange<T> y2) const noexcept
{
    OutputRange<T> difference = difference_.value_or(OutputRange<T>{});
    if (!difference_.has_value())
    {
        difference.reserve(y1.size());
        std::ranges::transform(y1, y2, std::back_inserter(difference), std::minus<>());
    }

    return Average<T>{}(difference, 2);
}

}
