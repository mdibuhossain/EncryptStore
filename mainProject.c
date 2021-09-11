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

int main()
{
    system("MODE 100, 35");

    // // declare file
    // FILE *outfile;

    // // open file for writing and append
    // outfile = fopen("person.dat", "a");

    // // FILE error handling (if file doesn't exit)
    // if (outfile == NULL)
    // {
    //     fprintf(stderr, "\nError opend file\n");
    //     exit(1);
    // }

    // Main menu
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

    // struct person data[3];
    // for (int i = 0; i < 3; ++i)
    // {
    //     char firstName[20], lastName[20];
    //     data[i].id = i + 1;
    //     gets(data[i].fname);
    //     gets(data[i].lname);
    //     fwrite(&data[i], sizeof(struct person), 1, outfile);
    // }

    // if (fwrite != 0)
    //     printf("contents to file written successfully !\n");
    // else
    //     printf("error writing file !\n");

    // // close file
    // fclose(outfile);

    // FILE *infile;
    // infile = fopen("person.txt", "r");
    // if (infile == NULL)
    // {
    //     fprintf(stderr, "\nError opening file\n");
    //     exit(1);
    // }
    // struct person input;
    // // read file contents till end of file
    // int idd;
    // char firstName[25];
    // char SecondName[25];
    // gets(firstName);
    // gets(SecondName);
    // scanf("%d", &idd);
    // while (fread(&input, sizeof(struct person), 1, infile))
    // {
    //     if (idd == input.id && !strcmp(firstName, input.fname) && !strcmp(SecondName, input.lname))
    //     {
    //         printf("id = %d name = %s %s\n", input.id, input.fname, input.lname);
    //     }
    // }

    // // close file
    // fclose(infile);

    return 0;
}
