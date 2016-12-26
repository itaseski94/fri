#include <stdio.h>
#include <stdlib.h>

int snakeLength(int arr[][3], int n, int num_steps);
int contains(int arr[][3], int n, int xs, int ys);
void makeMove(int **snake, int n, char a);
int gameOver(int **snake, int n);

int main() {

  int n;
  scanf("%d", &n);
  int array[n][3];
  for (int i = 0; i < n; ++i) {
      scanf("%d",&(array[i][0]));
      scanf("%d",&(array[i][1]));
      scanf("%d",&(array[i][2]));
  }
  int num_steps;
  scanf("%d", &num_steps);
  printf("%d", snakeLength(array,n,num_steps));
  printf("\n");

  return 0;

}

int snakeLength(int arr[][3], int n, int num_steps) {
   int **snake = (int **)malloc(sizeof(int *));
   snake[0] = (int *)malloc(sizeof(int) * 2);
   snake[0][0] = 0; snake[0][1] = 1;
   int snake_length = 1;
   char move_dir = 'u';
   char temp_dir = '0';
   int exists;
   for (int i = 1; i <= num_steps; ++i) {
       exists = contains(arr,n,snake[0][0], snake[0][1]);
       if (exists != -1) {
          if (arr[exists][2] == 1) {
             snake = (int **)realloc(snake,sizeof(int *) * snake_length + 1);
             snake[snake_length] = (int *)malloc(sizeof(int) * 2);
             snake_length += 1;
          } else if (arr[exists][2] == 2) {
             if (move_dir == 'u') temp_dir = 'l';
             else if (move_dir == 'd') temp_dir = 'r';
             else if (move_dir == 'l') temp_dir = 'd'; 
             else if (move_dir == 'r') temp_dir = 'u';
             move_dir = temp_dir;
          } else if (arr[exists][2] == 3) {
             if (move_dir == 'u') temp_dir = 'r'; 
             else if (move_dir == 'd') temp_dir = 'l'; 
             else if (move_dir == 'l') temp_dir = 'u'; 
             else if (move_dir == 'r') temp_dir = 'd'; 
             move_dir = temp_dir;
          }
          makeMove(snake,snake_length,temp_dir);
       } else {
          makeMove(snake,snake_length,move_dir); 
       }  
       if (gameOver(snake,snake_length)) { 
          for (int i = 0; i < snake_length; ++i){ 
              free(snake[i]); 
          }
          free(snake);
          return 0; 
       }
   }
   for (int i = 0; i < snake_length; ++i){ 
       free(snake[i]); 
   }
   free(snake); 
   return snake_length; 
}

int contains(int arr[][3], int n, int xs, int ys) {
   for (int i = 0; i < n; ++i) {
       if (arr[i][0] == xs && arr[i][1] == ys) return i;
   }  
   return -1;
}

void makeMove(int **snake, int n, char a) {
   int last_i = n-1;
   if (n > 1) {
      for (int i = n-2; i >= 0; --i) {
          snake[last_i][0] = snake[i][0];
          snake[last_i][1] = snake[i][1];
          last_i--;
      }
   }
   if (a == 'u') snake[0][1]++;
   else if(a == 'd') snake[0][1]--;
   else if(a == 'l') snake[0][0]--;
   else if(a == 'r') snake[0][0]++;
}

int gameOver(int **snake, int n) {
   for (int i = 1; i < n; ++i) {
       if (snake[i][0] == snake[0][0] && snake[i][1] == snake[0][1]) return 1;
   }
   return 0;
}




