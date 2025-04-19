#pragma once

#include "psr_common.h"


namespace psr
{

class Gauss
{

public:
    Gauss(unsigned width) noexcept;
    Gauss() noexcept;
    ~Gauss() noexcept = default;

    template<class T>
    [[nodiscard(R"(Time complexity O(data.size()))")]] T operator()(ConstInputRange<T> data) const noexcept;

private:
    [[nodiscard(R"(Time complexity O(data.size()))")]] OutputRange<double> kernel(unsigned width) const noexcept;

    std::optional<OutputRange<double>> kernel_;

};

}
