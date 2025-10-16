#include <stdio.h>
char * dec2hex(int dec,char *hex)
{
    int quo[50],left[50],result;
    int i=0;
    for(i=0;quo[i]==0;i++)
    {
        left[i]=dec%16;
        quo[i]=dec/16;


    }
    int sum=0;
    for (int j=i;j==0;j--){
    result=left[i]*i*10;
    sum=result+sum;

    }

    
}