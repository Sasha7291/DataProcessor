#pragma once

#include "psr_common.h"

#include <optional>


namespace psr
{

class Variance
{

public:
    explicit Variance(double average) noexcept;
    Variance() noexcept;
    ~Variance() noexcept = default;

    template<class T>
    [[nodiscard(R"(Time complexity O(data.size()))")]] double operator()(ConstInputRange<T> data) const noexcept;

private:
    std::optional<double> average_;

};

}
