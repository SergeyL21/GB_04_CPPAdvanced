/*
 * Created by Qt Creator 4.11.0 @ 23 Jun 2021 17:47:02
 *
 * Project: GB_CppAdvanced
 * File: test_module.cpp
 *
 * Author: Sergey Lola
 */
#include "test_module.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <cstring>
#include <fstream>
#include <iomanip>
#include <tuple>
#include <deque>
#include <forward_list>
#include <random>
#include <map>
#include <thread>
#include <future>

#include "lesson_1.h"
#include "lesson_2.h"
#include "lesson_3.h"
#include "lesson_4.h"
#include "lesson_5.h"
#include "lesson_6.h"
#include "lesson_7.h"

#ifdef ENABLE_PROTOBUF_SECTION
#include "protobuf/data.pb.h"
#endif // ENABLE_PROTOBUF_SECTION

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
  cout /*<< fixed*/ << setprecision(2);

  // генерация массива синусоидального аналового сигнала
  vector<double> analog_data(100);
  double dt{0.};
  generate(analog_data.begin(), analog_data.end(), [&dt](){
    dt += 0.1;
    return 3. * sin(dt * M_PI_2 + 5.);
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

// --------------------------------------------------------------------------------------
void TestModule::lesson6_Task1() {
  using namespace lesson_6;
  cout << "--- TASK 1 ---" << endl;

  OutputWrapper pcout{OUT cout};
  auto func = [&pcout](int local_id) {
    for (size_t i{0u}; i < 5; ++i) {
      pcout << "thread-safe cout: th" << local_id <<
               " is in " << i << " iteration" << endl;
      this_thread::sleep_for(500ms);
    }
  };
  thread th1(func, 1);
  thread th2(func, 2);
  thread th3(func, 3);
  th1.join();
  th2.join();
  th3.join();

  pcout << endl;
}

// --------------------------------------------------------------------------------------
void TestModule::lesson6_Task2() {
  using namespace lesson_6;
  cout << "--- TASK 2 ---" << endl;

  OutputWrapper pcout{OUT cout};
  auto isPrime = [](uint64_t number) -> bool {
    for (uint64_t i{3ull}; (i*i) <= number; i += 2ull) {
      if (!(number % i)) return false;
    }
    return true;
  };

  auto getPrimeNumberByIndex = [isPrime, &pcout](uint64_t index) -> uint64_t {
    // кол-во вызовов информации о прогрессе расчета
    const auto sections{20};
    const auto div{index / sections};
    // если индекс равен единице, то нет смысла производить расчеты и
    // выводим первое простое число = 2
    if (1u == index) return 2u;
    uint64_t number{1ull}, counter{1ull};
    while (counter < index) {
      number += 2ull;
      if (isPrime(number)) {
        if (!(++counter % div)) {
          pcout << "Progress " << double(counter) / div * (100. / sections) << "%" << endl;
        }
      }
    }
    return number;
  };

  const auto prime_index{1'000'000};
  pcout << "Start prime number calculating: index i = " << prime_index << endl;
  auto futurePrimeRes(async(launch::async, getPrimeNumberByIndex, prime_index));
  const auto result{futurePrimeRes.get()};
  pcout << "End prime number calculating: result of index i = " << prime_index << " is " <<
           result << endl << endl;
}

// --------------------------------------------------------------------------------------
void TestModule::lesson6_Task3() {
  using namespace lesson_6;
  cout << "--- TASK 3 ---" << endl;

  Home home;
  const auto MASTER_NAME{"MASTER"};
  const auto THIEF_NAME{"THIEF"};
  // кол-во предметов, которые принесет хозяин
  const auto MAX_MASTER_ITEMS{10u};
  // кол-во проникновений вора в дом хозяина
  const auto MAX_THIEF_VISITS{5u};
  // интервал времени через которое хозяин принесет новую вещь
  const auto MASTER_INTERVAL{10ms};

  thread th_master{[=, &home]() {
    const auto seed{chrono::steady_clock::now().time_since_epoch().count() + 1ll};
    mt19937_64 generator{uint64_t(seed)};
    // разброс значений для ценности вещи
    uniform_int_distribution<> distr{0, 10};
    for (size_t n{0u}; n < MAX_MASTER_ITEMS; ++n) {
      this_thread::sleep_for(MASTER_INTERVAL);
      // генерируем вещь
      Home::Item item{{"item " + to_string(n + 1)}, distr(OUT generator)};
      // добавляем в дом
      home.addItem(item, MASTER_NAME);
    }
  }};

  thread th_thief{[=, &home](){
    const auto seed{chrono::steady_clock::now().time_since_epoch().count() + 2ll};
    mt19937_64 generator{uint64_t(seed)};
    // разброс промежутков времени, через которые вор наведывается к хозяину
    uniform_int_distribution<> distr{16, 21};
    for (size_t n{0u}; n < MAX_THIEF_VISITS; ++n) {
      this_thread::sleep_for(chrono::milliseconds{distr(OUT generator)});
      // вор забирает одну самую ценную вещь
      home.takeWorthItem(THIEF_NAME);
    }
  }};

  th_master.join();
  th_thief.join();
}

// --------------------------------------------------------------------------------------
void TestModule::lesson7_Task2() {
#ifdef ENABLE_PROTOBUF_SECTION
  using namespace lesson_7;
  cout << "--- TASK 2 ---" << endl;

  // инициализируем данные
  pb::StudentGroup group;
  pb::FullName full_name;
  full_name.set_name("Vasia");
  full_name.set_surname("Pupkin");

  auto student = group.add_students();
  student->add_scores(75);
  student->add_scores(25);
  student->add_scores(45);
  student->mutable_fullname()->Swap(&full_name);
  const auto &scores_ref{student->scores()};
  const auto average{
    accumulate(scores_ref.cbegin(), scores_ref.cend(), 0) / scores_ref.size()};
  student->set_average_score(average);

  cout << "Before serialization: " << endl;
  cout << group.DebugString() << endl;

  // выполняем сериализацию
  string data;
  group.SerializeToString(&data);

  // выполняем десериализацию
  group.Clear();
  group.ParseFromString(data);
  cout << "After deserialization: " << endl;
  cout << group.DebugString() << endl << endl;
#endif // ENABLE_PROTOBUF_SECTION
}

// --------------------------------------------------------------------------------------
void TestModule::lesson7_Task3() {
  using namespace lesson_7;
#ifndef ENABLE_GOOGLE_TEST_SECTION
  cout << "--- TASK 3 ---" << endl;
#endif //ENABLE_GOOGLE_TEST_SECTION

  auto getAverageScore = [](const auto &v) {
    return double(accumulate(v.cbegin(), v.cend(), 0)) / v.size();
  };

  // инициализируем данные
  FullName full_name_st1;
  full_name_st1.name = string{"Vasia"};
  full_name_st1.surname = string{"Pupkin"};
  FullName full_name_st2;
  full_name_st2.name = string{"Pavel"};
  full_name_st2.surname = string{"Morozov"};
  full_name_st2.patronymic = string{"Petrovich"};

  Student student_st1;
  student_st1.full_name = full_name_st1;
  student_st1.scores = {75, 25, 45};
  student_st1.average_score = getAverageScore(student_st1.scores);
  Student student_st2;
  student_st2.full_name = full_name_st2;
  student_st2.scores = {35, 50, 95};
  student_st2.average_score = getAverageScore(student_st2.scores);

  StudentsGroup group_A{{student_st1, student_st2}};
#ifndef ENABLE_GOOGLE_TEST_SECTION
  cout << "Before serialization: " << endl;
  cout << group_A.GetAllInfo() << endl;
#endif //ENABLE_GOOGLE_TEST_SECTION
  group_A.Save();

  StudentsGroup group_B{};
  group_B.Open();
#ifndef ENABLE_GOOGLE_TEST_SECTION
  cout << "After deserialization: " << endl;
  cout << group.GetAllInfo() << endl;
#else
  ASSERT_EQ(group_A.Size(), group_B.Size());
  const auto student_res_1 = group_B.Find(student_st1.full_name);
  ASSERT_TRUE(nullptr != student_res_1);
  const auto student_res_2 = group_B.Find(student_st2.full_name);
  ASSERT_TRUE(nullptr != student_res_2);
  // проверка первого студента
  for (size_t n{0u}; n < student_st1.scores.size(); ++n) {
    SCOPED_TRACE(n);
    ASSERT_EQ(student_st1.scores[n], student_res_1->scores[n]);
  }
  ASSERT_NEAR(student_st1.average_score,
              student_res_1->average_score,
              numeric_limits<double>::epsilon());
  // проверка второго студента
  for (size_t n{0u}; n < student_st2.scores.size(); ++n) {
    SCOPED_TRACE(n);
    ASSERT_EQ(student_st2.scores[n], student_res_2->scores[n]);
  }
  ASSERT_NEAR(student_st2.average_score,
              student_res_2->average_score,
              numeric_limits<double>::epsilon());
#endif //ENABLE_GOOGLE_TEST_SECTION
}
