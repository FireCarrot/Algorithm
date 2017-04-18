#include "bytesource.h"

void ByteSource::CopyRaw(byte* to, int number_of_bytes) {
    memcpy(to, data_+position_, number_of_bytes);
    Advance(number_of_bytes);
}

int ByteSource::GetBlob(const byte** data) {
    int size = GetInt();
    CHECK(position_ + size <= length_);
    *data = &data_[position_];
    Advance(size);
    return size;
}
