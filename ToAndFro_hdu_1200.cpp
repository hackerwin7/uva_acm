/*
even row ind+2*(col-original_ind)-1
odd row ind+2*(original_ind+1)-1
index begin from 0
*/
#include<stdio.h>
#include<string.h>
int col=0,row=0,len=0;
char str[200+5]={'\0'};
int de_ind[200+5]={'\0'};//decode string index store the index of str
int main()
{
    while(scanf("%d",&col)!=EOF&&col>0)
    {
        scanf("%s",str);
        len=strlen(str);
        row=len/col;
        for(int i=0;i<=col-1;i++)//set decode string per col start position
        {
            de_ind[i*row]=i;
            int j=i;
            int k=i*row;
            int line_ind=0;
            while(j<len)
            {
                if(line_ind%2==0)
                {
                    j=j+2*(col-i)-1;
                }
                else
                {
                    j=j+2*(i+1)-1;
                }
                if(j<len)
                {
                    de_ind[++k]=j;
                }
                line_ind++;
            }
        }
        for(int i=0;i<=len-1;i++)//print decode string
        {
            printf("%c",str[de_ind[i]]);
        }
        printf("\n");
    }
    return(0);
}
