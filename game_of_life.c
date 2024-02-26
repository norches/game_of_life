#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define HEIGHT 25
#define WIDTH 80

int input(int **matrix);
int should_be_alive(int **matrix, int x, int y);
void draw(int **matrix);
int sum_of_neighbors(int **matrix, int x, int y);
int state_of_cell(int **matrix, int x, int y);
int **allocate_memory();
void draw_and_update(int ***matrix);

int should_be_alive(int **matrix, int x, int y) {
  // На основе sum_of_neighbors вычисляет if elsa-ами должна быть клетка живой
  // или нет
  /*из README.md Any live cell with two or three live neighbours survives. Any
   * dead cell with three live neighbours becomes a live cell. All other live
   * cells die in the next generation. Similarly, all other dead cells stay
   * dead. */
  int should_be_alive_res = 0;
  int sum = 0;
  sum = sum_of_neighbors(matrix, x, y);
  if (state_of_cell(matrix, x, y) == 1) {
    if (sum > 1 && sum < 4) {
      should_be_alive_res = 1;
    }
  } else if (sum == 3) {
    should_be_alive_res = 1;
  }

  return should_be_alive_res;
}

int **update_matrix(int **matrix) {
  // вычисляет какое состояние должно быть у следующего поколения
  int **matrix_new = (int **)calloc(HEIGHT, sizeof(int *));
  for (int i = 0; i < HEIGHT; i++) {
    matrix_new[i] = (int *)calloc(WIDTH, sizeof(int));
  }

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      matrix_new[i][j] = should_be_alive(matrix, i, j);
    }
  }

  for (int i = 0; i < HEIGHT; i++) {
    free(matrix[i]);
  }
  free(matrix);
  return matrix_new;
}

void draw(int **matrix) {
  //рисует матрицу
  clear();
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (matrix[i][j] == 1)
        printw("*");
      else
        printw(".");
    }
    printw("\n");
  }
}

int sum_of_neighbors(int **matrix, int x, int y) {
  /*
   x =2;
   y =2;
  for(int i = -1; i<=1; i++){
      for(int j = -1; j<=1;j++) {
  if (i ==0&& j==0){
      //skip
  } else {
          sum += state_of_cell(matrix, x+i, y+j);
  }*/
  int sum = 0;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0) {
        ;  // do nothing
      } else {
        sum += state_of_cell(matrix, x + i, y + j);
      }
    }
  }
  return sum;
}

int state_of_cell(int **matrix, int x, int y) {
  // Определяем координату (y может быть больше 25, x может быть больше 80)

  // Нужно предусмотреть что Сетка закрыта сама в себе т.е если Y больше чем
  // HEIGHT например 26 то математически нужно вычислить что нужно вернуть
  // остаток от деления на HEIGHT т.е 26 % 25 = 1, значит нам нужен
  // matrix[X][0], так если допустим y -2 тогда -2 значит -2 % 25 = 23 нам нужна
  // координата 23

  // функция принимает координаты X_Y и позвращает текущее состояние 0 или 1
  int coordinate_x = x % HEIGHT;
  int coordinate_y = y % WIDTH;
  if (coordinate_x < 0) coordinate_x += HEIGHT;
  if (coordinate_y < 0) coordinate_y += WIDTH;
  return matrix[coordinate_x % HEIGHT][coordinate_y % WIDTH];
}

int input(int **matrix) {
  int x, y = 0;
  int break_flag = 0;
  while (scanf("%d,%d", &y, &x) == 2) {
    break_flag = 1;
    if (x == -1 && y == -1) {
      break_flag = 0;
      break;
    }

    if (x > HEIGHT - 1 || y > WIDTH - 1) {
      printf(
          "wrong input(out of field) %d, %d: \n1's clause: %d\n 2'nd "
          "clause%d\n",
          x, y, x > WIDTH - 1, y > HEIGHT - 1);
      break;
    }

    matrix[x][y] = 1;

    break_flag = 0;
  }

  //считывает с STDin координаты живых клеток и включает их по координатам x Y
  // scanf(...)
  //если возникла ошибка возвращает 0
  // иначе 1

  fclose(stdin);
  freopen("/dev/tty", "r", stdin);
  return break_flag ? 0 : 1;
}

int **allocate_memory() {
  int **matrix = (int **)calloc(HEIGHT, sizeof(int *));

  for (int i = 0; i < HEIGHT; i++) {
    matrix[i] = (int *)calloc(WIDTH, sizeof(int));
  }
  return matrix;
}

void draw_and_update(int ***matrix) {
  draw(*matrix);
  *matrix = update_matrix(*matrix);
}

void cleanup() { endwin(); }

int main() {
  atexit(cleanup);
  int **matrix = allocate_memory();

  if (input(matrix) != 1) {
    printf("n/a");
    // Free the allocated memory before exiting due to input error
    for (int i = 0; i < HEIGHT; i++) {
      free(matrix[i]);
    }
    free(matrix);

    return 0;
  }
  initscr();
  cbreak();     // Line buffering disabled
  noecho();     // Don't echo input
  curs_set(0);  // Hide the cursor
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);

  int c = getch();

  int halt_state = -1;
  int speed = 500000;

  while (1) {
    c = getch();
    int set_exit = 0;

    switch (c) {
      case 'h':
        halt_state *= -1;
        break;
      case 'q':
        set_exit = 1;
        break;
      case ' ':
        draw_and_update(&matrix);
        break;
      case KEY_UP:
        speed *= 0.75;
        break;
      case KEY_DOWN:
        speed *= 1.25;
        break;
      default:
        break;
    }

    if (set_exit == 1) break;

    if (halt_state != 1) {
      draw_and_update(&matrix);
      usleep(speed);
    }
  }

  for (int i = 0; i < HEIGHT; i++) {
    free(matrix[i]);
  }
  free(matrix);

  endwin();

  return 0;
}
