#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/account.h"


// Function to check if an account number already exists
int accountExists(long long account_number){
    Account acc;
    FILE *fp = fopen("data/accounts.dat", "rb");

    if(fp == NULL){
        printf("Error opening file from account exist checking!\n");
        return 0;
    }

    while(fread(&acc, sizeof(acc), 1, fp)){
        if(acc.account_number == account_number){
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}