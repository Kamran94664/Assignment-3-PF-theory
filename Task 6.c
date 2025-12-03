#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int studentID;
    char fullName[100];
    char batch[50];
    char membership[10];
    char regDate[20];
    char dob[20];
    char interest[10];
} Student;

Student *database = NULL;
int total = 0;



void loadDatabase(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("No previous database found. Creating new.\n");
        return;
    }

    Student temp;
    while (fread(&temp, sizeof(Student), 1, fp)) {
        database = realloc(database, (total + 1) * sizeof(Student));
        database[total] = temp;
        total++;
    }

    fclose(fp);
}


void saveDatabase(const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        printf("Error saving database!\n");
        return;
    }
	int i;
    for ( i = 0; i < total; i++) {
        fwrite(&database[i], sizeof(Student), 1, fp);
    }

    fclose(fp);
}


int findStudent(int id) {
    int i;
	for (i = 0; i < total; i++) {
        if (database[i].studentID == id)
            return i;
    }
    return -1;
}


void addStudent(const char *filename) {
    Student s;

    printf("Enter Student ID: ");
    scanf("%d", &s.studentID);

    if (findStudent(s.studentID) != -1) {
        printf("Student ID already exists!\n");
        return;
    }

    printf("Enter Full Name: ");
    getchar();
    fgets(s.fullName, 100, stdin);
    s.fullName[strcspn(s.fullName, "\n")] = 0;

    printf("Enter Batch (CS/SE/AI/Cyber Security): ");
    fgets(s.batch, 50, stdin);
    s.batch[strcspn(s.batch, "\n")] = 0;

    printf("Enter Membership (IEEE/ACM): ");
    fgets(s.membership, 10, stdin);
    s.membership[strcspn(s.membership, "\n")] = 0;

    printf("Enter Registration Date (YYYY-MM-DD): ");
    fgets(s.regDate, 20, stdin);
    s.regDate[strcspn(s.regDate, "\n")] = 0;

    printf("Enter Date of Birth (YYYY-MM-DD): ");
    fgets(s.dob, 20, stdin);
    s.dob[strcspn(s.dob, "\n")] = 0;

    printf("Enter Interest (IEEE/ACM/Both): ");
    fgets(s.interest, 10, stdin);
    s.interest[strcspn(s.interest, "\n")] = 0;

   
    database = realloc(database, (total + 1) * sizeof(Student));
    database[total] = s;
    total++;

    
    saveDatabase(filename);

    printf("Student Added Successfully!\n");
}

void updateStudent(const char *filename) {
    int id;
    printf("Enter Student ID to update: ");
    scanf("%d", &id);

    int pos = findStudent(id);
    if (pos == -1) {
        printf("Student not found!\n");
        return;
    }

    printf("Enter New Batch: ");
    getchar();
    fgets(database[pos].batch, 50, stdin);
    database[pos].batch[strcspn(database[pos].batch, "\n")] = 0;

    printf("Enter New Membership (IEEE/ACM): ");
    fgets(database[pos].membership, 10, stdin);
    database[pos].membership[strcspn(database[pos].membership, "\n")] = 0;

    saveDatabase(filename);

    printf("Record Updated!\n");
}


void deleteStudent(const char *filename) {
    int id;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    int pos = findStudent(id);
    if (pos == -1) {
        printf("Student Not Found!\n");
        return;
    }
	int i;
    for (i = pos; i < total - 1; i++) {
        database[i] = database[i + 1];
    }
    total--;

    database = realloc(database, total * sizeof(Student));

    saveDatabase(filename);

    printf("Student Deleted!\n");
}


void displayAll() {
    if (total == 0) {
        printf("No records found.\n");
        return;
    }
	int i;
    for (i = 0; i < total; i++) {
        printf("\n----------------------------\n");
        printf("Student ID: %d\n", database[i].studentID);
        printf("Name: %s\n", database[i].fullName);
        printf("Batch: %s\n", database[i].batch);
        printf("Membership: %s\n", database[i].membership);
        printf("Reg Date: %s\n", database[i].regDate);
        printf("DOB: %s\n", database[i].dob);
        printf("Interest: %s\n", database[i].interest);
    }
}

void batchReport() {
    char batchName[50];

    printf("Enter batch (CS/SE/AI/Cyber Security): ");
    getchar();
    fgets(batchName, 50, stdin);
    batchName[strcspn(batchName, "\n")] = 0;

    printf("\n--- Students in Batch %s ---\n", batchName);

    int found = 0;
	int i;
    for (i = 0; i < total; i++) {
        if (strcmp(database[i].batch, batchName) == 0) {
            printf("ID: %d | Name: %s | Membership: %s\n",
                   database[i].studentID,
                   database[i].fullName,
                   database[i].membership);
            found = 1;
        }
    }

    if (!found)
        printf("No students found in this batch.\n");
}


int main() {
    const char *filename = "members.dat";

    loadDatabase(filename);

    int choice;

    while (1) {
        printf("\n==== MEMBERSHIP SYSTEM MENU ====\n");
        printf("1. Register New Student\n");
        printf("2. Update Student\n");
        printf("3. Delete Student\n");
        printf("4. View All Students\n");
        printf("5. Batch-wise Report\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(filename); break;
            case 2: updateStudent(filename); break;
            case 3: deleteStudent(filename); break;
            case 4: displayAll(); break;
            case 5: batchReport(); break;
            case 6: 
                saveDatabase(filename);
                printf("Exiting... Data Saved.\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
