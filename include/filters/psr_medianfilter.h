#pragma once

#include "psr_median.h"
#include "psr_windowfilter.h"


namespace psr
{

template<class T>
class MedianFilter : public WindowFilter<T>
{

public:
    MedianFilter() noexcept;
    ~MedianFilter() noexcept = default;

    [[nodiscard]] OutputRange<T> operator()(ConstInputRange<T> data, std::size_t width) const noexcept;

};

template<class T>
MedianFilter<T>::MedianFilter() noexcept
    : WindowFilter<T>{}
{}

template<class T>
OutputRange<T> MedianFilter<T>::operator()(ConstInputRange<T> data, std::size_t width) const noexcept
{
    return this->filter(data, width, Median<T>{});
}

}
