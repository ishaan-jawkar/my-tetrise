#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#define row 20
#define column 10 
//gcc step8f.c -o step8f
//./step8f
struct GameRecord
{
     char name[30];
     int score;
     int rank;
};

char **boxes_grid;
void make_boxes(){// to make the base grid
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
    //i-block_1
    {0,1,0,0},
    {0,1,0,0},
    {0,1,0,0},
    {0,1,0,0},
},
{   //o-block_2
   {0,0,0,0},
   {0,1,1,0},
   {0,1,1,0},
   {0,0,0,0},
},
{  //s-block_3
    {0,1,1,0},
    {1,1,0,0},
    {0,0,0,0},
    {0,0,0,0},
},
{    //z-block_4
    {1,1,0,0},
    {0,1,1,0},
    {0,0,0,0},
    {0,0,0,0},
},
{   //L-block_5
    {0,1,0,0},
    {0,1,0,0},
    {0,1,1,0},
    {0,0,0,0},},
{    //j-block_6
    {0,1,0,0},
    {0,1,0,0},
    {1,1,0,0},
    {0,0,0,0},},
{  //T-block_7
    {1,1,1,0},
    {0,1,0,0},
    {0,0,0,0},
    {0,0,0,0}, }
};
void  bubblesorting(struct GameRecord p[],int n)
{
    struct GameRecord temp;
    {
    for(int i=0;i<n-1;i++)
    {
       for( int j=0;j<n-i-1;j++)
       {
        if(p[j].score<p[j+1].score)
        {
            temp=p[j];
            p[j]=p[j+1];
            p[j+1]=temp;
        }
       }
    }
}
}
int cheak_collision(int x_tar, int y_tar, char piece[4][4]){

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(piece[i][j] == 1)
            {
                int box_x = x_tar + j;
                int box_y = y_tar + i;

                if(box_x < 0 || box_x >= column || box_y >= row || box_y < 0)
                {
                 return 1;
            }
              if(boxes_grid[box_y][box_x]=='@')
                   { return 1;}
                }
        }
    }
    return 0;
}
void rotate(char piece[4][4]){
 char temp[4][4];
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
          temp[i][j]=piece[i][j];
        }
    }
    for(int i=0;i<4;i++)
    {
    for(int j=0;j<4;j++)
    {
    piece[j][3-i] = temp[i][j];
    }
}
}
void input(int *xco,int *yco,char curr_piece[4][4]){

       if(_kbhit())
        {
            char ch=_getch();
            if(ch=='a'||ch=='A')
            {
              if(cheak_collision((*xco)-1,(*yco),curr_piece)==0)
                {(*xco)--;}
            }
            else if(ch=='s'||ch=='S')
            {
                if(cheak_collision((*xco),(*yco)+1,curr_piece)==0)
                {(*yco)++;}
            }
            else if(ch=='d'||ch=='D')
            {
                if(cheak_collision((*xco)+1,(*yco),curr_piece)==0)
                {(*xco)++;}
            }
           else if(ch == 'w' || ch == 'W')
           {
                char temp[4][4];
                for(int i = 0; i < 4; i++)
                    { 
                    for(int j = 0; j < 4; j++)
                    {
                        temp[i][j]=curr_piece[i][j];
                    }
                    }
                     rotate(temp);
                    if(cheak_collision((*xco),(*yco), temp) == 0)
                     {
                     rotate(curr_piece);
                      }
        
               }
        }
}
void clear_line(char **boxes_grid,int *score){

    for(int i=row-1;i>=0;i--)
    {
        int is_full=1;
        for(int j=0;j<column;j++)
    {
        if(boxes_grid[i][j]!='@')
        {
            is_full=0;
        }
    }
    if(is_full)
    {
        (*score)+=100;
        
        for(int k=i;k>0;k--)
        {
            for(int j=0;j<column;j++)
            boxes_grid[k][j]=boxes_grid[k-1][j];
        }
            for(int j=0;j<column;j++)
        {
            boxes_grid[0][j]='.';
            
        }
        
        i++;
    }
    
}
}
int main()
{ 
    int pl=1;
    struct GameRecord *p = (struct GameRecord*)calloc(pl, sizeof(struct GameRecord));
   
    boxes_grid = (char**)calloc(row,sizeof(char*));
    for(int i=0;i<row;i++)
    {
        boxes_grid[i] = (char*)calloc(column,sizeof(char));
    }
    
    srand(time(NULL));
    while(1)
{
    int score=0;
    int xco=3;//starting position
    int yco=0;
    int game_over=1; 
     int speed=10;
    int frame=0; 
        make_boxes();

        int shape = rand() % 7;
        char curr_piece[4][4];
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                curr_piece[i][j] = tetromeinoes[shape][i][j];
            }
        }

    while(game_over!=0)
    {
        input(&xco, &yco,  curr_piece);

        system("cls");
        printf("A or a=left\n");
        printf("D ot d=right\n");
        printf("S or s=down\n");
        printf("W ot w=rotate\n");
        
        for(int i=0;i<row;i++)/*to print the game box*/
        {
            for(int j=0;j<column;j++)
            {
                int cur_x=i-yco ,cur_y=j-xco;
                if(boxes_grid[i][j]=='@'||(cur_x>=0&&cur_y>=0&&cur_x<4&&cur_y<4&&curr_piece[cur_x][cur_y]==1))
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

        frame++;
        if(frame>=speed)
        {
            frame=0;
        }
        if(cheak_collision(xco,yco+1,curr_piece)==0)//to cheak if block touch the floor
        {
                    yco++;
        }
        else
        {
           for(int i=0;i<4;i++)
           {
            for(int j=0;j<4;j++)
           {
             if(curr_piece[i][j]==1)
             {
                int cur_x=xco+j;
                int cur_y=yco+i;
                if(cur_x>=0&&cur_y>=0&&cur_x<column&&cur_y<row)
                {
                    boxes_grid[cur_y][cur_x]='@';
                }
            }
             }
            }
        
            clear_line(boxes_grid,&score);
             speed=10-score/500;
             if(speed<2)
             {
                speed=2;
             }
     
            yco=0;
            xco=3;
            shape=rand() % 7;
            for(int i=0;i<4;i++)
                {
                    for(int j=0;j<4;j++)
                    {
                        curr_piece[i][j]=tetromeinoes[shape][i][j];
                    }
                }
        
        if(cheak_collision(xco,yco,curr_piece)==1)
        {
            game_over=0;
        }
        }
           Sleep(100);
    }
         printf("======game over======\n");
         printf("enter your name\n");
            scanf("%s",p[pl-1].name);
            p[pl-1].score=score;
         char select;
         printf("\npress E or e to try again or ");//for user to decide to quit or start again
         printf("press Q or q to end the program");
         scanf(" %c",&select);
         if(select=='E'||select=='e')
         {
            break;
         }
         else if(select=='Q'||select=='q')
        {
           pl++;
           p=(struct GameRecord*)realloc(p,pl*sizeof(struct GameRecord));
        }
        else
        {
            printf("invaild input,end game");
            break;
        }
 
    }
    if(pl>0)
    {
    printf("\n---leaderboard---\n");
    bubblesorting(p,pl);
    for(int i=0;i<pl;i++)
    {
      printf("\n name:%s||score:%d||rank:%d\n",p[i].name,p[i].score,i+1);
    }
}
free(p);
for(int i=0;i<row;i++)
{
    free(boxes_grid[i]);
}
free(boxes_grid);

    return 0;
}