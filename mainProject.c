// C program for writing
// struct to file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Cursor position change
void gotoxy(short x, short y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// a struct to read and write
struct person
{
    char username[20];
    char passcode[20];
};

// Main menu print function
void mainScreen()
{
    system("cls");
    gotoxy(25, 2);
    printf("--------------------WELCOME---------------------\n");
    gotoxy(39, 4);
    printf("Press 1 for LOG IN\n");
    gotoxy(39, 6);
    printf("Press 2 for SING IN\n");
    gotoxy(39, 8);
    printf("Press 3 for Main Menu\n");
    gotoxy(39, 10);
    printf("Press 4 for EXIT\n");
    gotoxy(25, 12);
    printf("------------------------------------------------\n");
}

// Loading Screen
void loadingScreen()
{
    gotoxy(8, 15);
    for (int i = 1; i <= 85; i++)
    {
        printf("-");
        Sleep(5);
    }
}

// login screen
void loginScreen()
{
    system("cls");
    loadingScreen();
    system("cls");
    struct person userData, storedData;
    FILE *userRecord;
    userRecord = fopen("person.dat", "rb");
    gotoxy(25, 2);
    printf("-------------------- LOG IN ---------------------\n");
    gotoxy(30, 4);
    printf("username      :");
    gotoxy(46, 4);
    gets(userData.username);
    gotoxy(30, 6);
    printf("password      :");
    gotoxy(46, 6);
    gets(userData.passcode);
    int flag = 1;
    while (!feof(userRecord))
    {
        fread(&storedData, sizeof(struct person), 1, userRecord);
        if (!strcmp(storedData.username, userData.username) && !strcmp(storedData.passcode, userData.passcode))
        {
            gotoxy(8, 15);
            printf("Valid account");
            flag = 0;
            break;
        }
    }
    if (flag)
    {
        system("cls");
        gotoxy(8, 15);
        printf("Invalid account");
    }
    fclose(userRecord);
}

// sign in screen
void signinScreen()
{
    system("cls");
    loadingScreen();
    system("cls");
    struct person userData;
    FILE *userRecord;
    userRecord = fopen("person.dat", "ab");
    gotoxy(25, 2);
    printf("--------------------SIGN IN---------------------\n");
    gotoxy(30, 4);
    printf("username      :");
    gotoxy(46, 4);
    gets(userData.username);
    gotoxy(30, 6);
    printf("password      :");
    gotoxy(46, 6);
    gets(userData.passcode);
    fwrite(&userData, sizeof(struct person), 1, userRecord);
    fclose(userRecord);
}

// Code Run from here
int main()
{
    // CMD window resize
    system("MODE 100, 35");

    // Display main menu
    mainScreen();

    while (1)
    {
        printf("> ");
        char inp;

        scanf("%c", &inp);
        getchar();
        switch (inp)
        {
        case '1':
            loginScreen();
            break;
        case '2':
            signinScreen();
            break;
        case '3':
            printf("Pressed THREE (3)\n");
            break;
        case '4':
            printf("Pressed FOUR (4)\n");
            break;
        default:
            printf("Invalid command\n");
        }
    }

    return 0;
}
