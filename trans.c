// Simple Bank Account Management System using File Handling

#include <stdio.h>
#include <stdlib.h>

// structure definition
struct account
{
    int accNo;
    char name[30];
    float balance;
};

// function prototypes
void addAccount(FILE *fp);
void displayAccounts(FILE *fp);
void searchAccount(FILE *fp);
void updateBalance(FILE *fp);
void deleteAccount(FILE *fp);

int main()
{
    FILE *fp;
    int choice;

    // open file
    fp = fopen("bank.dat", "rb+");

    // create file if not present
    if (fp == NULL)
    {
        fp = fopen("bank.dat", "wb+");

        if (fp == NULL)
        {
            printf("File cannot be opened.\n");
            exit(1);
        }
    }

    do
    {
        printf("\n===== BANK MANAGEMENT SYSTEM =====\n");

        printf("1. Add Account\n");
        printf("2. Display Accounts\n");
        printf("3. Search Account\n");
        printf("4. Update Balance\n");
        printf("5. Delete Account\n");
        printf("6. Exit\n");

        printf("Enter your choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addAccount(fp);
                break;

            case 2:
                displayAccounts(fp);
                break;

            case 3:
                searchAccount(fp);
                break;

            case 4:
                updateBalance(fp);
                break;

            case 5:
                deleteAccount(fp);
                break;

            case 6:
                printf("Program Ended.\n");
                break;

            default:
                printf("Invalid Choice.\n");
        }

    } while (choice != 6);

    fclose(fp);

    return 0;
}

// add new account
void addAccount(FILE *fp)
{
    struct account a;

    printf("\nEnter Account Number : ");
    scanf("%d", &a.accNo);

    printf("Enter Name : ");
    scanf("%s", a.name);

    printf("Enter Balance : ");
    scanf("%f", &a.balance);

    fseek(fp, 0, SEEK_END);

    fwrite(&a, sizeof(struct account), 1, fp);

    printf("Account Added Successfully.\n");
}

// display all accounts
void displayAccounts(FILE *fp)
{
    struct account a;

    rewind(fp);

    printf("\n===== ACCOUNT DETAILS =====\n");

    printf("%-10s %-15s %-10s\n",
           "AccNo",
           "Name",
           "Balance");

    while (fread(&a,
                 sizeof(struct account),
                 1,
                 fp))
    {
        if (a.accNo != 0)
        {
            printf("%-10d %-15s %-10.2f\n",
                   a.accNo,
                   a.name,
                   a.balance);
        }
    }
}

// search account
void searchAccount(FILE *fp)
{
    struct account a;

    int num;
    int found = 0;

    printf("\nEnter Account Number to Search : ");
    scanf("%d", &num);

    rewind(fp);

    while (fread(&a,
                 sizeof(struct account),
                 1,
                 fp))
    {
        if (a.accNo == num)
        {
            printf("\nAccount Found\n");

            printf("Account Number : %d\n",
                   a.accNo);

            printf("Name           : %s\n",
                   a.name);

            printf("Balance        : %.2f\n",
                   a.balance);

            found = 1;

            break;
        }
    }

    if (found == 0)
    {
        printf("Account Not Found.\n");
    }
}

// update balance
void updateBalance(FILE *fp)
{
    struct account a;

    int num;
    float amount;

    printf("\nEnter Account Number : ");
    scanf("%d", &num);

    rewind(fp);

    while (fread(&a,
                 sizeof(struct account),
                 1,
                 fp))
    {
        if (a.accNo == num)
        {
            printf("Current Balance : %.2f\n",
                   a.balance);

            printf("Enter Amount to Add : ");
            scanf("%f", &amount);

            a.balance += amount;

            fseek(fp,
                  -sizeof(struct account),
                  SEEK_CUR);

            fwrite(&a,
                   sizeof(struct account),
                   1,
                   fp);

            printf("Balance Updated Successfully.\n");

            return;
        }
    }

    printf("Account Not Found.\n");
}

// delete account
void deleteAccount(FILE *fp)
{
    struct account a;

    struct account blank = {0, "", 0};

    int num;

    printf("\nEnter Account Number to Delete : ");
    scanf("%d", &num);

    rewind(fp);

    while (fread(&a,
                 sizeof(struct account),
                 1,
                 fp))
    {
        if (a.accNo == num)
        {
            fseek(fp,
                  -sizeof(struct account),
                  SEEK_CUR);

            fwrite(&blank,
                   sizeof(struct account),
                   1,
                   fp);

            printf("Account Deleted Successfully.\n");

            return;
        }
    }

    printf("Account Not Found.\n");
}