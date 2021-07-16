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
#include <deque>
#include <forward_list>
#include <random>
#include <map>

#include "lesson_1.h"
#include "lesson_2.h"
#include "lesson_3.h"
#include "lesson_4.h"
#include "lesson_5.h"

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

// --------------------------------------------------------------------------------------
void TestModule::lesson3_Task1() {
  using namespace lesson_3;
  cout << "--- TASK 1 ---" << endl;
  list<int> l {1, 2, 3, 4, 5};
  cout << "Before: ";
  utils::print(OUT cout, l);
  cout << endl;
  accumulateAndAppend(OUT l);
  cout << "After: ";
  utils::print(OUT cout, l);
  cout << endl << endl;
}

// --------------------------------------------------------------------------------------
void TestModule::lesson3_Task2() {
  using namespace lesson_3;
  cout << "--- TASK 2 ---" << endl;

  SquareMatrix<int> m1{{2, 2, 2, 2}, {1, 4, 1, 4}, {3, 5, 2, 3}, {5, 5, 4, 2}};
  cout << "Origin matrix M1: " << endl << m1;
  cout << "Determinant M1: " << m1.determinant() << endl << endl;

  SquareMatrix<double> m2{{0.5, 0.5}, {2.5, 4.35}};
  cout << "Origin matrix M2: " << endl << m2;
  cout << "Determinant M2: " << m2.determinant() << endl << endl;
}

// --------------------------------------------------------------------------------------
void TestModule::lesson3_Task3() {
  using namespace lesson_3;
  cout << "--- TASK 3 ---" << endl;
  TestContainer<int> container{1, 2, 3, 4, 5};
  cout << "For-range-based cycle: ";
  for (const auto &element : container) {
    cout << element << ' ';
  }
}

// --------------------------------------------------------------------------------------
void TestModule::lesson4_Task1() {
  using namespace lesson_4;
  cout << "--- TASK 1 ---" << endl;

  const auto insert_value1{3};
  vector<int> test_c1{1, 2, 4, 5};
  cout << "Test container 1 (vector) - before: ";
  utils::print(OUT cout, test_c1);
  cout << endl;
  insert_sorted(OUT test_c1, insert_value1);
  cout << "Insert value = " << insert_value1 << endl;
  cout << "Test container 1 (vector) - after:  ";
  utils::print(OUT cout, test_c1);
  cout << endl << endl;

  const auto insert_value2{5};
  list<int> test_c2{2, 3, 4, 7, 8};
  cout << "Test container 2 (list) - before: ";
  utils::print(OUT cout, test_c2);
  cout << endl;
  insert_sorted(OUT test_c2, insert_value2);
  cout << "Insert value = " << insert_value2 << endl;
  cout << "Test container 2 (list) - after:  ";
  utils::print(OUT cout, test_c2);
  cout << endl << endl;

  const auto insert_value3{0.9f};
  deque<float> test_c3{0.3f, 0.5f, 1.1f, 1.4f};
  cout << "Test container 3 (deque) - before: ";
  utils::print(OUT cout, test_c3);
  cout << endl;
  insert_sorted(OUT test_c3, insert_value3);
  cout << "Insert value = " << insert_value3 << endl;
  cout << "Test container 3 (deque) - after:  ";
  utils::print(OUT cout, test_c3);
  cout << endl << endl;
}

// --------------------------------------------------------------------------------------
void TestModule::lesson4_Task2() {
  using namespace lesson_4;
  cout << "--- TASK 2 ---" << endl;
  cout << fixed << setprecision(2);

  // генерация массива синусоидального аналового сигнала
  vector<double> analog_data(100);
  random_device rnd_device;
  mt19937 generator{rnd_device()};
  uniform_int_distribution<> dis(0, 180);
  int dt{0};
  generate(analog_data.begin(), analog_data.end(), [&generator, &dis, &dt](){
    const auto fi = dis(generator);
    return 10 * sin(2. * M_PI * (dt++) + fi);
  });

  // создания массива цифрового сигнала, путем откидывания дробного значения из
  // массива аналоговых сигналов
  vector<int> digital_data(analog_data.cbegin(), analog_data.cend());
  //transform(analog_data.cbegin(), analog_data.cend(), digital_data.begin(),
  //          [](auto value) { return static_cast<int>(value); });
  cout << "Print analog signals array: ";
  utils::print(OUT cout, analog_data);
  cout << endl << endl;
  cout << "Print digital signals array: ";
  utils::print(OUT cout, digital_data);
  cout << endl << endl;

  // подсчет ошибки
  const auto D = inner_product(
    analog_data.cbegin(),
    analog_data.cend(),
    digital_data.cbegin(),
    0.,
    std::plus<double>(),
    [](const auto &a, const auto &b) {
      return pow(a - b, 2);
    }
  );
  cout << "D: " << D << endl;
}

// --------------------------------------------------------------------------------------
void TestModule::lesson5_Task1() {
  using namespace lesson_5;
  cout << "--- TASK 1 ---" << endl;

  // Input Iterator
  vector<string> seq_1 {"bow", "sword", "crossbow", "gun", "pike", "sword", "bow"};
  cout << "Print sequence of unique words - test 1 (input iterator)" << endl;
  cout << " Before: ";
  copy(seq_1.cbegin(), seq_1.cend(), ostream_iterator<string>{OUT cout, " "});
  cout << endl << " After:  ";
  printUnique(seq_1.begin(), seq_1.end());
  cout << endl << endl;

  // Bidirectional Iterator
  list<string> seq_2 { "alpha", "beta", "gamma", "omega", "alpha", "beta", "epsilon" };
  cout << "Print sequence of unique words - test 2 (bidirectional iterator)" << endl;
  cout << " Before: ";
  copy(seq_2.cbegin(), seq_2.cend(), ostream_iterator<string>{OUT cout, " "});
  cout << endl << " After:  ";
  printUnique(seq_2.begin(), seq_2.end());
  cout << endl << endl;

  forward_list<string> seq_3 { "1", "0", "00", "11", "1", "01", "0", "10"};
  cout << "Print sequence of unique words - test 3 (forward iterator)" << endl;
  cout << " Before: ";
  copy(seq_3.cbegin(), seq_3.cend(), ostream_iterator<string>{OUT cout, " "});
  cout << endl << " After:  ";
  printUnique(seq_3.begin(), seq_3.end());
  cout << endl << endl;
}

// --------------------------------------------------------------------------------------
void TestModule::lesson5_Task2() {
  using namespace lesson_5;
  cout << "--- TASK 2 ---" << endl;

  string input;
  cout << "Input any text separated into the sentences ('.', '?', '!', '...', '!!!'):" << endl;
  getline(OUT cin, OUT input);
  multimap<size_t, string> sentenses;
  // разбор введенных данных на предложения
  // разделители предложений: '.', '?', '!', '...', '!!!'
  const string delimiters {".?!...!!!"};
  size_t start{input.find_first_not_of(delimiters)}, end{};
  while (start != string::npos) {
    end = input.find_first_of(delimiters, start);
    // пропускаем все следующие вхождения разделителей и начинаем поиск нового предложения
    auto sentence = input.substr(start, end - start);
    // удаление лишнего пробела спереди
    sentence.erase(0, sentence.find_first_not_of(' '));
    // добавляем полученное предложение в multimap
    sentenses.insert(make_pair(sentence.size(), sentence));
    // пропускаем все следующие вхождения разделителей и начинаем поиск нового предложения
    start = input.find_first_not_of(delimiters, end);
  }

  cout << endl << "Parsing the entered sentences:" << endl;
  utils::print(OUT cout, sentenses, '\n');
}
