#pragma once

#include "psr_common.h"


namespace psr
{

template<class T>
class Rationing
{

public:
    Rationing(const std::pair<T, T> &oldRange, const std::pair<T, T> &newRange) noexcept;
    Rationing() noexcept;
    ~Rationing() noexcept = default;

    [[nodiscard(R"(Time complexity O(data.size()))")]] OutputRange<T> operator()(ConstInputRange<T> data) const noexcept;

private:
    std::optional<std::pair<double, double>> oldRange_;
    std::optional<std::pair<double, double>> newRange_;

};

template<class T>
Rationing<T>::Rationing(const std::pair<T, T> &oldRange, const std::pair<T, T> &newRange) noexcept
    : oldRange_{std::make_optional(std::make_pair(
        static_cast<double>(oldRange.first),
        static_cast<double>(oldRange.second - oldRange.first
    )))}
    , newRange_{std::make_optional(std::make_pair(
        static_cast<double>(newRange.first),
        static_cast<double>(newRange.second - newRange.first)
    ))}
{}

template<class T>
Rationing<T>::Rationing() noexcept
    : oldRange_{std::nullopt}
    , newRange_{std::make_optional(std::make_pair(0.0, 1.0))}
{}

template<class T>
OutputRange<T> Rationing<T>::operator()(ConstInputRange<T> data) const noexcept
{
    OutputRange<T> result;
    result.reserve(data.size());

    const auto [min, max] = std::ranges::minmax(data);
    const auto oldRange = oldRange_.value_or(std::make_pair(min, max - min));
    const auto newRange = newRange_.value();
    std::ranges::transform(data, std::back_inserter(result), [oldRange, newRange](T value) -> T {
        return static_cast<T>((static_cast<double>(value) - oldRange.first) / oldRange.second * newRange.second + newRange.first);
    });

    return result;
}

}
