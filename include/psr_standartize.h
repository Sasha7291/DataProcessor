#pragma once

#include "psr_common.h"


namespace psr
{

class Standartize
{

public:
    Standartize(double average, double variance) noexcept;
    Standartize() noexcept;
    ~Standartize() noexcept = default;

    template<class T>
    [[nodiscard(R"(Time complexity O(data.size()))")]] OutputRange<T> operator()(ConstInputRange<T> data) const noexcept;

private:
    std::optional<double> average_;
    std::optional<double> variance_;

};

}
