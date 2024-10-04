#include "account.h"

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"

// Function to create a new account
Account* createAccount(const char* username, const char* password, const char* fullName) {
    Account* newAccount = (Account*)malloc(sizeof(Account));
    if (newAccount) {
        newAccount->accountNumber = accountGen();
        strcpy(newAccount->username, username);
        strcpy(newAccount->password, password);
        strcpy(newAccount->fullName, fullName); // Store full name
        newAccount->amount = 0; // Initial amount set to 0
        newAccount->next = NULL;
    }
    return newAccount;
}

// Function to add an account to the linked list
void addAccount(Account** head, const char* username, const char* password, const char* fullName) {
    Account* newAccount = createAccount(username, password, fullName);
    if (!newAccount) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Add to the beginning of the list
    newAccount->next = *head;
    *head = newAccount;

    // Save the accounts to the file after adding
    saveFile(*head, "database.txt");
    printf("Account added successfully! Account Number: %d\n", newAccount->accountNumber);
}

// Function to login
Account* login(Account* head, const char* username, const char* password) {
    for (Account* curr = head; curr != NULL; curr = curr->next) {
        if (strcmp(curr->username, username) == 0 && strcmp(curr->password, password) == 0) {
            return curr; // Return the logged-in account
        }
    }
    return NULL; // No matching account found
}

// Function to add funds to an account
int addFunds(Account* head, int accountNumber, int amount) {
    if (amount <= 0) {
        printf(RED "Error: Amount to add must be a positive value.\n" RESET);
        return -1;
    }

    Account* account = NULL;

    // Find the account
    for (Account* curr = head; curr != NULL; curr = curr->next) {
        if (curr->accountNumber == accountNumber) {
            account = curr;
            break;
        }
    }

    if (account == NULL) {
        printf(RED "Account number %d not found.\n" RESET, accountNumber);
        return -1;
    }

    account->amount += amount;

    // Save the accounts to the file after adding funds
    saveFile(head, "database.txt");
    printf(GREEN "Successfully added %d to Account Number %d. New Balance: %d\n" RESET, amount, accountNumber, account->amount);
    return 0;
}

void displayAccounts(const Account* head) {
    if (head == NULL) {
        printf("No accounts available.\n");
        return;
    }

    printf("\nAccounts List:\n");
    while (head != NULL) {
        printf("Account Number: %d, Username: %s, Full Name: %s, Amount: %d\n", 
               head->accountNumber, head->username, head->fullName, head->amount);
        head = head->next;
    }
}

// Function -> Transfer Amount
int transferAmount(Account* head, int fromAccount, int toAccount, int amount) {
    if (amount <= 0) {
        printf(RED "Error: Transfer amount must be a positive value.\n" RESET);
        return -1;
    }

    Account* from = NULL;
    Account* to = NULL;

    // Find both accounts
    for (Account* curr = head; curr != NULL; curr = curr->next) {
        if (curr->accountNumber == fromAccount) {
            from = curr;
        }
        if (curr->accountNumber == toAccount) {
            to = curr;
        }
    }

    if (from == NULL || to == NULL) {
        printf(RED "Error: One or both account numbers not found.\n" RESET);
        return -1;
    }

    if (from->amount < amount) {
        printf(RED "Error: Insufficient funds in account number %d. Available balance: %d\n" RESET, fromAccount, from->amount);
        return -1;
    }

    // Transfer the amount
    from->amount -= amount;
    to->amount += amount;

    // Save changes to the file
    saveFile(head, "database.txt");
    printf(GREEN "Successfully transferred %d from Account %d to Account %d. New Balance: %d\n" RESET, amount, fromAccount, from->amount);
    return 0;
}

// Function -> Free Memory Allocated for Accounts
void freeAccounts(Account* head) {
    Account* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int accountGen() {
    static int accountNumber = 1001; // Initialization 1000
    return accountNumber++;
}

// Function -> Save Accounts
void saveFile(Account* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }

    while (head != NULL) {
        fprintf(file, "%d,%s,%s,%s,%d\n", head->accountNumber, head->username, head->password, head->fullName, head->amount);
        head = head->next;
    }

    fclose(file);
}

// Function to load accounts from a text file
void dbAccount(Account** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("No existing account file found. Starting with an empty list.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int accountNumber;
        char username[50], password[50], fullName[100]; // Added full name
        int amount;

        sscanf(line, "%d,%49[^,],%49[^,],%99[^,],%d", &accountNumber, username, password, fullName, &amount);
        Account* newAccount = createAccount(username, password, fullName); // Pass full name
        if (newAccount) {
            newAccount->accountNumber = accountNumber; // Use the loaded account number
            newAccount->amount = amount; // Set the loaded amount
            newAccount->next = *head; // Add to the beginning of the list
            *head = newAccount;
        }
    }

    fclose(file);
}
