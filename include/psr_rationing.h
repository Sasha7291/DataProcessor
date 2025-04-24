#pragma once

#include "psr_common.h"


namespace psr
{

template<class T>
class Rationing
{

public:
    Rationing(std::pair<T, T> oldRange, std::pair<T, T> newRange) noexcept;
    Rationing() noexcept;
    ~Rationing() noexcept = default;

    [[nodiscard(R"(Time complexity O(data.size()))")]] OutputRange<T> operator()(ConstInputRange<T> data) const noexcept;

private:
    std::optional<std::pair<T, T>> oldRange_;
    std::optional<std::pair<T, T>> newRange_;

};

template<class T>
Rationing<T>::Rationing(std::pair<T, T> oldRange, std::pair<T, T> newRange) noexcept
    : oldRange_{std::make_optional(std::make_pair(oldRange.first, oldRange.second - oldRange.first))}
    , newRange_{std::make_optional(std::make_pair(newRange.first, newRange.second - newRange.first))}
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
    std::ranges::transform(data, std::back_inserter(result), [oldRange = oldRange_.value_or(std::make_pair(min, max - min)), newRange = newRange_.value()](T value) -> T {
        return (value - oldRange.first) / (oldRange.second - oldRange.first) * (newRange.second - newRange.first) + newRange.first;
    });

    return result;
}

}
