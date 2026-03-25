#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/update.h"
#include "../include/config.h"


void changePassword(Account *acc)
{
    char newPassword[20], oldPassword[20];
    Account temp;
    printf("Enter your old password: ");
    scanf("%s", oldPassword);
    printf("Enter your new password: ");
    scanf("%s", temp.password);

    if(acc -> password == oldPassword)
    {
        acc->password = temp.password;
    }
}