/*
Part (m):
Dynamic memory allocation is more efficient than using fixed-size rows because
it allocates only the exact amount of memory needed for each line. A fixed-size
2D array wastes space when lines are short, but with malloc, realloc, and free,
this editor grows and shrinks memory on demand. This minimizes memory usage,
allows unlimited line lengths, and supports flexible resizing without wasting RAM.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **lines = NULL;
int lineCount = 0;
int capacity = 0;

void ensureCapacity() {
    if (lineCount >= capacity) {
        int newcap = capacity == 0 ? 2 : capacity * 2;
        char **temp = realloc(lines, newcap * sizeof(char*));
        if (!temp) {
            printf("Memory error\n");
            exit(1);
        }
        lines = temp;
        capacity = newcap;
    }
}

void shrinkToFit() {
    if (lineCount < capacity) {
        char **temp = realloc(lines, lineCount * sizeof(char*));
        if (!temp && lineCount > 0) return;
        lines = temp;
        capacity = lineCount;
    }
}

void insertLine(int index, const char *text) {
    if (index < 0 || index > lineCount) return;
    ensureCapacity();
    memmove(&lines[index+1], &lines[index], (lineCount - index) * sizeof(char*));
    char *s = malloc(strlen(text) + 1);
    if (!s) {
        printf("Memory error\n");
        exit(1);
    }
    strcpy(s, text);
    lines[index] = s;
    lineCount++;
}

void deleteLine(int index) {
    if (index < 0 || index >= lineCount) return;
    free(lines[index]);
    memmove(&lines[index], &lines[index+1], (lineCount - index - 1) * sizeof(char*));
    lineCount--;
}

void printAllLines() {
    int i;
    for (i = 0; i < lineCount; i++) {
        printf("%d: %s\n", i, lines[i]);
    }
}

void freeAll() {
    int i;
    for (i = 0; i < lineCount; i++) free(lines[i]);
    free(lines);
    lines = NULL;
    lineCount = 0;
    capacity = 0;
}

void saveToFile(const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) return;
    int i;
    for (i = 0; i < lineCount; i++) fprintf(f, "%s\n", lines[i]);
    fclose(f);
}

void loadFromFile(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return;
    freeAll();
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), f)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        insertLine(lineCount, buffer);
    }
    fclose(f);
}

int main() {
    int choice;

    while (1) {
        printf("1 Insert Line\n");
        printf("2 Delete Line\n");
        printf("3 Print All Lines\n");
        printf("4 Save To File\n");
        printf("5 Load From File\n");
        printf("6 Shrink To Fit\n");
        printf("7 Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int index;
            char text[1024];
            printf("Enter index: ");
            scanf("%d", &index);
            printf("Enter text: ");
            scanf("%*c");
            fgets(text, sizeof(text), stdin);
            text[strcspn(text, "\n")] = '\0';
            insertLine(index, text);
        }

        else if (choice == 2) {
            int index;
            printf("Enter index: ");
            scanf("%d", &index);
            deleteLine(index);
        }

        else if (choice == 3) {
            printAllLines();
        }

        else if (choice == 4) {
            char filename[256];
            printf("Enter filename: ");
            scanf("%s", filename);
            saveToFile(filename);
        }

        else if (choice == 5) {
            char filename[256];
            printf("Enter filename: ");
            scanf("%s", filename);
            loadFromFile(filename);
        }

        else if (choice == 6) {
            shrinkToFit();
        }

        else if (choice == 7) {
            freeAll();
            break;
        }
    }

    return 0;
}

