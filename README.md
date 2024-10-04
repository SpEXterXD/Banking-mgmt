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
gcc -o banking_management main.c account.c fileManagement.c