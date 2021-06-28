/*
 * Created by Qt Creator 4.11.0 @ 27 Jun 2021 21:10:32
 *
 * Project: GB_CppAdvanced
 * File: lesson_2.cpp
 *
 * Author: Sergey Lola
 */
#include "lesson_2.h"

#include <iostream>

#include "test_module.h"

using namespace std;

namespace lesson_2 {

// --------------------------- Timer class implementation -------------------------------
// --------------------------------------------------------------------------------------
Timer::Timer() : m_beg(clock_t::now()) {}

// --------------------------------------------------------------------------------------
Timer::Timer(const string &name) : m_name(name), m_beg(clock_t::now()) {}

// --------------------------------------------------------------------------------------
void Timer::start(const string &name) {
  m_name = name;
  m_beg = clock_t::now();
}

// --------------------------------------------------------------------------------------
void Timer::print() const {
  cout << m_name << ":" << utils::tab << elapsed() * 1000 << " ms" << endl;
}

// --------------------------------------------------------------------------------------
double Timer::elapsed() const {
  return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
}

}  // namespace lesson_2
