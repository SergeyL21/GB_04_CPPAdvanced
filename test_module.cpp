/*
 * Created by Qt Creator 4.11.0 @ 23 Jun 2021 17:47:02
 *
 * Project: GB_CppAdvanced
 * File: test_module.cpp
 *
 * Author: Sergey Lola
 */
#include "test_module.h"

#include <cstring>
#include <fstream>
#include <iomanip>
#include <tuple>

#include "lesson_1.h"
#include "lesson_2.h"

using namespace std;

// --------------------------------------------------------------------------------------
void TestModule::lesson1_Task3() {
  using namespace lesson_1;
  cout << "--- TASK 3 ---" << endl;

  ifstream file("db.txt");
  PhoneBook book(OUT file);
  cout << book;

  cout << "------ SortByName --------" << endl;
  book.SortByName();
  cout << book;

  cout << "------ SortByPhone -------" << endl;
  book.SortByPhone();
  cout << book;

  cout << "----- GetPhoneNumber -----" << endl;
  // лямбда функция, которая принимает фамилию и выводит номер телефона этого
  // человека, либо строку с ошибкой
  auto print_phone_number = [&book](const string &surname) {
    cout << surname << "\t";
    const auto answer = book.GetPhoneNumber(surname);
    if (get<0>(answer).empty()) {
      cout << get<1>(answer);
    } else {
      cout << get<0>(answer);
    }
    cout << endl;
  };

  // вызовы лямбды
  print_phone_number("*T-800* ");
  print_phone_number("Egorushkina");
  print_phone_number("Sokolova");

  cout << "---- ChangePhoneNumber ----" << endl;
  book.ChangePhoneNumber(Person{"Zaytceva", "Maria", "Andreevna"},
                         PhoneNumber{7, 123, "15344458", nullopt});
  cout << book;
}

// --------------------------------------------------------------------------------------
void TestModule::lesson2_Task1() {
  using namespace lesson_2;
  cout << "--- TASK 1 ---" << endl;
  auto val1 = make_unique<double>(0.333);
  auto val2 = make_unique<double>(0.);
  cout << "Before pointers swap: val1 = " << *val1 << ", val2 = " << *val2 << endl;
  Swap<double>(val1.get(), val2.get());
  cout << "After pointers swap:  val1 = " << *val1 << ", val2 = " << *val2 << endl;
  cout << endl;
}

// --------------------------------------------------------------------------------------
void TestModule::lesson2_Task2() {
  using namespace lesson_2;
  cout << "--- TASK 2 ---" << endl;
  vector<int *> v{new int{7}, new int{13}, new int{4}, new int{3}, new int{-1}};
  auto printVector = [](const auto &v) {
    for_each(v.cbegin(), v.cend(), [](auto ptr) { cout << *ptr << " "; });
  };
  cout << "Before sort vector: ";
  printVector(v);
  cout << endl;

  SortPointers<int>(v);
  cout << "After sort vector: ";
  printVector(v);
  cout << endl << endl;

  // очистка выделенных ресурсов
  for_each(v.begin(), v.end(), [](auto ptr) { delete ptr; });
}

// --------------------------------------------------------------------------------------
void TestModule::lesson2_Task3() {
  using namespace lesson_2;
  cout << "--- TASK 3 ---" << endl;
  const vector<char> vowels{'A', 'E', 'I', 'O', 'U', 'Y', 'a', 'e', 'i', 'o', 'u', 'y'};

  ifstream file("war_and_peace_pt1.txt");
  Timer timer;
  if (file.is_open()) {
    string data;
    // заранее резервируем место под данные
    file.seekg(0u, ios::end);
    data.reserve(file.tellg());
    file.seekg(0u, ios::beg);
    data.assign(istreambuf_iterator<char>{file}, istreambuf_iterator<char>{});

    // первый способ (count_if и find)
    timer.start("Test 1 (count_if + find)");
    auto counter = count_if(data.cbegin(), data.cend(), [&](char ch) {
      auto res = find(vowels.cbegin(), vowels.cend(), ch);
      return res != vowels.cend();
    });
    timer.print();
    cout << "Vowels counter: " << counter << endl << endl;

    // второй способ (count_if и цикл for)
    timer.start("Test 2 (count_if + cycle for)");
    counter = count_if(data.cbegin(), data.cend(), [&](char ch) {
      for (size_t n{0u}; n < vowels.size(); ++n) {
        if (ch == vowels.at(n)) return true;
      }
      return false;
    });
    timer.print();
    cout << "Vowels counter: " << counter << endl << endl;

    // третий способ (цикл for и find)
    counter = 0;
    timer.start("Test 3 (cycle for + find)");
    for (const auto &ch : data) {
      if (find(vowels.cbegin(), vowels.cend(), ch) != vowels.cend()) {
        counter++;
      }
    }
    timer.print();
    cout << "Vowels counter: " << counter << endl << endl;

    // четвертый способ (2 цикла for)
    counter = 0;
    timer.start("Test 4 (two for cycles)");
    for (const auto &ch : data) {
      for (size_t n{0u}; n < vowels.size(); ++n) {
        if (ch == vowels.at(n)) {
          ++counter;
          break;
        }
      }
    }
    timer.print();
    cout << "Vowels counter: " << counter << endl << endl;

    // доп. способ
    timer.start("Extra test (count_if + strchr)");
    // цикл for сам по себе достаточно медленный, поэтому реализация с do-while
    // внутри std::strchr работает быстрее нежели два цикла for из теста 4 например
    counter = count_if(data.cbegin(), data.cend(), [&](char ch) {
      return (nullptr != std::strchr("AEIOUYaeiouy", ch));
    });
    timer.print();
    cout << "Vowels counter: " << counter << endl << endl;

    file.close();
  }
}
