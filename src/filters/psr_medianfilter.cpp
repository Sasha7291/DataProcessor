#include "psr_medianfilter.h"

#include "psr_median.h"


namespace psr
{

MedianFilter::MedianFilter() noexcept
    : WindowFilter{}
{}

template<class T>
OutputRange<T> MedianFilter::operator()(ConstInputRange<T> data, unsigned int width) const noexcept
{
    return operator()(data, width, Median{});
}

}
