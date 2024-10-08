# Banking Management System

A simple console-based banking management system that allows users to create accounts, log in, manage funds, and perform transactions such as adding funds and transferring amounts between accounts. The system supports user authentication and data persistence through file storage.

## Features

- User Registration (Sign Up)
- User Login
- Display Account Details
- Add Funds to Account
- Transfer Amount Between Accounts
- View All Accounts
- Persistent data storage in a text file

## Requirements

- C Compiler (e.g., GCC)
- Standard C Libraries

## Compilation

To compile the program, navigate to the `src` directory and run the following command:

```bash
gcc -o banking_management.exe src\main.c src\account.c src\fileManagement.c -Iinclude -Wall
```

## Possible Future Updates
  - Input Validation -

    > - **Use More Detailed Error Messages:** Implement rules for username and password creation (e.g., minimum length, complexity requirements).
    > - **Sanitize Inputs:** Prevent buffer overflows and ensure inputs do not contain harmful characters.

  - Secure Password Storage -

    > - **Hash Passwords:** Instead of storing passwords in plain text, use a hashing algorithm (like bcrypt or Argon2) to secure passwords.
    > - **Salt Passwords:** Use a salt along with hashing to make it more secure against rainbow table attacks.

  - Account Features -

    > - **Transaction History:** Allow users to view their transaction history (deposits, withdrawals, transfers).
    > - **Account Types:** Implement different account types (savings, checking) with varying features and interest rates.

