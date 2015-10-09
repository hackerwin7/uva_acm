#include<stdio.h>
#include<string.h>
#define GET_INT(x) x-48
#define GET_CHAR(x) x+48
char str[10];//input START or END or ENDOFINPUT
char maze[10][10];//original image
char ali_maze[10][10];//anti-aliased image
int R,C;
char get_char(int i,int j)
{
    return GET_CHAR((GET_INT(maze[i][j])+GET_INT(maze[i+1][j])+GET_INT(maze[i][j+1])+GET_INT(maze[i+1][j+1]))/4);
}
int main()
{
    while(scanf("%s%d%d",str,&R,&C)!=EOF&&strcmp(str,"ENDOFINPUT")!=0)
    {
        for(int i=0;i<=R-1;i++)
        {
            scanf("%s",maze[i]);
        }
        scanf("%s",str);//get the  string END
        for(int i=0;i<=R-2;i++)
        {
            for(int j=0;j<=C-2;j++)
            {
                ali_maze[i][j]=get_char(i,j);
            }
            ali_maze[i][C-1]='\0';
        }
        for(int i=0;i<=R-2;i++)
        {
            printf("%s\n",ali_maze[i]);
        }
    }
    return(0);
}
