#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/account.h"
#include "../include/models.h"



// Create a new account
void createAccount(){
    Account acc;
    FILE *fp;

    printf("\n--- Create New Account ---\n");
    printf("Enter Account Number: ");
    scanf("%lld", &acc.account_number);

    // Check for unique account number
    if(accountExists(acc.account_number)){
        printf("Account number already exists. Please try again.\n");
        return;
    }
    printf("Enter Name: ");
    getchar(); // Clear newline character from buffer
    fgets(acc.name, sizeof(acc.name), stdin);
    acc.name[strcspn(acc.name, "\n")] = 0; // Remove newline character

    printf("Enter Password: ");
    scanf("%s", acc.password);

    acc.balance = 0.0;
    fp = fopen("accounts.dat", "ab");
    if(fp == NULL){
        printf("Error opening file!\n");
        return;
    }
    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);
    printf("Account created successfully!\n");
    
}