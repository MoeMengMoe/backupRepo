// #include <stdio.h>
// #include <string.h>
// char * CopyString(char str[]){
//     if(strlen(str)==1){return NULL;}
//     char* cpstring;
//     static char temp[50];
//     for(int i=0;i<strlen(str);i ++){
//         temp[i]=str[i];
//     }
//     cpstring=temp;
//     return cpstring;
// }
// int main (){
//     char input[] ="hello  world";
//     char *output=CopyString(input);
//     if(*output != NULL){printf("%s\n",output);}else{printf("NULL\n");}
//     return 0;
// }


#include <stdio.h>

// 自定义字符串复制函数
// 参数：
//   dest: 目标数组（存放复制结果）
//   src: 源字符串（被复制的字符串）
void my_strcpy(char dest[], const char src[]) {
    int i = 0;
    
    // 逐个复制字符，直到遇到源字符串的结束符
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    
    // 手动添加目标字符串的结束符
    dest[i] = '\0';
}

int main() {
    // 源字符串
    char source[] = "Hello, 自定义函数!";
    
    // 目标数组（确保足够大）
    char destination[50];
    
    // 使用自定义函数复制字符串
    my_strcpy(destination, source);
    
    // 输出结果
    printf("源字符串: %s\n", source);
    printf("复制结果: %s\n", destination);
    
    return 0;
}
