#pragma once

#include "psr_common.h"


namespace psr
{

template<class T>
class Selection
{

public:
    Selection() noexcept = default;
    ~Selection() noexcept = default;

    [[nodiscard(R"(Time complexity depends on func)")]] OutputRange<T> operator()(ConstInputRange<T> data, const std::function<unsigned(unsigned)> &func) const noexcept;

};

template<class T>
OutputRange<T> Selection<T>::operator()(ConstInputRange<T> data, const std::function<unsigned(unsigned)> &func) const noexcept
{
    OutputRange<T> result;

    for (auto i = 0u; i < data.size(); i = func(i))
        result.push_back(data[i]);

    return result;
}

}
