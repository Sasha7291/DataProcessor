#pragma once

#include "psr_common.h"


namespace psr
{

template<class T>
class Calibration
{

public:
    explicit Calibration(double origin);
    Calibration();
    ~Calibration() = default;

    [[nodiscard(R"(Time complexity O(data.size()))")]] OutputRange<T> operator ()(ConstInputRange<T> data) const;

private:
    std::optional<double> origin_;

};

template<class T>
Calibration<T>::Calibration(double origin)
    : origin_{std::make_optional(origin)}
{}

template<class T>
Calibration<T>::Calibration()
    : origin_{std::nullopt}
{}

template<class T>
OutputRange<T> Calibration<T>::operator()(ConstInputRange<T> data) const
{
    OutputRange<T> result;
    result.reserve(data.size());

    std::ranges::transform(data, std::back_inserter(result), [origin = origin_.has_value() ? origin_.value() : std::ranges::min(data)](T value) -> T {
        return value - origin;
    });

    return result;
}

}


