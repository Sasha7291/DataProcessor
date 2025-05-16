#pragma once

#include "psr_common.h"


namespace psr
{

template<class T>
class WindowFilter
{

protected:
    WindowFilter() noexcept = default;
    virtual ~WindowFilter() noexcept = default;

    template<class FilterFunction>
    [[nodiscard]] OutputRange<T> filter(ConstInputRange<T> data, unsigned width, FilterFunction func) const noexcept;

};

template<class T>
template<class FilterFunction>
OutputRange<T> WindowFilter<T>::filter(ConstInputRange<T> data, unsigned width, FilterFunction func) const noexcept
{
    OutputRange<T> result{data.cbegin(), data.cend()};

    for (auto i = 0u; i < width; ++i)
    {
        result.insert(result.begin(), result.front());
        result.push_back(result.back());
    }

    for (auto it = result.begin() + width; it != result.end() - width; ++it)
        *it = func({it - width / 2, it + width / 2});

    result.erase(result.begin(), result.begin() + width);
    result.erase(result.end() - width, result.end());
    return result;
}

}
