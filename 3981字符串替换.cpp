#include<stdio.h>
#include<string.h>
int main()
{
    char s[1010];
    int len = 1000;
    while(gets(s)){
        char * pch;
        while(pch=strstr(s,"you"),pch)
            strncpy(pch,"we#",3);
        char *p=s;
        while(*p){
            if(*p!='#') putchar(*p);
            p++;
            
        }
        putchar('\n');
    }
    return 0;
}
