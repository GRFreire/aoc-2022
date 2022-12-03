#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#if 1 
#define INPUT_FILE "input.txt"
#else
#define INPUT_FILE "example.txt"
#endif

#define PART 2

#define LINE_CAP 64

void part1(void) {
  FILE *input = fopen(INPUT_FILE, "r");

  char line[LINE_CAP];

  int p_sum = 0;

  while(fgets(line, sizeof(line), input)) {
    // len - 1 because the last char of line is '\n'
    size_t len = strlen(line) - 1;

    char common = '\0';

    for (size_t i = len / 2; i < len; i++) {
      for (size_t j = 0; j < len / 2; j++) {
        if (line[i] == line[j]) {
          common = line[i];
          break;
        }
      }

      if (common != '\0') {
        int priority = (common < 'a') ? (common - 'A' + 27) : (common - 'a' + 1);
        p_sum += priority;
        break;
      }
    }
  }

  fclose(input);

  printf("%d", p_sum);
}


void part2(void) {
  FILE *input = fopen(INPUT_FILE, "r");

  char line1[LINE_CAP] = {0};
  char line2[LINE_CAP] = {0};
  char line3[LINE_CAP] = {0};

  int p_sum = 0;
  while(fgets(line1, sizeof(line1), input)) {
    fgets(line2, sizeof(line2), input);
    fgets(line3, sizeof(line3), input);

    // len - 1 because the last char of line is '\n'
    size_t len1 = strlen(line1) - 1;
    size_t len2 = strlen(line2) - 1;
    size_t len3 = strlen(line3) - 1;

    char in_common[LINE_CAP] = {0};
    size_t in_common_sz = 0;

    for (size_t i = 0; i < len2; i++) {
      for (size_t j = 0; j < len1; j++) {
        if (line2[i] == line1[j]) {
          in_common[in_common_sz] = line2[i];
          in_common_sz++;
        }
      }
    }

    char common = '\0';

    for (size_t i = 0; i < len3; i++) {
      for (size_t j = 0; j < in_common_sz; j++) {
        if (line3[i] == in_common[j]) {
          common = line3[i];
          break;
        }
      }

      if (common != '\0') {
        int priority = (common < 'a') ? (common - 'A' + 27) : (common - 'a' + 1);
        p_sum += priority;
        break;
      }
    }
  }

  fclose(input);

  printf("%d", p_sum);
}


int main(void) {
#if PART == 1
  part1();
#else
  part2();
#endif
}

