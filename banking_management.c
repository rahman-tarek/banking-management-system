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
void transferMoney(struct Account *acc);
void dipositMoney(struct Account *acc);

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
                transferMoney(&acc);
                break;
            case 3:
                dipositMoney(&acc);
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



// Display account information
void accountInfo(struct Account acc){
    printf("\n--- Account Information ---\n");
    printf("Account Number: %lld\n", acc.account_number);
    printf("Name: %s\n", acc.name);
    printf("Balance: %.2f $USD \n", acc.balance);
}

// Function to deposit money
void dipositMoney(struct Account *acc){
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
    fp = fopen("accounts.dat", "rb+");
    if(fp == NULL){
        printf("Error opening file!\n");
        return;
    }
    struct Account temp;
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

void transferMoney(struct Account *acc){
    // Transfer money and update balances
    // Update balances in which account to be transferred

    FILE *fp;
    double amount;
    long long int targetAcc;
    printf("\n--- Transfer Money ---\n");
    printf("Enter amount to transfer: ");
    scanf("%lf", &amount);
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

    fp = fopen("accounts.dat", "rb+");
    if(fp == NULL){
        printf("Error opening file!\n");
        return;
    }
    
    int found = 0;
    struct Account temp;
    while(fread(&temp, sizeof(temp), 1, fp)){
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