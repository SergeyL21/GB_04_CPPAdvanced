/*
 * Created by Qt Creator 4.11.0 @ 27 Jun 2021 21:07:15
 *
 * Project: GB_CppAdvanced
 * File: lesson_2.h
 *
 * Author: Sergey Lola
 */
#pragma once

#include <algorithm>
#include <chrono>
#include <string>
#include <type_traits>
#include <vector>

namespace lesson_2 {

// --------------------------------------------------------------------------------------
template <typename T>
using T_Ptr = std::add_pointer_t<std::decay_t<T>>;

// --------------------------------------------------------------------------------------
template <typename T>
void Swap(T_Ptr<T> a, T_Ptr<T> b) {
  std::decay_t<T> temp = *a;
  *a = *b;
  *b = temp;
  return;
}

// --------------------------------------------------------------------------------------
template <typename T>
void SortPointers(std::vector<T_Ptr<T>> &v) {
  std::sort(v.begin(), v.end(), [](T_Ptr<T> a, T_Ptr<T> b) { return *a < *b; });
}

// --------------------------------------------------------------------------------------
class Timer {
 public:
  Timer();
  Timer(const std::string &name);
  ~Timer() = default;

  void start(const std::string &name);
  void print() const;

 private:
  using clock_t = std::chrono::high_resolution_clock;
  using second_t = std::chrono::duration<double, std::ratio<1>>;

  std::string m_name;
  std::chrono::time_point<clock_t> m_beg;
  double elapsed() const;
};

}  // namespace lesson_2
