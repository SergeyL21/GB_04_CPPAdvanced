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

// ---------------------------------------------------------------------------
// вспомогательная шаблонная функция для вывода в консоль значения
template <typename T>
std::ostream &print(std::ostream &out,
                    T const &value,
                    char separator = char{}) {
  return (out << value << separator);
}

// ---------------------------------------------------------------------------
// вспомогательная шаблонная функция для вывода в консоль пары значений
template <typename T1, typename T2>
std::ostream &print(std::ostream &out,
                    std::pair<T1, T2> const &value,
                    char separator = char{}) {
  return (out << '{' << value.first << ", " << value.second << "}" << separator);
}

// ---------------------------------------------------------------------------
// вспомогательная шаблонная функция для вывода в консоль любого контейнера
template <template<typename, typename...> class TT, typename... Args>
std::ostream &print(std::ostream &out,
                    TT<Args...> const &container,
                    char separator = char{}) {
  for (auto &&element : container) print(out, element, separator);
  return out;
}

}  // namespace utils

class TestModule {
 public:
  static void lesson1_Task3();

  static void lesson2_Task1();
  static void lesson2_Task2();
  static void lesson2_Task3();

  static void lesson3_Task1();
  static void lesson3_Task2();
  static void lesson3_Task3();

  static void lesson4_Task1();
  static void lesson4_Task2();

  static void lesson5_Task1();
  static void lesson5_Task2();

  static void lesson6_Task1();
  static void lesson6_Task2();
  static void lesson6_Task3();
};
