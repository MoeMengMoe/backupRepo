#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include <windows.h>

#define MAX_PDF 1000
#define MAX_STUDENT 1000
#define NAME_LEN 50
#define LINE_LEN 100
#define DIR_LEN 200

typedef struct {
    char name[NAME_LEN];
    long long id;  // 13位序号用long long存储
} Student;

char error_msg[512] = {0};

// 异常处理函数（消除未使用参数警告）
LONG WINAPI ExceptionHandler(EXCEPTION_POINTERS* ExceptionInfo) {
    (void)ExceptionInfo;  // 标记参数未使用
    printf("\n【错误提示】%s\n", error_msg[0] ? error_msg : "未知错误");
    printf("按任意键退出...");
    getchar();
    exit(1);
    return EXCEPTION_EXECUTE_HANDLER;
}

// 设置错误信息
void setError(const char* msg) {
    strncpy(error_msg, msg, sizeof(error_msg) - 1);
}

// 检查namelist.txt是否存在
int checkNameList() {
    FILE* fp = fopen("namelist.txt", "r");
    if (fp) {
        fclose(fp);
        return 1;
    }
    setError("未找到namelist.txt！请放在程序同目录下");
    return 0;
}

// 检查目标文件夹是否存在
int checkDir(const char* dir) {
    struct stat st;
    if (stat(dir, &st) == 0 && S_ISDIR(st.st_mode)) {
        return 1;
    }
    setError("目标文件夹不存在！请检查num值是否正确");
    return 0;
}

// 读取学生数据（修正格式字符串错误）
void readYourData(Student* students, int* count) {
    *count = 0;
    if (!checkNameList()) {
        int* p = NULL; *p = 0;  // 触发异常
    }

    FILE* fp = fopen("namelist.txt", "r");
    char line[LINE_LEN];
    int line_num = 0;

    while (fgets(line, LINE_LEN, fp)) {
        line_num++;
        line[strcspn(line, "\r\n")] = '\0';
        if (strlen(line) == 0) continue;

        char* tab = strchr(line, '\t');
        if (!tab) {
            // 修正：删除空格式字符串，正确打印提示
            printf("第%d行格式错误！必须用制表符分隔姓名和序号\n", line_num);
            setError("文件格式错误：存在非制表符分隔的行");
            int* p = NULL; *p = 0;
        }

        *tab = '\0';
        char* name = line;
        char* id_str = tab + 1;

        if (strlen(name) == 0) {
            printf("第%d行姓名为空！\n", line_num);
            setError("文件格式错误：存在空姓名");
            int* p = NULL; *p = 0;
        }

        for (int i = 0; id_str[i]; i++) {
            if (!isdigit((unsigned char)id_str[i])) {
                printf("第%d行序号不是纯数字！\n", line_num);
                setError("文件格式错误：序号包含非数字字符");
                int* p = NULL; *p = 0;
            }
        }

        long long id = atoll(id_str);  // 用atoll转换长整数
        if (id == 0) {
            printf("第%d行序号无效！\n", line_num);
            setError("文件格式错误：序号无效（可能为0）");
            int* p = NULL; *p = 0;
        }

        strncpy(students[*count].name, name, NAME_LEN - 1);
        students[*count].id = id;
        (*count)++;
    }

    fclose(fp);
    if (*count == 0) {
        setError("未读取到有效数据，请检查namelist.txt格式");
        int* p = NULL; *p = 0;
    }
    printf("成功读取 %d 条学生信息\n", *count);  // 暂时去掉中文符号，避免编码问题
}

