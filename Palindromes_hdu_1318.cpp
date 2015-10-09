#include<stdio.h>
#include<string.h>
#include<ctype.h>
//char - 'A'  -> index   number - '1' + 26
char chars[35]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','1','2','3','4','5','6','7','8','9'};
char rev_chars[35]={'A',' ',' ',' ','3',' ',' ','H','I','L',' ','J','M',' ','O',' ',' ',' ','2','T','U','V','W','X','Y','5','1','S','E',' ','Z',' ',' ','8',' '};
char in_str[50];
//judge the string is a palindrome
bool is_palindrome()
{
    int i=0,j=strlen(in_str) - 1;
    while(i<j)
    {
        if(in_str[i]!=in_str[j]) return(false);
        i++;
        j--;
    }
    return(true);
}
//judge the string is a mirrored
bool is_mirrored()
{
    int i=0,j=strlen(in_str)-1;
    while(i<=j)
    {
        char l = in_str[i],re_l = '\0',r = in_str[j];
        if(isdigit(l)) re_l = rev_chars[l - '1' + 26];
        else re_l = rev_chars[l - 'A'];
        if(re_l!=' ')
        {
            if(re_l!=r) return(false);
        }
        else return(false);
        i++;
        j--;
    }
    return(true);
}
int main()
{
    while(scanf("%s",in_str)!=EOF)
    {
        printf("%s",in_str);
        if(is_palindrome())
        {
            if(is_mirrored()) printf(" -- is a mirrored palindrome.\n");
            else printf(" -- is a regular palindrome.\n");
        }
        else
        {
            if(is_mirrored()) printf(" -- is a mirrored string.\n");
            else printf(" -- is not a palindrome.\n");
        }
        printf("\n");
    }
    return(0);
}
