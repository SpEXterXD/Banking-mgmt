#include "account.h"
#include "fileManagement.h" 

#ifdef _WIN32
    #define CLEAR "cls"
#endif

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"

int main() {
    Account* head = NULL;
    dbAccount(&head, "data/database.txt");

    int choice;
    char username[50];
    char password[50];
    char confirmPassword[50];
    char fullName[100];
    int amount;

    do {
        // Clear the screen before showing the menu
        system(CLEAR);

        printf(CYAN "\n====== Welcome to the Account Management System ======\n" RESET);
        printf("1. Login\n");
        printf("2. Sign Up\n");
        printf("3. Exit\n");
        printf(CYAN "=====================================================\n" RESET);
        printf("Choose an option (1-3): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Login
                system(CLEAR);
                printf(CYAN "\n==== Login ====\n" RESET);
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);

                Account* loggedInAccount = login(head, username, password);
                if (loggedInAccount) {
                    printf(GREEN "\nLogin successful! Welcome, %s.\n" RESET, loggedInAccount->fullName);

                    // Account Management Menu
                    int accountChoice;
                    do {
                        printf(CYAN "\n====== Account Management Menu ======\n" RESET);
                        printf("1. Display Accounts\n");
                        printf("2. Add Funds\n");
                        printf("3. Transfer Amount\n");
                        printf("4. Logout\n");
                        printf(CYAN "=====================================\n" RESET);
                        printf("Choose an option (1-4): ");
                        scanf("%d", &accountChoice);

                        switch (accountChoice) {
                            case 1:
                                system(CLEAR);
                                printf(CYAN "\n=== Displaying Accounts ===\n" RESET);
                                displayAccounts(head);
                                break;
                            case 2:
                                printf("\nEnter amount to add: ");
                                if (scanf("%d", &amount) != 1 || amount <= 0) {
                                    printf(RED "Invalid input! Amount must be a positive number.\n" RESET);
                                    while (getchar() != '\n'); // Clear invalid input
                                } else {
                                    addFunds(head, loggedInAccount->accountNumber, amount);
                                }
                                break;
                            case 3:
                                int toAccount;
                                printf("\nEnter the recipient's account number: ");
                                scanf("%d", &toAccount);
                                printf("Enter amount to transfer: ");
                                if (scanf("%d", &amount) != 1 || amount <= 0) {
                                    printf(RED "Invalid input! Amount must be a positive number.\n" RESET);
                                    while (getchar() != '\n'); // Clear invalid input
                                } else {
                                    transferAmount(head, loggedInAccount->accountNumber, toAccount, amount);
                                }
                                break;
                            case 4:
                                printf(GREEN "\nLogging out...\n" RESET);
                                break;
                            default:
                                printf(RED "Invalid option! Please choose between 1-4.\n" RESET);
                        }
                    } while (accountChoice != 4);
                } else {
                    printf(RED "\nInvalid username or password. Please try again.\n" RESET);
                }
                break;
            
            case 2: // Sign Up
                system(CLEAR);
                printf(CYAN "\n==== Sign Up ====\n" RESET);
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                printf("Confirm password: ");
                scanf("%s", confirmPassword);
                printf("Enter full name: ");
                scanf(" %[^\n]", fullName); // Read full name with spaces

                if (strcmp(password, confirmPassword) != 0) {
                    printf(RED "Passwords do not match. Please try again.\n" RESET);
                } else {
                    addAccount(&head, username, password, fullName);
                    printf(GREEN "\nAccount created successfully! You can now log in.\n" RESET);
                }
                break;

            case 3: // Exit
                freeAccounts(head);
                printf(GREEN "\nThank you for using our banking management system! Exiting...\n" RESET);
                break;

            default:
                printf(RED "Invalid option! Please choose between 1-3.\n" RESET);
                // exit(1);
        }
    } while (choice != 3);

    return 0;
}