// 提取PDF文件名末尾的三位数字（适配Calculus_1_陈镜羽_026.pdf）
int extractPdfEnd3(const char* filename, int* end3) {
    char name_no_ext[200];
    strncpy(name_no_ext, filename, sizeof(name_no_ext) - 1);
    char* ext = strrchr(name_no_ext, '.');
    if (!ext || strcasecmp(ext, ".pdf") != 0) {
        return 0;
    }
    *ext = '\0';

    char* last_underline = strrchr(name_no_ext, '_');
    if (!last_underline) {
        return 0;
    }
    char* num_str = last_underline + 1;

    if (strlen(num_str) != 3) {
        return 0;
    }
    for (int i = 0; i < 3; i++) {
        if (!isdigit((unsigned char)num_str[i])) {
            return 0;
        }
    }

    *end3 = atoi(num_str);
    return 1;
}

// 读取PDF文件的末尾数字（修正中文编码问题）
void readPdfEnd3(const char* dir, int* pdf_end3, int* count) {
    *count = 0;
    if (!checkDir(dir)) {
        int* p = NULL; *p = 0;
    }

    DIR* d = opendir(dir);
    struct dirent* entry;

    while ((entry = readdir(d))) {
        if (entry->d_type != DT_REG) continue;

        int end3;
        if (extractPdfEnd3(entry->d_name, &end3)) {
            pdf_end3[*count] = end3;
            (*count)++;
            printf("识别PDF：%s -> 末尾数字：%d\n", entry->d_name, end3);  // 用英文符号
        } else {
            printf("跳过无效文件：%s\n", entry->d_name);  // 避免中文
        }
    }

    closedir(d);
    printf("共识别 %d 个有效PDF文件\n", *count);
}

// 匹配序号后三位与PDF末尾三位
int isMatch(long long id, const int* pdf_end3, int pdf_count) {
    int id_end3 = (int)(id % 1000);
    for (int i = 0; i < pdf_count; i++) {
        if (pdf_end3[i] == id_end3) {
            return 1;
        }
    }
    return 0;
}

int main() {
    SetUnhandledExceptionFilter(ExceptionHandler);

    Student students[MAX_STUDENT] = {0};
    int student_count = 0;
    int pdf_end3[MAX_PDF] = {0};
    int pdf_count = 0;
    char num[20] = {0};
    char target_dir[DIR_LEN] = {0};

    printf("PDF匹配程序\n");  // 避免中文，或确保编码正确
    printf("按任意键继续...");
    getchar();
    system("cls");

    printf("请输入num值：");
    if (fgets(num, sizeof(num), stdin) == NULL) {
        setError("输入失败");
        int* p = NULL; *p = 0;
    }
    num[strcspn(num, "\r\n")] = '\0';
    if (strlen(num) == 0) {
        setError("num值不能为空");
        int* p = NULL; *p = 0;
    }

    snprintf(target_dir, DIR_LEN, "Calculus_%s_Class3", num);
    printf("目标文件夹：%s\n", target_dir);

    readYourData(students, &student_count);
    readPdfEnd3(target_dir, pdf_end3, &pdf_count);

    // 输出存在对应PDF的条目（修正long long输出格式）
    printf("\n存在对应PDF的条目：\n");
    int has_match = 0;
    for (int i = 0; i < student_count; i++) {
        int id_end3 = (int)(students[i].id % 1000);
        if (isMatch(students[i].id, pdf_end3, pdf_count)) {
            // 修正：long long用%lld输出
            printf("Name: %s | ID: %lld | Last 3: %d | Status: Exists\n",
                   students[i].name, students[i].id, id_end3);
            has_match = 1;
        }
    }
    if (!has_match) printf("No matching files\n");

    // 输出不存在对应PDF的条目
    printf("\n不存在对应PDF的条目：\n");
    int no_match = 0;
    for (int i = 0; i < student_count; i++) {
        int id_end3 = (int)(students[i].id % 1000);
        if (!isMatch(students[i].id, pdf_end3, pdf_count)) {
            printf("Name: %s | ID: %lld | Last 3: %d | Status: Missing\n",
                   students[i].name, students[i].id, id_end3);
            no_match = 1;
        }
    }
    if (!no_match) printf("All entries have matching PDFs\n");

    printf("\n处理完成！按任意键退出...");
    getchar();
    return 0;
}