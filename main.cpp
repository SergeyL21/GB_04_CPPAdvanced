/*
 * Created by Qt Creator 4.11.0 @ 23 Jun 2021 18:21:18
 *
 * Project: GB_CppAdvanced
 * File: main.cpp
 *
 * Author: Sergey Lola
 */

#include "test_module.h"

#ifdef ENABLE_GOOGLE_TEST_SECTION
TEST(Lesson_08, test_for_lesson7_Task3) {
  TestModule::lesson7_Task3();
}
#endif //ENABLE_GOOGLE_TEST_SECTION

// --------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  UNUSED(argc)
  UNUSED(argv)

  setlocale(LC_ALL, "Russian");

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
