#pragma once

#include "psr_common.h"


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
    OutputRange<T> sortedData{data.cbegin(), data.cend()};
    std::ranges::sort(sortedData);
    auto middleElement = sortedData.cbegin() + data.size() / 2;

    return (data.size() & 1)
               ? (*middleElement)
               : ((*middleElement + *(middleElement - 1)) / 2);
}


}
