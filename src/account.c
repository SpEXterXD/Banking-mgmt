#include "account.h"
#include "fileManagement.h" 

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"

Account* createAccount(const char* username, const char* password, const char* fullName) {
    Account* newAccount = (Account*)malloc(sizeof(Account));
    if (newAccount) {
        newAccount->accountNumber = accountGen();
        strcpy(newAccount->username, username);
        strcpy(newAccount->password, password);
        strcpy(newAccount->fullName, fullName);
        newAccount->amount = 0;
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

    saveFile(*head, "data/database.txt");
    printf("Account added successfully! Account Number: %d\n", newAccount->accountNumber);
}


Account* login(Account* head, const char* username, const char* password) {
    for (Account* curr = head; curr != NULL; curr = curr->next) {
        if (strcmp(curr->username, username) == 0 && strcmp(curr->password, password) == 0) {
            return curr; 
        }
    }
    return NULL;
}

int addFunds(Account* head, int accountNumber, int amount) {
    if (amount <= 0) {
        printf(RED "Error: Amount to add must be a positive value.\n" RESET);
        return -1;
    }

    Account* account = NULL;

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

    saveFile(head, "data/database.txt");
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

int transferAmount(Account* head, int fromAccount, int toAccount, int amount) {
    if (amount <= 0) {
        printf(RED "Error: Transfer amount must be a positive value.\n" RESET);
        return -1;
    }

    Account* from = NULL;
    Account* to = NULL;

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

    from->amount -= amount;
    to->amount += amount;

    // Save the accounts to the file after transferring
    saveFile(head, "data/database.txt");
    printf(GREEN "Successfully transferred %d from Account Number %d to Account Number %d.\n" RESET, amount, fromAccount, toAccount);
    return 0;
}

// Function to generate a unique account number
int accountGen() {
    static int lastAccountNumber = 1000; // Starting account number
    return lastAccountNumber++;
}

// Function to free all accounts
void freeAccounts(Account* head) {
    Account* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
