/*
 * Created by Qt Creator 4.11.0 @ 23 Jun 2021 17:47:02
 *
 * Project: GB_CppAdvanced
 * File: test_module.cpp
 *
 * Author: Sergey Lola
 */
#include "test_module.h"

#include "lesson_1.h"

#include <tuple>
#include <iomanip>

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
  // лямбда функция, которая принимает фамилию и выводит номер телефона этого    	человека, либо строку с ошибкой
  auto print_phone_number = [&book](const string& surname) {
    cout << surname << "\t";
    const auto answer = book.GetPhoneNumber(surname);
    if (get<0>(answer).empty()) {
      cout << get<1>(answer);
    }
    else {
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
