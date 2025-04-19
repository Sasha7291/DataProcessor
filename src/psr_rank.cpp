#include "psr_rank.h"


namespace psr
{

template<class T>
OutputRange<unsigned> Rank::operator()(ConstInputRange<T> data) const noexcept
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
