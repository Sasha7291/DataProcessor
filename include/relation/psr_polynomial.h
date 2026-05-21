#pragma once

#include "psr_relation.h"


namespace psr
{

template<class T>
class Polynomial : public Relation<T>
{

public:
    Polynomial(T from, T to);
    ~Polynomial() = default;

    [[nodiscard(R"(Time complexity O(size))")]] std::pair<OutputRange<double>, OutputRange<T>> operator()(
        std::size_t size,
        ConstInputRange<double> coeffs
    ) const;

};

template<class T>
Polynomial<T>::Polynomial(T from, T to)
    : Relation<T>{from, to}
{}

template<class T>
std::pair<OutputRange<double>, OutputRange<T>> Polynomial<T>::operator()(
    std::size_t size,
    ConstInputRange<double> coeffs
) const
{
    return Relation<T>::operator()(size, [coeffs](double x) -> double {
        T result = static_cast<T>(0);

        for (int i = 0; i < coeffs.size(); ++i)
            result += std::pow(x, i) * coeffs[i];

        return result;
    });
}

}
