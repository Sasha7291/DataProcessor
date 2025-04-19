#pragma once

#include "psr_common.h"


namespace psr
{

class SpearmanCoefficient
{

public:
    SpearmanCoefficient(ConstInputRange<unsigned> rankedX, ConstInputRange<unsigned> rankedY) noexcept;
    SpearmanCoefficient() noexcept;
    ~SpearmanCoefficient() noexcept = default;

    template<class T>
    [[nodiscard(R"(Time complexity O(data.size()))")]] double operator()(ConstInputRange<T> x, ConstInputRange<T> y) const noexcept;

private:
    std::optional<OutputRange<unsigned>> rankedX_;
    std::optional<OutputRange<unsigned>> rankedY_;

};

}
