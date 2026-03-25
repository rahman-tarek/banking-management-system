#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "models.h"
#include "account.h"
#include "auth.h"
#include "config.h"

int main(){
    int choice;

    while(1){
        printf("\n--- Banking Management System ---\n");
        printf("1. Create Account \n");
        printf("2. Login \n");
        printf("3. Exit \n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                createAccount();
                break;
            case 2:{
                Account acc;
                if(login(&acc)){
                    userMenu(&acc);
                } else {
                    printf("Login failed! Please try again.\n");
                }
                break;
            }
            case 3:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}