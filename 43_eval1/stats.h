#ifndef __STATS_H__
#define __STATS_H__

#include <stdlib.h>

#define MAX_NAME_LEN 64

enum position_tag { CENTER, FORWARD, GUARD };
typedef enum position_tag position_t;

struct player_tag {
  char name[MAX_NAME_LEN];
  unsigned number;
  position_t position;
  unsigned rebounds;
  unsigned points;
  unsigned games;
};
typedef struct player_tag player_t;

player_t parseLine(char * line);

void addGame(player_t * roster,
             size_t n_players,
             unsigned number,
             unsigned rebounds,
             unsigned points);

void printDoubleDouble(player_t * roster, size_t n_players);

void printPosPoints(player_t * roster, size_t n_players);

#endif
