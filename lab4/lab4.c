#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define BUF_SIZE 128

struct header {
  uint64_t size;
  struct header *next;
};

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  if (len < 0) {
    // handle_error("snprintf");
    return;
  }
  write(STDOUT_FILENO, buf, len);
}

int main() {
  // allocate 256 space
  void *start_addr = sbrk(256);

  // create block1
  struct header *block1 = (struct header *)start_addr;
  block1->size = 128;
  block1->next = NULL;

  // create block2
  void *new_addr = (char *)start_addr + 128; // chars are 1 byte so moving pointer by 128 * 1 bytes
  struct header *block2 = (struct header *)new_addr;
  block2->size = 128;
  block2->next = block1;

  // find where data goes (after the header)
  void *data1_ptr = (char *)block1 + sizeof(struct header);
  void *data2_ptr = (char *)block2 + sizeof(struct header);
  // fill with data
  memset(data1_ptr, 0, 128 - sizeof(struct header)); // fills block iwth size - header size with 0
  memset(data2_ptr, 1, 128 - sizeof(struct header)); // same but with 1s

  // now print needed info---------------------------
  // starting addresses
  print_out("first block addr: %p\n", &block1, sizeof(block1));
  print_out("second block addr: %p\n", &block2, sizeof(block2));
  // header info
  print_out("b1 size: %lu\n", &block1->size, sizeof(block1->size));
  print_out("b1 next: %p\n", &block1->next, sizeof(block1->next));
  print_out("b2 size: %lu\n", &block2->size, sizeof(block2->size));
  print_out("b2 next: %p\n", &block2->next, sizeof(block2->next));
  // data of each block
  char *p = data1_ptr; // data as a string of characters
  for (int i = 0; i < 128 - sizeof(struct header); i++) {
    uint64_t value = p[i]; // print out each index of the string
    print_out("%lu\n", &value, sizeof(value));
  }

  char *s = data2_ptr;
  for (int j = 0; j < 128 - sizeof(struct header); j++) {
    uint64_t val = s[j];
    print_out("%lu\n", &val, sizeof(val));
  }

  return 0;
}
