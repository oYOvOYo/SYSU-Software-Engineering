/*
 *
 * test.c 
 * 
 * test some function
 * 
 * 
 * */

#include <test.h>

int main(int argc, char* argv[]) {
  uint8_t key[8], new_key[8];
  uint64_t key64;

  read_key(argv[1], key);
  // test convertion
  uint8_to_uint64(key, &key64);
  uint64_to_uint8(&key64, new_key);

  save_key(argv[2], new_key);

  // test map
  uint64_t initial_num = (uint64_t)0xF0;
  uint64_t last_num = initial_num;
  uint8_t table1[] = {2, 1};
  uint8_t table2[] = {2, 1};
  map_uint64(&last_num, table1, 2);
  map_uint64(&last_num, table2, 2);
  assert(last_num == initial_num);

  // test mask_uint64_from_to
  initial_num = mask_uint64_from_to(4, 7);
  assert(last_num == initial_num);
  assert(mask_uint64_from_to(0, 63) == UINT64_MAX);
  assert(mask_uint64_from_to(63, 63) == mask_uint64(63));
}