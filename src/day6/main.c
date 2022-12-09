#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdbool.h>


#if 1 
#define INPUT_FILE "input.txt"
#else
#define INPUT_FILE "example.txt"
#endif

#define PART 2


void part1(void) {
  int fd = open(INPUT_FILE, O_RDONLY);

  struct stat statbuf = {0};
  if (fstat(fd, &statbuf) < 0) {
    printf("Failed to open file\n");
    return;
  }

  size_t size = statbuf.st_size;
  char *data = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
  if(data == MAP_FAILED){
    printf("Mapping Failed\n");
    return;
  }

  for (int i = 4 - 1; i < (int)size; i++) {
    char a = data[i - 3];
    char b = data[i - 2];
    char c = data[i - 1];
    char d = data[i - 0];

    if (a == b) continue;
    if (a == c) continue;
    if (a == d) continue;
    if (b == c) continue;
    if (b == d) continue;
    if (c == d) continue;

    printf("%d", i + 1);
    break;
  }

  close(fd);
}

bool chars_are_unique(char* data,size_t size) {
 for (int i = 0; i < (int)size; i++) {
    for (int j = 0; j < (int)size; j++) {
      if (i == j) continue;

      if (data[i] == data[j]) return false;
    }
  }

 return true;
}

void part2(void) {
  int fd = open(INPUT_FILE, O_RDONLY);

  struct stat statbuf = {0};
  if (fstat(fd, &statbuf) < 0) {
    printf("Failed to open file\n");
    return;
  }

  size_t size = statbuf.st_size;
  char *data = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
  if(data == MAP_FAILED){
    printf("Mapping Failed\n");
    return;
  }

  for (int i = 0; i < (int)size; i++) {

    char *stride = &(data[i]);

    if (chars_are_unique(stride, 14)) {
      printf("%d", i + 14);
      break;
    } 
  }

  close(fd);
}


int main(void) {
#if PART == 1
  part1();
#else
  part2();
#endif
}

