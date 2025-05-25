#pragma once

#include "psr_rmsroughness.h"


namespace psr
{

template<class T>
class AsymmetryParameter
{

public:
    explicit AsymmetryParameter(double rmsRoughness);
    AsymmetryParameter();
    ~AsymmetryParameter() = default;

    [[nodiscard(R"(Time complexity O(data.size()))")]] double operator()(ConstInputRange<T> y1, ConstInputRange<T> y2) const;

private:
    std::optional<double> rmsRoughness_;

};

template<class T>
AsymmetryParameter<T>::AsymmetryParameter(double rmsRoughness)
    : rmsRoughness_{std::make_optional(rmsRoughness)}
{}

template<class T>
AsymmetryParameter<T>::AsymmetryParameter()
    : rmsRoughness_{std::nullopt}
{}

template<class T>
double AsymmetryParameter<T>::operator()(ConstInputRange<T> y1, ConstInputRange<T> y2) const
{
    OutputRange<T> difference;
    difference.reserve(y1.size());
    std::ranges::transform(y1, y2, std::back_inserter(difference), [](double value1, double value2) -> double {
        return std::pow(value1 - value2, 3);
    });

    return rmsRoughness_.has_value()
        ? Average<T>{}(difference) / std::pow(rmsRoughness_.value(), 3)
        : Average<T>{}(difference) / std::pow(RmsRoughness<T>{}(y1, y2), 3);
}

}
