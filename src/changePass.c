#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/update.h"
#include "../include/config.h"
#include "../include/models.h"


void changePassword(Account *acc)
{
    FILE *fp;

    char newPassword[20], oldPassword[20];
    Account temp;
    printf("Enter your old password: ");
    scanf("%s", oldPassword);
    printf("Enter your new password: ");
    scanf("%s", newPassword);

    if(strcmp(oldPassword, acc -> password) != 0)
    {
        printf("Incorrect old password! Please try again.\n");
        return;
    }

    // Update the password in the file
    fp = fopen(FILE_PATH, "rb+");

    if(fp == NULL)
    {
        printf("File is not opened!\n");
        return;
    }

    // Read 
    while(fread(&temp, sizeof(temp), 1, fp))
    {
        if(temp.account_number == acc -> account_number)
        {
            // Modify the password in the temporary struct
            strcpy(temp.password, newPassword);
            fseek(fp, -(long)sizeof(temp), SEEK_CUR); // Move file pointer back to the position of the account
            // Write the update account back to the file
            fwrite(&temp, sizeof(temp), 1, fp);
            printf("Password updated successfully!\n");
            fclose(fp);
            exit(0);
            return;
        }
    }
}