#ifndef ACCOUNT_H
#define ACCOUNT_H

#define ACCOUNT_FILE "accounts.dat"

typedef struct Account
{
    char name[50];
    long long account_number;
    float balance;
    char password[20];
} Account;

void createAccount(Account *acc);
int accountExists(long long account_number);
void accountInfo(Account *acc);
void transferMoney(Account *acc);
void dipositMoney(Account *acc);

#endif // ACCOUNT_H