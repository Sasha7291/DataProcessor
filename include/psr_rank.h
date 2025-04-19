#pragma once

#include "psr_common.h"


namespace psr
{

class Rank
{

public:
    Rank() noexcept = default;
    ~Rank() noexcept = default;

    template<class T>
    [[nodiscard(R"(Time complexity O(data.size() * log(data.size())))")]] OutputRange<unsigned> operator()(ConstInputRange<T> data) const noexcept;

};

}
