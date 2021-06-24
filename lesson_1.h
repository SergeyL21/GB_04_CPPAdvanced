/*
 * Created by Qt Creator 4.11.0 @ 23 Jun 2021 17:33:56
 *
 * Project: GB_CppAdvanced
 * File: lesson_1.h
 *
 * Author: Sergey Lola
 */
#pragma once

#include <string>
#include <optional>
#include <fstream>
#include <vector>

namespace lesson_1 {

// --------------------------------------------------------------------------------------
struct Person {
  std::string surname;
  std::string first_name;
  std::optional<std::string> middle_name;

  Person() = default;
  inline Person(const std::string &_surname, const std::string &_first_name,
         const std::optional<std::string> &_middle_name = std::nullopt) :
    surname(_surname), first_name(_first_name), middle_name(_middle_name) {}
  ~Person() = default;

  friend std::ostream &operator<<(std::ostream &s, const Person &person);

  bool operator<(const Person &rhs) const;
  bool operator==(const Person &rhs) const;
};

// --------------------------------------------------------------------------------------
struct PhoneNumber {
  int country_code{0};
  int city_code{0};
  std::string number;
  std::optional<int> extra;

  PhoneNumber() = default;
  inline PhoneNumber(int _country_code, int _city_code, const std::string &_number,
                     const std::optional<int> &_extra = std::nullopt)
      : country_code(_country_code),
        city_code(_city_code),
        number(_number),
        extra(_extra) {}
  ~PhoneNumber() = default;

  friend std::ostream &operator<<(std::ostream &s, const PhoneNumber &rhs);

  bool operator<(const PhoneNumber &rhs) const;
};

// --------------------------------------------------------------------------------------
class PhoneBook {
public:
  PhoneBook(std::ifstream &file);

  friend std::ostream &operator<<(std::ostream &s, const PhoneBook &rhs);

  void SortByName();
  void SortByPhone();
  std::tuple<std::string, PhoneNumber> GetPhoneNumber(const std::string &surname) const;
  bool ChangePhoneNumber(const Person &person, const PhoneNumber &phone_number);

private:
  using data_pair = std::pair<Person, PhoneNumber>;
  std::vector<data_pair> m_data;
};

} // namespace lesson_1
