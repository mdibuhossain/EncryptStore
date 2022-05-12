#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define DataDirectory "data"
#define dataPath "data\\"
#define personPath "data\\users.bin"
#define MAX_PASSWORD_SIZE 50
#define MAX_USERNAME_SIZE 50
#define MAX_PLATFORM_SIZE 50
#define MAX_EMAIL_SIZE 100
#define MAX_FILENAME_SIZE 50

// Cursor position change
void gotoxy(short x, short y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// a structure for user
typedef struct person
{
    char username[MAX_USERNAME_SIZE];
    char passcode[MAX_PASSWORD_SIZE];
} person;

// a structure for user data
typedef struct socialData
{
    char platform[MAX_PLATFORM_SIZE];
    char email[MAX_EMAIL_SIZE];
    char password[MAX_PASSWORD_SIZE];
} socialData;

// Declare File pointer
FILE *userRecord = NULL;
FILE *userDataFile = NULL;

// Encrypt and Decrypt data -------------------
void subEncrypt(char *st)
{
    int i;
    int len = strlen(st);
    for (i = 0; i < len; i++)
    {
        st[i] = st[i] + 1;
    }
}
void subDecrypt(char *st)
{
    unsigned int len = strlen(st);
    for (int i = 0; i < len; i++)
    {
        st[i] = st[i] - 1;
    }
}
void encryptUserData(person *user)
{
    subEncrypt(user->username);
    subEncrypt(user->passcode);
}
void encryptSocialData(socialData *data)
{
    subEncrypt(data->platform);
    subEncrypt(data->email);
    subEncrypt(data->password);
}
void decryptUserData(person *user)
{
    subDecrypt(user->username);
    subDecrypt(user->passcode);
}
void decryptSocialData(socialData *data)
{
    subDecrypt(data->platform);
    subDecrypt(data->email);
    subDecrypt(data->password);
}
// --------------------------------------------

// Main menu print function
void mainScreen()
{
    system("cls");
    gotoxy(25, 2);
    printf("------------------ WELCOME TO ------------------\n");
    gotoxy(25, 3);
    printf("----------------- EncryptStore -----------------");
    gotoxy(39, 5);
    printf("Press 1 for LOG IN\n");
    gotoxy(39, 7);
    printf("Press 2 for SIGN UP\n");
    gotoxy(39, 9);
    printf("Press 3 for Check User Existence\n");
    gotoxy(39, 11);
    printf("Press 4 for Terminate Program\n");
    gotoxy(25, 13);
    printf("------------------------------------------------\n");
    gotoxy(25, 16);
    printf("Enter your choice ~> ");
}

// Loading Screen
void loadingScreen()
{
    system("cls");
    gotoxy(8, 15);
    for (int i = 1; i <= 42; i++)
    {
        printf("--");
        Sleep(10); // milliseconds
    }
}

// ask to return main menu
void askToReturnMainMenu()
{
    system("echo Press any key to continue");
    getch();
}

// status message
void statusMessage(char st[])
{
    system("cls");
    system("color F9");
    int len = strlen(st);
    gotoxy(35, 8);
    for (int i = 0; i < (14 + len); i++)
        printf("*");
    gotoxy(35, 10);
    for (int i = 0; i < 6; i++)
        printf("\xB2");
    printf(" %s ", st);
    for (int i = 0; i < 6; i++)
        printf("\xB2");
    gotoxy(35, 12);
    for (int i = 0; i < (14 + len); i++)
        printf("*");
    gotoxy(33, 19);
    // Sleep(800);
    askToReturnMainMenu();
    system("color F0");
}

// Error message for username and password length
void loadErrorMessage()
{
    system("cls");

    gotoxy(33, 8);
    printf("!=================================!");

    gotoxy(33, 10);
    printf("!......Username and Password......!\n");

    gotoxy(33, 12);
    printf("!............Should be............!\n");

    gotoxy(33, 14);
    printf("!..(max:12 char and min: 4 char)..!\n");

    gotoxy(33, 16);
    printf("!=================================!");

    gotoxy(33, 21);
    askToReturnMainMenu();
    // system("pause");
}

// Invalid command
void invalidCommand()
{
    system("cls");
    printf("\n\n\t\t\t\t----------- Invalid command -----------\n");
    Sleep(1000);
}

// checking file existance
void isFileExist(FILE *checkFile)
{
    system("cls");

    gotoxy(33, 10);
    printf("!===========================!");

    gotoxy(33, 11);
    printf("!...........................!\n");

    gotoxy(33, 12);
    printf("!......Data Not Found.......!\n");

    gotoxy(33, 13);
    printf("!...........................!\n");

    gotoxy(33, 14);
    printf("!===========================!");

    fclose(checkFile);
    gotoxy(33, 18);
    askToReturnMainMenu();
    // system("pause");
}

// generate path and user data file name
void *intoUserData(char username[])
{
    static char fileName[MAX_FILENAME_SIZE];
    strcpy(fileName, "");
    strcat(fileName, dataPath);
    strcat(fileName, username);
    strcat(fileName, ".bin");
    return fileName;
}

// add new social information
void addNewSocialData(char *username)
{
    userDataFile = fopen(intoUserData(username), "ab");
    socialData userInfo;
    system("cls");
    gotoxy(25, 2);
    printf("--------------------- NewData ----------------------\n");
    gotoxy(35, 4);
    printf("%-12s :\n", "Platform");
    gotoxy(35, 6);
    printf("%-12s :\n", "Email");
    gotoxy(35, 8);
    printf("%-12s :\n", "Password");

    gotoxy(50, 4);
    gets(userInfo.platform);
    gotoxy(50, 6);
    gets(userInfo.email);
    gotoxy(50, 8);
    gets(userInfo.password);

    strlwr(userInfo.platform);
    strlwr(userInfo.email);

    encryptSocialData(&userInfo);
    fwrite(&userInfo, sizeof(socialData), 1, userDataFile);
    fclose(userDataFile);
    statusMessage("Data stored successfully");
}

// Data Table title
void displayDataTitle()
{
    printf("\t   %-25s %-35s %-20s\n", "PLATFORM", "EMAIL", "PASSWORD");
    puts("---------------------------------------------------------------------------------------------------");
}

// filter social data by platform
void filterByPlatform(char *username)
{
    system("cls");
    socialData tmpFilteredSocial;
    char tmpPlatform[MAX_PLATFORM_SIZE];
    gotoxy(25, 2);
    printf("----------------------Filter By Platform-----------------------\n");
    gotoxy(35, 4);
    printf("%-12s :\n", "Platform");
    gotoxy(50, 4);
    gets(tmpPlatform);

    strlwr(tmpPlatform);

    userDataFile = fopen(intoUserData(username), "rb");
    int count = 0, flag = 1;
    if (userDataFile == NULL)
    {
        fclose(userDataFile);
        statusMessage("Data not found");
        return;
    }
    system("cls");
    displayDataTitle();
    while (fread(&tmpFilteredSocial, sizeof(socialData), 1, userDataFile) == 1)
    {
        decryptSocialData(&tmpFilteredSocial);
        if (!strcmp(tmpFilteredSocial.platform, tmpPlatform))
        {
            printf("\t%d. %-25s %-35s %-20s\n", ++count, tmpFilteredSocial.platform, tmpFilteredSocial.email, tmpFilteredSocial.password);
            puts("---------------------------------------------------------------------------------------------------");
            flag = 0;
        }
    }
    if (flag)
    {
        statusMessage("Data not found");
        return;
    }
    fclose(userDataFile);
    askToReturnMainMenu();
}

// Filter Social by Email
void filterByEmail(char *username)
{
    system("cls");
    socialData tmpFilteredData;
    char tmpEmail[MAX_EMAIL_SIZE];
    gotoxy(25, 2);
    printf("----------------------Filter By Email-----------------------\n");
    gotoxy(35, 4);
    printf("%-8s :\n", "Email");
    gotoxy(46, 4);
    gets(tmpEmail);

    strlwr(tmpEmail);

    userDataFile = fopen(intoUserData(username), "rb");
    int count = 0, flag = 1;
    if (userDataFile == NULL)
    {
        fclose(userDataFile);
        statusMessage("Data not found");
        return;
    }
    system("cls");
    displayDataTitle();
    while (fread(&tmpFilteredData, sizeof(socialData), 1, userDataFile) == 1)
    {
        if (feof(userDataFile))
            break;
        decryptSocialData(&tmpFilteredData);
        if (!strcmp(tmpFilteredData.email, tmpEmail))
        {
            printf("\t%d. %-25s %-35s %-20s\n", ++count, tmpFilteredData.platform, tmpFilteredData.email, tmpFilteredData.password);
            puts("---------------------------------------------------------------------------------------------------");
            flag = 0;
        }
    }
    if (flag)
    {
        statusMessage("Data not found");
        return;
    }
    fclose(userDataFile);
    askToReturnMainMenu();
}

// show all social data
int showAllSocialData(char *username)
{
    system("cls");
    socialData tmpAllSocial;
    userDataFile = fopen(intoUserData(username), "rb");
    int count = 0;
    if (userDataFile == NULL)
    {
        fclose(userDataFile);
        statusMessage("Data not found");
        return -1;
    }
    system("cls");
    displayDataTitle();
    while (fread(&tmpAllSocial, sizeof(socialData), 1, userDataFile) == 1)
    {
        decryptSocialData(&tmpAllSocial);
        printf("\t%d. %-25s %-35s %-20s\n", ++count, tmpAllSocial.platform, tmpAllSocial.email, tmpAllSocial.password);
        puts("---------------------------------------------------------------------------------------------------");
    }
    fclose(userDataFile);
    return count;
}

// delete single data
void deleteData(char *username)
{
    int serialNumber;
    int totalData = showAllSocialData(username);
    if (totalData == -1)
        return;
    if (totalData == 0)
    {
        statusMessage("Empty");
        return;
    }
    socialData *filterData;
    filterData = (socialData *)malloc(totalData * sizeof(socialData));

    userDataFile = fopen(intoUserData(username), "rb");
    if (userDataFile == NULL)
    {
        fclose(userDataFile);
        statusMessage("Data not found");
        return;
    }
    int index = 0;
    while (fread(&filterData[index], sizeof(socialData), 1, userDataFile) == 1)
    {
        decryptSocialData(&filterData[index]);
        index++;
    }
    fclose(userDataFile);

    printf("\nPut the serial number => ");
    scanf("%d", &serialNumber);

    if (serialNumber >= 1 && serialNumber <= totalData)
    {
        puts("---------------------------------------------------------------------------------------------------");
        printf("\t%-25s %-35s %-20s\n", filterData[serialNumber - 1].platform, filterData[serialNumber - 1].email, filterData[serialNumber - 1].password);
        puts("---------------------------------------------------------------------------------------------------");
    }
    else
    {
        statusMessage("Not found");
        return;
    }

    printf("Are you sure want to delete (y / n): ");
    char ch;
    fflush(stdin);
    scanf("%c", &ch);

    if (ch == 'Y' || ch == 'y')
    {
        userDataFile = fopen(intoUserData(username), "wb");
        if (userDataFile == NULL)
        {
            fclose(userDataFile);
            statusMessage("Data not found");
            return;
        }
        for (int i = 1; i <= totalData; i++)
        {
            if (i != serialNumber)
            {
                encryptSocialData(&filterData[i - 1]);
                fwrite(&filterData[i - 1], sizeof(socialData), 1, userDataFile);
            }
        }
        fclose(userDataFile);
        statusMessage("Delete successfully");
    }
    else
    {
        statusMessage("Deletation abort");
    }
    // Sleep(1);
}

// Edit data
void editData(char *username)
{
    int serialNumber;
    int totalData = showAllSocialData(username);
    if (totalData == -1)
        return;
    if (totalData == 0)
    {
        statusMessage("Empty");
        return;
    }
    socialData *filterData;
    filterData = (socialData *)malloc(totalData * sizeof(socialData));

    userDataFile = fopen(intoUserData(username), "rb");
    if (userDataFile == NULL)
    {
        fclose(userDataFile);
        statusMessage("Data not found");
        return;
    }
    int index = 0;
    while (fread(&filterData[index], sizeof(socialData), 1, userDataFile) == 1)
    {
        decryptSocialData(&filterData[index]);
        index++;
    }
    fclose(userDataFile);

    printf("\nPut the serial number => ");
    scanf("%d", &serialNumber);
    fflush(stdin);

    if (serialNumber >= 1 && serialNumber <= totalData)
    {
        system("cls");
        puts("===================================================================================================");
        printf("\t%-25s %-35s %-20s\n", filterData[serialNumber - 1].platform, filterData[serialNumber - 1].email, filterData[serialNumber - 1].password);
        puts("===================================================================================================");
        printf("Are you sure want to edit (y / n): ");
        char ch;
        scanf("%c", &ch);
        fflush(stdin);

        if (ch == 'Y' || ch == 'y')
        {
            socialData newData;
            puts("\n\n\t\t\t\tIf you don't want to update any field\n\t\t\t\t\t  Leave that blank.");
            gotoxy(35, 10);
            printf("%-12s :\n", "Platform");
            gotoxy(35, 12);
            printf("%-12s :\n", "Email");
            gotoxy(35, 14);
            printf("%-12s :\n", "Password");

            gotoxy(50, 10);
            gets(newData.platform);
            gotoxy(50, 12);
            gets(newData.email);
            gotoxy(50, 14);
            gets(newData.password);

            if (!strlen(newData.platform))
            {
                strcpy(newData.platform, filterData[serialNumber - 1].platform);
            }
            if (!strlen(newData.email))
            {
                strcpy(newData.email, filterData[serialNumber - 1].email);
            }
            if (!strlen(newData.password))
            {
                strcpy(newData.password, filterData[serialNumber - 1].password);
            }

            char tmp_username[MAX_USERNAME_SIZE + 10] = "";
            char tmp_final_username[MAX_USERNAME_SIZE + 5] = " ";
            char del[5 * MAX_USERNAME_SIZE] = "del ";
            char ren[5 * MAX_USERNAME_SIZE] = "ren ";
            strcpy(tmp_username, username);
            strcat(tmp_username, "_tmp");
            strcat(del, intoUserData(username));
            strcat(ren, intoUserData(tmp_username));
            strcat(tmp_final_username, username);
            strcat(tmp_final_username, ".bin");
            strcat(ren, tmp_final_username);

            userDataFile = fopen(intoUserData(tmp_username), "wb");
            for (int i = 1; i <= totalData; i++)
            {
                if (i == serialNumber)
                {
                    encryptSocialData(&newData);
                    fwrite(&newData, sizeof(socialData), 1, userDataFile);
                }
                else
                {
                    encryptSocialData(&filterData[i - 1]);
                    fwrite(&filterData[i - 1], sizeof(socialData), 1, userDataFile);
                }
            }
            fclose(userDataFile);

            system(del); // delete previous user file
            system(ren); // rename new updated file to current user name
            statusMessage("Successfully updated");
        }
        else
        {
            statusMessage("Abort editing");
        }
    }
    else
    {
        statusMessage("Not found");
        return;
    }

    free(filterData);
}

// delete account
int deleteAccount(char *username)
{
    system("cls");
    char ch;
    printf("Are you sure want to delete your account? (y / n): ");
    scanf("%c", &ch);
    if (ch == 'Y' || ch == 'y')
    {
        userDataFile = fopen(intoUserData(username), "rb");
        char del[5 * MAX_USERNAME_SIZE] = "del ";
        if (userDataFile != NULL)
        {
            fclose(userDataFile);
            strcat(del, intoUserData(username));
            system(del); // delete user social information
            statusMessage("Account delete successfully");
        }
        else
        {
            fclose(userDataFile);
            statusMessage("Account already deleted");
        }

        userRecord = fopen(personPath, "rb");
        int totalUser = 0;
        person *usersTmp;
        usersTmp = (person *)malloc(1 * sizeof(person));
        while (fread(&usersTmp[totalUser], sizeof(person), 1, userRecord) == 1)
        {
            usersTmp = (person *)realloc(usersTmp, (totalUser + 2) * sizeof(person));
            decryptUserData(&usersTmp[totalUser]);
            ++totalUser;
        }
        fclose(userRecord);

        userRecord = fopen(personPath, "wb");
        for (int i = 0; i < totalUser; i++)
        {
            if (strcmp(username, usersTmp[i].username))
            {
                encryptUserData(&usersTmp[i]);
                fwrite(&usersTmp[i], sizeof(person), 1, userRecord);
            }
        }
        free(usersTmp);
        fclose(userRecord);
        return 1;
    }
    else
    {
        statusMessage("Account deletation abort");
        return 0;
    }
}

// menu after user logged in
void loggedInMenu()
{
    system("cls");
    gotoxy(25, 2);
    puts("--------------------- USER ----------------------");
    gotoxy(35, 4);
    puts("Press 1 for ADD NEW DATA");
    gotoxy(35, 6);
    puts("Press 2 for FILTER DATA BY PLATFORM");
    gotoxy(35, 8);
    puts("Press 3 for FILTER DATA BY EMAIL");
    gotoxy(35, 10);
    puts("Press 4 for SHOW ALL DATA");
    gotoxy(35, 12);
    puts("Press 5 for DELETE DATA");
    gotoxy(35, 14);
    puts("Press 6 for EDIT DATA");
    gotoxy(35, 16);
    puts("Press 7 for DELETE THIS ACCOUNT");
    gotoxy(35, 18);
    puts("Press 8 for LOG OUT");
    gotoxy(25, 20);
    puts("-------------------------------------------------");
    gotoxy(25, 22);
    printf("Enter your choice ~> ");
}

// User Logged in
void userLoggedIn(char *username)
{
    int inp;
    int flag = 0;
    while (1)
    {
        loggedInMenu();

        scanf("%d", &inp);
        getchar();
        switch (inp)
        {
        case 1:
            addNewSocialData(username);
            break;
        case 2:
            filterByPlatform(username);
            break;
        case 3:
            filterByEmail(username);
            break;
        case 4:
            showAllSocialData(username);
            askToReturnMainMenu();
            break;
        case 5:
            deleteData(username);
            break;
        case 6:
            editData(username);
            break;
        case 7:
            flag = deleteAccount(username);
            if (flag)
                return;
            break;
        case 8:
            // loadingScreen();
            return;
        default:
            invalidCommand();
            break;
        }
    }
}

// login screen
void loginScreen()
{
    loadingScreen();
    system("cls");

    person userData, storedData;

    // File open for read
    userRecord = fopen(personPath, "rb");

    gotoxy(25, 2);
    printf("-------------------- LOG IN ---------------------\n");

    gotoxy(30, 4);
    printf("username      :");

    gotoxy(30, 6);
    printf("password      :");

    gotoxy(46, 4);
    gets(userData.username);

    // Password input
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

    if (userRecord == NULL)
    {
        fclose(userRecord);
        statusMessage("Data not found");
        return;
    }
    int flag = 1;
    while (fread(&storedData, sizeof(person), 1, userRecord) == 1)
    {
        decryptUserData(&storedData);
        if (!strcmp(storedData.username, userData.username) && !strcmp(storedData.passcode, userData.passcode))
        {
            flag = 0;
            char msg[] = "Welcome, ";
            strcat(msg, userData.username);
            statusMessage(msg);
            userLoggedIn(userData.username);
            return;
        }
    }
    if (flag)
    {
        statusMessage("Invalid username or password");
    }

    // File close
    fclose(userRecord);
}

// sign in screen
void signupScreen()
{
    system("cls");
    loadingScreen();
    system("cls");

    person userData, storedData;

    gotoxy(25, 2);
    printf("--------------------SIGN IN---------------------\n");

    gotoxy(30, 4);
    printf("(max:12 char and min: 4 char)");

    gotoxy(30, 6);
    printf("username      :");

    gotoxy(30, 8);
    printf("password      :");

    gotoxy(46, 6);
    gets(userData.username);

    gotoxy(46, 8);
    gets(userData.passcode);

    if (!(strlen(userData.username) >= 4 && strlen(userData.username) <= 12) ||
        !(strlen(userData.passcode) >= 4 && strlen(userData.passcode) <= 12))
    {
        loadErrorMessage();
    }
    else
    {
        // Create file
        userRecord = fopen(personPath, "ab");
        fclose(userRecord);

        // File open for read
        userRecord = fopen(personPath, "rb");

        // checking user already existance
        while (fread(&storedData, sizeof(person), 1, userRecord) == 1)
        {
            decryptUserData(&storedData);
            if (!strcmp(userData.username, storedData.username))
            {
                fclose(userRecord);
                statusMessage("Username not available");
                return;
            }
        }
        // File close
        fclose(userRecord);

        // File open for append
        userRecord = fopen(personPath, "ab");
        encryptUserData(&userData);
        fwrite(&userData, sizeof(person), 1, userRecord);

        // File close
        fclose(userRecord);

        system("cls");
        gotoxy(33, 13);
        printf("Username and Password are Stored\n");
        gotoxy(33, 18);
        askToReturnMainMenu();
        // system("pause");
    }
}

// Check User Existence
void userExistence()
{
    loadingScreen();
    system("cls");

    person userData, storedData;

    userRecord = fopen(personPath, "rb");

    if (userRecord == NULL)
    {
        fclose(userRecord);
        statusMessage("Data not found");
        return;
    }

    gotoxy(25, 2);
    printf("--------------Check User Existence---------------\n");

    gotoxy(30, 4);
    printf("username      :");

    gotoxy(46, 4);
    gets(userData.username);

    int flag = 1;
    while (fread(&storedData, sizeof(person), 1, userRecord) == 1)
    {
        decryptUserData(&storedData);
        if (!strcmp(storedData.username, userData.username))
        {
            flag = 0;
            statusMessage("User exist");
            break;
        }
    }
    if (flag)
    {
        statusMessage("User dosen't exist");
    }

    // File close
    fclose(userRecord);
}

// Code Run from here
int main()
{
    // CMD window resize
    // system("MODE 100, 100"); // MODE Columns, Rows (ASCII)

    system("title EncryptStore");
    system("color F0");

    // create folder --> "md data"
    char createDir[MAX_FILENAME_SIZE] = "md ";
    strcat(createDir, DataDirectory);
    system(createDir);

    int inp;

    while (1)
    {
        // Display main menu
        mainScreen();

        scanf("%d", &inp);
        getchar();

        switch (inp)
        {
        case 1:
            loginScreen();
            break;
        case 2:
            signupScreen();
            break;
        case 3:
            userExistence();
            break;
        case 4:
            system("cls");
            puts("\n\n\n\tTHANK YOU\n\n\n\n");
            return 0;
        default:
            invalidCommand();
            break;
        }
    }
    return 0;
}