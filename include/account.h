#ifndef ACCOUNT_H
#define ACCOUNT_H

#define ACCOUNT_FILE "accounts.dat"
#include "models.h"

void createAccount();
int accountExists(long long account_number);
void accountInfo(Account *acc);
void transferMoney(Account *acc);
void dipositMoney(Account *acc);
void userMenu(Account *acc);

#endif // ACCOUNT_H