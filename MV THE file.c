// mv_file.c
// A tool to rename and move PDF files based on a name list.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <io.h>

#define MAX_LEN        512
#define MAX_LINE       256
#define MAX_NAME       128
#define MAX_STUDENTS   1000

typedef struct {
    char name[MAX_NAME];   // Student name (for matching filename)
    int  id;               // Last 3 digits of the 13-digit number
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

/**
 * Parse a line: Name<Tab>13DigitNumber
 * @param line Input line
 * @param id Output: last 3 digits
 * @param name Output: student name
 * @return 1 on success, 0 on failure
 */
int parse_line(const char* line, int* id, char* name) {
    char buf[MAX_LINE];
    strcpy(buf, line);

    // Remove newline
    buf[strcspn(buf, "\r\n")] = '\0';

    // Find Tab
    char* tab = strchr(buf, '\t');
    if (!tab) return 0;

    *tab = '\0';
    char* name_str = buf;
    char* num_str   = tab + 1;

    // Trim whitespace from name
    while (*name_str == ' ' || *name_str == '\t') name_str++;
    char* name_end = name_str + strlen(name_str) - 1;
    while (name_end > name_str && (*name_end == ' ' || *name_end == '\t')) name_end--;
    name_end[1] = '\0';

    if (strlen(name_str) == 0) return 0;

    // Validate number: must be 13 digits
    if (strlen(num_str) != 13) return 0;
    for (int i = 0; i < 13; i++) {
        if (num_str[i] < '0' || num_str[i] > '9') return 0;
    }

    // Extract last 3 digits
    *id = (num_str[10] - '0') * 100 + 
          (num_str[11] - '0') * 10 + 
          (num_str[12] - '0');

    strncpy(name, name_str, MAX_NAME - 1);
    name[MAX_NAME - 1] = '\0';
    return 1;
}

/**
 * Create directory recursively
 * @param path Directory path
 * @return 1 on success, 0 on failure
 */
int create_directory(const char* path) {
    char p[MAX_LEN];
    strcpy(p, path);
    int len = strlen(p);
    if (len <= 0) return 0;
    if (p[len-1] == '\\' || p[len-1] == '/') p[len-1] = '\0';

    for (char* q = p + 1; *q; q++) {
        if (*q == '\\' || *q == '/') {
            *q = '\0';
            _mkdir(p);
            *q = '\\';
        }
    }
    return _mkdir(p) == 0 || _access(p, 0) == 0;
}

/**
 * Scan and move PDF files
 * @param search_dir Source directory
 * @param dest_dir Target directory
 * @param num User input number
 */
/**
 * Scan and move PDF files - Strict filename match
 * @param search_dir Source directory
 * @param dest_dir Target directory
 * @param num User input number
 */
void scan_and_move(const char* search_dir, const char* dest_dir, int num) {
    char pattern[MAX_LEN];
    // Use dir command to list only .pdf files
    snprintf(pattern, sizeof(pattern), "dir \"%s\" /b 2>nul", search_dir);

    FILE* fp = _popen(pattern, "r");
    if (!fp) {
        printf("Failed to scan directory: %s\n", search_dir);
        return;
    }

    char filename[MAX_NAME];
    while (fgets(filename, sizeof(filename), fp)) {
        // Remove newline
        filename[strcspn(filename, "\r\n")] = '\0';
        if (strlen(filename) == 0) continue;

        // Check if it ends with .pdf (case insensitive)
        int len = strlen(filename);
        if (len < 5) continue;
        char* ext = filename + len - 4;
        if (_stricmp(ext, ".pdf") != 0) {
            printf("Skipped: %s (not a PDF file)\n", filename);
            continue;
        }

        // Extract basename (without .pdf)
        char basename[MAX_NAME];
        strcpy(basename, filename);
        basename[len - 4] = '\0';  // Remove .pdf

        // Search for matching student
        int found = 0;
        for (int i = 0; i < student_count; i++) {
            if (_stricmp(basename, students[i].name) == 0) {
                found = 1;
                // Generate new filename
                char new_filename[MAX_NAME];
                snprintf(new_filename, sizeof(new_filename), 
                         "Calculus_%d_%s_%03d.pdf", num, students[i].name, students[i].id);

                // Build full paths
                char src_path[MAX_LEN], dest_path[MAX_LEN];
                snprintf(src_path, sizeof(src_path), "%s\\%s", search_dir, filename);
                snprintf(dest_path, sizeof(dest_path), "%s\\%s", dest_dir, new_filename);

                // Execute move command
                char cmd[MAX_LEN];
                snprintf(cmd, sizeof(cmd), "move \"%s\" \"%s\"", src_path, dest_path);
                system(cmd);
                printf("Moved: %s -> %s\n", filename, new_filename);
                break;
            }
        }

        if (!found) {
            printf("Skipped: %s (no matching name in list)\n", filename);
        }
    }
    _pclose(fp);
}

/**
 * Main function
 */
int main() {
    FILE* f = fopen("namelist.txt", "r");
    if (!f) {
        printf("Error: cannot open namelist.txt\n");
        printf("Please check if the file exists and is in the same directory.\n");
        return 1;
    }

    printf("Parsing namelist.txt...\n\n");
    char line[MAX_LINE];
    int line_num = 0;

    while (fgets(line, sizeof(line), f)) {
        line_num++;
        printf("Line %d: [%s]", line_num, line);

        int id;
        char name[MAX_NAME];
        if (parse_line(line, &id, name)) {
            strcpy(students[student_count].name, name);
            students[student_count].id = id;
            printf("  --> Success: name='%s', last3=%03d\n\n", name, id);
            student_count++;
        } else {
            printf("  --> Failed: invalid format or data\n\n");
        }
    }
    fclose(f);

    if (student_count == 0) {
        printf("Error: no valid data loaded from namelist.txt\n");
        printf("Please check:\n");
        printf("1. File encoding: save as ANSI in Notepad\n");
        printf("2. Columns separated by Tab (not space)\n");
        printf("3. Number must be exactly 13 digits\n");
        printf("4. Name must match filename exactly (e.g., LiQijun.pdf)\n");
        return 1;
    }

    printf("Loaded %d students successfully.\n\n", student_count);

    int num;
    printf("Enter Num value: ");
    if (scanf("%d", &num) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    char dest_dir[MAX_LEN];
    snprintf(dest_dir, sizeof(dest_dir), "D:\\Assignment\\Calculus_%d_Class3", num);

    if (!create_directory(dest_dir)) {
        printf("Failed to create directory: %s\n", dest_dir);
        return 1;
    }
    printf("Output directory: %s\n\n", dest_dir);

    printf("Processing files...\n");
    scan_and_move(".", dest_dir, num);
    scan_and_move(".\\QQ", dest_dir, num);
    printf("All tasks completed.\n");

    return 0;
}