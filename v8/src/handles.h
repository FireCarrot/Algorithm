#ifndef V8_HANDLES_H_
#define V8_HANDLES_H_

namespace v8 {
namespace internal {
// A handle provides a reference to an object that survives reloation by
// the garbage collector.
// Handles are only valid within a HandleScope.
// When a handle is created for an object a cell is allocated in the heap.

template <class T>
class Handle {
 public:
  INLINE(Handle(T** location)) { location_ = location; }
  INLINE(explicit Handle(T* obj));

  INLINE(Handle()) : location_(nullptr) {}

  // Constructor for handling automatic up casting.a
  // Ex. Handle<JSFunction> can be passed when Handle<Object> is expected.
  template <class S> Handle(Handle<S> handle) {
    location_ = reinterpret_cast<T**>(handle.location());
  }

  INLINE(T* operator ->() const) { return operator*(); }

  // Check if this handle refers to the exact same object as the other handle.
  bool is_identical_to(const Handle<T> other) const {
    return operator*() == *other;
  }

  // Provides the C++ dereference operator.
  INLINE(T* operator *() const);

  // Returns the address to where the raw pointer is stored.
  T** location() const {
    ASSERT(locations_ == nullptr ||
           reinterpret_cast<Address>(*location_) != kZapValue);
    return location_;
  }

  template <class S> static Handle<T> cast(Handle<S> that) {
    T::cast(*that);
    return Handle<T>(reinterpret_cast<T**>(that.location()));
  }

  static Handle<T> null() { return Handle<T>(); }
  bool is_null() { return location_ == nullptr; }

  // Closes the given scope, but lets this handle escape. See
  // implementation in api.h.
  inline Handle<T> EscapeFrom(HandleScope* scope);

 private:
  T** location_;
};

// Handle operations.
// They might invoke garbage collection. The result is an handle to
// an object of expected type, or the handle is an error if running out
// of space or encounting an internal error.

void NormalizeProperties(Handle<JSObject> object);
void NormalizeElements(Handle<JSObject> object);
void TransformToFastProperties(Handle<JSObject> object,
                               int unused_property_fiels);
void FlattenString(Handle<String> str);

}  // namespace v8
}  // namespace internal
