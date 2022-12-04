#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#if 1 
#define INPUT_FILE "input.txt"
#else
#define INPUT_FILE "example.txt"
#endif

#define PART 2

void part1(void) {
  FILE *input = fopen(INPUT_FILE, "r");

  int overlap_c = 0;
  int a1, a2, b1, b2 = 0;
  while(fscanf(input, "%d-%d,%d-%d\n", &a1, &a2, &b1, &b2) != EOF) {
    if ((b1 >= a1 && b2 <= a2) || (a1 >= b1 && a2 <= b2)) {
      overlap_c++;
    } 

  }

  fclose(input);

  printf("%d", overlap_c);
}


void part2(void) {
  FILE *input = fopen(INPUT_FILE, "r");

  int overlap_c = 0;
  int a1, a2, b1, b2 = 0;
  while(fscanf(input, "%d-%d,%d-%d\n", &a1, &a2, &b1, &b2) != EOF) {
    if ((b1 <= a2 && b2 >= a1) || (a1 <= b2 && a2 >= b1)) {
      overlap_c++;
    } 

  }

  fclose(input);

  printf("%d", overlap_c);
}


int main(void) {
#if PART == 1
  part1();
#else
  part2();
#endif
}

