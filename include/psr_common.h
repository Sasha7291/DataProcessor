#pragma once


#ifdef QT
#include <QHash>
#include <QMap>
#include <QSpan>
#include <QVector>
#else
#include <map>
#include <span>
#include <vector>
#include <unordered_map>
#endif


namespace psr
{
#ifdef QT
template<class T>
using ConstInputRange = QSpan<const T>;
template<class T>
using InputRange = QSpan<T>;
template<class T>
using OutputRange = QVector<T>;
template<class T, class K>
using Map = QMap<T, K>;
template<class T, class K>
using UnorderedMap = QHash<T, K>;
#else
template<class T>
using ConstInputRange = std::span<const T>;
template<class T>
using InputRange = std::span<T>;
template<class T>
using OutputRange = std::vector<T>;
template<class T, class K>
using Map = std::map<T, K>;
template<class T, class K>
using UnorderedMap = std::unordered_map<T, K>;
#endif
}
