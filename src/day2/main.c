#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#if 1 
#define INPUT_FILE "input.txt"
#else
#define INPUT_FILE "example.txt"
#endif

#define PART 2

#define LINE_CAP 8

void part1(void) {
  FILE *input = fopen(INPUT_FILE, "r");

  char line[LINE_CAP];

  int total = 0;

  while (fgets(line, sizeof(line), input)) {
      char enemy, player;
      sscanf(line, "%c %c", &enemy, &player);

      char state;

      if (enemy == 'A') { // rock
          if (player == 'X') state = 't'; // rock - tie
          if (player == 'Y') state = 'w'; // paper - win
          if (player == 'Z') state = 'l'; // scissors - lose
      } else if (enemy == 'B') { // paper
          if (player == 'X') state = 'l'; // rock - tie
          if (player == 'Y') state = 't'; // paper - win
          if (player == 'Z') state = 'w'; // scissors - lose
      } else if (enemy == 'C') { // scissors
          if (player == 'X') state = 'w'; // rock - tie
          if (player == 'Y') state = 'l'; // paper - win
          if (player == 'Z') state = 't'; // scissors - lose
      }

      int points = (state == 'w') ? 6 : ((state == 't') ? 3 : 0);
      points += (player == 'X') ? 1 : ((player == 'Y') ? 2 : 3);

      total += points;
  }

  fclose(input);

  printf("%d", total);
}


void part2(void) {
  FILE *input = fopen(INPUT_FILE, "r");

  char line[LINE_CAP];

  int total = 0;

  while (fgets(line, sizeof(line), input)) {
      char enemy, state;
      sscanf(line, "%c %c", &enemy, &state);

      int points = 0;
      points += (state == 'X') ? 0 : ((state == 'Y') ? 3 : 6);
      if (enemy == 'A') { // rock
          if (state == 'X') points += 3; // lose - scissors
          if (state == 'Y') points += 1; // tie - rock
          if (state == 'Z') points += 2; // win - paper
      } else if (enemy == 'B') { // paper
          if (state == 'X') points += 1; // lose - rock
          if (state == 'Y') points += 2; // tie - paper
          if (state == 'Z') points += 3; // win - scissors
      } else if (enemy == 'C') { // scissors
          if (state == 'X') points += 2; // lose - paper
          if (state == 'Y') points += 3; // tie - scissors
          if (state == 'Z') points += 1; // win - rock
      }

      total += points;
  }

  fclose(input);

  printf("%d", total);
}


int main(void) {
#if PART == 1
  part1();
#else
  part2();
#endif
}

