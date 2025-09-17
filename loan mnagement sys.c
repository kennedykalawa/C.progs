#include <stdio.h>
#include <string.h>

struct Loan {
    char name[50];
    int age;
    float loan_amount;
    float interest_rate;
    int duration_months;
    float balance; // total balance including interest
};

#define FILENAME "loans.txt"

// Save loans to file
void saveToFile(struct Loan loans[], int n) {
    FILE *file = fopen(FILENAME, "w");
    if (!file) {
        printf("Error saving file.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        fprintf(file, "%s,%d,%.2f,%.2f,%d,%.2f\n",
                loans[i].name,
                loans[i].age,
                loans[i].loan_amount,
                loans[i].interest_rate,
                loans[i].duration_months,
                loans[i].balance);
    }
    fclose(file);
    printf("Data saved successfully.\n");
}

// Load loans from file
int loadFromFile(struct Loan loans[]) {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("No previous data found. Starting fresh.\n");
        return 0;
    }
    int count = 0;
    while (fscanf(file, " %49[^,],%d,%f,%f,%d,%f\n",
                  loans[count].name,
                  &loans[count].age,
                  &loans[count].loan_amount,
                  &loans[count].interest_rate,
                  &loans[count].duration_months,
                  &loans[count].balance) == 6) {
        count++;
    }
    fclose(file);
    printf("Loaded %d loan records.\n", count);
    return count;
}

// Calculate balance with interest
float calculateBalance(float loan, float rate, int months) {
    float interest = loan * (rate / 100.0) * (months / 12.0);
    return loan + interest;
}

int main() {
    struct Loan loans[100];
    int n = loadFromFile(loans);
    int choice;

    do {
        printf("\n==== Loan Management Menu ====\n");
        printf("1. Add new loan applicant\n");
        printf("2. View all loans\n");
        printf("3. Search loan by name\n");
        printf("4. Make a repayment\n");
        printf("5. Show loans with pending balance\n");
        printf("6. Save and Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int newCount;
            printf("How many applicants to add? ");
            scanf("%d", &newCount);

            for (int i = n; i < n + newCount; i++) {
                printf("\nEnter details for applicant %d:\n", i + 1);

                printf("Name: ");
                scanf(" %[^\n]", loans[i].name);

                printf("Age: ");
                scanf("%d", &loans[i].age);

                printf("Loan Amount: ");
                scanf("%f", &loans[i].loan_amount);

                printf("Interest Rate (%%): ");
                scanf("%f", &loans[i].interest_rate);

                printf("Duration (months): ");
                scanf("%d", &loans[i].duration_months);

                loans[i].balance = calculateBalance(loans[i].loan_amount,
                                                    loans[i].interest_rate,
                                                    loans[i].duration_months);
                printf("Loan added! Total balance (with interest): %.2f\n", loans[i].balance);
            }
            n += newCount;
        }
        else if (choice == 2) {
            printf("\n--- Loan Records ---\n");
            for (int i = 0; i < n; i++) {
                printf("\nApplicant %d:\n", i + 1);
                printf("Name       : %s\n", loans[i].name);
                printf("Age        : %d\n", loans[i].age);
                printf("Loan Amt   : %.2f\n", loans[i].loan_amount);
                printf("Rate       : %.2f%%\n", loans[i].interest_rate);
                printf("Duration   : %d months\n", loans[i].duration_months);
                printf("Balance    : %.2f\n", loans[i].balance);
            }
        }
        else if (choice == 3) {
            char searchName[50];
            int found = 0;
            printf("Enter name to search: ");
            scanf(" %[^\n]", searchName);

            for (int i = 0; i < n; i++) {
                if (strcmp(loans[i].name, searchName) == 0) {
                    printf("\nLoan Found:\n");
                    printf("Name     : %s\n", loans[i].name);
                    printf("Age      : %d\n", loans[i].age);
                    printf("Balance  : %.2f\n", loans[i].balance);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("No loan found for \"%s\".\n", searchName);
            }
        }
        else if (choice == 4) {
            char payName[50];
            int found = 0;
            printf("Enter applicant name for repayment: ");
            scanf(" %[^\n]", payName);

            for (int i = 0; i < n; i++) {
                if (strcmp(loans[i].name, payName) == 0) {
                    float payment;
                    printf("Enter repayment amount: ");
                    scanf("%f", &payment);

                    if (payment > loans[i].balance) {
                        printf("Payment exceeds balance. Setting balance to 0.\n");
                        loans[i].balance = 0;
                    } else {
                        loans[i].balance -= payment;
                        printf("Payment recorded. Remaining balance: %.2f\n", loans[i].balance);
                    }
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("No loan found for \"%s\".\n", payName);
            }
        }
        else if (choice == 5) {
            printf("\n--- Pending Loan Balances ---\n");
            int found = 0;
            for (int i = 0; i < n; i++) {
                if (loans[i].balance > 0) {
                    printf("%s owes: %.2f\n", loans[i].name, loans[i].balance);
                    found = 1;
                }
            }
            if (!found) {
                printf("All loans cleared!\n");
            }
        }
        else if (choice == 6) {
            saveToFile(loans, n);
            printf("Exiting... Goodbye!\n");
        }
        else {
            printf("Invalid choice. Try again.\n");
        }

    } while (choice != 6);

    return 0;
}
