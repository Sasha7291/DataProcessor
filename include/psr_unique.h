#pragma once

#include "psr_common.h"


namespace psr
{

template<class T>
class Unique
{

public:
    Unique() = default;
    ~Unique() = default;

    [[nodiscard(R"(Time complexity O(data.size()))")]] OutputRange<T> operator()(ConstInputRange<T> data) const;

};


template<class T>
OutputRange<T> Unique<T>::operator()(ConstInputRange<T> data) const
{
    OutputRange<T> result(data.cbegin(), data.cend());

    std::ranges::sort(result);
    (void)std::ranges::unique(result);

    return result;
}

}
