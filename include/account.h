#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Account {
    int accountNumber;
    char username[50];
    char password[50];
    char fullName[100]; 
    int amount;
    struct Account* next;
} Account;

Account* createAccount(const char* username, const char* password, const char* fullName);
void addAccount(Account** head, const char* username, const char* password, const char* fullName);
void displayAccounts(const Account* head);
int transferAmount(Account* head, int fromAccount, int toAccount, int amount);
void freeAccounts(Account* head);
int accountGen();
void saveFile(Account* head, const char* filename);
void dbAccount(Account** head, const char* filename);
int addFunds(Account* head, int accountNumber, int amount); 
Account* login(Account* head, const char* username, const char* password);

#endif // ACCOUNT_H
