#include "psr_median.h"

#include <set>


namespace psr
{

template<class T>
T Median::operator()(ConstInputRange<T> data) const noexcept
{
    std::multiset sortedData{data.cbegin(), data.cend()};
    auto middleElement = sortedData.cbegin() + data.size() / 2;

    return (data.size() & 1)
        ? (*middleElement)
        : ((*middleElement + *(middleElement - 1)) / 2);
}

}

