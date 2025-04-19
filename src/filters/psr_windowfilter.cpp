#include "psr_windowfilter.h"

namespace psr
{

template<class T, class FilterFunction>
OutputRange<T> WindowFilter::operator()(ConstInputRange<T> data, unsigned width, FilterFunction func) const noexcept
{
    OutputRange<T> result{data.cbegin(), data.cend()};

    for (auto i = 0u; i < width; ++i)
    {
        result.insert(result.begin(), result.front());
        result.push_back(result.back());
    }

    for (auto it = result.begin() + width; it != result.end() - width; ++it)
        *it = func({it - width, it + width});

    return result;
}

}
