#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define LEN 128

char key[5][5];

void generate_key()
{
    int alphabet[26];
    for(int i=0;i<26;i++)
        alphabet[i]=1;
    
    alphabet['j'-'a']=0;
    
    int r;
    
    int x=0;
    int y=0;
    
    int t;
    
    for(int i=0;i<25;i++)
    {   
        r=rand()%26;
        if(alphabet[r]==0)
        {
            i--;
            continue;
        }

        key[y][x++]=r+'a';
        alphabet[r]=0;
        if(x==5)
        {
            y++;
            x=0;
        }
    }
    
    return;
}


char* decode(char text[])
{
    int a[2], b[2];
    int len=strlen(text);
    char *r=malloc(len+100);
    int k=0;
    int temp;
    for(int i=0;i<len;i+=2)
    {
        for(int m=0;m<5;m++)
            for(int n=0;n<5;n++)
            {
                if(text[i]==key[m][n])
                {
                    a[0]=n;
                    a[1]=m;
                }

                if(text[i+1]==key[m][n])
                {
                    b[0]=n;
                    b[1]=m;
                }
            }
        
        if(a[1]==b[1])
        {
            a[0]+=4;
            b[0]+=4;
            
            a[0]%=5;
            b[0]%=5;
        }
        
        else if(a[0]==b[0])
        {
            a[1]+=4;
            b[1]+=4;
            
            a[1]%=5;
            b[1]%=5;
        }
        else
        {
            temp=a[0];
            a[0]=b[0];
            b[0]=temp;
        }
        r[k++]=key[a[1]][a[0]];
        r[k++]=key[b[1]][b[0]];

    }
    r[k]='\0';
    return r;
}

void main()
{
    srand(time(NULL));
    
    generate_key();

    
    printf("%s\n",decode("SFQNDWATWLON"));
    return;
}
        
