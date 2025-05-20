#pragma once

#include "psr_gauss.h"
#include "psr_windowfilter.h"


namespace psr
{

template<class T>
class GaussFilter : public WindowFilter<T>
{

public:
    GaussFilter() noexcept;
    ~GaussFilter() noexcept = default;

    [[nodiscard]] OutputRange<T> operator()(ConstInputRange<T> data, std::size_t width) const noexcept;

};

template<class T>
GaussFilter<T>::GaussFilter() noexcept
    : WindowFilter<T>{}
{}

template<class T>
OutputRange<T> GaussFilter<T>::operator()(ConstInputRange<T> data, std::size_t width) const noexcept
{
    return this->filter(data, width, Gauss<T>{width});
}

}
