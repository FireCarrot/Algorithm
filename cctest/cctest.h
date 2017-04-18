#ifndef CCTEST_H_
#define CCTEST_H_

#include <functional>
#include <string.h>

using namespace std;

#ifndef TEST
#define TEST(Name)                                                          \
    static void Test##Name();                                               \
    CcTest register_test_##Name(Test##Name, __FILE__, #Name, true, true);   \
    static void Test##Name()
#endif

#ifndef UNINITIALIZED_TEST
#define UNINITIALIZED_TEST(Name)                                            \
    static void Test##Name();                                               \
    CcTest register_test##Name(Test##Name, __FILE__, #Name, true, false);   \
    static void Test##Name()
#endif

#ifndef DISABLED_TEST
#define DISABLED_TEST(Name)                                                 \
    static void Test##Name();                                               \
    CcTest register_test_##Name(Test##Name, __FILE__, #Name, false, true);  \
    static void Test##Name()
#endif

static char* StrDup(const char* str) {
    int length = strlen(str);
    char* result = new char[length];
    strcpy(result, str);
    return result;
}

class CcTest {
public:
    // typedef void(*TestFunction)(void);
    // using TestFunction = void(*)(void);
    // std::function<void(void)> TestFunction;
    typedef function<void()> TestFunction;
    CcTest(TestFunction callback, const char* file, const char* name,
            bool enabled, bool initialize);
    ~CcTest();

    static CcTest* last() { return last_; }
    CcTest* prev() { return prev_; }
    const char* file() { return file_; }
    const char* name() { return name_; }
    bool enabled() { return enabled_; }

    void Run();

    static void TearDown() { }

private:
    TestFunction callback_;
    const char* file_;
    const char* name_;
    bool enabled_;
    bool initialize_;
    CcTest* prev_;
    static CcTest* last_;
};

#endif // #define CCTEST_H_
