#include "fileManagement.h"

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"

// Function to save accounts to a file
void saveFile(Account* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf(RED "Error opening file for writing.\n" RESET);
        return;
    }

    while (head != NULL) {
        fprintf(file, "%d,%s,%s,%s,%d\n", head->accountNumber, head->username, head->password, head->fullName, head->amount);
        head = head->next;
    }

    fclose(file);
}

// Function to read accounts from a file
void dbAccount(Account** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("No existing account file found. Starting with an empty list.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int accountNumber;
        char username[50], password[50], fullName[100];
        int amount;

        sscanf(line, "%d,%49[^,],%49[^,],%99[^,],%d", &accountNumber, username, password, fullName, &amount);
        Account* newAccount = createAccount(username, password, fullName);
        if (newAccount) {
            newAccount->accountNumber = accountNumber;
            newAccount->amount = amount;
            newAccount->next = *head;
            *head = newAccount;
        }
    }

    fclose(file);
}
