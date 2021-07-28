/*
 * Created by Qt Creator 4.11.0 @ 23 Jun 2021 18:21:18
 *
 * Project: GB_CppAdvanced
 * File: main.cpp
 *
 * Author: Sergey Lola
 */

#include "test_module.h"

// --------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  UNUSED(argc)
  UNUSED(argv)

  setlocale(LC_ALL, "Russian");

  TestModule::lesson7_Task2();
  TestModule::lesson7_Task3();

  return 0;
}
