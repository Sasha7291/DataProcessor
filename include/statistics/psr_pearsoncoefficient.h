#pragma once

#include "psr_common.h"


namespace psr
{

class PearsonCoefficient
{

public:
    PearsonCoefficient(double averageX, double averageY, double varianceX, double varianceY) noexcept;
    PearsonCoefficient() noexcept;
    ~PearsonCoefficient() noexcept = default;

    template<class T>
    [[nodiscard(R"(Time complexity O(x.size()))")]] double operator()(ConstInputRange<T> x, ConstInputRange<T> y) const noexcept;

private:
    std::optional<double> averageX_;
    std::optional<double> averageY_;
    std::optional<double> varianceX_;
    std::optional<double> varianceY_;

};

}
