#pragma once

#include "psr_rmsroughness.h"


namespace psr
{

template<class T>
class ExcessMeasure
{

public:
    explicit ExcessMeasure(double rmsRoughness);
    ExcessMeasure();
    ~ExcessMeasure() = default;

    [[nodiscard(R"(Time complexity O(data.size()))")]] double operator()(ConstInputRange<T> y1, ConstInputRange<T> y2) const;

private:
    std::optional<double> rmsRoughness_;

};

template<class T>
ExcessMeasure<T>::ExcessMeasure(double rmsRoughness)
    : rmsRoughness_{std::make_optional(rmsRoughness)}
{}

template<class T>
ExcessMeasure<T>::ExcessMeasure()
    : rmsRoughness_{std::nullopt}
{}

template<class T>
double ExcessMeasure<T>::operator()(ConstInputRange<T> y1, ConstInputRange<T> y2) const
{
    OutputRange<T> difference;
    difference.reserve(y1.size());
    std::ranges::transform(y1, y2, std::back_inserter(difference), [](double value1, double value2) -> double {
        return std::pow(value1 - value2, 4);
    });

    return rmsRoughness_.has_value()
               ? Average<T>{}(difference) / std::pow(rmsRoughness_.value(), 4)
               : Average<T>{}(difference) / std::pow(RmsRoughness<T>{}(y1, y2), 4);
}

}
