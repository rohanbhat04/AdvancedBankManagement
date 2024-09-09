#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
 
// Declaring all the functions
void checkbalance(char*);
void transfermoney(void);
void display(char*);
void person(char*);
void login(void);
void account(void);
void accountcreated(void);
void afterlogin(void);
void logout(void);
void admin(void);
 
// Declaring gotoxy
// function for setting
// cursor position
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
 
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), c);
}
 
// Creating a structure to store
// data of the user
struct pass {
    char username[50];
    int date, month, year;
    char pnumber[15];
    char adharnum[20];
    char fname[20];
    char lname[20];
    char fathname[20];
    char mothname[20];
    char address[50];
    char typeaccount[20];
    char password[20];
    long int balance;
};
 
// Structure to keep track
// of amount transfer
struct money {
    char usernameto[50];
    char userpersonfrom[50];
    long int money1;
};
 
// struct userpass {
//     char password[50];
// };

void deleteAccount() {
    FILE *fp, *temp;
    struct pass u1;
    char username[50];
    int found = 0;

    fp = fopen("username.txt", "r");
    temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        gotoxy(30, 5);
        printf("Error opening file!");
        return;
    }

    system("cls");

    // Header with border
    gotoxy(30, 3);
    printf("-------------------------------------------------------");
    gotoxy(30, 4);
    printf("|                                                     |");
    gotoxy(30, 5);
    printf("|                DELETE AN ACCOUNT                    |");
    gotoxy(30, 6);
    printf("|                                                     |");
    gotoxy(30, 7);
    printf("-------------------------------------------------------");

    // Prompt for username
    gotoxy(30, 9);
    printf("Enter the username of the account to delete: ");
    scanf("%s", username);

    // Search and delete account
    while (fread(&u1, sizeof(u1), 1, fp)) {
        if (strcmp(u1.username, username) != 0) {
            fwrite(&u1, sizeof(u1), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    // Update files
    remove("username.txt");
    rename("temp.txt", "username.txt");

    // Display success or failure message
    gotoxy(30, 11);
    if (found) {
        printf("-------------------------------------------------------");
        gotoxy(30, 12);
        printf("|            Account deleted successfully!            |");
        gotoxy(30, 13);
        printf("-------------------------------------------------------");
    } else {
        printf("-------------------------------------------------------");
        gotoxy(30, 12);
        printf("|                Account not found!                   |");
        gotoxy(30, 13);
        printf("-------------------------------------------------------");
    }

    // Prompt to return to the Admin Menu
    gotoxy(30, 15);
    printf("Press any key to return to Admin Menu...");
    getch();
    admin();
}


void updateAccount() {
    FILE *fp, *temp;
    struct pass u1;
    char username[50];
    int found = 0;

    fp = fopen("username.txt", "r");
    temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        gotoxy(30, 5);
        printf("Error opening file!");
        return;
    }

    system("cls");

    // Header with border
    gotoxy(30, 3);
    printf("-------------------------------------------------------");
    gotoxy(30, 4);
    printf("|                                                     |");
    gotoxy(30, 5);
    printf("|                UPDATE AN ACCOUNT                    |");
    gotoxy(30, 6);
    printf("|                                                     |");
    gotoxy(30, 7);
    printf("-------------------------------------------------------");

    // Prompt for the username
    gotoxy(30, 9);
    printf("Enter the username of the account to update: ");
    scanf("%s", username);

    // Search for the account and update fields
    while (fread(&u1, sizeof(u1), 1, fp)) {
        if (strcmp(u1.username, username) == 0) {
            found = 1;
            
            gotoxy(30, 11);
            printf("Enter new phone number: ");
            scanf("%s", u1.pnumber);

            gotoxy(30, 12);
            printf("Enter new address     : ");
            scanf("%s", u1.address);
        }
        fwrite(&u1, sizeof(u1), 1, temp);  // Write data to temp file, whether updated or not
    }

    fclose(fp);
    fclose(temp);

    // Update the main file
    remove("username.txt");
    rename("temp.txt", "username.txt");

    // Display success or failure message
    gotoxy(30, 14);
    if (found) {
        printf("-------------------------------------------------------");
        gotoxy(30, 15);
        printf("|            Account updated successfully!            |");
        gotoxy(30, 16);
        printf("-------------------------------------------------------");
    } else {
        printf("-------------------------------------------------------");
        gotoxy(30, 15);
        printf("|                Account not found!                   |");
        gotoxy(30, 16);
        printf("-------------------------------------------------------");
    }

    // Prompt to return to Admin Menu
    gotoxy(30, 18);
    printf("Press any key to return to Admin Menu...");
    getch();
    admin();
}


void viewAccounts() {
    FILE *fp;
    struct pass u1;
    int row = 5; // Starting row for account details

    fp = fopen("username.txt", "r");
    if (fp == NULL) {
        printf("\nError opening file!");
        return;
    }

    system("cls");

    // Create a border for the account list header
    gotoxy(30, 0);
    printf("-------------------------------------------------------");
    gotoxy(30, 1);
    printf("|                                                     |");
    gotoxy(30, 2);
    printf("|              LIST OF ALL ACCOUNTS                   |");
    gotoxy(30, 3);
    printf("|                                                     |");
    gotoxy(30, 4);
    printf("-------------------------------------------------------");

    // Display account details within a box
    while (fread(&u1, sizeof(u1), 1, fp)) {
        gotoxy(30, row);
        printf("| Username      : %-35s |", u1.username);
        gotoxy(30, row + 1);
        printf("| First Name    : %-35s |", u1.fname);
        gotoxy(30, row + 2);
        printf("| Last Name     : %-35s |", u1.lname);
        gotoxy(30, row + 3);
        printf("| Phone Number  : %-35s |", u1.pnumber);
        gotoxy(30, row + 4);
        printf("| Adhar Number  : %-35s |", u1.adharnum);
        gotoxy(30, row + 5);
        printf("| Account Type  : %-35s |", u1.typeaccount);
        gotoxy(30, row + 6);
        printf("-------------------------------------------------------");

        row += 8; // Increase the row index for the next account
    }

    fclose(fp);
    gotoxy(30, row + 2);
    printf("Press any key to return to Admin Menu...");
    getch();
    admin();
}


void admin() {
    int choice;

    system("cls");

    // Print the header with border
    gotoxy(30, 3);
    printf("-------------------------------------------------------");
    gotoxy(30, 4);
    printf("|                                                     |");
    gotoxy(30, 5);
    printf("|                ADMIN CONTROL PANEL                  |");
    gotoxy(30, 6);
    printf("|                                                     |");
    gotoxy(30, 7);
    printf("-------------------------------------------------------");

    // Menu options within a box
    gotoxy(30, 9);
    printf("-------------------------------------------------------");
    gotoxy(30, 10);
    printf("| 1. Create an Account                                |");
    gotoxy(30, 11);
    printf("| 2. Delete an Account                                |");
    gotoxy(30, 12);
    printf("| 3. Update an Account                                |");
    gotoxy(30, 13);
    printf("| 4. View all Accounts                                |");
    gotoxy(30, 14);
    printf("| 5. Logout                                           |");
    gotoxy(30, 15);
    printf("-------------------------------------------------------");

    // Prompt user for input
    gotoxy(30, 17);
    printf("ENTER YOUR CHOICE: ");
    scanf("%d", &choice);

    gotoxy(30, 19);
    printf("                                                   "); // Clear previous message

    switch (choice) {
        case 1:
            system("cls");
            createNewUser();
            break;
        case 2:
            system("cls");
            deleteAccount();
            break;
        case 3:
            system("cls");
            updateAccount();
            break;
        case 4:
            system("cls");
            viewAccounts();
            break;
        case 5:
            gotoxy(30, 20);
            printf("Logging out...");
            exit(0);
            break;
        default:
            gotoxy(30, 19);
            printf("Invalid choice! Please select a valid option.");
            getch();
            admin(); // Reload admin menu
            break;
    }
}

 
// Driver Code
int main() {
    int choice;

    system("cls"); // Clear the screen for a clean interface

    // Create a border for the welcome message
    gotoxy(30, 0);
    printf("-------------------------------------------------------");
    gotoxy(30, 1);
    printf("|                                                     |");
    gotoxy(30, 2);
    printf("|           WELCOME TO BANK ACCOUNT SYSTEM            |");
    gotoxy(30, 3);
    printf("|                                                     |");
    gotoxy(30, 4);
    printf("-------------------------------------------------------");

    // Developer name
    gotoxy(45, 6);
    printf("DEVELOPER: ROHAN BHAT");

    // Displaying menu options within a box
    gotoxy(30, 8);
    printf("-------------------------------------------------------");
    gotoxy(30, 9);
    printf("|                    MAIN MENU                        |");
    gotoxy(30, 10);
    printf("-------------------------------------------------------");

    gotoxy(30, 12);
    printf("| 1. ADMIN LOGIN                                      |");
    gotoxy(30, 13);
    printf("| 2. USER LOGIN                                       |");
    gotoxy(30, 14);
    printf("| 3. EXIT                                             |");
    gotoxy(30, 15);
    printf("-------------------------------------------------------");

    // Prompt the user for their choice
    gotoxy(30, 17);
    printf("ENTER YOUR CHOICE: ");
    scanf("%d", &choice);

    // Clear previous error message before displaying new one
    gotoxy(30, 19);
    printf("                                                   "); // Clears previous text

    switch (choice) {
        case 1:
            system("cls");
            admin(); // Call the admin login
            break;

        case 2:
            login(); // Call the user login function
            break;

        case 3:
            exit(0); // Exit the program
            break;

        default:
            gotoxy(30, 19);
            printf("Invalid choice! Please select a valid option.");
            getch();
            main(); // Restart the menu if input is invalid
            break;
    }
}


 
// Login function to check
// the username of the user
void login(void) {
    system("cls");

    char username[50];
    char password[50];

    int i;
    char ch;
    FILE *fp;
    struct pass u1;

    // Opening file of user data
    fp = fopen("username.txt", "r");

    if (fp == NULL) {
        gotoxy(30, 5);
        printf("Error in opening file!");
        return;
    }

    // Login header with border
    gotoxy(30, 2);
    printf("-------------------------------------------------------");
    gotoxy(30, 3);
    printf("|                                                     |");
    gotoxy(30, 4);
    printf("|                    ACCOUNT LOGIN                    |");
    gotoxy(30, 5);
    printf("|                                                     |");
    gotoxy(30, 6);
    printf("-------------------------------------------------------");

    // Username input prompt
    gotoxy(30, 9);
    printf("USERNAME  : ");
    scanf("%s", username);

    // Password input prompt
    gotoxy(30, 11);
    printf("PASSWORD  : ");
    
    // Input the password with masked characters ('*')
    for (i = 0; i < 50; i++) {
        ch = getch();
        if (ch != 13) {  // Enter key (ASCII 13) to stop
            password[i] = ch;
            printf("*");
        } else {
            password[i] = '\0';  // Null terminate the string
            break;
        }
    }

    // Checking if username exists in the file or not
    while (fread(&u1, sizeof(u1), 1, fp)) {
        if (strcmp(username, u1.username) == 0 && strcmp(password, u1.password) == 0) {
            // If login is successful
            gotoxy(30, 13);
            printf("-------------------------------------------------------");
            gotoxy(30, 14);
            printf("|              Login successful!                      |");
            gotoxy(30, 15);
            printf("-------------------------------------------------------");
            gotoxy(30, 19);
            printf("Press enter to continue...");
            getch();  // Pause to show success message
            
            display(username);  // Show user dashboard or information
            fclose(fp);
            return;
        }
    }

    // If login fails
    gotoxy(30, 13);
    printf("-------------------------------------------------------");
    gotoxy(30, 14);
    printf("|                Invalid username or password!         |");
    gotoxy(30, 15);
    printf("-------------------------------------------------------");
    getch();  // Pause to show error message

    // Closing the file
    fclose(fp);

    // Optionally, you can return to the main menu or reattempt login
}


void createNewUser() {
    char pass[20];
    int passwordlength;
    char ch;
    FILE *fp;
    struct pass u1;
    int i;

    fp = fopen("username.txt", "a");
    if (fp == NULL) {
        gotoxy(30, 5);
        printf("Error opening file!");
        return;
    }

    system("cls");

    // Header with border
    gotoxy(30, 3);
    printf("-------------------------------------------------------");
    gotoxy(30, 4);
    printf("|                                                     |");
    gotoxy(30, 5);
    printf("|                  CREATE NEW USER                    |");
    gotoxy(30, 6);
    printf("|                                                     |");
    gotoxy(30, 7);
    printf("-------------------------------------------------------");

    // User input fields
    gotoxy(30, 9);
    printf("First Name     : ");
    scanf("%s", u1.fname);

    gotoxy(30, 10);
    printf("Last Name      : ");
    scanf("%s", u1.lname);

    gotoxy(30, 11);
    printf("Father's Name  : ");
    scanf("%s", u1.fathname);

    gotoxy(30, 12);
    printf("Mother's Name  : ");
    scanf("%s", u1.mothname);

    gotoxy(30, 13);
    printf("Address        : ");
    scanf("%s", u1.address);

    gotoxy(30, 14);
    printf("Account Type   : ");
    scanf("%s", u1.typeaccount);

    gotoxy(30, 15);
    printf("Date of Birth (DD MM YYYY): ");
    scanf("%d %d %d", &u1.date, &u1.month, &u1.year);

    gotoxy(30, 16);
    printf("Adhar Number   : ");
    scanf("%s", u1.adharnum);

    gotoxy(30, 17);
    printf("Phone Number   : ");
    scanf("%s", u1.pnumber);

    gotoxy(30, 18);
    printf("Initail Balance :");
    scanf("%f", &u1.balance);

    gotoxy(30, 19);
    printf("Username       : ");
    scanf("%s", u1.username);

   

    // Password input with masking
gotoxy(30, 20);
printf("Password       : ");
for (i = 0; i < 20; i++) {
    ch = getch();
    if (ch != 13) {  // Enter key to stop
        u1.password[i] = ch;
        printf("*");
    } else {
        break;
    }
}
u1.password[i] = '\0';  // Ensure password is null-terminated

// Write the new user to the file
fwrite(&u1, sizeof(u1), 1, fp);


   

    fclose(fp);

    // Success message
    gotoxy(30, 21);
    printf("-------------------------------------------------------");
    gotoxy(30, 22);
    printf("|            New user created successfully!           |");
    gotoxy(30, 23);
    printf("-------------------------------------------------------");

    gotoxy(30, 25);
    printf("Press any key to return to Admin Menu...");
    getch();
    admin();
}
 
// Display function to show the
// data of the user on screen
void display(char username1[]) {
    system("cls");
    
    FILE* fp;
    int choice;
    fp = fopen("username.txt", "r");
    struct pass u1;
 
    if (fp == NULL) {
        gotoxy(30, 5);
        printf("Error in opening file!");
        return;
    }

    // Header with border and welcome message
    gotoxy(30, 2);
    printf("-------------------------------------------------------");
    gotoxy(30, 3);
    printf("|                                                     |");
    gotoxy(30, 4);
    printf("|               WELCOME TO YOUR ACCOUNT               |");
    gotoxy(30, 5);
    printf("|                                                     |");
    gotoxy(30, 6);
    printf("-------------------------------------------------------");
    
    // Fetch and display user information
    while (fread(&u1, sizeof(u1), 1, fp)) {
        if (strcmp(username1, u1.username) == 0) {
            gotoxy(30, 7);
            printf("Name: %s %s", u1.fname, u1.lname);
            gotoxy(30, 8);
            printf("Father's Name: %s", u1.fathname);
            gotoxy(30, 9);
            printf("Mother's Name: %s", u1.mothname);
            gotoxy(30, 10);
            printf("Adhar Card Number: %s", u1.adharnum);
            gotoxy(30, 11);
            printf("Mobile Number: %s", u1.pnumber);
            gotoxy(30, 12);
            printf("Date of Birth: %02d-%02d-%d", u1.date, u1.month, u1.year);
            gotoxy(30, 13);
            printf("Address: %s", u1.address);
            gotoxy(30, 14);
            printf("Account Type: %s", u1.typeaccount);
            break;  // Exit loop once the user is found
        }
    }

    fclose(fp);

    // Footer with updated user menu options
    gotoxy(30, 16);
    printf("-------------------------------------------------------");
    gotoxy(30, 17);
    printf("|                                                     |");
    gotoxy(30, 18);
    printf("|                    USER MENU                        |");
    gotoxy(30, 19);
    printf("|                                                     |");
    gotoxy(30, 20);
    printf("-------------------------------------------------------");
    
    // User Menu Options
    gotoxy(30, 22);
    printf("1. Check Balance");
    gotoxy(30, 23);
    printf("2. Deposit Money");
    gotoxy(30, 24);
    printf("3. Transfer Money");
    gotoxy(30, 25);
    printf("4. Withdraw Money");
    gotoxy(30, 26);
    printf("5. Change Password");
    gotoxy(30, 27);
    printf("6. Update Account Details");
    gotoxy(30, 28);
    printf("7. Log out");
    gotoxy(30, 29);
    printf("8. Exit");
    
    gotoxy(30, 31);
    printf("Enter your choice: ");
    scanf("%d", &choice);
 
    switch (choice) {
        case 1:
            checkbalance(username1); // Function to check balance
            break;
 
        case 2:
            depositmoney(); // Function to deposit money
            break;
 
        case 3:
            transfermoney(); // Function to transfer money
            break;

        case 4:
            //withdrawmoney(username1); // Function to withdraw money
            break;

        case 5:
            changepassword(); // Function to change password
            break;

        case 6:
            updateAccount(); // Function to update account details
            break;

        case 7:
            logout();
            login();
            break;
 
        case 8:
            exit(0);
            break;

        default:
            gotoxy(30, 33);
            printf("Invalid choice! Please try again.");
            getch(); // Pause before re-displaying the menu
            display(username1); // Redisplay the menu
    }
}

// Function to check balance
// in users account
void checkbalance(char username2[])
{
    system("cls");
    FILE* fm;
    struct money m1;
    char ch;
    int i = 1, summoney = 0;
 
    // Opening amount file record
    fm = fopen("mon.txt", "r");
 
    int k = 5, l = 10;
    int m = 30, n = 10;
    int u = 60, v = 10;
 
    gotoxy(30, 2);
    printf("==== BALANCE DASHBOARD ====");
    gotoxy(30, 3);
    printf("***************************");
    gotoxy(k, l);
    printf("S no.");
    gotoxy(m, n);
    printf("TRANSACTION ID");
    gotoxy(u, v);
    printf("AMOUNT");
 
    // Reading username to
    // fetch the correct record
    while (fread(&m1, sizeof(m1),
                 1, fm)) {
        if (strcmp(username2,
                   m1.usernameto)
            == 0) {
            gotoxy(k, ++l);
            printf("%d", i);
            i++;
            gotoxy(m, ++n);
            printf("%s", m1.userpersonfrom);
 
            gotoxy(u, ++v);
            printf("%d", m1.money1);
            // Adding and
            // finding total money
            summoney = summoney + m1.money1;
        }
    }
 
    gotoxy(80, 10);
    printf("TOTAL AMOUNT");
 
    gotoxy(80, 12);
    printf("%d", summoney);
 
    getch();
 
    // Closing file after
    // reading it
    fclose(fm);
    display(username2);
}

//Function to deposit money
//in user's account
void depositmoney(void)
{
    int i, j;
    FILE *fm, *fp;
    struct pass u1;
    struct money m1;
    char usernamet[20];
    system("cls");

    // Opening file in read mode to read user's username
    fp = fopen("username.txt", "r");

    // Creating another file to write the deposit transaction
    fm = fopen("mon.txt", "a");

    gotoxy(33, 4);
    printf("---- DEPOSIT MONEY ----");
    gotoxy(33, 5);
    printf("========================");

    gotoxy(33, 11);
    printf("YOUR USERNAME: ");
    scanf("%s", &usernamet);

    // Checking if username exists in the file
    int user_found = 0;
    while (fread(&u1, sizeof(u1), 1, fp)) 
    {
        if (strcmp(usernamet, u1.username) == 0) 
        {
            strcpy(m1.usernameto, u1.username);
            strcpy(m1.userpersonfrom, "DEPOSIT");
            user_found = 1;
            break;
        }
    }

    if (!user_found)
    {
        gotoxy(33, 16);
        printf("USERNAME NOT FOUND!");
        fclose(fp);
        fclose(fm);
        getch();
        return;
    }

    gotoxy(33, 13);
    printf("ENTER THE AMOUNT TO BE DEPOSITED: ");
    scanf("%d", &m1.money1);

    // Writing to the file
    fwrite(&m1, sizeof(m1), 1, fm);

    gotoxy(0, 26);
    printf("--------------------------------------------------"
           "--------------------------------------------");

    gotoxy(0, 28);
    printf("--------------------------------------------------"
           "--------------------------------------------");

    gotoxy(0, 29);
    printf("Depositing amount, Please wait..");

    gotoxy(10, 27);
    for (i = 0; i < 70; i++) {
        for (j = 0; j < 1200000; j++) {
            j++;
            j--;
        }
        printf("*");
    }

    gotoxy(33, 40);
    printf("AMOUNT SUCCESSFULLY DEPOSITED....");
    getch();

    // Close the files
    fclose(fp);
    fclose(fm);

    // Function to return to the home screen
    display(usernamet);
}



 
// Function to transfer
// money from one user to
// another
void transfermoney(void)
{
    int i, j;
    FILE *fp, *ftemp, *fm;
    struct pass u1, sender, receiver;
    struct money m1;
    char usernamet[50];
    char usernamep[50];
    long int amount;
    int found_sender = 0, found_receiver = 0;

    system("cls");

    // Opening files
    fp = fopen("username.txt", "r");
    if (fp == NULL) {
        printf("Error opening user file!\n");
        return;
    }

    ftemp = fopen("temp.txt", "w");
    if (ftemp == NULL) {
        printf("Error creating temp file!\n");
        fclose(fp);
        return;
    }

    fm = fopen("mon.txt", "a");
    if (fm == NULL) {
        printf("Error opening transaction file!\n");
        fclose(fp);
        fclose(ftemp);
        return;
    }

    gotoxy(33, 4);
    printf("---- TRANSFER MONEY ----");
    gotoxy(33, 5);
    printf("========================");

    gotoxy(33, 11);
    printf("FROM (your username).. ");
    scanf("%s", usernamet);

    gotoxy(33, 13);
    printf("TO (username of person).. ");
    scanf("%s", usernamep);

    // Read user information and find sender and receiver
    while (fread(&u1, sizeof(u1), 1, fp)) {
        if (strcmp(usernamet, u1.username) == 0) {
            found_sender = 1;
            sender = u1; // Store sender's information
        }
        if (strcmp(usernamep, u1.username) == 0) {
            found_receiver = 1;
            receiver = u1; // Store receiver's information
        }
        fwrite(&u1, sizeof(u1), 1, ftemp); // Write all users to temp file for later updates
    }

    // If sender or receiver not found, show error
    if (!found_sender) {
        gotoxy(33, 16);
        printf("SENDER'S USERNAME NOT FOUND!");
        fclose(fp);
        fclose(ftemp);
        fclose(fm);
        remove("temp.txt");
        getch();
        return;
    }

    if (!found_receiver) {
        gotoxy(33, 16);
        printf("RECEIVER'S USERNAME NOT FOUND!");
        fclose(fp);
        fclose(ftemp);
        fclose(fm);
        remove("temp.txt");
        getch();
        return;
    }

    gotoxy(33, 16);
    printf("ENTER THE AMOUNT TO BE TRANSFERRED: ");
    scanf("%ld", &amount);

    // Check if the sender has enough balance
    if (sender.balance < amount) {
        gotoxy(33, 18);
        printf("INSUFFICIENT FUNDS! YOUR BALANCE IS: %ld", sender.balance);
        fclose(fp);
        fclose(ftemp);
        fclose(fm);
        remove("temp.txt");
        getch();
        return;
    }

    // Deduct amount from sender's balance and add to receiver's balance
    sender.balance -= amount;
    receiver.balance += amount;

    // Log the transfer transaction
    strcpy(m1.usernameto, receiver.username);
    strcpy(m1.userpersonfrom, sender.username);
    m1.money1 = amount;
    fwrite(&m1, sizeof(m1), 1, fm); // Write transaction to mon.txt

    // Rewind temp file and update user balances
    rewind(ftemp); 
    while (fread(&u1, sizeof(u1), 1, ftemp)) {
        if (strcmp(u1.username, sender.username) == 0) {
            fwrite(&sender, sizeof(sender), 1, ftemp); // Write updated sender
        } else if (strcmp(u1.username, receiver.username) == 0) {
            fwrite(&receiver, sizeof(receiver), 1, ftemp); // Write updated receiver
        } else {
            fwrite(&u1, sizeof(u1), 1, ftemp); // Write other users unchanged
        }
    }

    gotoxy(33, 18);
    printf("AMOUNT DEDUCTED. NEW BALANCE: %ld", sender.balance);

    gotoxy(33, 22);
    printf("AMOUNT SUCCESSFULLY TRANSFERRED....");

    gotoxy(0, 26);
    printf("--------------------------------------------------"
           "--------------------------------------------");

    gotoxy(0, 28);
    printf("--------------------------------------------------"
           "--------------------------------------------");

    gotoxy(0, 29);
    printf("Transferring amount, Please wait..");

    gotoxy(10, 27);
    for (i = 0; i < 70; i++) {
        for (j = 0; j < 1200000; j++) {
            j++;
            j--;
        }
        printf("*");
    }

    // Close all files
    fclose(fp);
    fclose(ftemp);
    fclose(fm);

    // Rename temp file to username.txt
    remove("username.txt");
    rename("temp.txt", "username.txt");

    getch();

    // Function to return to the home screen
    display(usernamet);
}

 //fucntion to change the password
void changepassword(void)
{
    FILE *fp, *ftemp;
    struct pass u1;
    char username[50];
    char old_password[20];
    char new_password[20];
    int found = 0;

    system("cls"); // Clear the screen for a clean interface

    // Create a border for the change password message
    gotoxy(30, 0);
    printf("-------------------------------------------------------");
    gotoxy(30, 1);
    printf("|                                                     |");
    gotoxy(30, 2);
    printf("|                CHANGE PASSWORD                     |");
    gotoxy(30, 3);
    printf("|                                                     |");
    gotoxy(30, 4);
    printf("-------------------------------------------------------");

    // Open user file for reading , writing new password and temporary file for writing
    fp = fopen("username.txt", "r+");
    if (fp == NULL) {
        gotoxy(30, 8);
        printf("Error opening user file!");
        getch();
        return;
    }

    ftemp = fopen("temp.txt", "w");
    if (ftemp == NULL) {
        gotoxy(30, 8);
        printf("Error creating temp file!");
        fclose(fp);
        getch();
        return;
    }

    // Prompt the user for username, old password, and new password
    gotoxy(30, 10);
    printf("Enter your username: ");
    scanf("%s", username);

    gotoxy(30, 12);
    printf("Enter old password: ");
    // Read the old password with masking
    int i;
    for (i = 0; i < 20; i++) {
        char ch = getch();
        if (ch != 13) {  // Enter key to stop
            old_password[i] = ch;
            printf("*");
        } else {
            break;
        }
    }
    old_password[i] = '\0'; // Null-terminate the old password

    gotoxy(30, 14);
    printf("Enter new password: ");
    // Read the new password with masking
    for (i = 0; i < 20; i++) {
        char ch = getch();
        if (ch != 13) {  // Enter key to stop
            new_password[i] = ch;
            printf("*");
        } else {
            break;
        }
    }
    new_password[i] = '\0'; // Null-terminate the new password

    // Read the user file and update the password
    while (fread(&u1, sizeof(u1), 1, fp)) {
        if (strcmp(username, u1.username) == 0 && strcmp(old_password, u1.password) == 0) {
            // User found and old password matches, update the password
            strcpy(u1.password, new_password);
            found = 1;
        }
        // Write user data to temporary file
        fwrite(&u1, sizeof(u1), 1, ftemp);
    }

    if (found) {
        gotoxy(30, 16);
        printf("Password updated successfully!");
    } else {
        gotoxy(30, 16);
        printf("Username or old password is incorrect!");
    }

    gotoxy(30, 18);
    printf("Updating password, please wait...");

    // Simulate processing delay
    for (int i = 0; i < 70; i++) {
        for (int j = 0; j < 1200000; j++) {
            j++;
            j--;
        }
        printf("*");
    }

    // Close the files
    fclose(fp);
    fclose(ftemp);

    // Replace the original file with the updated one
    remove("username.txt");
    rename("temp.txt", "username.txt");

    gotoxy(30, 22);
    printf("Operation completed.");
    getch();

    // Log out the user
    logout();
    login();
}


 
// Logout function to bring
// user to the login screen
void logout(void)
{
    int i, j;
    system("cls");
    printf("please wait, logging out");
 
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 25000000; j++) {
            i++;
            i--;
        }
        printf(".");
    }
 
    gotoxy(30, 10);
    printf("Sign out successfully..\n");
 
    gotoxy(0, 20);
    printf("press any key to continue..");
 
    getch();
}