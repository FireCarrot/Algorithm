#include <vector>

template <typename T>
class ScopedVector {
  public:
      ScopedVector(int length) {
         data_ = new vector<T>(length);
      }
      ~ScopedVector() {
          delete data_;
      }
  private:
      vector<T>* data_;
};

TEST(PreParserScopeAnalysis) {

}
