#pragma once

#include "psr_common.h"


namespace psr
{

class Average
{

public:
    Average() noexcept = default;
    ~Average() noexcept = default;

    template<class T>
    [[nodiscard(R"(Time omplexity O(data.size()))")]] double operator()(ConstInputRange<T> data) const noexcept;

    template<class T>
    [[nodiscard(R"(Time complexity O(data.size()))")]] double operator()(ConstInputRange<T> weights, ConstInputRange<T> data) const noexcept;

    template<class T>
    [[nodiscard(R"(Time complexity O(data.size()))")]] double operator()(ConstInputRange<T> data, unsigned n) const noexcept;

};

}
