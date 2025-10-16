// #define _CRT_SECURE_NO_WARNINGS
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <io.h>
// #include <windows.h>
// #include <ctype.h>  // 用于 isdigit()

// // 避免重定义 MAX_PATH
// #ifndef MAX_PATH
// #define MAX_PATH 260
// #endif

// #define MAX_LINE      256
// #define MAX_STUDENTS  1000

// typedef struct {
//     char name[64];
//     char id[16];
// } Student;

// Student students[MAX_STUDENTS];
// int student_count = 0;

// // 函数声明
// int read_namelist(void);
// int find_student_by_last3(const char* last3, Student* result);
// int copy_directory(const char* src, const char* dst);
// void rename_pdfs_in_folder(const char* folder_path, int num);

// int main() {
//     int Num;
//     char src_folder[MAX_PATH];
//     char dst_folder[MAX_PATH];

//     printf("Please enter the homework number Num: ");  // 改为英文输出，避免编码问题
//     if (scanf("%d", &Num) != 1 || Num <= 0) {
//         fprintf(stderr, "Error: Please enter a positive integer!\n");
//         return 1;
//     }

//     sprintf(src_folder, "Calculus_%d_Class3", Num);
//     sprintf(dst_folder, "2025级电通三班微积分第%d次作业", Num);  // 暂用英文路径

//     if (_access(src_folder, 0) != 0) {
//         fprintf(stderr, "Error: Source folder '%s' does not exist!\n", src_folder);
//         return 1;
//     }

//     if (read_namelist() == -1) {
//         fprintf(stderr, "Error: Cannot read namelist.txt!\n");
//         return 1;
//     }
//     printf("Loaded %d students.\n", student_count);

//     printf("Copying folder...\n");
//     if (copy_directory(src_folder, dst_folder) != 0) {
//         fprintf(stderr, "Error: Failed to copy folder!\n");
//         return 1;
//     }
//     printf("Folder copied to '%s'\n", dst_folder);

//     rename_pdfs_in_folder(dst_folder, Num);

//     printf("All done!\n");
//     system("pause");
//     return 0;
// }

// // 读取名单（不再使用 cp936）
// int read_namelist() {
//     FILE* fp = fopen("namelist.txt", "r");  // 标准 fopen，仅两个参数
//     if (!fp) {
//         perror("fopen failed");
//         return -1;
//     }

//     char line[MAX_LINE];
//     while (fgets(line, sizeof(line), fp)) {
//         line[strcspn(line, "\r\n")] = '\0';
//         if (line[0] == '\0') continue;

//         char* tab = strchr(line, '\t');
//         if (!tab) continue;

//         *tab = '\0';
//         char* name = line;
//         char* id = tab + 1;

//         if (strlen(name) == 0 || strlen(id) < 3) continue;

//         if (student_count < MAX_STUDENTS) {
//             strcpy(students[student_count].name, name);
//             strcpy(students[student_count].id, id);
//             student_count++;
//         }
//     }

//     fclose(fp);
//     return student_count > 0 ? 0 : -1;
// }

// int find_student_by_last3(const char* last3, Student* result) {
//     for (int i = 0; i < student_count; i++) {
//         int len = strlen(students[i].id);
//         if (len >= 3) {
//             const char* tail = students[i].id + len - 3;
//             if (strncmp(tail, last3, 3) == 0) {
//                 *result = students[i];
//                 return 1;
//             }
//         }
//     }
//     return 0;
// }

// int copy_directory(const char* src, const char* dst) {
//     SHFILEOPSTRUCT fileop;
//     char from[MAX_PATH + 2] = {0};
//     char to[MAX_PATH + 2] = {0};

//     strcpy(from, src);
//     strcpy(to, dst);
//     from[strlen(from) + 1] = '\0';
//     to[strlen(to) + 1] = '\0';

//     ZeroMemory(&fileop, sizeof(fileop));
//     fileop.hwnd = NULL;
//     fileop.wFunc = FO_COPY;
//     fileop.pFrom = from;
//     fileop.pTo = to;
//     fileop.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;

//     int ret = SHFileOperation(&fileop);
//     return (ret == 0 && !fileop.fAnyOperationsAborted) ? 0 : -1;
// }

// void rename_pdfs_in_folder(const char* folder_path, int num) {
//     char search_path[MAX_PATH];
//     WIN32_FIND_DATA findData;
//     HANDLE hFind;

