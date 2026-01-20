#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    char name[50];
    long long account_number;
    float balance;
    char password[20];
};

void createAccount();
int accountExists(long long account_number);
int login(struct Account *acc);
void accountInfo(struct Account acc);
void userMenu(struct Account acc);

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
                struct Account acc;
                if(login(&acc)){
                    userMenu(acc);
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
// Function to check if an account number already exists
int accountExists(long long account_number){
    struct Account acc;
    FILE *fp = fopen("accounts.dat", "rb");

    if(fp == NULL){
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

// Create a new account
void createAccount(){
    struct Account acc;
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

// Login to an existing account
int login(struct Account *acc){
    struct Account user;
    long long account_number;
    char password[20];
    FILE *fp;

    printf("\n--- Login ---\n");
    printf("Enter Account Number: ");
    scanf("%lld", &account_number);
    printf("Enter Password: ");
    scanf("%s", password);

    fp = fopen("accounts.dat", "rb");
    if(fp == NULL){
        printf("Error opening file!\n");
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


// Function to display user menu after login
void userMenu(struct Account acc){
    int choice;

    while(1){
        printf("\n--- User Menu ---\n");
        printf("1. View Profile\n");
        printf("2. Update Name\n");
        printf("3. Update Password\n");
        printf("4. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                accountInfo(acc);
                break;
            case 2:
                // updateName(&acc);
                printf("Update Name functionality not implemented yet.\n");
                break;
            case 3:
                // updatePassword(&acc);
                printf("Update Password functionality not implemented yet.\n");
                break;
            case 4:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}



// Display account information
void accountInfo(struct Account acc){
    printf("\n--- Account Information ---\n");
    printf("Account Number: %lld\n", acc.account_number);
    printf("Name: %s\n", acc.name);
    printf("Balance: %.2f\n", acc.balance);
}
// Function to update profile info
// void updateProfile(struct Account *acc){
//     struct Account updatedAcc;
//     FILE *fp = fopen("accounts.dat", "rb+");

//     if(fp == NULL){
//         printf("Error opening file!\n");
//         return;
//     }

//     printf("\n--- Update Profile ---\n");


// }