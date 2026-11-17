#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
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
const char tetromeinoes[7][4][4]={
    {
    //i-block
    {1,0,0,0},
    {1,0,0,0},
    {1,0,0,0},
    {1,0,0,0},
},
{
   //o-block
   {1,1,0,0},
   {1,1,0,0},
   {0,0,0,0},
   {0,0,0,0},
},
{
    //s-block
    {0,1,1,0},
    {1,1,0,0},
    {0,0,0,0},
    {0,0,0,0},
},
{
    //z-block
    {1,1,0,0},
    {0,1,1,0},
    {0,0,0,0},
    {0,0,0,0},    
},
{
    //L-block
    {0,1,0,0},
    {0,1,0,0},
    {0,1,1,0},
    {0,0,0,0},    
},
{
    //j-block
    {0,1,0,0},
    {0,1,0,0},
    {1,1,0,0},
    {0,0,0,0},    
},
{
    //T-block
    {1,1,1,0},
    {0,1,0,0},
    {0,0,0,0},
    {0,0,0,0},    
}
};
int main()
{
    srand(time(NULL));

    int xco=3;
    int yco=0;

    int shape=rand() % 7;

    while(1)
    {
        if(_kbhit())
        {
            char ch=_getch();
            if(ch=='a'||ch=='A')
            {
                if(xco>=0)
                xco--;
            }
            else if(ch=='s'||ch=='S')
            {
                yco++;
            }
            else if(ch=='d'||ch=='D')
            {
                if(xco<column-1)xco++;
            }
        }
        make_boxes();

        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                if(tetromeinoes[shape][i][j]==1)
                {
                   int cur_x=xco+j;
                   int cur_y=yco+i;

                   if(cur_x>=0&&cur_y>=0&&cur_x<column&&cur_y<row)
                   {
                  boxes_grid[cur_y][cur_x] ='@';
                   }

                }
            }
        }
        system("cls");
        
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<column;j++)
            {
                if(boxes_grid[i][j]=='@')
                {
                    printf("@");
                }
                else 
                {
                    printf(".");
                }
            }
            printf("\n");
        }
        yco++;
        if(yco+4>=row)
        {
            yco=0;
            xco=3;
            shape=rand() % 7;
        }
        Sleep(500);
    }
    return 0;
}`