//     sprintf(search_path, "%s\\*.pdf", folder_path);
//     hFind = FindFirstFile(search_path, &findData);

//     if (hFind == INVALID_HANDLE_VALUE) {
//         printf("No PDF files found in '%s'\n", folder_path);
//         return;
//     }

//     do {
//         if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;

//         const char* filename = findData.cFileName;
//         size_t len = strlen(filename);
//         if (len < 8 || _stricmp(filename + len - 4, ".pdf") != 0) continue;

//         char basename[256] = {0};
//         strncpy(basename, filename, len - 4);

//         const char* last_under = strrchr(basename, '_');
//         if (!last_under || strlen(last_under + 1) != 3) {
//             printf("Skipped (format): %s\n", filename);
//             continue;
//         }

//         const char* digits = last_under + 1;
//         if (!isdigit((unsigned char)digits[0]) ||
//             !isdigit((unsigned char)digits[1]) ||
//             !isdigit((unsigned char)digits[2])) {
//             printf("Skipped (not digit): %s\n", filename);
//             continue;
//         }

//         char last3[4] = {0};
//         strncpy(last3, digits, 3);

//         Student stu;
//         if (!find_student_by_last3(last3, &stu)) {
//             printf("Not matched (%s): %s\n", last3, filename);
//             continue;
//         }

//         char id_last2[3] = {0};
//         int id_len = strlen(stu.id);
//         if (id_len >= 2) {
//             strncpy(id_last2, stu.id + id_len - 2, 2);
//         } else {
//             printf("ID too short: %s\n", stu.id);
//             continue;
//         }

//         char new_name[MAX_PATH] = {0};
//         // 使用英文文件名避免编码问题
//         sprintf(new_name, "微积分第%d次作业_3班_%s_%s.pdf", num, id_last2, stu.name);

//         char old_path[MAX_PATH], new_path[MAX_PATH];
//         sprintf(old_path, "%s\\%s", folder_path, filename);
//         sprintf(new_path, "%s\\%s", folder_path, new_name);

//         if (MoveFileEx(old_path, new_path, MOVEFILE_REPLACE_EXISTING)) {
//             printf("Renamed: %s -> %s\n", filename, new_name);
//         } else {
//             printf("Rename failed (error %lu): %s\n", GetLastError(), filename);
//         }

//     } while (FindNextFile(hFind, &findData));

//     FindClose(hFind);
// }
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <windows.h>
#include <ctype.h>  // 用于 isdigit()

// 避免重定义 MAX_PATH
#ifndef MAX_PATH
#define MAX_PATH 260
#endif

#define MAX_LINE      256
#define MAX_STUDENTS  1000

typedef struct {
    char name[64];
    char id[16];     // 足够存储13位学号 + '\0'
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

// 函数声明
int read_namelist(void);
int find_student_by_last3(const char* last3, Student* result);
int copy_directory(const char* src, const char* dst);
void rename_pdfs_in_folder(const char* folder_path, int num);

int main() {
    int Num;
    char src_folder[MAX_PATH];
    char dst_folder[MAX_PATH];

    // 设置控制台为 UTF-8 编码，支持中文输出
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    printf("Please enter the homework number Num: ");
    if (scanf("%d", &Num) != 1 || Num <= 0) {
        fprintf(stderr, "Error: Please enter a positive integer!\n");
        return 1;
    }

    // 清除输入缓冲区残留字符
    while (getchar() != '\n');

    sprintf(src_folder, "Calculus_%d_Class3", Num);
    sprintf(dst_folder, "2025级电通三班微积分第%d次作业", Num);

    if (_access(src_folder, 0) != 0) {
        fprintf(stderr, "Error: Source folder '%s' does not exist!\n", src_folder);
        return 1;
    }

    if (read_namelist() == -1) {
        fprintf(stderr, "Error: Cannot read namelist.txt!\n");
        return 1;
    }
    printf("Loaded %d students.\n", student_count);

    printf("Copying folder...\n");
    if (copy_directory(src_folder, dst_folder) != 0) {
        fprintf(stderr, "Error: Failed to copy folder!\n");
        return 1;
    }
    printf("Folder copied to '%s'\n", dst_folder);

    rename_pdfs_in_folder(dst_folder, Num);

    printf("All done!\n");
    system("pause");
    return 0;
}

// 读取名单：格式为 “姓名\t学号”，每行一条
int read_namelist() {
    FILE* fp = fopen("namelist.txt", "r");
    if (!fp) {
        perror("fopen failed");
        return -1;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), fp)) {
        // 去除换行符
        line[strcspn(line, "\r\n")] = '\0';
        if (line[0] == '\0') continue;

        char* tab = strchr(line, '\t');
        if (!tab) continue;

        *tab = '\0';
        char* name = line;
        char* id = tab + 1;

        if (strlen(name) == 0 || strlen(id) < 3) continue;

        if (student_count < MAX_STUDENTS) {
            strcpy(students[student_count].name, name);
            strcpy(students[student_count].id, id);
            student_count++;
        }
    }

    fclose(fp);
    return student_count > 0 ? 0 : -1;
}

