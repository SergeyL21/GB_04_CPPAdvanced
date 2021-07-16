/*
 * Created by Qt Creator 4.11.0 @ 14 Jul 2021 18:33:21
 *
 * Project: GB_CppAdvanced
 * File: lesson_5.h
 *
 * Author: Sergey Lola
 */
#pragma once

#include <iostream>
#include <algorithm>
#include <iterator>
#include <unordered_set>

namespace lesson_5 {

// --------------------------------------------------------------------------------------
template <typename It>
void printUnique(It begin, It end) {
  using ValueType = typename std::iterator_traits<It>::value_type;
  std::unordered_set<ValueType> v_set{begin, end};
  std::copy(v_set.cbegin(), v_set.cend(), std::ostream_iterator<ValueType>(std::cout, " "));
}

}  // namespace lesson_5
