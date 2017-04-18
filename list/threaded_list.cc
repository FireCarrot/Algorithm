template <typename T>
class ThreadedList {
    public:
        ThreadedList() : head_(nullptr), tail_(&head_) {}
        void Add(T* v) {
            if (*tail_ != nullptr)
                return;

            *tail_ = v;
            tail_ = v->next();
        }
};
