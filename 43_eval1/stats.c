#include "stats.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
// any other headers you need here

player_t parseLine(char * line) {
  // STEP 1: write me
  player_t answer;
  if (line == NULL) {
    fprintf(stderr, "Invalid line\n");
    exit(EXIT_FAILURE);
  }
  char * colon1 = strchr(line, ':');
  char * colon2 = strchr(colon1 + 1, ':');
  if (colon1 == NULL || colon2 == NULL) {
    fprintf(stderr, "Not enough colon\n");
    exit(EXIT_FAILURE);
  }
  //Initialize name
  for (int i = 0; line[i] != ':'; i++) {
    if (i >= MAX_NAME_LEN - 1) {
      fprintf(stderr, "Invalid name\n");
      exit(EXIT_FAILURE);
    }
    else {
      answer.name[i] = line[i];
    }
    answer.name[i + 1] = '\0';
  }
  //Initialize number
  for (int i = 0; (colon1 + 1)[i] != ':'; i++) {
    //Condition that the number is 0
    if (colon1[1] == '0' && colon1[2] == ':') {
      break;
    }
    //Ensure that the number is digit and non-negative integer does not start with 0
    else if (!isdigit((colon1 + 1)[i])) {
      fprintf(stderr, "Invalid number\n");
      exit(EXIT_FAILURE);
    }
  }
  char * endptr;
  answer.number = strtol(colon1 + 1, &endptr, 10);
  //Initialize position
  if (strlen(colon2 + 1) != 1) {
    fprintf(stderr, "Invalid position\n");
    exit(EXIT_FAILURE);
  }
  if (toupper(colon2[1]) == 'C') {
    answer.position = CENTER;
  }
  else if (toupper(colon2[1]) == 'F') {
    answer.position = FORWARD;
  }
  else if (toupper(colon2[1]) == 'G') {
    answer.position = GUARD;
  }
  else {
    fprintf(stderr, "Invalid position name\n");
    exit(EXIT_FAILURE);
  }
  answer.rebounds = 0;
  answer.points = 0;
  answer.games = 0;
  return answer;
}

void addGame(player_t * roster,
             size_t n_players,
             unsigned number,
             unsigned rebounds,
             unsigned points) {
  // STEP 2: write me
  if (roster == NULL) {
    fprintf(stderr, "Invalid record");
    exit(EXIT_FAILURE);
  }
  if (n_players <= 0) {
    fprintf(stderr, "Invalid # players");
    exit(EXIT_FAILURE);
  }
  if (number < 0 || rebounds < 0 || points < 0) {
    fprintf(stderr, "Invalid number or rebounds or points");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < n_players; i++) {
    if (roster[i].number != number) {
      /*if (i == n_players - 1) {
        fprintf(stderr, "The player number is not in the roster\n");
        exit(EXIT_FAILURE);
      }*/
      continue;
    }
    else {
      roster[i].points += points;
      roster[i].games++;
      roster[i].rebounds += rebounds;
    }
  }
}

void printDoubleDouble(player_t * roster, size_t n_players) {
  // STEP 3: write me
  if (roster == NULL) {
    fprintf(stderr, "Invalid record");
    exit(EXIT_FAILURE);
  }
  if (n_players <= 0) {
    fprintf(stderr, "Invalid # players");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < n_players; i++) {
    if (roster[i].rebounds >= 10 && roster[i].points >= 10) {
      printf("%s\n", roster[i].name);
    }
  }
}

void printPosPoints(player_t * roster, size_t n_players) {
  // STEP 4: write me
  if (roster == NULL) {
    fprintf(stderr, "Invalid record");
    exit(EXIT_FAILURE);
  }
  if (n_players <= 0) {
    fprintf(stderr, "Invalid # players");
    exit(EXIT_FAILURE);
  }

  unsigned maxc = 0;
  unsigned maxf = 0;
  unsigned maxg = 0;
  for (size_t i = 0; i < n_players; i++) {
    if (roster[i].position == CENTER) {
      maxc += roster[i].points;
    }
    if (roster[i].position == FORWARD) {
      maxf += roster[i].points;
    }
    else {
      maxg += roster[i].points;
    }
  }
  unsigned max = maxc;
  char Array[3][10] = {"Centers", "Forwards", "Guards"};
  int index = 0;
  if (maxf > max) {
    max = maxf;
    index = 1;
  }
  if (maxg > max) {
    max = maxg;
    index = 2;
  }
  printf("%s had the most points with %u points\n", Array[index], max);
}
