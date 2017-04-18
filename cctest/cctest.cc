#include "cctest.h"

#include <iostream>

CcTest* CcTest::last_ = nullptr;

CcTest::CcTest(TestFunction callback, const char* file, const char* name,
               bool enabled, bool initialize)
    : callback_(callback)
    , name_(name)
    , enabled_(enabled)
    , initialize_(initialize)
    , prev_(last_) {
    // Find the base name of this test
    char* basename = strchr(const_cast<char*>(file), '/');
    if (!basename) {
        basename = strrchr(const_cast<char*>(file), '\\');
    }
    if (!basename) {
        basename = StrDup(file);
    } else {
        basename = StrDup(basename + 1);
    }

    char* extension = strrchr(basename, '.');
    if (extension) *extension = 0;

    file_ = basename;
    prev_ = last_;
    last_ = this;
}

CcTest::~CcTest() {
    delete[] file_;
}

void CcTest::Run() {
    callback_();
}

static void PrintTestList(CcTest* current) {
    if (current == nullptr) return;
    PrintTestList(current->prev());
    cout << current->file() << "/" << current->name() << endl;
}

static void SuggestTestHarness(int tests_run) {
    if (tests_run == 0) return;
    cout << "Running multiple tests in sequence is deprecated and may cause "
         << "bogus failure. Consider using tools/run-tests.py instead."
         << endl;
}

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        char* arg = argv[i];
        if ((strcmp(arg, "--help") == 0) || (strcmp(arg, "-h") == 0)) {
            cout << "Usage: " << argv[0] << "[--list]" << endl;
            cout << "OPtions: " << endl;
            cout << "   --list: list all cctests" << endl;
            cout << endl << endl;
        }
    }

    int tests_run = 0;
    bool print_run_count = true;
    for (int i = 1; i < argc; i++) {
        char* arg = argv[i];
        if (strcmp(arg, "--list") == 0) {
            PrintTestList(CcTest::last());
            print_run_count = false;
        } else {
            char* arg_copy = StrDup(arg);
            char* testname = strchr(arg_copy, '/');
            if (testname) {
                *testname = 0;
                char* file = arg_copy;
                char* name = testname + 1;
                CcTest* test = CcTest::last();
                while (test != nullptr) {
                    if (test->enabled()
                     && strcmp(test->file(), file) == 0
                     && strcmp(test->name(), name) == 0) {
                        SuggestTestHarness(tests_run++);
                        test->Run();
                    }
                    test = test->prev();
                }
            } else {
                char* file_or_name = arg_copy;
                CcTest* test = CcTest::last();
                while (test != nullptr) {
                    if (test->enabled()
                     && (strcmp(test->file(), file_or_name) == 0
                     || strcmp(test->name(), file_or_name) == 0)) {
                        SuggestTestHarness(tests_run++);
                        test->Run();
                    }
                    test = test->prev();
                }
            }
            delete[] arg_copy;
        }
    }

    if (print_run_count && tests_run != 1)
        cout << "Ran " << tests_run << " tests." << endl;
    CcTest::TearDown();
}
