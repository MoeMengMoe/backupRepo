# include<stdio.h>
int calculate_str_length(char *str1){
    int i;
    for(i=0;str1[i]!='\0';i++){}
    return i;
}