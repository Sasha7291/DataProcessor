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

    [[nodiscard(R"(Time complexity O(data.size() * log(data.size())))")]] OutputRange<double> operator()(ConstInputRange<T> data) const noexcept;

};


template<class T>
OutputRange<double> Rank<T>::operator()(ConstInputRange<T> data) const noexcept
{
    MultiMap<T, int> indicies;
    for (auto i = 0; i < data.size(); ++i)
        indicies.insert(data[i], i);

    Map<T, int> counts;
    for (const auto value : indicies.keys())
        ++counts[value];

    OutputRange<double> ranks(data.size());
    int i = 1;
    for (const auto &value : counts.keys())
    {
        double rank = 0.0;
        for (auto j = i; j < i + indicies.count(value); ++j)
            rank += j;
        rank /= indicies.count(value);

        for (const auto &index : indicies.values(value))
            ranks[index] = rank;
        i += indicies.count(value);
    }

    return ranks;
}

}
