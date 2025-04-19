#pragma once

#include "psr_common.h"

#include <set>


namespace psr
{

template<class T>
class Median
{

public:
    Median() noexcept = default;
    ~Median() noexcept = default;

    [[nodiscard(R"(Time complexity O(data.size() * log(data.size())))")]] T operator()(ConstInputRange<T> data) const noexcept;

};

template<class T>
T Median<T>::operator()(ConstInputRange<T> data) const noexcept
{
    std::multiset sortedData{data.cbegin(), data.cend()};
    auto middleElement = sortedData.cbegin() + data.size() / 2;

    return (data.size() & 1)
               ? (*middleElement)
               : ((*middleElement + *(middleElement - 1)) / 2);
}


}
