#ifndef VECTOR_H_
#define VECTOR_H_

using namespace std;

// Time
// O(1) to add/remove at end (amortized for allocations for more space), index, or update
// O(n) to insert/remove elsewhere
// Space
// Contiguous in memory, so proximity helps performance
// space needed = (array capacity, which is >= n) * size of item, but even if 2n, stil O(n)

template <typename T>
class Vector {
  public:
    Vector() : data_(nullptr), length_(length) {}
    Vector(T* data, size_t length) : data_(data), length_(length) {}
    Vector(size_t size);
    Vector(Vector<T>& x);

    size_t size() { return length_; }
    size_t capaticy() { return capacity_; }
    bool is_empty() { length_? false:true; }

    T* operator[](int index) { return data_[index]; }
    T* at(size_t index) { return operator[](index); }
    void push(T* item);
    void insert(size_t index, T* item);
    void prepend(T* item);
    bool pop();
    void erase(size_t index);
    bool remove(T* item);
    int find(T* item);

  private:
    // When reaching capaticy, resize to double the size
    // When popping an item, if size is 1/4 of capacity, resize to half
    bool resize(size_t new_capaticy);

    T* data_;
    size_t length_;
    size_t capacity_;
};
