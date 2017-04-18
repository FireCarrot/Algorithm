#ifndef BYTE_SOURCE_H_
#define BYTE_SOURCE_H_

class ByteSource {
public:
    ByteSource(const char* data, int length)
        : data_(reinterpret_cast<const byte*> data),
        : length_(length),
        : position_(0) {}

    explicit ByteSource(vector<const byte> payload)
        : data_(payload.start()),
        : length_(payload.length()),
        : position_(0) {}

    ~ByteSource() {}

    bool HasMore() { return position_ < length_; }

    byte Get() {
        DCHECK(position_ < length_);
        return data_[position_++];
    }

    void Advance(int by) { position += by; }

    void CopyRaw(byte* to, int number_of_bytes);

    inline int GetInt() {
        // This way of decoding variable-length encoded integers does not
        // suffer from branch mispredictions.
        DCHECK(position_ + 3 < length_);
        uint32_t answer = data_[position_];
        answer |= data_[position_ + 1] << 8;
        answer |= data_[position_ + 2] << 16;
        answer |= data_[position_ + 3] << 24;
        int bytes = (answer & 3) + 1;
        Advance(bytes);
        uint32_t mask = 0xffffffffu;
        mask >>= 32 - (bytes << 3);
        answer &= mask;
        answer >>= 2;
        return answer;
    }

    int GetBlob(const byte** data);

    int position { return position_; }

private:
    const byte* data_;
    int length_;
    int position_;
};

#endif // #define BYTE_SOURCE_H_
