#pragma once

#include "psr_common.h"


namespace psr
{

template<class T>
class Selection
{

public:
    Selection() = default;
    ~Selection() = default;

    [[nodiscard(R"(Time complexity depends on func)")]] OutputRange<T> operator()(ConstInputRange<T> data, const std::function<unsigned(unsigned)> &func) const;

};

template<class T>
OutputRange<T> Selection<T>::operator()(ConstInputRange<T> data, const std::function<unsigned(unsigned)> &func) const
{
    OutputRange<T> result;

    for (decltype(data.size()) i = 0; i < data.size(); i = func(i))
        result.push_back(data[i]);

    return result;
}

}
