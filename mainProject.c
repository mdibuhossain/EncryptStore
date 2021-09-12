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
    printf("Press 3 for Check User Existence\n");
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
        Sleep(4); // milliseconds
    }
}

// Error message for username and password length
void loadErrorMessage()
{
    system("cls");

    gotoxy(33, 10);
    printf("!=================================!");

    gotoxy(33, 12);
    printf("!......Username and Password......!\n");

    gotoxy(33, 14);
    printf("!............Should be............!\n");

    gotoxy(33, 16);
    printf("!..(max:12 char and min: 4 char)..!\n");

    gotoxy(33, 18);
    printf("!=================================!");

    gotoxy(33, 23);
    system("pause");

    mainScreen();
}

// login screen
void loginScreen()
{
    system("cls");
    loadingScreen();
    system("cls");

    struct person userData, storedData;
    FILE *userRecord;
    userRecord = fopen("person.bin", "rb");

    gotoxy(25, 2);
    printf("-------------------- LOG IN ---------------------\n");

    gotoxy(30, 4);
    printf("username      :");

    gotoxy(46, 4);
    gets(userData.username);

    gotoxy(30, 6);
    printf("password      :");

    gotoxy(46, 6);
    int ch, i = 0;
    while (1)
    {
        ch = getch();
        if (ch == 13)
            break;
        else if (ch == 8)
        {
            i--;
            printf("*");
            continue;
        }
        else
            printf("*");
        userData.passcode[i++] = (char)ch;
    }
    userData.passcode[i] = '\0';

    if (!(strlen(userData.username) >= 4 && strlen(userData.username) <= 12) ||
        !(strlen(userData.passcode) >= 4 && strlen(userData.passcode) <= 12))
    {
        loadErrorMessage();
    }
    else
    {
        int flag = 1;
        while (!feof(userRecord))
        {
            fread(&storedData, sizeof(struct person), 1, userRecord);
            if (!strcmp(storedData.username, userData.username) && !strcmp(storedData.passcode, userData.passcode))
            {
                flag = 0;
                system("cls");
                gotoxy(40, 16);
                printf("Welcome, %s\n", userData.username);
                gotoxy(35, 25);
                system("pause");
                mainScreen();
                break;
            }
        }
        if (flag)
        {
            system("cls");
            gotoxy(35, 16);
            printf("------Invalid account------\n");
            gotoxy(35, 25);
            system("pause");
            mainScreen();
        }
    }

    // File close
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
    userRecord = fopen("person.bin", "ab");

    gotoxy(25, 2);
    printf("--------------------SIGN IN---------------------\n");

    gotoxy(30, 4);
    printf("(max:12 char and min: 4 char)");

    gotoxy(30, 6);
    printf("username      :");

    gotoxy(46, 6);
    gets(userData.username);

    gotoxy(30, 8);
    printf("password      :");

    gotoxy(46, 8);
    gets(userData.passcode);

    if (!(strlen(userData.username) >= 4 && strlen(userData.username) <= 12) ||
        !(strlen(userData.passcode) >= 4 && strlen(userData.passcode) <= 12))
    {
        loadErrorMessage();
    }
    else
    {
        fwrite(&userData, sizeof(struct person), 1, userRecord);
    }

    // File close
    fclose(userRecord);
}

// User Exist
void userExist()
{
    system("cls");

    gotoxy(33, 10);
    printf("|=================================|");

    gotoxy(33, 11);
    printf("|.................................|\n");

    gotoxy(33, 12);
    printf("|...........User Exist............|\n");

    gotoxy(33, 13);
    printf("|.................................|\n");

    gotoxy(33, 14);
    printf("|=================================|");

    gotoxy(33, 18);
    system("pause");

    mainScreen();
}

// User Doesn't Exist
void userDoesntExist()
{
    system("cls");

    gotoxy(33, 10);
    printf("!=================================!");

    gotoxy(33, 11);
    printf("!.................................!\n");

    gotoxy(33, 12);
    printf("!.......User Doesn't Exist........!\n");

    gotoxy(33, 13);
    printf("!.................................!\n");

    gotoxy(33, 14);
    printf("!=================================!");

    gotoxy(33, 18);
    system("pause");

    mainScreen();
}

// Check User Existence
void userExistence()
{
    system("cls");
    loadingScreen();
    system("cls");

    struct person userData, storedData;
    FILE *userRecord;
    userRecord = fopen("person.bin", "rb");

    gotoxy(25, 2);
    printf("--------------Check User Existence---------------\n");

    gotoxy(30, 4);
    printf("username      :");

    gotoxy(46, 4);
    gets(userData.username);

    int flag = 1;
    while (!feof(userRecord))
    {
        fread(&storedData, sizeof(struct person), 1, userRecord);
        if (!strcmp(storedData.username, userData.username))
        {
            flag = 0;
            userExist();
            mainScreen();
            break;
        }
    }
    if (flag)
    {
        userDoesntExist();
        mainScreen();
    }

    // File close
    fclose(userRecord);
}

// Code Run from here
void main()
{
    // CMD window resize
    system("MODE 100, 35"); // MODE Columns, Rows (ASCII)
    system("color F0");

    // Display main menu
    mainScreen();

    char inp;

    while (1)
    {
        printf("> ");

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
            userExistence();
            break;
        case '4':
            system("cls");
            system("color FC");
            exit(0);
            break;
        default:
            printf("Invalid command\n");
        }
    }
}