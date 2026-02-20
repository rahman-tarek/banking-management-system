// models.h
#ifndef MODELS_H
#define MODELS_H

typedef struct Account {
    char name[50];
    long long account_number;
    float balance;
    char password[20];
} Account;

#endif 