#pragma once

#include "psr_common.h"


namespace psr
{

template<class T>
class FourierTransform
{

public:
    FourierTransform() = default;
    ~FourierTransform() = default;

    [[nodiscard]] std::pair<OutputRange<T>, OutputRange<T>> operator()(ConstInputRange<T> data, double period) const;

private:
    [[nodiscard]] static std::complex<T> fourierCoefficient(const unsigned index, ConstInputRange<T> data);

};

template<class T>
std::pair<OutputRange<T>, OutputRange<T>> FourierTransform<T>::operator ()(ConstInputRange<T> data, double period) const
{
    OutputRange<T> resultValues;
    OutputRange<T> resultKeys;
    resultValues.reserve(data.size());
    resultKeys.reserve(data.size());

    for (std::size_t k = 0; k < data.size(); ++k)
    {
        std::complex<T> temp{0.0, 0.0};

        for (std::size_t n = 0; n < data.size(); ++n)
            temp += data[n] * std::exp(-2 * std::numbers::pi * 1i * k * n / data.size());

        resultValues.push_back(std::abs(temp));
        resultKeys.push_back(k / (data.size() * period));
    }

    return std::make_pair(resultKeys, resultValues);
}

}
