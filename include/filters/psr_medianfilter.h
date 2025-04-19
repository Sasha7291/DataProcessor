#pragma once

#include "psr_windowfilter.h"


namespace psr
{

class MedianFilter : public WindowFilter
{

public:
    MedianFilter() noexcept;
    ~MedianFilter() noexcept = default;

    template<class T>
    [[nodiscard]] OutputRange<T> operator()(ConstInputRange<T> data, unsigned width) const noexcept;

};

}