// 根据学号后三位查找学生
int find_student_by_last3(const char* last3, Student* result) {
    for (int i = 0; i < student_count; i++) {
        int len = strlen(students[i].id);
        if (len >= 3) {
            const char* tail = students[i].id + len - 3;
            if (strncmp(tail, last3, 3) == 0) {
                *result = students[i];
                return 1;
            }
        }
    }
    return 0;
}

// 复制整个文件夹（使用 Windows API）
int copy_directory(const char* src, const char* dst) {
    SHFILEOPSTRUCT fileop;
    char from[MAX_PATH + 2] = {0};
    char to[MAX_PATH + 2] = {0};

    strcpy(from, src);
    strcpy(to, dst);
    from[strlen(from) + 1] = '\0';  // 双 null 结尾
    to[strlen(to) + 1] = '\0';

    ZeroMemory(&fileop, sizeof(fileop));
    fileop.hwnd = NULL;
    fileop.wFunc = FO_COPY;
    fileop.pFrom = from;
    fileop.pTo = to;
    fileop.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT;

    int ret = SHFileOperation(&fileop);
    return (ret == 0 && !fileop.fAnyOperationsAborted) ? 0 : -1;
}

// 重命名目标文件夹中的所有 PDF 文件
void rename_pdfs_in_folder(const char* folder_path, int num) {
    char search_path[MAX_PATH];
    WIN32_FIND_DATA findData;
    HANDLE hFind;

    sprintf(search_path, "%s\\*.pdf", folder_path);
    hFind = FindFirstFile(search_path, &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("No PDF files found in '%s'\n", folder_path);
        return;
    }

    do {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;

        const char* filename = findData.cFileName;
        size_t len = strlen(filename);
        if (len < 8 || _stricmp(filename + len - 4, ".pdf") != 0) continue;

        char basename[256] = {0};
        strncpy(basename, filename, len - 4);  // 去掉 .pdf

        const char* last_under = strrchr(basename, '_');
        if (!last_under || strlen(last_under + 1) != 3) {
            printf("Skipped (format): %s\n", filename);
            continue;
        }

        const char* digits = last_under + 1;
        if (!isdigit((unsigned char)digits[0]) ||
            !isdigit((unsigned char)digits[1]) ||
            !isdigit((unsigned char)digits[2])) {
            printf("Skipped (not digit): %s\n", filename);
            continue;
        }

        char last3[4] = {0};
        strncpy(last3, digits, 3);

        Student stu;
        if (!find_student_by_last3(last3, &stu)) {
            printf("Not matched (%s): %s\n", last3, filename);
            continue;
        }

        // 构造新文件名：微积分I+电通+学号+姓名+第Num次作业.pdf
        char new_name[MAX_PATH] = {0};
        sprintf(new_name, "微积分I+电通+%s+%s+第%d次作业.pdf", stu.id, stu.name, num);

        char old_path[MAX_PATH], new_path[MAX_PATH];
        sprintf(old_path, "%s\\%s", folder_path, filename);
        sprintf(new_path, "%s\\%s", folder_path, new_name);

        if (MoveFileEx(old_path, new_path, MOVEFILE_REPLACE_EXISTING)) {
            printf("Renamed: %s -> %s\n", filename, new_name);
        } else {
            DWORD error = GetLastError();
            printf("Rename failed (error %lu): %s\n", error, filename);
        }

    } while (FindNextFile(hFind, &findData));

    FindClose(hFind);
}