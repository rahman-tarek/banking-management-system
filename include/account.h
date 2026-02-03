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

void createAccount();
int accountExists(long long account_number);
void accountInfo(struct Account acc);
void transferMoney(struct Account *acc);
void dipositMoney(struct Account *acc);

#endif // ACCOUNT_H