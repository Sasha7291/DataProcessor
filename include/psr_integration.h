#pragma once

#include "psr_common.h"

namespace psr
{

class Integration
{

public:
    Integration() noexcept = default;
    ~Integration() noexcept = default;

    template<class T>
    [[nodiscard(R"(Time complexity O(data.size()))")]] double operator()(ConstInputRange<T> x, ConstInputRange<T> y) const noexcept;

};

}
