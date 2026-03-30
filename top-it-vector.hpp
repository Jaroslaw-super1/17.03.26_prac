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
    Vector(const Vector< T > &);
    ~Vector();
    Vector(Vector< T > &&) noexcept;
    Vector(std::initializer_list< T > il);

    VIter< T > begin();
    VIter< T > end();

    void swap(Vector< T > & rhs) noexcept;

    bool isEmpety() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;
    void reserve(size_t k);

    T & operator[](size_t id) noexcept;
    const T & operator[](size_t id) const noexcept;

    T & at(size_t id);
    const T & at(size_t id) const;

    Vector< T > & operator=(const Vector< T > & rhs);
    Vector< T > & operator=(Vector< T > &&) noexcept;

    template < class IT >
    void pushBackRange(IT begin, size_t k);
    // знаем сколько вставить
    // выделяем память
    // вызываем pushBackImpl

    void pushBack(const T &);
    void popBack();

    void pushFront(const T &);
    void popFront();

    // Классная работа
    // с идиомой копи и свап
    void insert(size_t i, const T & val);
    void erase(size_t i);
    void insert(size_t i, const Vector< T > & rhs, size_t beg, size_t end);
    void erase(size_t beg, size_t end);

    // Дз
    template < class FwdIteretor >
    void insert(VIter< T > pos, FwdIteretor beg, FwdIteretor end);


   private:
    T * data_;
    size_t size_, capacity_;

    explicit Vector(size_t k);

    void pushBackImpl(const T &);
    // вставка без проверки на ёмкость
    // классная работа
    void reserve(size_t pos, size_t k);
  };


  template < class T >
  struct VIter
  {
    explicit VIter(Vector< T > & v, size_t pos);
    bool operator==(const VIter< T > &) const noexcept;
    bool operator!=(const VIter< T > &) const noexcept;
    VIter< T > & operator++() noexcept;
    VIter< T > & operator--() noexcept;
    VIter< T > operator+(size_t i) noexcept;
    VIter< T > operator-(size_t i) noexcept;
    T & operator*();

  private:
    Vector< T > & v_;
    size_t pos_;
    friend class Vector< T >;
  };
}





template < class T >
void topit::Vector< T >::pushBackImpl(const T & value)
{
  data_[size_] = value;
  ++size_;
}

template < class T >
void topit::Vector< T >::reserve(size_t pos, size_t k)
{
  size_t new_cap = std::max(capacity_, size_ + k);
  if (new_cap == capacity_)
  {
    return;
  }

  T * new_data = new T[new_cap];
  try
  {
    for (size_t i = 0; i < pos; ++i)
    {
      new_data[i] = std::move(data_[i]);
    }

    for (size_t i = pos; i < size_; ++i)
    {
      new_data[i + k] = std::move(data_[i]);
    }
  }
  catch (...)
  {
    delete[] new_data;
    throw;
  }
  delete[] data_;
  data_ = new_data;
  capacity_ = new_cap;
}

template < class T >
void topit::Vector< T >::insert(size_t i, const T & val)
{
  assert(i <= size_);
  if (size_ == capacity_)
  {
    reserve(capacity_ == 0 ? 1 : capacity_ * 2);
  }

  for (size_t j = size_; j > i; --j)
  {
    data_[j] = std::move(data_[j - 1]);
  }
  data_[i] = val;
  ++size_;
}

template < class T >
void topit::Vector< T >::erase(size_t i)
{
  assert(i < size_);
  for (size_t j = i + 1; j < size_; ++j)
  {
    data_[j - 1] = std::move(data_[j]);
  }
  --size_;
}

template < class T >
void topit::Vector< T >::insert(size_t i, const Vector< T > & rhs, size_t beg, size_t end)
{
  assert(i <= size_);
  assert(beg <= end && end <= rhs.size_);
  size_t count = end - beg;
  if (size_ + count > capacity_)
  {
    reserve(std::max(capacity_ * 2, size_ + count));
  }

  for (size_t j = size_; j > i; --j)
  {
    data_[j + count - 1] = std::move(data_[j - 1]);
  }

  for (size_t j = 0; j < count; ++j)
  {
    data_[i + j] = rhs.data_[beg + j];
  }
  size_ += count;
}

