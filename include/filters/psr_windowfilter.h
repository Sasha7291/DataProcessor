#pragma once

#include "psr_common.h"


namespace psr
{

class WindowFilter
{

protected:
    WindowFilter() noexcept = default;
    virtual ~WindowFilter() noexcept = default;

    template<class T, class FilterFunction>
    [[nodiscard]] OutputRange<T> operator()(ConstInputRange<T> data, unsigned width, FilterFunction func) const noexcept;

};

}
