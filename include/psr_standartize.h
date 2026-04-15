#pragma once

#include "psr_average.h"
#include "psr_variance.h"


namespace psr
{

template<class T>
class Standartize
{

public:
    Standartize(double average, double variance);
    Standartize();
    ~Standartize() = default;

    [[nodiscard(R"(Time complexity O(data.size()))")]] OutputRange<T> operator()(ConstInputRange<T> data) const;

private:
    std::optional<double> average_;
    std::optional<double> variance_;

};

template<class T>
Standartize<T>::Standartize(double average, double variance)
    : average_{std::make_optional(average)}
    , variance_{std::make_optional(variance)}
{}

template<class T>
Standartize<T>::Standartize()
    : average_{std::nullopt}
    , variance_{std::nullopt}
{}

template<class T>
OutputRange<T> Standartize<T>::operator()(ConstInputRange<T> data) const
{
#if __cplusplus >= 202302L
    const auto aver =
        (average_.has_value())
            ? (average_.value())
            : (Average<T>{}(data));
    const auto var =
        (variance_.has_value())
            ? (variance_.value())
            : (Variance<T>{aver}(data));

    return data
        | std::views::transform(
            [aver, var](T value) -> T {
                return static_cast<T>((value - aver) / std::sqrt(var));
            }
        )
        | std::ranges::to<OutputRange<T>>();
#else
    OutputRange<T> result;
    result.reserve(data.size());

    const auto aver =
        (average_.has_value())
            ? (average_.value())
            : (Average<T>{}(data));
    const auto var =
        (variance_.has_value())
            ? (variance_.value())
            : (Variance<T>{aver}(data));
    std::ranges::transform(data, std::back_inserter(result), [aver, var](T value) -> T {
        return static_cast<T>((value - aver) / var);
    });

    return result;
#endif
}

}
