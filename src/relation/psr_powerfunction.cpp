#include "psr_powerfunction.h"


namespace psr
{

template<class T>
PowerFunction<T>::PowerFunction(T from, T to) noexcept
    : Relation<T>(from, to)
{}

template<class T>
std::pair<OutputRange<T>, OutputRange<double>> PowerFunction<T>::operator()(std::size_t size, double k, double b) const noexcept
{
    return operator()(size, [k, b](double x) -> T {
        return k * std::pow(x, b);
    });
}

}
