#include "psr_gaussfilter.h"

#include "psr_gauss.h"


namespace psr
{

GaussFilter::GaussFilter() noexcept
    : WindowFilter{}
{}

template<class T>
OutputRange<T> GaussFilter::operator()(ConstInputRange<T> data, unsigned int width) const noexcept
{
    return operator()(data, width, Gauss{width});
}

}
