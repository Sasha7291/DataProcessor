#pragma once

#include "psr_gauss.h"
#include "psr_windowfilter.h"


namespace psr
{

template<class T>
class GaussFilter : public WindowFilter
{

public:
    GaussFilter() noexcept;
    ~GaussFilter() noexcept = default;

    [[nodiscard]] OutputRange<T> operator()(ConstInputRange<T> data, unsigned width) const noexcept;

};

template<class T>
GaussFilter<T>::GaussFilter() noexcept
    : WindowFilter{}
{}

template<class T>
OutputRange<T> GaussFilter<T>::operator()(ConstInputRange<T> data, unsigned int width) const noexcept
{
    return operator()(data, width, Gauss{width});
}

}
