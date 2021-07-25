/*
 * Created by Qt Creator 4.11.0 @ 21 Jul 2021 17:41:29
 *
 * Project: GB_CppAdvanced
 * File: lesson_6.h
 *
 * Author: Sergey Lola
 */
#pragma once

#include <ostream>
#include <mutex>
#include <vector>
#include <map>
#include <iostream>

namespace lesson_6 {

// --------------------------------------------------------------------------------------
class OutputWrapper {
public:
  using Manipulator = std::add_pointer_t<std::ostream&(std::ostream&)>;

  inline OutputWrapper(std::ostream &stream) : m_stream{stream} {}
  ~OutputWrapper() = default;

  // для экземпляров типов
  template <typename T>
  OutputWrapper &operator<<(T const &obj) {
    std::lock_guard guard{m_mutex};
    m_stream << obj;
    return *this;
  }

  // для функций
  OutputWrapper &operator<<(Manipulator manip) {
    std::lock_guard guard{m_mutex};
    m_stream << manip;
    return *this;
  }

private:
  std::ostream &m_stream;
  std::mutex m_mutex;
};

// --------------------------------------------------------------------------------------
class Home {
public:
  struct Item {
    std::string name;
    int worth{0};

    inline Item() {}
    inline Item(const std::string &_name, int _worth) : name(_name), worth(_worth) {}

    friend std::ostream &operator<<(std::ostream &stream, const Item &item);
  };

  void addItem(const Item &item, const std::string &person = {});
  Item takeWorthItem(const std::string &person = {});

private:
  std::multimap<int, Item> m_items;
  std::mutex m_mutex;
};

}  // namespace lesson_6
