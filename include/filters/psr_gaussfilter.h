#pragma once

#include "psr_windowfilter.h"


namespace psr
{

class GaussFilter : public WindowFilter
{

public:
    GaussFilter() noexcept;
    ~GaussFilter() noexcept = default;

    template<class T>
    [[nodiscard]] OutputRange<T> operator()(ConstInputRange<T> data, unsigned width) const noexcept;

};

}
