#pragma once

#include "psr_common.h"


namespace psr
{

class Median
{

public:
    Median() noexcept = default;
    ~Median() noexcept = default;

    template<class T>
    [[nodiscard(R"(Time complexity O(data.size() * log(data.size())))")]] T operator()(ConstInputRange<T> data) const noexcept;

};

}
