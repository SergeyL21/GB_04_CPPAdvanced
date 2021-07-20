/*
 * Created by Qt Creator 4.11.0 @ 11 Jul 2021 16:34:28
 *
 * Project: GB_CppAdvanced
 * File: lesson_4.h
 *
 * Author: Sergey Lola
 */
#pragma once

#include <vector>
#include <algorithm>

namespace lesson_4 {

template <typename Container, typename Value>
typename Container::iterator insert_sorted(Container &container, Value const &value) {
  return container.insert(
        std::upper_bound(container.cbegin(), container.cend(), value), value
  );
}

// --------------------------------------------------------------------------------------

}  // namespace lesson_4
