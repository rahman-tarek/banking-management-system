#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/account.h"
#include "../include/models.h"


// Display account information
void accountInfo(Account *acc){
    printf("\n--- Account Information ---\n");
    printf("Account Number: %lld\n", acc->account_number);
    printf("Name: %s\n", acc->name);
    printf("Balance: %.2f $USD \n", acc->balance);
}