#include <stdio.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    char designation[50];
    float salary;
};

void displayEmployees(struct Employee e[], int n) {
    int i;
	printf("\nAll Employees:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", e[i].id);
        printf("%s ", e[i].name);
        printf("%s ", e[i].designation);
        printf("%.2f\n", e[i].salary);
    }
}

void findHighestSalary(struct Employee e[], int n) {
    int idx = 0;
    int i;
    for (i = 1; i < n; i++) {
        if (e[i].salary > e[idx].salary) {
            idx = i;
        }
    }
    printf("\nHighest Salary Employee:\n");
    printf("%d ", e[idx].id);
    printf("%s ", e[idx].name);
    printf("%s ", e[idx].designation);
    printf("%.2f\n", e[idx].salary);
}

void searchEmployee(struct Employee e[], int n, int id, char name[]) {
    int i;
	for (i = 0; i < n; i++) {
        if (e[i].id == id || strcmp(e[i].name, name) == 0) {
            printf("\nEmployee Found:\n");
            printf("%d ", e[i].id);
            printf("%s ", e[i].name);
            printf("%s ", e[i].designation);
            printf("%.2f\n", e[i].salary);
            return;
        }
    }
    printf("\nNot Found\n");
}

void giveBonus(struct Employee *e, int n, float threshold) {
    int i;
	for (i = 0; i < n; i++) {
        if (e[i].salary < threshold) {
            e[i].salary = e[i].salary * 1.10;
        }
    }
}

int main() {
    int n;

    printf("Enter number of employees: ");
    scanf("%d", &n);

    struct Employee e[n];
	int i;
    for (i = 0; i < n; i++) {
        printf("\nEnter Employee ID: ");
        scanf("%d", &e[i].id);

        printf("Enter Name: ");
        scanf("%s", e[i].name);

        printf("Enter Designation: ");
        scanf("%s", e[i].designation);

        printf("Enter Salary: ");
        scanf("%f", &e[i].salary);
    }

    displayEmployees(e, n);

    findHighestSalary(e, n);

    int searchID;
    char searchName[50];

    printf("\nEnter ID to search: ");
    scanf("%d", &searchID);

    printf("Enter Name to search: ");
    scanf("%s", searchName);

    searchEmployee(e, n, searchID, searchName);

    giveBonus(e, n, 50000);

    printf("\nAfter Bonus:\n");
    displayEmployees(e, n);

    return 0;
}

