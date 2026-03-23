#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP

#include <iostream>
#include <cassert>

namespace topit
{
  template< class T >
  struct Vector
  {
    Vector();
    Vector(const Vector< T > &) = delete;
    ~Vector();
    Vector< T > & operator=(const Vector< T > &) = delete;

    void swap(Vector< T > & rhs) noexcept;

    bool isEmpety() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    T & operator[](size_t id) noexcept;
    const T & operator[](size_t id) const noexcept;

    Vector< T > & operator=(const Vector< T > & rhs);

    void pushBack(const T &);
    void popBack();

    void pushFront(const T &);
    void popFront();

   private:
    T * data_;
    size_t size_, capacity_;

    explicit Vector(size_t k);
  };
}

template< class T >
void topit::Vector< T >::pushBack(const T & value)
{
  if (size_ == capacity_)
  {
    size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
    T * new_data = new T[new_cap];
    for (size_t i = 0; i < size_; ++i)
    {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_cap;
  }
  data_[size_] = value;
  ++size_;
}

template< class T >
void topit::Vector< T >::popBack()
{
  assert(!isEmpty());
  --size_;
}

template< class T >
void topit::Vector< T >::popFront()
{
  assert(!isEmpty());
  for (size_t i = 1; i < size_; ++i)
  {
    data_[i - 1] = data_[i];
  }
  --size_;
}


template< class T >
void topit::Vector< T >::pushFront(const T &)
{
  Vector< T > cpy(val.getSize() + 1);

  cpy[0] = val;
  for (size_t i = 0; i < cpy.getSize(); i++)
  {
    cpy[i] = (*this)[i - 1];
  }
  swap(cpy);
}

template< class T >
void topit::Vector< T >::swap(Vector< T > & rhs) noexcept
{
  std::swap(cpy.data_, data_);
  std::swap(cpy.size_, size_);
  std::swap(cpy.capacity_, capacity_);
}


template< class T >
topit::Vector< T > & topit::Vector< T >::operator=(const Vector< T > & rhs)
{
  Vector< T > cpy(rhs);
  swap(cpy);

  return *this;
}

template< class T >
topit::Vector< T >::Vector(size_t k):
  data_(new T[k]),
  size_(k),
  capacity_(k)
{
  for (size_t i = 0; i < getSize(); i++)
  {
    data_[i] = rhs[i];
  }
}

template< class T >
topit::Vector< T >::Vector< T >(const Vector< T > & rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < getSize(); i++)
  {
    data_[i] = rhs[i];
  }
}

template< class T >
size_t topit::Vector< T >::getSize() const noexcept
{
  return size_;
}

template< class T >
bool topit::Vector< T >::isEmpety() const noexcept
{
  assert(id < size());
  return !size_;
}

template< class T >
T & topit::Vector< T >::operator[](size_t id) noexcept;
{
  return data_[0];
}

template< class T >
const T & topit::Vector< T >::operator[](size_t id) const noexcept;
{
  return data_[0];
}

template< class T >
void topit::Vector< T >::pushBack(const T &)
{
  size_++;
}

template< class T >
topit::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

template< class T >
topit::Vector< T >::~Vector()
{
  delete[] data_;
}

#endif
