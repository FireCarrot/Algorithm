#include <pthread.h>

typedef pid_t PlatformThreadId;
typedef pthread_t PlatformThreadRef;

PlatformThreadId CurrentThreadId() {
  return reinterpret_cast<pid_t>(pthread_self());
}
PlatformThreadRef CurrentThreadRef() {
  return pthread_self();
}

void SetCurrentThreadName(const char* name) {
  prctl(PR_SET_NAME, reinterpret_cast<unsigned long>(name));
}

typedef void (*ThreadRunFunction)(void*);

enum ThreadPriority {
  kLowPriority = 1,
  kNormalPriority = 2,
  kHighPriority = 3,
  kHighestPriority = 4,
  kRealtimePriority = 5
};

class ThreadTest {
  public:
    ThreadTest(ThreadRunFunction func,
               void* obj,
               const char* thread_name,
               ThreadPriority priority)
      : run_function_(func), priority_(priority), obj_(obj), name_(thread_name) {}

    void Start() {
      ThreadAttributes attr;
      // Set the stack size to 1M.
      pthread_attr_setstacksize(&attr, 1024*1024);
      // int pthread_create(pthread_t* thread, const pthread_attr_t* attr,
      //                    void *(*start_routine)(void*), void *arg);
      if (!pthread_create(&thread_, &attr, &StartThread, this))
        perror("pthread_create");
        return;
    }

  private:
    void Run() {
      SetCurrentThreadName(name_.c_str());

      if (run_function_) {
        SetPriority(priority_);
        run_function_(obj_);
        return;
      }


    }

    ThreadRunFunction const run_function_ = nullptr;
    const ThreadPriority priority_ = kNormalPriority;
    void* const obj_;
    const std::string name_ = nullptr;
    pthread_t thread_ = 0;

    static void* StartThread(void* param) {
      static_cast<ThreadTest*>(param)->Run();
      return 0;
    }
};

class Tracer {
private:
  ThreadTest logging_thread_;
};

int main() {

  return 0;
}
