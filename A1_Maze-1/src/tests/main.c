#include "../maze/maze.h"

int main() {
  char* file_name = "maze/examples/example_1.txt";
  maze obj;
  loading_maze(file_name, &obj);
  printf("row = %d\n", obj.rows_);
  printf("columns = %d\n", obj.columns_);
  for (int row = 0; row < obj.rows_; row++) {
    for (int col = 0; col < obj.columns_; col++) {
      printf("%d ", obj.wall_on_the_right_[row][col]);
    }
    printf("\n");
  }
  printf("\n");
  for (int row = 0; row < obj.columns_; row++) {
    for (int col = 0; col < obj.rows_; col++) {
      printf("%d ", obj.wall_below_[row][col]);
    }
    printf("\n");
  }
  
  maze_destructor(&obj);
  // printf("%c\n", 180);
  return 0;
}