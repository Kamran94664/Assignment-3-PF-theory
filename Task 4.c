#include <stdio.h>
#include <string.h>

struct Book {
    int id;
    int pop;
    int lastUsed;
};

int main() {
    int cap;
    int q;
	int i;
    printf("Enter shelf capacity: ");
    scanf("%d", &cap);

    printf("Enter number of operations: ");
    scanf("%d", &q);

    struct Book shelf[cap];
    int size = 0;
    int timer = 1;

    while (q > 0) {
        char op[10];
        int x;
        int y;

        printf("\nEnter operation (ADD or ACCESS): ");
        scanf("%s", op);

        if (strcmp(op, "ADD") == 0) {
            printf("Enter Book ID: ");
            scanf("%d", &x);

            printf("Enter Popularity: ");
            scanf("%d", &y);

            int found = -1;
			int i;
            for (i = 0; i < size; i++) {
                if (shelf[i].id == x) {
                    found = i;
                }
            }

            if (found != -1) {
                shelf[found].pop = y;
                shelf[found].lastUsed = timer;
                timer++;
                q--;
                continue;
            }

            if (size == cap) {
                int idx = 0;
                for (i = 1; i < size; i++) {
                    if (shelf[i].lastUsed < shelf[idx].lastUsed) {
                        idx = i;
                    }
                }
                for (i = idx; i < size - 1; i++) {
                    shelf[i] = shelf[i + 1];
                }
                size--;
            }
		
            shelf[size].id = x;
            shelf[size].pop = y;
            shelf[size].lastUsed = timer;
            timer++;
            size++;
        }

        else if (strcmp(op, "ACCESS") == 0) {
            printf("Enter Book ID: ");
            scanf("%d", &x);

            int found = -1;

            for (i= 0; i < size; i++) {
                if (shelf[i].id == x) {
                    found = i;
                }
            }

            if (found == -1) {
                printf("-1\n");
            } else {
                printf("%d\n", shelf[found].pop);
                shelf[found].lastUsed = timer;
                timer++;
            }
        }

        q--;
    }

    return 0;
}

