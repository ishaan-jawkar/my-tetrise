#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#define row 20
#define column 10 
//gcc main_tetrise.c -o main_tetrise
//./main_tetrise 
struct GameRecord // for recording player score
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
const char tetromeinoes[7][4][4]={// to create different type of falling block
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
void  bubblesorting(struct GameRecord p[],int n)// to rank player by score
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
int cheak_collision(int x_tar, int y_tar, char piece[4][4]){//to cheak if the block touched side of board and don't fall out the boundry
                                                             //also to cheak if it toucher another block
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
              if(boxes_grid[box_y][box_x]=='#')
                   { return 1;}
                }
        }
    }
    return 0;
}
void rotate(char piece[4][4]){//used for turning the piece 90 degree to give more mobility to piece 
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
void input(int *xco,int *yco,char curr_piece[4][4]){// fot input (dont use scanf as it wait for the user input pause the program) 
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
            if(ch=='e'||ch=='E')
            {
                while(cheak_collision((*xco),(*yco)+1,curr_piece)==0)
                {(*yco)++;}
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
void clear_line(char **boxes_grid,int *score){//to cheak if the row is full and then increase the score  
    for(int i=row-1;i>=0;i--)
    {
        int is_full=1;
        for(int j=0;j<column;j++)
    {
        if(boxes_grid[i][j]!='#')
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
    int pl=0;
    struct GameRecord *p = NULL;

   FILE *file=fopen("leaderboard.dat", "rb");
   if(file!=NULL)
   {
    struct  GameRecord temp1;
        while(fread(&temp1,sizeof(struct GameRecord),1,file)==1)
        {
         struct GameRecord *temp1_t=realloc(p,(pl+1)*sizeof( struct GameRecord ));
        if(temp1_t!=NULL)
        {
            p=temp1_t;
            p[pl]=temp1;
            pl++;
        }
    }
    fclose(file);
  }
  struct GameRecord *temp_current = realloc(p, (pl + 1) * sizeof(struct GameRecord));
    if(temp_current == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    p=temp_current;
    int curr_player=pl;
    pl++;
    
    boxes_grid = (char**)calloc(row,sizeof(char*));
    if (boxes_grid == NULL) {
    printf("Memory allocation failed!\n");
    return 1;
    }
    for(int i=0;i<row;i++)
    {
        boxes_grid[i] = (char*)calloc(column,sizeof(char));
    }
    
    srand(time(NULL));
    while(1)//to start the first loop
{
    int score=0;
    int xco=3;//starting position
    int yco=0;
    int game_over=1; 
     int speed=10;
    int frame=0; 
        make_boxes();//first make empty boxes

        int shape = rand() % 7;//to randomonize the piece
        char curr_piece[4][4];
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                curr_piece[i][j] = tetromeinoes[shape][i][j];//as the tetro..... is constant
            }
        }
    while(game_over!=0)//second inner loop fo rthe actual game
    {
        input(&xco, &yco,  curr_piece);

        system("cls");//to make sure that is nothing except the game
        printf("A or a=left\n");
        printf("D ot d=right\n");
        printf("S or s=down\n");
        printf("W ot w=rotate\n");
        
        for(int i=0;i<row;i++)/*to print the game box*/
        {
            for(int j=0;j<column;j++)
            {
                int cur_x=i-yco ,cur_y=j-xco;
                if(boxes_grid[i][j]=='#'||(cur_x>=0&&cur_y>=0&&cur_x<4&&cur_y<4&&curr_piece[cur_x][cur_y]==1))
                {
                    printf("#");
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
                if(cur_x>=0&&cur_y>=0&&cur_x<column&&cur_y<row)//if inside the game border
                {
                    boxes_grid[cur_y][cur_x]='#';
                }
            }
             }
            }
            clear_line(boxes_grid,&score);//if line is full
             speed=10-score/500;
             if(speed<2)
             {
                speed=2;
             }
            yco=0;
            xco=3;
            shape=rand() % 7;//re randominize the piece
            for(int i=0;i<4;i++)
                {
                    for(int j=0;j<4;j++)
                    {
                        curr_piece[i][j]=tetromeinoes[shape][i][j];// to put that re randomize piece for cheaking
                    }
                }
        if(cheak_collision(xco,yco,curr_piece)==1)
        {
            game_over=0;
        }
        }
           Sleep(450);//so that the piece does not instantly come down
    }//end of the inner loop  as the game is over 
         printf("======game over======\n");
         printf("enter your name\n");
            scanf("%29s",p[curr_player].name);
            p[curr_player].score=score;
            printf("your score is:%d",p[curr_player].score);
            FILE *filew = fopen("leaderboard.dat","ab");
              if(filew!= NULL)
              {
                fwrite(&p[curr_player],sizeof(struct GameRecord),1,filew);
                fclose(filew);
              }
         char select;
         printf("\npress E or e to try again \n ");//for user to decide to quit or start again
         printf("press Q or q to end the program\n");
         scanf(" %c",&select);
         if(select=='E'||select=='e')// game ends 
         {
          struct GameRecord *temp_p = (struct GameRecord*)realloc(p, (pl + 1) * sizeof(struct GameRecord));
           if ( temp_p== NULL)
            {
        printf("Reallocation failed!\n");
        return 1;
             }
             p=temp_p;
             curr_player=pl;
             pl++;
            } 
         else if(select=='Q'||select=='q')//game start again
        {
          break;
        }
        else
        {
            printf("invaild input,end game");//game end if anything other than q,e is put
            break;
        }
 
    }
    if(pl>0)//to insure that number of play is more that 0
    {
    printf("\n---leaderboard---\n");
    bubblesorting(p,pl);
    for(int i=0;i<pl;i++)
    {
      printf("\n name:%s||score:%d||rank:%d\n",p[i].name,p[i].score,i+1);
    }
}
free(p);//remove  the memory stored in p,struct
for(int i=0;i<row;i++)//remove the value stored in box /game boundry
{
    free(boxes_grid[i]);
}
free(boxes_grid);
    return 0;//end program
}