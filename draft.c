#include <stdio.h>

int main() {
   
    
    char *str1 = "hello";  
    printf(" str1: %s\n", str1);
    
   
    str1[0] = 'H';  
    printf(" str1: %s\n", str1);  
    printf("str1[0] \n\n");


    // 场景2：加 const（安全！编译阶段直接拦截错误）
    printf("=== 场景2：const char *str（有 const） ===\n");
    const char *str2 = "world";  // 标准写法：明确字符串只读
    printf("初始 str2: %s\n", str2);
    
    // 尝试修改字符串内容（编译阶段直接报错，根本无法运行）
    // str2[0] = 'W';  // 取消注释后，编译器立即报错：“只读变量不能赋值”
    // 错误信息示例：assignment of read-only location '*str2'
    printf("（若取消 str2[0] 修改注释，编译器直接报错，避免崩溃）\n");

    return 0;
}
