#include <vector.h>

typedef const INIT_CAPACITY 16;
typedef const DOUBLE 2;

template <typename T>
T* NewArray(size_t size) {
  return new T[size];
}

template <typename T>
Vector<T>::Vector(size_t size) {
  if (resize(size))
    length_ = size;
}

template <typename T>
Vector<T>::Vector(Vector<T>& x) {
  capacity_  = x.capacity_;
  length_ = x.length_;
  data_ = NewArray(capacity_);
  memcpy(data_, &x[0], capacity_);
}

template <typename T>
void Vector<T>::push(T* item) {
  if (length_ + 1 >= capacity_)
    resize(length_+1);

  data_[length+1] = item;
}

template <typename T>
void Vector<T>::insert(size_t index, T* item) {
  if (length_ + 1 >= capacity_)
    resize(length_+1);

  for (int i = length; i > index; i--) {
    data_[i] = data_[i-1];
  }

  data_[index] = item;
}

template <typename T>
bool Vector<T>::resize(size_t length) {
  int n = length / INIT_CAPACITY;
  capacity = INIT_CAPACITY * (n+1);
  T* data = NewArray(capacity);
  if (!data)
    return false;

  if (data_) {
    memcpy(data, data_, capacity_);
    delete data_;
    data_ = data;
  }

  capacity_ = capacity;

  return true;
}
