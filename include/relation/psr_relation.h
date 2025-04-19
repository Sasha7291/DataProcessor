#pragma once

#include "psr_common.h"


namespace psr
{

template<class T>
class Relation
{

public:
    Relation(T from, T to) noexcept;
    virtual ~Relation() noexcept = default;

    [[nodiscard(R"(Time complexity O(size))")]] std::pair<OutputRange<T>, OutputRange<double>> operator()(std::size_t size, const std::function<double(double)> &func);

private:
    std::pair<T, T> range_;

};

}
