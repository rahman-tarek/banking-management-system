#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/update.h"
#include "../include/config.h"
#include "../include/models.h"


void changeName(Account *acc)
{

    FILE *fp;
    char newName[50];
    printf("Enter your new name: ");
    scanf("%s", newName);

    Account temp;

    fp = fopen(FILE_PATH, "rb+");
    if(fp == NULL)
    {
        printf("File is not opened.\n");
        return;
    }

    // Read
    while(fread(&temp, sizeof(temp), 1, fp))
    {
       if(temp.account_number == acc -> account_number)
       {
            // Modify the name in the temporary struct
            strcpy(temp.name, newName);

            fseek(fp, -(long)sizeof(temp), SEEK_CUR); // Move the pointer back to the position of the account
            // Write the update account back to the file
            fwrite(&temp, sizeof(temp), 1, fp) ;
            fclose(fp);
            return;
       }
    }



}