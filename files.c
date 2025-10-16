#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <direct.h>
#include <errno.h>

char g_prefix[256];
char g_dest_dir[512];

void search_and_move(const char* current_dir) {
    WIN32_FIND_DATA find_data;
    char search_path[512];
    HANDLE hFind;

    sprintf(search_path, "%s\\*.*", current_dir);
    hFind = FindFirstFile(search_path, &find_data);

    if (hFind == INVALID_HANDLE_VALUE) {
        return;
    }

    do {
        if (strcmp(find_data.cFileName, ".") == 0 || strcmp(find_data.cFileName, "..") == 0) {
            continue;
        }

        char full_path[512];
        sprintf(full_path, "%s\\%s", current_dir, find_data.cFileName);

        if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            search_and_move(full_path);
        } else {
            if (strstr(find_data.cFileName, g_prefix) == find_data.cFileName) {
                char dest_path[512];
                sprintf(dest_path, "%s\\%s", g_dest_dir, find_data.cFileName);
                
                if (MoveFileEx(full_path, dest_path, MOVEFILE_REPLACE_EXISTING)) {
                    printf("已移动: %s -> %s\n", full_path, dest_path);
                } else {
                    // 修正格式符：将 %d 改为 %lu（匹配 DWORD 类型）
                    printf("移动失败: %s (错误代码: %lu)\n", full_path, GetLastError());
                }
            }
        }
    } while (FindNextFile(hFind, &find_data));

    FindClose(hFind);
}

int main() {
    char num[50];
    
    printf("请输入数字num: ");
    if (scanf("%s", num) != 1) {
        printf("输入错误！\n");
        return 1;
    }

    sprintf(g_prefix, "Calculus_%s_", num);
    sprintf(g_dest_dir, "D:\\Assignment\\Calculus_%s_Class3", num);

    if (_mkdir("D:\\Assignment") != 0 && errno != EEXIST) {
        printf("创建D:\\Assignment失败！\n");
        return 1;
    }
    
    if (_mkdir(g_dest_dir) != 0 && errno != EEXIST) {
        printf("创建目标目录 %s 失败！\n", g_dest_dir);
        return 1;
    }

    char current_dir[512];
    if (_getcwd(current_dir, sizeof(current_dir)) == NULL) {
        printf("获取当前目录失败！\n");
        return 1;
    }

    printf("开始搜索并移动文件...\n");
    printf("搜索前缀: %s\n", g_prefix);
    printf("目标目录: %s\n", g_dest_dir);
    
    search_and_move(current_dir);

    printf("操作完成！\n");
    return 0;
}