template < class T >
void topit::Vector< T >::erase(size_t beg, size_t end)
{
  assert(beg <= end && end <= size_);
  size_t count = end - beg;
  for (size_t i = end; i < size_; ++i)
  {
    data_[i - count] = std::move(data_[i]);
  }
  size_ -= count;
}

template < class T >
template < class FwdIterator >
void topit::Vector< T >::insert(VIter< T > pos, FwdIterator beg, FwdIterator end)
{
  size_t index = pos.pos_;
  size_t count = std::distance(beg, end);
  if (size_ + count > capacity_)
  {
    reserve(std::max(capacity_ * 2, size_ + count));
  }

  for (size_t j = size_; j > index; --j)
  {
    data_[j + count - 1] = std::move(data_[j - 1]);
  }

  for (size_t j = 0; j < count; ++j)
  {
    data_[index + j] = *beg++;
  }
  size_ += count;
}








template < class T >
template < class IT >
void topit::Vector< T >::pushBackRange(IT begin, size_t k)
{
  if (size_ + k > capacity_)
  {
    reserve(std::max(capacity_ * 2, size_ + k));
  }

  for (size_t i = 0; i < k; ++i)
  {
    pushBackImpl(*(begin + i));
  }
}





template < class T >
topit::VIter< T >::VIter(Vector< T > & v, size_t pos):
  v_(v),
  pos_(pos)
{}

template< class T >
bool topit::VIter< T >::operator==(const VIter< T > & other) const noexcept
{
  return & v_ == & other.v_ && pos_ == other.pos_;
}

template< class T >
bool topit::VIter< T >::operator!=(const VIter< T > & other) const noexcept
{
  return !(*this == other);
}

template< class T >
topit::VIter< T > & topit::VIter< T >::operator++() noexcept
{
  ++pos_;
  return *this;
}

template< class T >
topit::VIter< T > & topit::VIter< T >::operator--() noexcept
{
  --pos_;
  return *this;
}

template< class T >
topit::VIter< T > topit::VIter< T >::operator+(size_t i) noexcept
{
  return VIter(v_, pos_ + i);
}

template< class T >
topit::VIter< T > topit::VIter< T >::operator-(size_t i) noexcept
{
  return VIter(v_, pos_ - i);
}

template< class T >
T & topit::VIter< T >::operator*()
{
  return v_[pos_];
}







template< class T >
void topit::Vector< T >::reserve(size_t k)
{
  if (capacity_ >= cap)
  {
    return;
  }
  T * d = new T[cap];

  try
  {
    for (size_t i = 0; i < getSize(); i++)
    {
      d[i] = std::move(data_[i]);
    }
  }
  catch(...)
  {
    delete[] d;
    throw;
  }
  delete[] data_;
  data_ = d;
  capacity_ = cap;
}

template< class T >
topit::Vector< T >::Vector(std::initializer_list< T > il):
  Vector(il.size())
{
  size_t i = 0;
  for (auto && v: il)
  {
    data_[i++] = v;
  }
  
}

template< class T >
T & topit::Vector< T >::at(size_t id)
{
  const Vector< T > * cthis = this;
  const T & ret = cthis->at(id);
  return const_cast< T & >(ret);
}

template< class T >
const T & topit::Vector< T >::at(size_t id) const
{
  if (id < getSize())
  {
    return data_[id];
  }
  throw std::range_error("bad id");
}

template< class T >
topit::Vector< T >::Vector(Vector< T > && rhs) noexcept :
  data_(rhs.data_),
  size_(rhs.size_),
  capacity_(rhs.capacity_)
{
  rhs.data_ = nullptr;
}

template< class T >
topit::Vector< T > & topit::Vector<T>::operator=(Vector< T > &&) noexcept
{
  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  return *this;
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
  if (this == std::addressof(rhs))
  {
    return *this;
  }
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
topit::Vector< T >::Vector(const Vector< T > & rhs):
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
T & topit::Vector< T >::operator[](size_t id) noexcept
{
  return data_[0];
}

template< class T >
const T & topit::Vector< T >::operator[](size_t id) const noexcept
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
