#include <stdio.h>
#include <windows.h>

#define row 20
#define column 10
char boxes_grid[row][column];
void make_boxes()// to make the base grid
{
   for(int i=0;i<row;i++)
   {
    for(int j=0;j<column;j++)
    {
       boxes_grid[i][j]='.';
    }
   }
}
const char tetromeinoes[4][4]=
{
    //i-block
    {1,0,0,0},
    {1,0,0,0},
    {1,0,0,0},
    {1,0,0,0},
};
int main()
{
    int Xco=3;//starting piece
    int Yco=0;

  while(1)
  {
 make_boxes();

    for(int i=0;i<4;i++)
    {
    for(int j=0;j<4;j++)        
    {
        if(tetromeinoes[i][j]==1)
        {
       int cur_x=Xco+j;// to cheak if the x co-ordinat is inside the box or not
       int cur_y=Yco+i;

    if(cur_x>=0&&cur_x<column&&cur_y<row&&cur_y>=0)
    {
        boxes_grid[cur_y][cur_x]='@';
    }
}
    }
}
system("cls"); //to clear the ternimal

for(int i=0;i<row;i++)
{
    for(int j=0;j<column;j++)
    {
        printf("%c ",boxes_grid[i][j]);
    }
    printf("\n");
}
Yco ++;

if(Yco + 4 >= row)
 {
    Yco = 0;
}
Sleep(500);
  }
return 0;
}