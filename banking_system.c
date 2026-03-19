#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id;
    char name[50];
    float balance;
} Account;

Account accounts[MAX];
int count = 0;

// Function to create account
void createAccount() {
    if(count >= MAX) {
        printf("Account limit reached!\n");
        return;
    }

    Account acc;
    printf("\nEnter Account ID: ");
    scanf("%d", &acc.id);

    printf("Enter Account Holder Name: ");
    scanf(" %[^\n]", acc.name);

    printf("Enter Initial Deposit: ");
    scanf("%f", &acc.balance);

    accounts[count++] = acc;

    // Save to file
    char filename[50];
    sprintf(filename, "account_%d.txt", acc.id);
    FILE *fp = fopen(filename, "w");
    if(fp == NULL) {
        printf("Error creating file!\n");
        return;
    }
    fprintf(fp, "ID: %d\nName: %s\nBalance: %.2f\n", acc.id, acc.name, acc.balance);
    fclose(fp);

    printf("Account created successfully! File saved as %s\n", filename);
}

// Function to deposit money
void deposit() {
    int id;
    float amount;
    printf("\nEnter Account ID for deposit: ");
    scanf("%d", &id);

    int found = 0;
    for(int i = 0; i < count; i++) {
        if(accounts[i].id == id) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            accounts[i].balance += amount;

            // Update file
            char filename[50];
            sprintf(filename, "account_%d.txt", accounts[i].id);
            FILE *fp = fopen(filename, "w");
            fprintf(fp, "ID: %d\nName: %s\nBalance: %.2f\n", accounts[i].id, accounts[i].name, accounts[i].balance);
            fclose(fp);

            printf("Deposit successful! New Balance: %.2f\n", accounts[i].balance);
            found = 1;
            break;
        }
    }

    if(!found) {
        printf("Account not found!\n");
    }
}

// Function to withdraw money
void withdraw() {
    int id;
    float amount;
    printf("\nEnter Account ID for withdrawal: ");
    scanf("%d", &id);

    int found = 0;
    for(int i = 0; i < count; i++) {
        if(accounts[i].id == id) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            if(amount > accounts[i].balance) {
                printf("Insufficient balance!\n");
            } else {
                accounts[i].balance -= amount;

                // Update file
                char filename[50];
                sprintf(filename, "account_%d.txt", accounts[i].id);
                FILE *fp = fopen(filename, "w");
                fprintf(fp, "ID: %d\nName: %s\nBalance: %.2f\n", accounts[i].id, accounts[i].name, accounts[i].balance);
                fclose(fp);

                printf("Withdrawal successful! New Balance: %.2f\n", accounts[i].balance);
            }
            found = 1;
            break;
        }
    }

    if(!found) {
        printf("Account not found!\n");
    }
}

// Function to view account
void viewAccount() {
    int id;
    printf("\nEnter Account ID to view: ");
    scanf("%d", &id);

    int found = 0;
    for(int i = 0; i < count; i++) {
        if(accounts[i].id == id) {
            printf("\n--- Account Details ---\n");
            printf("ID: %d\nName: %s\nBalance: %.2f\n", accounts[i].id, accounts[i].name, accounts[i].balance);
            found = 1;
            break;
        }
    }

    if(!found) {
        printf("Account not found!\n");
    }
}

int main() {
    int choice;
    do {
        printf("\n===== Mini Banking System =====\n");
        printf("1. Create Account\n2. Deposit\n3. Withdraw\n4. View Account\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: viewAccount(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 5);

    return 0;
}