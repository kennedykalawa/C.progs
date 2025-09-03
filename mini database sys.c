#include <stdio.h>
#include <string.h>

struct Student {
    char name[50];
    int age;
    float fee_balance;
};

#define FILENAME "students.txt"

void saveToFile(struct Student students[], int n) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        fprintf(file, "%s,%d,%.2f\n", students[i].name, students[i].age, students[i].fee_balance);
    }
    fclose(file);
    printf("Data saved successfully.\n");
}

int loadFromFile(struct Student students[]) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No previous data found. Starting fresh.\n");
        return 0;
    }
    int count = 0;
    while (fscanf(file, " %49[^,],%d,%f\n", 
                  students[count].name, 
                  &students[count].age, 
                  &students[count].fee_balance) == 3) {
        count++;
    }
    fclose(file);
    printf("Loaded %d students from file.\n", count);
    return count;
}

int main() {
    int n, i, choice;
    struct Student students[100]; // max 100 students

    // Load existing records if available
    n = loadFromFile(students);

    // Menu system
    do {
        printf("\n==== Student Management Menu ====\n");
        printf("1. Add new students\n");
        printf("2. View all students\n");
        printf("3. Search student by name\n");
        printf("4. Show students with pending fees\n");
        printf("5. Update a student's record\n");
        printf("6. Save and Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int newCount;
            printf("How many students do you want to add? ");
            scanf("%d", &newCount);

            for (i = n; i < n + newCount; i++) {
                printf("\nEnter details for student %d:\n", i + 1);

                printf("Name: ");
                scanf(" %49[^\n]", students[i].name);

                printf("Age: ");
                scanf("%d", &students[i].age);

                printf("Fee Balance: ");
                scanf("%f", &students[i].fee_balance);
            }
            n += newCount;
        }
        else if (choice == 2) {
            printf("\n--- Student Records ---\n");
            for (i = 0; i < n; i++) {
                printf("\nStudent %d:\n", i + 1);
                printf("Name       : %s\n", students[i].name);
                printf("Age        : %d\n", students[i].age);
                printf("Fee Balance: $%.2f\n", students[i].fee_balance);
            }
        } 
        else if (choice == 3) {
            char searchName[50];
            int found = 0;
            printf("\nEnter name to search: ");
            scanf(" %49[^\n]", searchName);

            for (i = 0; i < n; i++) {
                if (strcmp(students[i].name, searchName) == 0) {
                    printf("\nStudent Found:\n");
                    printf("Name       : %s\n", students[i].name);
                    printf("Age        : %d\n", students[i].age);
                    printf("Fee Balance: $%.2f\n", students[i].fee_balance);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("No student found with name \"%s\".\n", searchName);
            }
        }
        else if (choice == 4) {
            printf("\n--- Students with Pending Fees ---\n");
            int found = 0;
            for (i = 0; i < n; i++) {
                if (students[i].fee_balance > 0) {
                    printf("%s owes $%.2f\n", students[i].name, students[i].fee_balance);
                    found = 1;
                }
            }
            if (!found) {
                printf("All students have cleared their fees!\n");
            }
        }
        else if (choice == 5) {
            char updateName[50];
            int found = 0;
            printf("\nEnter the name of the student to update: ");
            scanf(" %49[^\n]", updateName);

            for (i = 0; i < n; i++) {
                if (strcmp(students[i].name, updateName) == 0) {
                    found = 1;
                    int updateChoice;
                    printf("\nStudent Found: %s\n", students[i].name);
                    printf("1. Update Name\n");
                    printf("2. Update Age\n");
                    printf("3. Update Fee Balance\n");
                    printf("4. Record a Payment (reduce fee)\n");
                    printf("Choose what to update: ");
                    scanf("%d", &updateChoice);

                    if (updateChoice == 1) {
                        printf("Enter new name: ");
                        scanf(" %49[^\n]", students[i].name);
                    }
                    else if (updateChoice == 2) {
                        printf("Enter new age: ");
                        scanf("%d", &students[i].age);
                    }
                    else if (updateChoice == 3) {
                        printf("Enter new fee balance: ");
                        scanf("%f", &students[i].fee_balance);
                    }
                    else if (updateChoice == 4) {
                        float payment;
                        printf("Enter payment amount: ");
                        scanf("%f", &payment);
                        if (payment > students[i].fee_balance) {
                            printf("Payment exceeds balance. Setting balance to 0.\n");
                            students[i].fee_balance = 0;
                        } else {
                            students[i].fee_balance -= payment;
                        }
                    }
                    printf("Record updated successfully!\n");
                    break;
                }
            }
            if (!found) {
                printf("No student found with name \"%s\".\n", updateName);
            }
        }
        else if (choice == 6) {
            saveToFile(students, n);
            printf("Exiting program. Goodbye!\n");
        }
        else {
            printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    return 0;
}
