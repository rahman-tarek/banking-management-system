#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/account.h"
#include "../include/models.h"
#include "../include/auth.h"
#include "../include/config.h"

// Login to an existing account
int login(Account *acc){
    Account user;
    long long account_number;
    char password[20];
    FILE *fp;

    printf("\n--- Login ---\n");
    printf("Enter Account Number: ");
    scanf("%lld", &account_number);
    printf("Enter Password: ");
    scanf("%s", password);

    fp = fopen(FILE_PATH, "rb");
    if(fp == NULL){
        printf("Error opening file from login!\n");
        return 0;
    }
    
    while(fread(&user, sizeof(user), 1, fp)){
        if(user.account_number == account_number && strcmp(user.password, password) == 0){
            *acc = user;
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
   return 0;
}
