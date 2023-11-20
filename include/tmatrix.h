// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  size_t si;
  T* pMem;
public:
  TDynamicVector(size_t size = 1,size_t start_index=0) : sz(size), si(start_index)
  {
    if (sz < 0) throw out_of_range("The magnitude of the vector must be greater than zero");
    if ((sz > MAX_VECTOR_SIZE)||(si<0)) 
        throw out_of_range("It's too big");

    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    for (int i = 0; i < sz; i++)
    {
        pMem[i] = 0;
    }
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "Error: The vector takes a null pointer");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v){
      sz = v.sz;
      si = v.si;
      if (this != &v) {
          pMem = new T[sz];
          for (int i = 0; i < sz; i++) pMem[i] = v.pMem[i];
      }
      else
          throw invalid_argument("error");
   }

  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v)
      {
          delete[] this->pMem;
          sz = v.sz;
          si = v.si;
          pMem = new T[sz];
          for (int i = 0; i < sz; i++)
              pMem[i] = v.pMem[i];
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this != &v)
      {
          delete[] this->pMem;
          sz = v.sz;
          si = v.si;
          pMem = new T[sz];
          for (int i = 0; i < sz; i++)
              pMem[i] = v.pMem[i];
      }
      return *this;
  }

  size_t size() const noexcept
  { 
      return sz;
  }
  size_t start_index() const noexcept 
  {
      return si;
  }

  // индексация
  T& operator[](size_t ind)
  {
      if ((ind >= sz) || (ind < 0)) 
          throw invalid_argument("");
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      if ((ind >= sz) || (ind < 0)) 
          throw invalid_argument("");
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if ((ind >= sz) || (ind < 0)) 
          throw invalid_argument("");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if ((ind >= sz) || (ind < 0)) 
          throw invalid_argument("");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) 
          return false;
      if (si != v.si) 
          return false;
      for (int i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) 
              return false;
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !operator==(v);

  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector<T>vector_result(*this);
      for (size_t i = 0; i < sz; i++) {
          vector_result.pMem[i] += val;
      }
      return vector_result;

  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector<T>vector_result(*this);
      for (size_t i = 0; i < sz; i++) {
          vector_result.pMem[i] -= val;
      }
      return vector_result;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector<T>vector_result(*this);
      for (size_t i = 0; i < sz; i++) {
          vector_result.pMem[i] *= val;
      }
      return vector_result;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw "It is not possible to add vectors of different sizes";
      TDynamicVector<T> vector_result(sz, __min(si, v.si));
      for (int i = 0; i < sz; i++)
          vector_result.pMem[i] = this->pMem[i] + v.pMem[i];
      return vector_result;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw "Subtraction of vectors of different sizes is not possible";
      TDynamicVector<T> vector_result(sz, __min(si, v.si));
      for (int i = 0; i < sz; i++)
          vector_result.pMem[i] = this->pMem[i] - v.pMem[i];
      return vector_result;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz) 
          throw invalid_argument("Multiplication vectors of different size is impossible");
      T vector_result={};
      for (size_t i = 0; i < sz; i++) {
          vector_result += this->pMem[i]*v.pMem[i];
      }
      return vector_result;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);

  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix :  public TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(int s) : TDynamicVector<TDynamicVector<T>>(s)
  {
      
      if ((s < 0) || (s > MAX_MATRIX_SIZE))
          throw "Size is out of range";
      for (int i = 0; i < sz; i++) {
          pMem[i] = TDynamicVector<T>(sz);
        }
  }
  TDynamicMatrix(const TDynamicMatrix& m): TDynamicVector<TDynamicVector<T>>(m) {}

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение 
  bool operator!=(const TDynamicMatrix& m) const 
  {
      return (!( * this == m));
  }
  bool operator==(const TDynamicMatrix& m) const
  {
      return TDynamicVector<TDynamicVector<T>>::operator==(m);
  }
  TDynamicMatrix operator=(const TDynamicMatrix<T>& m)
  {
      if (*this != m)
      {
          if (sz != m.sz)
          {
              sz = m.sz;
              delete[] pMem;
              pMem = new TDynamicVector<T>[sz];
          }
          si = m.si;
          for (int i = 0; i < sz; i++)
              pMem[i] = m.pMem[i];
      }
      return *this;
  }
  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicVector<T>matrix_result(*this);
      for (size_t i = 0; i < sz; i++) {
          pMem[i] *= val;
      }
      return matrix_result;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz!= v.sz)
          throw "Multiplication of vectors of different sizes is not possible";
      TDynamicVector vector_result(sz);
      for (int i = 0; i < sz; i++)
          vector_result += this->pMem[i] * v.pMem[i];
      return vector_result;
  }

  // матрично-матричные операции
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw "Multiplication of matrix of different sizes is not possible";
      TDynamicMatrix matrix_result(*this);
      for (int i = 0; i < sz; i++)
          matrix_result.pMem[i] = matrix_result.pMem[i] - m.pMem[i];
      return matrix_result;
  }
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw "Multiplication of matrix of different sizes is not possible";
      TDynamicMatrix matrix_result(*this);
      for (int i = 0; i < sz; i++)
          matrix_result.pMem[i] = matrix_result.pMem[i]+m.pMem[i];
      return matrix_result;
  }
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; i++)
          istr >> v.pMem[i];
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; i++)
          ostr << v.pMem[i]<<endl;
      return ostr;
  }
};
#endif


