#pragma once

#include "psr_relation.h"


namespace psr
{

template<class T>
class PowerFunction : public Relation<T>
{

public:
    PowerFunction(T from, T to) noexcept;
    ~PowerFunction() noexcept = default;

    [[nodiscard(R"(Time complexity O(size))")]] std::pair<OutputRange<T>, OutputRange<double>> operator ()(std::size_t size, double k, double b) const noexcept;

};

}
