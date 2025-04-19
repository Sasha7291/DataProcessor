#pragma once

#include "psr_common.h"


namespace psr
{

template<class T>
class Rationing
{

public:
    Rationing(std::pair<T, T> oldRange, std::pair<T, T> newRange) noexcept;
    Rationing() noexcept;
    ~Rationing() noexcept = default;

    [[nodiscard(R"(Time complexity O(data.size()))")]] OutputRange<T> operator()(ConstInputRange<T> data) const noexcept;

private:
    std::optional<std::pair<T, T>> oldRange_;
    std::optional<std::pair<T, T>> newRange_;

};

}
