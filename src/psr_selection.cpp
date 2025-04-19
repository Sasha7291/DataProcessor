#include "psr_selection.h"


namespace psr
{

template<class T>
OutputRange<T> Selection::operator()(ConstInputRange<T> data, const std::function<unsigned(unsigned)> &func) const noexcept
{
    OutputRange<T> result;

    for (auto i = 0u; i < data.size(); i = func(i))
        result.push_back(data[i]);

    return result;
}

}
