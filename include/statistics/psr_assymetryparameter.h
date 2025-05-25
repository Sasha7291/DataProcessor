#pragma once

#include "psr_rmsroughness.h"


namespace psr
{

template<class T>
class AssymetryParameter
{

public:
    explicit AssymetryParameter(double rmsRoughness);
    AssymetryParameter();
    ~AssymetryParameter() = default;

    [[nodiscard(R"(Time complexity O(data.size()))")]] double operator()(ConstInputRange<T> y1, ConstInputRange<T> y2) const;

private:
    std::optional<double> rmsRoughness_;

};

template<class T>
AssymetryParameter<T>::AssymetryParameter(double rmsRoughness)
    : variance_{std::make_optional(rmsRoughness_)}
{}

template<class T>
AssymetryParameter<T>::AssymetryParameter()
    : variance_{std::nullopt}
{}

template<class T>
double AssymetryParameter<T>::operator()(ConstInputRange<T> y1, ConstInputRange<T> y2) const
{
    OutputRange<T> difference;
    difference.reserve(y1.size());
    std::ranges::transform(y1, y2, std::back_inserter(difference), [](double val1, double val2) -> double {
        return std::pow(y1 - y2, 3);
    });

    return rmsRoughness_.has_value()
        ? Average{}(difference) / std::pow(variance_.value(), 3)
        : Average{}(difference) / std::pow(RmsRoughness{}(y1, y2), 3);
}

;
