#include <iostream>
#include <string>

#define DataDirectory "data"
#define dataPath "data/"
#define personPath "data/person.bin"
#define MAX_PASSWORD_SIZE 50
#define MAX_USERNAME_SIZE 50
#define MAX_PLATFORM_SIZE 50
#define MAX_EMAIL_SIZE 100
#define MAX_FILENAME_SIZE 50

using namespace std;

class Person
{
public:
    string username, passcode;
};

class SocialData
{
public:
    string platform, email, password;
};

void scrClr()
{
    system("cls");
}

void home_menu()
{
    scrClr();
    cout << "--------------WELCOME--------------" << endl;
    cout << "Press 1 for LOG IN" << endl;
    cout << "Press 2 for SIGN UP" << endl;
    cout << "Press 3 for Check USER" << endl;
    cout << "Press 4 for Terminate Program" << endl;
    cout << "-----------------------------------" << endl;
}

void user_exist_notice()
{
    scrClr();
    cout << "----------------------------" << endl
         << "----------------------------" << endl
         << "----------------------------" << endl
         << "----------------------------" << endl
         << "---------User Exist---------" << endl
         << "----------------------------" << endl
         << "----------------------------" << endl
         << "----------------------------" << endl
         << "----------------------------" << endl;
}

int main()
{
    system("EncryptStorage");
    system("color F0");
    user_exist_notice();
    return 0;
}