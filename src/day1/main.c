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

  int current = 0;
  int max = 0;

  while (fgets(line, LINE_CAP, input) != NULL) {
      if (strncmp("\n", line, 1) == 0) {
          if (current > max) max = current;
          current = 0;
      } 
      else {
          int calories = atoi(line);
          current += calories;
      }
  }

  if (current > max) max = current;
  current = 0;
 
  fclose(input);

  printf("%d\n", max);
}

void swapi(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void part2(void) {
  FILE *input = fopen(INPUT_FILE, "r");

  char line[LINE_CAP];

  int current = 0;
  int max1 = 0;
  int max2 = 0;
  int max3 = 0;

  while (fgets(line, LINE_CAP, input) != NULL) {
      int calories = atoi(line);
      current += calories;
 
      if (calories == 0) {

          if (current > max3) swapi(&current, &max3);
          if (max3 > max2) swapi(&max3, &max2);
          if (max2 > max1) swapi(&max2, &max1);

          current = 0;
      }
  }

  fclose(input);

  if (current > max3) swapi(&current, &max3);
  if (max3 > max2) swapi(&max3, &max2);
  if (max2 > max1) swapi(&max2, &max1);

  int max_total = max1 + max2 + max3;
  printf("%d\n", max_total);
}


int main(void) {
#if PART == 1
  part1();
#else
  part2();
#endif
}

