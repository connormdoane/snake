#include "pixul.h"
#include <unistd.h>
#include <time.h>

#define w 50
#define h 50

int snakeTailX[128], snakeTailY[128];

int snakeTailLength;

int gameover, direction, score;

int x, y, direction, fruitx, fruity;

void setup() {
  gameover = 0;
  x = w / 2;
  y = w / 2;
  direction = 0;

  srand(time(NULL));
  fruitx = (rand() % w-1) + 1;
  fruity = (rand() % h-1) + 1;
}

int** init_board() {
  int** board;

  board = malloc(w * sizeof(int*));
  for (int i = 0; i < w; i++) {
    board[i] = calloc(h, sizeof(int));
  }

  return board;
}

void destroy_board(int** board) {
  for (int i = 0; i < w; i++) {
    free(board[i]);
  }
  free(board);
}

void iterate() {
  int prevX = snakeTailX[0];
  int prevY = snakeTailY[0];
  int prev2X, prev2Y;
  snakeTailX[0] = x;
  snakeTailY[0] = y;

  for (int i = 1; i < snakeTailLength; i++) {
    prev2X = snakeTailX[i];
    prev2Y = snakeTailY[i];
    snakeTailX[i] = prevX;
    snakeTailY[i] = prevY;
    prevX = prev2X;
    prevY = prev2Y;
  }

  switch(direction) {
  case 0:
    y--;
    break;
  case 1:
    y++;
    break;
  case 2:
    x--;
    break;
  case 3:
    x++;
    break;
  default:
    break;
  }

  // Check for game over
  if (x < 0 || x >= w || y < 0 || y >= h) gameover = 1;

  for (int i = 0; i < snakeTailLength; i++) {
    if (snakeTailX[i] == x && snakeTailY[i] == y) gameover = 1;
  }

  if (x == fruitx && y == fruity) {
    fruitx = (rand() % w-1) + 1;
    fruity = (rand() % h-1) + 1;
    snakeTailLength++;
  }
}

void render() {
  // Draw borders
  for (int i = 0; i < h; i++) {
    P_Set(i, 0, (P_Color){255, 255, 255, 255});
    P_Set(i, w-1, (P_Color){255, 255, 255, 255});
  }
  for (int i = 0; i < w; i++) {
    P_Set(0, i, (P_Color){255, 255, 255, 255});
    P_Set(h-1, i, (P_Color){255, 255, 255, 255});
  }
  // Draw fruit
  P_Set(fruitx, fruity, (P_Color){255, 255, 255, 255});
  // Draw snake
  P_Set(x, y, (P_Color){255, 255, 255, 255});
  for (int i = 0; i < snakeTailLength; i++) {
    P_Set(snakeTailX[i], snakeTailY[i], (P_Color){255, 255, 255, 255});
  }
}

int main() {
  P_Create("Snake", 500, 500, w, h);

  int** board = init_board();
  setup();

  int play = 1;

  while (!P_Done()) {
    P_Clear((P_Color){0,0,0,255});

    render();

    if (play && !gameover) {
      iterate();
    } else {
      if (P_KeyPress(SDL_SCANCODE_N)) {
        iterate();
      }
    }

    // MOVE
    if (P_KeyPress(SDL_SCANCODE_W)) {
      if (direction != 1) direction = 0;
    }
    if (P_KeyPress(SDL_SCANCODE_S)) {
      if (direction != 0) direction = 1;
    }
    if (P_KeyPress(SDL_SCANCODE_A)) {
      if (direction != 3) direction = 2;
    }
    if (P_KeyPress(SDL_SCANCODE_D)) {
      if (direction != 2) direction = 3;
    }

    // PAUSE
    if (P_KeyPress(SDL_SCANCODE_SPACE)) {
      play = !play;
    }

    // QUIT
    if (P_KeyPress(SDL_SCANCODE_Q)) {
      break;
    }

    P_Update();
    usleep(100000);
  }

  destroy_board(board);
  P_Destroy();

  return 0;
}
