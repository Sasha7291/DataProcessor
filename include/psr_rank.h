#pragma once

#include "psr_common.h"


namespace psr
{

template<class T>
class Rank
{

public:
    Rank() noexcept = default;
    ~Rank() noexcept = default;

    [[nodiscard(R"(Time complexity O(data.size() * log(data.size())))")]] OutputRange<unsigned> operator()(ConstInputRange<T> data) const noexcept;

};

template<class T>
OutputRange<unsigned> Rank<T>::operator()(ConstInputRange<T> data) const noexcept
{
    Map<T, unsigned> rankedValues;
    for (auto i = 0; i < data.size(); ++i)
        rankedValues[data[i]] = i;

#ifdef QT
    return rankedValues.values();
#else
    OutputRange<unsigned> result;
    result.reserve(data.size());

    std::ranges::transform(rankedValues, std::back_inserter(result), [](const auto &pair) -> unsigned {
        return pair.second;
    });

    return result;
#endif
}


}
