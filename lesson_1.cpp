/*
 * Created by Qt Creator 4.11.0 @ 23 Jun 2021 17:39:11
 *
 * Project: GB_CppAdvanced
 * File: lesson_1.cpp
 *
 * Author: Sergey Lola
 */
#include "lesson_1.h"

#include <iomanip>
#include <regex>

#include "test_module.h"

using namespace std;

namespace lesson_1 {

// ------------------------------- LOCAL VARIABLES --------------------------------------
// --------------------------------------------------------------------------------------
const int OUTPUT_OFFSET{14};
const char FILE_LINE_DELIMITER{'\n'};
const char FILE_FORMAT_DELIMITER{','};

// -------------------------- Person class implementation -------------------------------
// --------------------------------------------------------------------------------------
ostream &operator<<(ostream &s, const Person &person) {
  s << setw(OUTPUT_OFFSET) << person.surname << setw(OUTPUT_OFFSET) << person.first_name
    << setw(OUTPUT_OFFSET);
  return person.middle_name ? (s << *person.middle_name) : s;
}

// --------------------------------------------------------------------------------------
bool Person::operator<(const Person &rhs) const {
  const auto first_cmp = surname.compare(rhs.surname);
  if (0 == first_cmp) {
    const auto second_cmp = first_name.compare(rhs.first_name);
    if (0 == second_cmp) {
      return ((*middle_name).compare(*rhs.middle_name) < 0);
    }
    return (second_cmp < 0);
  }
  return (first_cmp < 0);
}

// --------------------------------------------------------------------------------------
bool Person::operator==(const Person &rhs) const {
  return (tie(OUT surname, OUT first_name, OUT middle_name) ==
          tie(OUT rhs.surname, OUT rhs.first_name, OUT rhs.middle_name));
}

// ------------------------ PhoneNumber class implementation ----------------------------
// --------------------------------------------------------------------------------------
ostream &operator<<(ostream &s, const PhoneNumber &rhs) {
  return s << "+" << rhs.country_code << "(" << rhs.city_code << ")" << rhs.number
           << (rhs.extra ? string{" "}.append(to_string(*rhs.extra)) : string{});
}

// --------------------------------------------------------------------------------------
bool PhoneNumber::operator<(const PhoneNumber &rhs) const {
  if (country_code == rhs.country_code) {
    if (city_code == rhs.city_code) {
      const auto number_cmp = number.compare(rhs.number);
      if (0 == number_cmp) {
        return (extra ? *extra < *rhs.extra : false);
      }
      return (number_cmp < 0);
    }
    return (city_code < rhs.city_code);
  }
  return (country_code < rhs.country_code);
}

// -------------------------- PhoneBook class implementation ----------------------------
// --------------------------------------------------------------------------------------
PhoneBook::PhoneBook(ifstream &file) {
  if (file.is_open()) {
    string data;
    // заранее резервируем место под данные
    file.seekg(0u, ios::end);
    data.reserve(file.tellg());
    file.seekg(0u, ios::beg);

    data.assign(istreambuf_iterator<char>{file}, istreambuf_iterator<char>{});

    vector<string> lines;
    // сначала разбираем каждую строку
    utils::splitString(data, FILE_LINE_DELIMITER, back_inserter(OUT lines));
    for (auto line_it = lines.cbegin(); line_it != lines.cend(); ++line_it) {
      vector<string> words;
      // затем разбираем в полученной строке отдельные слова
      utils::splitString(*line_it, FILE_FORMAT_DELIMITER, back_inserter(OUT words));
      size_t index{0u};
      Person person;
      PhoneNumber phone_number;
      for (auto word_it = words.cbegin(); word_it != words.cend(); ++word_it, ++index) {
        switch (index) {
          case 0:
            person.surname = *word_it;
            break;
          case 1:
            person.first_name = *word_it;
            break;
          case 2:
            person.middle_name = make_optional(*word_it);
            break;
          case 3:
            phone_number.country_code = stoi(*word_it);
            break;
          case 4:
            phone_number.city_code = stoi(*word_it);
            break;
          case 5:
            phone_number.number = *word_it;
            break;
          case 6:
            phone_number.extra = make_optional(stoi(*word_it));
            break;
        }
      }
      m_data.push_back(make_pair(person, phone_number));
    }
    file.close();
  }
}

// --------------------------------------------------------------------------------------
ostream &operator<<(ostream &s, const PhoneBook &rhs) {
  for (const auto &[person, phone_number] : rhs.m_data) {
    s << person << setw(OUTPUT_OFFSET) << phone_number << endl;
  }
  return s;
}

// --------------------------------------------------------------------------------------
void PhoneBook::SortByName() {
  sort(m_data.begin(), m_data.end(),
       [](const auto &pA, const auto &pB) -> bool { return pA.first < pB.first; });
}

// --------------------------------------------------------------------------------------
void PhoneBook::SortByPhone() {
  sort(m_data.begin(), m_data.end(),
       [](const auto &pA, const auto &pB) -> bool { return pA.second < pB.second; });
}

// --------------------------------------------------------------------------------------
std::tuple<string, PhoneNumber> PhoneBook::GetPhoneNumber(const string &surname) const {
  auto counter{0};
  PhoneNumber value;
  for_each(m_data.cbegin(), m_data.cend(), [&](const auto &p) -> void {
    if (p.first.surname == surname) {
      value = p.second;
      counter++;
    }
  });

  const auto key{1 == counter ? string{}
                              : (0 == counter ? "not found" : "found more than 1")};
  return make_tuple(key, value);
}

// --------------------------------------------------------------------------------------
bool PhoneBook::ChangePhoneNumber(const Person &person, const PhoneNumber &phone_number) {
  auto it = find_if(m_data.begin(), m_data.end(),
                    [&person](const auto &p) -> bool { return p.first == person; });
  if (it != m_data.end()) {
    (*it).second = phone_number;
    return true;
  }
  return false;
}

}  // namespace lesson_1
