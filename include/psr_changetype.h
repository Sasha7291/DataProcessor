#pragma once


#include "psr_common.h"


namespace psr
{

template<class T, class K>
class TypeChanger
{

public:
    TypeChanger() = default;
    ~TypeChanger() = default;

    [[nodiscard(R"(Time complexity O(data.size()))")]] OutputRange<K> operator()(ConstInputRange<T> data) const;

};

template<class T, class K>
OutputRange<K> TypeChanger<T, K>::operator()(ConstInputRange<T> data) const
{
    OutputRange<K> result;
    result.reserve(data.size());

    std::ranges::transform(data, std::back_inserter(result), [](T value) -> K {
        return static_cast<K>(value);
    });

    return result;
}

}
