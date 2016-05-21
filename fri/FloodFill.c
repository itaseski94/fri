#include <stdio.h>
#include <stdlib.h>

void floodFill(char **bitmap, int N, int M, int x, int y, char c);

int main() {

 int N, M;
 scanf("%d", &M);
 scanf("%d", &N);
 char bitmap[N][M];
 
 for (int i = 0; i < N; ++i){
     for (int j = 0; j < M; ++j) { 
         bitmap[i][j] = '.';
     } 
 }
 
 int nLines;
 int x0, y0, x1, y1;
 scanf("%d", &nLines);
 for (int i = 1; i <= nLines; ++i) {
     scanf("%d", &x0);
     scanf("%d", &y0);
     scanf("%d", &x1);
     scanf("%d", &y1);
     for (int r = y0; r <= y1; ++r) {
         for (int c = x0; c <= x1; ++c) {
             bitmap[r][c] = '*';         
         }
     }    
 }
   
 char *a[N];
 for (int x = 0; x < N; ++x) a[x] = bitmap[x];

 int num_areas = 0;
 char s = 'f';
 for (int i = 0; i < N; ++i) {
     for (int j = 0; j < M; ++j) {
         if (bitmap[i][j] == '.') { 
            floodFill(a,N,M,i,j,s);
            num_areas++;
         }
     }
 }  
 printf("%d", num_areas);
 printf("\n");
 return 0;

}

void floodFill(char **bitmap, int N, int M, int x, int y, char c) {
  if (x < 0 || x >= N || y < 0 || y >= M) { 
     return;
  }
  if (bitmap[x][y] == c || bitmap[x][y] == '*') {  
     return;
  }
  bitmap[x][y] = c;
  floodFill(bitmap,N,M,x+1,y,c);
  floodFill(bitmap,N,M,x-1,y,c);
  floodFill(bitmap,N,M,x,y+1,c);
  floodFill(bitmap,N,M,x,y-1,c);
}




