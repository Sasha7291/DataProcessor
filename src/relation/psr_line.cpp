#include "psr_line.h"


namespace psr
{

template<class T>
Line<T>::Line(T from, T to) noexcept
    : Relation<T>(from, to)
{}

template<class T>
std::pair<OutputRange<T>, OutputRange<double> > Line<T>::operator ()(std::size_t size, double k, double b) const noexcept
{
    return operator()(size, [k, b](double x) -> T {
        return k * x + b;
    });
}

}
