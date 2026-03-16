#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/account.h"
#include "../include/models.h"

// Function to display user menu after login
void userMenu(Account *acc){
    int choice;

    while(1){
        printf("\n--- User Menu ---\n");
        printf("1. View Profile\n");
        printf("2. Transfer Money\n");
        printf("3. Diposit Money\n");
        printf("4. Update Name\n");
        printf("5. Update Password\n");
        printf("6. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                accountInfo(acc);
                break;
            case 2:
                transferMoney(acc);
                break;
            case 3:
                dipositMoney(acc);
                break;
            case 4:
                // updateName(&acc);
                printf("Update Name functionality not implemented yet.\n");
                break;
            case 5:
                // updatePassword(&acc);
                printf("Update Password functionality not implemented yet.\n");
                break;
            case 6:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}