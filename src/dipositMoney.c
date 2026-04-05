#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/account.h"
#include "../include/models.h"
#include "../include/config.h"


// Function to deposit money
void dipositMoney(Account *acc){
    // Deposit money into account and update balance
    double amount;
    FILE *fp;
    printf("\n--- Deposit Money ---\n");
    printf("Enter amount to deposit: ");
    scanf("%lf", &amount);
    if(amount <= 0){
        printf("Invalid amount! Please try again.\n");
        return;
    }
    acc -> balance += amount;
    // Update the account in the file
    fp = fopen(FILE_PATH, "rb+");
    if(fp == NULL){
        printf("Error opening file!\n");
        fclose(fp);
        return;
    }
    Account temp;
    while(fread(&temp, sizeof(temp), 1, fp)){
        if(temp.account_number == acc -> account_number){
            fseek(fp, -sizeof(temp), SEEK_CUR);
            fwrite(acc, sizeof(*acc), 1, fp);
            printf("Deposit successful! New balance: %.2f $USD\n", acc -> balance);
            fclose(fp);
            return;
        }
    }

}