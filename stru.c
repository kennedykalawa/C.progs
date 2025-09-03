#include <stdio.h>

struct Student {
    char name[50];
    int age;
    float fee_balance;
};

int main() {
    int i;
    struct Student students[6];

    // Input data for each student
    for (i = 0; i < 6; i++) {
        printf("Enter details for student %d:\n", i + 1);
        printf("Name: ");
        scanf(" %[^\n]", students[i].name);
        printf("Age: ");
        scanf("%d", &students[i].age);
        printf("Fee Balance: ");
        scanf("%f", &students[i].fee_balance);
    }

    // Output data for each student
    printf("\nStudent Records:\n");
    for (i = 0; i < 6; i++) {
        printf("Student %d:\n", i + 1);
        printf("Name: %s\n", students[i].name);
        printf("Age: %d\n", students[i].age);
        printf("Fee Balance: $%.2f\n", students[i].fee_balance);
    }

    return 0;
}