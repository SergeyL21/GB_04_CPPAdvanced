/*
 * Created by Qt Creator 4.11.0 @ 03 Jul 2021 14:04:29
 *
 * Project: GB_CppAdvanced
 * File: lesson_3.h
 *
 * Author: Sergey Lola
 */
#pragma once

#include <list>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <memory>

namespace lesson_3 {

// --------------------------------------------------------------------------------------

template <typename T>
void accumulateAndAppend(std::list<T> &l) {
  const auto sum = std::accumulate(l.cbegin(), l.cend(), T{});
  l.push_back(sum / l.size());
}

// --------------------------------------------------------------------------------------
template<typename T>
class SquareMatrix {
public:
  SquareMatrix(std::size_t N) : m_N(N), m_size(N * N) {
    m_data = new T*[m_N];
    for (std::size_t i{0u}; i < m_N; ++i) {
      m_data[i] = new T[m_N];
    }
  }
  SquareMatrix(std::initializer_list<std::initializer_list<T>> l) :
    m_N(l.size()), m_size(l.size() * l.size()) {
    m_data = new T*[m_N];
    auto it{l.begin()};
    for (std::size_t i{0u}; i < m_N; ++i, ++it) {
      m_data[i] = new T[m_N];
      std::copy(it->begin(), it->end(), m_data[i]);
    }
  }

  ~SquareMatrix(void) {
    clearMatrix(m_data, m_N);
  };

  const T* operator[](std::size_t index) const { return m_data[index]; }
  T* operator[](std::size_t index) { return m_data[index]; }

  friend std::ostream& operator<<(std::ostream &s, const SquareMatrix &matrix) {
    for (std::size_t i{0u}; i < matrix.m_N; ++i) {
      for (std::size_t j{0u}; j < matrix.m_N; ++j) {
        s << matrix[i][j];
        if (j + 1 != matrix.m_N) {
          s << ' ';
        }
      }
      s << std::endl;
    }
    return s;
  }

  T getElement(std::size_t x, std::size_t y, bool *ok = nullptr) const {
    if (x * y < m_size) {
      if (nullptr != ok) *ok = true;
      return m_data[x][y];
    }
    if (nullptr != ok) *ok = false;
    return T{};
  }

  bool setElement(std::size_t x, std::size_t y, T num) {
    if (x * y < m_size) {
      m_data[x][y] = num;
      return true;
    }
    return false;
  }

  T determinant() const {
    return determinant(m_data, m_N);
  }

private:
  T determinant(T **matrix, std::size_t N) const {
    if (1 == N) {
      return matrix[0][0];
    }
    if (2 == N) {
      return (matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1]);
    }

    auto createSubmatrix = [](T **matrix, std::size_t N, std::size_t x, std::size_t y) -> T** {
      T **submatrix = new T*[N - 1];
      for (std::size_t i{0u}, sub_i{0u}; i < N; ++i) {
        submatrix[sub_i] = new T[N - 1];
        if (i == y) continue;
        for (std::size_t j{0u}, sub_j{0u}; j < N; ++j) {
          if (j == x) continue;
          submatrix[sub_i][sub_j] = matrix[i][j];
          ++sub_j;
        }
        ++sub_i;
      }
      return submatrix;
    };

    T res{};
    for (std::size_t x{0u}; x < N; ++x) {
      T **submatrix = createSubmatrix(matrix, N, x, 0u);
      res += (!(x % 2) ? 1 : -1) * matrix[0][x] * determinant(submatrix, N - 1);
      clearMatrix(submatrix, N - 1);
    }
    return res;
  }

  void clearMatrix(T **matrix, std::size_t N) const {
    for (std::size_t i{0u}; i < N; ++i) {
      delete[] matrix[i];
    }
    delete[] matrix;
  }

private:
    T **m_data;
    const std::size_t m_N;
    const std::size_t m_size;
};

// --------------------------------------------------------------------------------------
template <typename T>
class TestContainer {

  template <typename ValueType>
  struct InnerIterator : std::iterator<std::input_iterator_tag, ValueType> {
    friend class TestContainer<ValueType>;
    using pointer = typename InnerIterator::pointer;
    using reference = typename InnerIterator::reference;
    private:
      inline InnerIterator(pointer p) : m_p(p) {}
    public:
      inline InnerIterator(const InnerIterator &it) : m_p(it.p) {}

      inline bool operator==(InnerIterator const& rhs) const {
        return (m_p == rhs.m_p);
      }
      inline bool operator!=(InnerIterator const& rhs) const {
        return (m_p != rhs.m_p);
      }

      inline reference operator*() const { return *m_p; }
      inline pointer operator->() const { return m_p; }

      inline InnerIterator& operator++() {
        ++m_p;
        return *this;
      }
    private:
      pointer m_p;
  };

public:
  using value_type = typename std::decay<T>::type;
  using const_value_type = std::add_const<value_type>;
  using iterator = InnerIterator<value_type>;
  using const_iterator = InnerIterator<const_value_type>;

  TestContainer(std::initializer_list<value_type> l) :
    m_size(l.size()), m_data(new value_type[m_size]) {
    std::copy(l.begin(), l.end(), m_data.get());
  }

  iterator begin() { return iterator{m_data.get()}; }
  iterator end() { return iterator{m_data.get() + m_size}; }

  const_iterator begin() const { return iterator{m_data.get()}; }
  const_iterator end() const { return iterator{m_data.get() + m_size}; }
  const_iterator cbegin() const { return iterator{m_data.get()}; }
  const_iterator cend() const { return iterator{m_data.get() + m_size}; }

private:
  const std::size_t m_size;
  std::unique_ptr<value_type[]> m_data;
};

}  // namespace lesson_3
