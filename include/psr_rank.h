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
    OutputRange<std::pair<T, int>> temp(data.size());
    for (int i = 0; i < data.size(); i++)
    {
        temp[i].first = data[i];
        temp[i].second = i;
    }

    std::sort(temp.begin(), temp.end(), [](const auto &val1, const auto &val2) -> bool {
        return val1.first < val2.first;
    });

    OutputRange<double> ranks(data.size());
    double rank = 1.0;
    int m = 1;
    for (int i = 0; i < data.size(); i += m)
    {
        auto j = i;
        while (j < data.size() - 1 && temp[j].first == temp[j + 1].first)
            j += 1;
        m = j - i + 1;

        for (int k = 0; k < m; k++)
            ranks[temp[i + k].second] = rank + (m - 1) * 0.5;

        rank += m;
    }

    return ranks;
}

}
