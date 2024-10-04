#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

#include "account.h"

void saveFile(Account* head, const char* filename);
void dbAccount(Account** head, const char* filename);

#endif // FILE_MANAGEMENT_H
