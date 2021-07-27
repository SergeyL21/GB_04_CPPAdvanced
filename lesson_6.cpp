/*
 * Created by Qt Creator 4.11.0 @ 21 Jul 2021 17:44:36
 *
 * Project: GB_CppAdvanced
 * File: lesson_6.cpp
 *
 * Author: Sergey Lola
 */
#include "lesson_6.h"

#include <iomanip>

using namespace std;

namespace lesson_6 {

// --------------------------------------------------------------------------------------
std::ostream &operator<<(ostream &stream, const Home::Item &item) {
  return stream << "{ name = " << quoted(item.name) << ", worth = " << item.worth << "}";
}

// --------------------------------------------------------------------------------------
void Home::addItem(const Home::Item &item, const std::string &person) {
  std::lock_guard guard{m_mutex};
  m_items.emplace(make_pair(item.worth, item));
  cout << "Add to item [" << person.c_str() << "]: " << item << endl;
}

// --------------------------------------------------------------------------------------
Home::Item Home::takeWorthItem(const std::string &person) {
  std::lock_guard guard{m_mutex};
  if (!m_items.empty()) {
    Home::Item item{m_items.rbegin()->second};
    m_items.erase(--m_items.end());
    cout << "Take item from home [" << person.c_str() << "]: " << item << endl;
    return item;
  }
  cout << "It's nothing to take from home [" << person.c_str() << "]" << endl;
  return {};
}

}  // namespace lesson_6
