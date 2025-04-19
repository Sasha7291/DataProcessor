#pragma once

#include "psr_common.h"


namespace psr
{

class Selection
{

public:
    Selection() noexcept = default;
    ~Selection() noexcept = default;

    template<class T>
    [[nodiscard(R"(Time complexity depends on func)")]] OutputRange<T> operator()(ConstInputRange<T> data, const std::function<unsigned(unsigned)> &func) const noexcept;

};


}
