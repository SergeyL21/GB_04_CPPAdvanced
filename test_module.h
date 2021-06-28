/*
 * Created by Qt Creator 4.11.0 @ 23 Jun 2021 17:45:07
 *
 * Project: GB_CppAdvanced
 * File: test_module.h
 *
 * Author: Sergey Lola
 */
#pragma once

#include <iostream>
#include <sstream>

// ---------------------------------------------------------------------------
// вспомогательный макрос для обозначения передачи по ссылке
#undef OUT
#define OUT

// ---------------------------------------------------------------------------
// вспомогательный макрос для удаления предупреждения об неиспользуемой
// переменной
#undef UNUSED
#define UNUSED(X) (void)(X);

namespace utils {
// ---------------------------------------------------------------------------
// вспомогательная шаблонная функция разделения строк по символу-разделителю
template <typename Out>
void splitString(const std::string &s, char delim, Out result) {
  std::istringstream iss(s);
  std::string item;
  while (std::getline(iss, OUT item, delim)) {
    *result++ = item;
  }
}

// ---------------------------------------------------------------------------
// вспомогательная шаблонная функция табулирования потока вывода
template <typename _CharT, typename _Traits>
inline std::basic_ostream<_CharT, _Traits> &tab(std::basic_ostream<_CharT, _Traits> &os) {
  return os.put(os.widen('\t'));
}

}  // namespace utils

class TestModule {
 public:
  static void lesson1_Task3();
  static void lesson2_Task1();
  static void lesson2_Task2();
  static void lesson2_Task3();
};
