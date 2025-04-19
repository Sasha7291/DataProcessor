#pragma once

#include "psr_common.h"


namespace psr
{

template<class T>
class CurvesProximity
{

public:
    CurvesProximity(ConstInputRange<T> difference) noexcept;
    CurvesProximity() noexcept;
    ~CurvesProximity() noexcept = default;

    [[nodiscard(R"(Time complexity O(y.size()))")]] double operator()(ConstInputRange<T> x, ConstInputRange<T> y1, ConstInputRange<T> y2) const noexcept;
    [[nodiscard(R"(Time complexity O(y.size()))")]] double operator()(ConstInputRange<T> y1, ConstInputRange<T> y2) const noexcept;

private:
    std::optional<OutputRange<T>> difference_;

};

}
