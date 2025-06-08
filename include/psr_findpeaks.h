#pragma once

#include "psr_common.h"


namespace psr
{

template<class T>
class PeakFinder
{

public:
    struct Peak
    {
        T value;
        T prominence;
        std::size_t position;
    };

    PeakFinder(
        T minHeight = -std::numeric_limits<T>::infinity(),
        T minProminence = static_cast<T>(0),
        std::size_t minDistance = 1
    );
    ~PeakFinder() = default;

    [[nodiscard(R"(Time complexity O(data.size()^2))")]] OutputRange<Peak> operator ()(ConstInputRange<T> data) const;

private:
    T minHeight_;
    T minProminence_;
    std::size_t minDistance_;

};

template<class T>
PeakFinder<T>::PeakFinder(T minHeight, T minProminence, std::size_t minDistance)
    : minHeight_{minHeight}
    , minProminence_{minProminence}
    , minDistance_{minDistance}
{}

template<class T>
OutputRange<typename PeakFinder<T>::Peak> PeakFinder<T>::operator()(ConstInputRange<T> data) const
{
    OutputRange<Peak> result;

    result.reserve(data.size());
    for (std::size_t i = 1; i < data.size() - 1; ++i)
        if (data[i] > data[i - 1] && data[i] > data[i + 1] && data[i] >= minHeight_)
            result.push_back(Peak{.value = data[i], .prominence = 0.0, .position = i});
    result.shrink_to_fit();

    for (auto &peak : result)
    {
        T leftMin = peak.value;
        T rightMin = peak.value;

        for (std::size_t i = peak.position; i > 0; --i)
        {
            if (data[i - 1] > peak.value)
                break;
            leftMin = std::min(leftMin, data[i - 1]);
        }

        for (std::size_t i = peak.position; i < data.size() - 1; ++i)
        {
            if (data[i + 1] > peak.value)
                break;
            rightMin = std::min(rightMin, data[i + 1]);
        }

        peak.prominence = peak.value - std::max(leftMin, rightMin);
    }

    result.erase(
        std::ranges::remove_if(result, std::bind(std::less<>(), std::placeholders::_1, minProminence_), &Peak::prominence),
        result.end()
    );

    if (minDistance_ > 1 && !result.empty())
    {
        OutputRange<Peak> filteredResult;
        filteredResult.reserve(result.size());
        filteredResult.push_back(result[0]);

        for (std::size_t i = 1; i < result.size(); ++i)
            if (result[i].position - filteredResult.back().position >= minDistance_)
                filteredResult.push_back(result[i]);

        filteredResult.shrink_to_fit();
        return filteredResult;
    }

    return result;
}

}
