#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/account.h"
#include "../include/models.h"
#include "../include/config.h"


void transferMoney(Account *acc){
    // Transfer money and update balances
    // Update balances in which account to be transferred

    FILE *fp;
    float amount;
    long long targetAcc;
    printf("\n--- Transfer Money ---\n");
    printf("Enter amount to transfer: ");
    scanf("%f", &amount);
    printf("Enter account number: ");
    scanf("%lld", &targetAcc);
    if(amount <= 0){
        printf("Invalid amount! Please try again.\n");
        return;
    }
    if(amount > acc -> balance){
        printf("Insufficient balance!\n");
        return;
    };

    fp = fopen(FILE_PATH, "rb+");
    if(fp == NULL){
        printf("Error opening file!\n");
        return;
    }
    
    int found = 0;
    Account temp;
    while(fread(&temp, sizeof(temp), 1, fp)){
        printf("%lld %lld\n", temp.account_number, targetAcc);
        if(temp.account_number == targetAcc){ // If targeted account found
            temp.balance += amount; // Update balance into temporary struct
            fseek(fp, -sizeof(temp), SEEK_CUR);
            fwrite(&temp, sizeof(temp), 1, fp); // And then update the main file according to temproray struct
            found = 1;
            break;
        }
    }
    if(!found){
        printf("Target account not found!\n");
        fclose(fp);
        return;
    }

    rewind(fp); // Reset file pointer to the beginning

    // Update sender's account balance
    while(fread(&temp, sizeof(temp), 1, fp)){
        if(temp.account_number == acc -> account_number){ // If sender's account found
            temp.balance -= amount; // Deduct the amount
            fseek(fp, -sizeof(temp), SEEK_CUR); // Move file pointer back
            fwrite(&temp, sizeof(temp), 1, fp); // Update the file
            acc -> balance = temp.balance; // Update the balance in the current session
            printf("Transfer successful! New balance: %.2f $USD\n", acc -> balance);
            fclose(fp);
            return;
        }
    }
}