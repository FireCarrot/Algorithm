typedef unsigned long long uint64;

int count_bit_size(uint64 bits) {
  if (bits == 0) return 0;

  return (bits % 2) + count_bit_size(bits /2 );
}

int main() {

}

