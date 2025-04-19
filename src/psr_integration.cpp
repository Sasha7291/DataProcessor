#include "psr_integration.h"


namespace psr
{

template<class T>
double Integration::operator()(ConstInputRange<T> x, ConstInputRange<T> y) const noexcept
{
    double result = 0.0;

    for (auto i = 1; i < x.size() - 1; ++i)
        result += 0.5 * (y[i] + y[i + 1]) * (x[i + 1] - x[i]);

    return result;
}

}
