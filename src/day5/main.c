#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#if 1 
#define INPUT_FILE "input.txt"
#else
#define INPUT_FILE "example.txt"
#endif

#define PART 2

#define LINE_CAP 64
#define STACK_COUNT 9
#define STACK_SIZE 100


void swapc(char* a, char* b) {
  char t = *a;
  *a = *b;
  *b = t;
}

void reverse_stacks(char stacks[STACK_COUNT][STACK_SIZE], size_t *sizes, int stack_ammount) {
  for (int i = 0; i < stack_ammount; i++) {
    char *stack = stacks[i];
    size_t size = sizes[i];
      
    for (size_t j = 0; j < size / 2; j++) {
      swapc(&stack[j], &stack[size - 1 - j]);
    }
  }
}

void parse_stack_input(FILE *input, char stacks[STACK_COUNT][STACK_SIZE], size_t *sizes, int *stack_ammount) {
  bool exit = false;


  while (!exit) {
    
    char line[LINE_CAP] = {0};
    fgets(line, sizeof(line), input);
    if (*stack_ammount == 0) *stack_ammount = (strlen(line) + 1) / 4;

    size_t l_off = 0;
    if (line[l_off] != '[' && line[l_off + 1] != ' ') {

      exit = true;
    } else {
  
      for (int i = 0; i < *stack_ammount; i++) {
       if (line[l_off] == '[') {
         l_off++;
         stacks[i][sizes[i]] = line[l_off];
         sizes[i]++;
         l_off += 3;
       } else {
         l_off += 4;
        }
      }

    }

  }


  reverse_stacks(stacks, sizes, *stack_ammount);


}

void perform_move_ins_part1(FILE* input, char stacks[STACK_COUNT][STACK_SIZE], size_t *sizes) {
  
  char line[LINE_CAP] = {0};

  while (fgets(line, sizeof(line), input)) {
    if (strncmp("\n", line, sizeof("\n")) == 0) continue;

    int amm, from, to = 0;

    sscanf(line, "move %d from %d to %d\n", &amm, &from, &to);

    from -= 1;
    to -= 1;

    for (int i = 0; i < amm; i++) {
      
      // remove from stack
      sizes[from] -= 1;
      char tmp = stacks[from][sizes[from]];

      // add to stack
      stacks[to][sizes[to]] = tmp;
      sizes[to] += 1;

    }

  }

}

void part1(void) {
  FILE *input = fopen(INPUT_FILE, "r");

  char stacks[STACK_COUNT][STACK_SIZE] = {0};
  size_t sizes[STACK_COUNT] = {0};
  int stack_ammount = 0;

  parse_stack_input(input, stacks, sizes, &stack_ammount);
  
  perform_move_ins_part1(input, stacks, sizes);

  // print top of each stack
  for (int i = 0; i < stack_ammount; i++) {
    char top = stacks[i][sizes[i] - 1];
    printf("%c", top);
  }

  fclose(input);
}

void perform_move_ins_part2(FILE* input, char stacks[STACK_COUNT][STACK_SIZE], size_t *sizes) {
  
  char line[LINE_CAP] = {0};

  while (fgets(line, sizeof(line), input)) {
    if (strncmp("\n", line, sizeof("\n")) == 0) continue;

    int amm, from, to = 0;

    sscanf(line, "move %d from %d to %d\n", &amm, &from, &to);

    from -= 1;
    to -= 1;

    memcpy(&(stacks[to][sizes[to]]), &(stacks[from][sizes[from] - amm]), amm);

    sizes[to] += amm;
    sizes[from] -= amm;

  }

}

void part2(void) {
  FILE *input = fopen(INPUT_FILE, "r");

  char stacks[STACK_COUNT][STACK_SIZE] = {0};
  size_t sizes[STACK_COUNT] = {0};
  int stack_ammount = 0;

  parse_stack_input(input, stacks, sizes, &stack_ammount);
  
  perform_move_ins_part2(input, stacks, sizes);

  // print top of each stack
  for (int i = 0; i < stack_ammount; i++) {
    char top = stacks[i][sizes[i] - 1];
    printf("%c", top);
  }

  fclose(input);
}


int main(void) {
#if PART == 1
  part1();
#else
  part2();
#endif
}

