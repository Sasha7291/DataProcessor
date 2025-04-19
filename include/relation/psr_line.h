#pragma once

#include "psr_relation.h"


namespace psr
{

template<class T>
class Line : public Relation<T>
{

public:
    Line(T from, T to) noexcept;
    ~Line() noexcept = default;

    [[nodiscard(R"(Time complexity O(size))")]] std::pair<OutputRange<T>, OutputRange<double>> operator()(std::size_t size, double k, double b) const noexcept;

};

}
