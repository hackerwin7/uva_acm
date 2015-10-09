#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string>
#include<string.h>
#define FORMU(t,i) 28*t+cip[i]+i
using namespace std;

char num_str[28]={'\0'};

//converting
int converts(int k,char cip_str[],int cip[],char pla_str[],int pla[])
{
    int n=strlen(cip_str);
    int i=0;
    // cipher text --> cipher code
    for(i=0;i<=n-1;i++)
    {
        if(cip_str[i]=='_')
        {
            cip[i]=0;
        }
        else if(cip_str[i]=='.')
        {
            cip[i]=27;
        }
        else
        {
            cip[i]=cip_str[i]-96;
        }
    }
    // cipher code --> plain code
    // p[k*i mod n] = 28*t+27+i
    for(i=0;i<=n-1;i++)
    {
        int t=0;
        while(FORMU(t,i)<0 || FORMU(t,i)>27)
        {
            if(FORMU(t,i)<0)
            {
                t++;
            }
            else
            {
                t--;
            }
        }
        pla[(k*i)%n]=FORMU(t,i);
    }
    //plain code --> plain text
    for(i=0;i<=n-1;i++)
    {
        pla_str[i]=num_str[pla[i]];
    }
    pla_str[n]='\0';
    return(0);
}

int main()
{
    //initialize
    int i=0;
    char c='a';
    num_str[0]='_';
    num_str[27]='.';
    for(i=1;i<=26;i++)
    {
        num_str[i]=c;
        c++;
    }
    
    //input 
    int k=0;
    char cip_str[100];
    int cip[100];
    char pla_str[100];
    int pla[100];
    while(scanf("%d%s",&k,cip_str)!=EOF&&k>0)
    {
        //converting
        converts(k,cip_str,cip,pla_str,pla);
        //output
        printf("%s\n",pla_str);
    }
    return(0);
}
