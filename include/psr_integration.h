#pragma once

#include "psr_common.h"

#include <QDebug>


namespace psr
{

template<class T>
class Integration
{

public:
    Integration() noexcept = default;
    ~Integration() noexcept = default;

    [[nodiscard(R"(Time complexity O(data.size()))")]] double operator()(ConstInputRange<T> x, ConstInputRange<T> y) const noexcept;

};

template<class T>
double Integration<T>::operator()(ConstInputRange<T> x, ConstInputRange<T> y) const noexcept
{
    double result = 0.0;
    qDebug() << x.size() << y.size();

    for (auto i = 1; i < x.size() - 1; ++i)
        result += 0.5 * (y[i] + y[i + 1]) * (x[i + 1] - x[i]);

    return result;
}

}
