#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "myStringLib.h"

using namespace std;

enum enMenuScreen {clientList = 1, AddClient = 2, DeletClient = 3, updatClient = 4, findClient = 5, transacions = 6, mangeUsers = 7, Exit = 8};
enum enTransactions {Deposit = 1, Withdraw = 2, TotalBalance = 3, Main = 4};
enum enMangeUsers {usersList = 1, AddUser = 2, deleteUser = 3, updateUser = 4, findUser = 5, goBack = 6};
enum enMainMenuPermission {All = -1, PClientList = 1, PAddClient = 2, PDeleteClient = 4, PUpdateClient = 8, PFindClient = 16, PTransactions = 32, PmangeUsers = 64};

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";

struct sClient {
    string accountNumber;
    string pincode;
    string name;
    string phone;
    int accountBalance;
    bool markForDelet = false;
};
struct sUser {
    string userName;
    string password;
    int permission;
    bool markForDelet = false;
};


sUser CurrentUser;



//---------------------------------------- Functions to handle Clients ----------------------------------------------

vector<sClient> loadDataClientFromFile(string fileName);


sClient readClientInfo(string message)
{
    cout << message << endl;


    sClient client;
    //client.accountNumber = readString("Enter Account Number: ");
    client.pincode = readString( "Enter pincode: ");
    client.name = readString("Enter Name: ");
    client.phone = readString("Enter phone: ");
    cout << "Enter Account Balance: "; cin >> client.accountBalance; cout << endl;



    return client;
}

string convertRecordToData (sClient client, string separetor)
{
    string s = "";

    s += to_string(client.accountBalance) + separetor;
    s += client.accountNumber + separetor;
    s += client.name + separetor;
    s += client.phone + separetor;
    s += client.pincode;

    return s;
}
sClient convertDataToRecord(string data, string delimiter)
{
    vector<string> vString = splitString(data, delimiter);

    sClient client;
    client.accountBalance = stoi(vString[0]);
    client.accountNumber = vString[1];
    client.name = vString[2];
    client.phone = vString[3];
    client.pincode = vString[4];

    return client;
}
void printClientData(sClient client)
{
    cout << "\n\n\n\t\t    **The Client Info** \n" << endl;
    cout << "\t\tName           : " << client.name << endl;
    cout << "\t\tAccount Balance: " << client.accountBalance << endl;
    cout << "\t\tAccount Number : " << client.accountNumber << endl;
    cout << "\t\tPhone Number   : " << client.phone << endl;
    cout << "\t\tPincode        : " << client.pincode << "\n\n\n";

}
void saveDataClientInFile(string fileName, string sData){

    fstream file;

    file.open(fileName, ios::out | ios::app);

    if(file.is_open()){
        file << sData << endl;
        file.close();
    }

}


void addNewClient (string accountNumber)
{
    sClient client = readClientInfo("Enter client data: ");
    client.accountNumber = accountNumber;
    saveDataClientInFile(ClientsFileName, convertRecordToData(client, "#//#"));
}
void addClients(vector<sClient> & vClients, string accountNumber)
{
    char addMore = 'Y';

    do{
        system("cls");
        cout << "Add New client: " << endl;

        addNewClient(accountNumber);
        vClients = loadDataClientFromFile(ClientsFileName);
        cout << "Added successfully, Do you want to add more clients : "; cin >> addMore;
    }while(toupper(addMore) == 'Y');
}

vector<sClient> loadDataClientFromFile(string fileName)
{
    vector<sClient> vClient;

    fstream file;
    file.open(fileName, ios::in);

    if(file.is_open()){


        string line;
        sClient client;


        while(getline(file, line)){

            client = convertDataToRecord(line, "#//#");
            vClient.push_back(client);
        }
        file.close();
    }
    return vClient;
}

void printClientRecord(sClient client)
{
    cout << "| " << left << setw(20) << client.accountNumber;
    cout << "| " << left << setw(10) << client.pincode;
    cout << "| " << left << setw(40) << client.name;
    cout << "| " << left << setw(12) << client.phone;
    cout << "| " << left << setw(12) << client.accountBalance;

}

void printAllClientsData(vector<sClient> clientsData)
{
    cout << "\n\t\t\t\t\tClient list (" << clientsData.size() << ") client(s).";
    cout << "\n----------------------------------------------------------------------------------------------------------------\n\n";
    cout << "| " << left << setw(20) << "Account Number: ";
    cout << "| " << left << setw(10) << "Pin code: ";
    cout << "| " << left << setw(40) << "Client Name: ";
    cout << "| " << left << setw(12) << "Phone: ";
    cout << "| " << left << setw(12) << "Balance: ";
    cout << endl;
    for(sClient & client : clientsData){
        printClientRecord(client);
        cout << endl;
    }
    cout << "\n----------------------------------------------------------------------------------------------------------------\n\n";

}
bool findClientByAccountNumber (vector<sClient> clients, string AccountNumber, sClient & client)
{
    for(sClient & item : clients){
        if(item.accountNumber == AccountNumber){
            client = item;
            return true;
        }
    }
    return false;
}
bool markClientForDeletByAccountNumber (string accountNumber, vector<sClient>  & vClients)
{
    for(sClient& c : vClients){
        if(c.accountNumber == accountNumber){
            c.markForDelet = true;
            return true;
        }
    }
    return false;
}
vector <sClient> saveClientsDataToFile(string fileName, vector<sClient> vClient)
{
    fstream myFile;
    myFile.open(fileName, ios::out); //over write

    string dataLine;

    if (myFile.is_open()){
        for(sClient c : vClient){
            if(!c.markForDelet){

                dataLine = convertRecordToData(c, "#//#");
                myFile << dataLine << endl;
                }
            }
        myFile.close();
        }
        return vClient;
    }

sClient changeDataClient(string accountNumber)
    {
        sClient c;

        c.accountNumber = accountNumber;
        cout << "\nPlease Enter the account balance: "; cin >> c.accountBalance; cout << endl;
        c.name = readString("please Enter the Name: ");
        c.phone = readString("please Enter the phone Number: ");
        c.pincode = readString("please Enter the Pin Code: ");

        return c;
    }
bool updateCientByAccountNumber (string accountNumber, vector<sClient> & vClients)
    {
        sClient client;
        char answer = 'n';

        if(findClientByAccountNumber(vClients, accountNumber, client)){
            printClientData(client);

            cout << "Are you sure you want to Update this client ? y/n ? "; cin >> answer;
            if(toupper(answer) == 'Y'){
                for(sClient & c : vClients){
                    if (c.accountNumber == accountNumber){
                        c = changeDataClient(accountNumber);
                        break;
                    }
                }

                saveClientsDataToFile(ClientsFileName, vClients);

                cout << "\n\nclient Updated Successfully.";
                return true;
            }
        }else{
            cout << "\nClient with Account Number (" << accountNumber << ") is not found :-(";
            return false;
        }
    }
bool deleleCientByAccountNumber (string accountNumber, vector<sClient> & vClients)
    {
        sClient client;
        char answer = 'n';

        if(findClientByAccountNumber(vClients, accountNumber, client)){
            printClientData(client);

            cout << "Are you sure you want to delete this client ? y/n ? "; cin >> answer;
            if(toupper(answer) == 'Y'){
                markClientForDeletByAccountNumber(accountNumber, vClients);
                saveClientsDataToFile(ClientsFileName, vClients);

                vClients = loadDataClientFromFile(ClientsFileName);

                cout << "\n\nclient Deleted Successfully.";
                return true;
            }
        }else{
            cout << "\nClient with Account Number (" << accountNumber << ") is not found :-(";
            return false;
        }
    }

//---------------------------------------- Functions to handle users ----------------------------------------------
int readPermissionToSet();

sUser convertUserLineToRecord (string line, string seperator = "#//#")
{
    vector<string> vUser = splitString(line, seperator);

    sUser user;
    user.userName = vUser[0];
    user.password = vUser[1];
    user.permission = stoi(vUser[2]);

    return user;
}
string convertRecordUserToData(sUser user, string separetor = "#//#")
{
    string data = "";
    data += (user.userName + separetor);
    data += (user.password + separetor);
    data += to_string(user.permission);

    return data;
}


vector<sUser> loadDataUsersFromFile(string fileNmae)
{
    vector<sUser> users;

    fstream myFile;
    myFile.open(fileNmae, ios::in);//read Mode

    if(myFile.is_open()){

        string line;
        sUser user;

        while(getline(myFile, line)){
            user = convertUserLineToRecord(line);
            users.push_back(user);
        }
        myFile.close();
    }


    return users;
}

bool findUsersByUsernameAndPassword(string userName, string password, sUser & user)
{
    vector <sUser> vUsers = loadDataUsersFromFile(UsersFileName);

    for(sUser u: vUsers){
        if(u.userName == userName && u.password == password){

            user = u;
            return true;
        }
    }

    return false;
}

bool loadUsersInfo (string userName, string password)
{
    if(findUsersByUsernameAndPassword(userName, password, CurrentUser))
        return true;
    else
        return false;
}

void printUserRecord(sUser user)
{
    cout << "| " << left << setw(10) << user.userName;
    cout << "| " << left << setw(10) << user.password;
    cout << "| " << left << setw(10) << user.permission;

}

void printAllUsersData()
{
    vector <sUser> users = loadDataUsersFromFile(UsersFileName);
    cout << "\n\t\t\t\t\tUsers list (" << users.size() << ") User(s).";
    cout << "\n----------------------------------------------------------------------------------------------------------------\n\n";
    cout << "| " << left << setw(10) << "UserName";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(10) << "permission";
    cout << endl;
    for(sUser & user : users){
        printUserRecord(user);
        cout << endl;
    }
    cout << "\n----------------------------------------------------------------------------------------------------------------\n\n";

}

bool checkPermission (enMainMenuPermission permission)
{
    if(permission == enMainMenuPermission::All)
        return true;

    if((permission & CurrentUser.permission) == permission)
        return true;
    else
        return false;
}
void printUserData(sUser user)
{
    cout << "\n\n\n\t\t    **The User Info** \n" << endl;
    cout << "\t\tUserName   : " << user.userName << endl;
    cout << "\t\tpassword   : " << user.password << endl;
    cout << "\t\tpermission : " << user.permission << "\n\n";
}
vector <sUser> saveUsersDataToFile(string fileName, vector<sUser> users)
{
    fstream myFile;
    myFile.open(fileName, ios::out); //over write

    string dataLine;

    if (myFile.is_open()){
        for(sUser c : users){
            if(!c.markForDelet){

                dataLine = convertRecordUserToData(c, "#//#");
                myFile << dataLine << endl;
                }
            }
        myFile.close();
        }
        return users;
    }

bool markUserForDeletByUserNameAndPassword (string userName, string password)
{
    vector <sUser> users = loadDataUsersFromFile(UsersFileName);

    for(sUser& user : users){
        if(user.password == password && user.userName == userName){
            user.markForDelet = true;
            saveUsersDataToFile(UsersFileName, users);
            return true;
        }
    }
    return false;
}

bool deleleUserByUserNameAndPassword (string userName, string password)
    {
        sUser user;
        char answer = 'n';

        if(findUsersByUsernameAndPassword(userName, password, user)){
            printUserData(user);

            cout << "Are you sure you want to delete this user ? y/n ? "; cin >> answer;
            if(toupper(answer) == 'Y'){
                markUserForDeletByUserNameAndPassword(userName, password);

                cout << "\n\nUser Deleted Successfully.";
                return true;
            }
        }else{
            cout << "\nUser with UserName (" << userName << ") is not found :-(";
            return false;
        }
    }
sUser changeDataUser(string userName)
{
    sUser user;

    user.userName = userName;
    user.password = readString("please enter a new password: ");
    user.permission = readPermissionToSet();

    return user;
}
bool updateUserByUserNameAndPassword (string userName, string password)
    {
        vector<sUser> users = loadDataUsersFromFile(UsersFileName);
        sUser user;
        char answer = 'n';

        if(findUsersByUsernameAndPassword(userName, password, user)){
            printUserData(user);

            cout << "Are you sure you want to Update this User ? y/n ? "; cin >> answer;
            if(toupper(answer) == 'Y'){
                for(sUser& u : users){
                    if (u.userName == userName && u.password == password){
                        u = changeDataUser(userName);
                        break;
                    }
                }

                saveUsersDataToFile(UsersFileName, users);

                cout << "\n\nUser Updated Successfully.";
                return true;
            }
        }else{
            cout << "\nUser with UserName (" << userName << ") is not found :-(";
            return false;
        }
    }
int readPermissionToSet()
{
    int permission = 0;
    char answer = 'n';


    cout << "Do you want to get this user full access ? (Y/N)\n";
    cin >> answer;
    if(answer == 'y' || answer == 'Y')
        return -1;

    cout << "please Enter 'Y' To get access to these permission:\n";

    cout << "clients list: "; cin >> answer;
    if(answer == 'y' || answer == 'Y')
        permission += enMainMenuPermission::PClientList;

    cout << "Add Clients: "; cin >> answer;
    if(answer == 'y' || answer == 'Y')
        permission += enMainMenuPermission::PAddClient;

    cout << "Delete client: "; cin >> answer;
    if(answer == 'y' || answer == 'Y')
        permission += enMainMenuPermission::PDeleteClient;

    cout << "Find Client: "; cin >> answer;
    if(answer == 'y' || answer == 'Y')
        permission += enMainMenuPermission::PFindClient;

    cout << "Mange users: "; cin >> answer;
    if(answer == 'y' || answer == 'Y')
        permission += enMainMenuPermission::PmangeUsers;

    cout << "Tranasactions: "; cin >> answer;
    if(answer == 'y' || answer == 'Y')
        permission += enMainMenuPermission::PTransactions;

    cout << "Update Client: "; cin >> answer;
    if(answer == 'y' || answer == 'Y')
        permission += enMainMenuPermission::PUpdateClient;

    return permission;
}

void addUser(string userName, string password)
{
        sUser user;
        user.userName = userName;
        user.password = password;
        user.permission = readPermissionToSet();

        saveDataClientInFile(UsersFileName, convertRecordUserToData(user));

}
//---------------------------------------- Build The Bank Project -------------------------------------------------
void login();
void mainMenu();
void mangeUsersMenu();
void transacionsMenu (vector<sClient> & clients);


int readOptionNumber(int from , int to){

    int option;
    do {
        cout << "Enter number from " << from << " to " << to << ": "; cin >> option; cout << endl;
    }while(option < from || option > to);

    return option;

}

void subMenuHeader(string header){

    cout << "\n\n-----------------------------------------" << endl;
    cout << "             "<< header <<"                  " << endl;
    cout << "-----------------------------------------\n\n" << endl;
}
void goBackToMainMenu ()
{
    cout << "press any key to go back to main menu...";
    system("pause>0");
    mainMenu();
}

void goBackToTransactionsMenu (vector<sClient> & clients)
{
    cout << "\n\nPress any key to go back to transactions menu...";
    system("pause>0");
    transacionsMenu(clients);
}
void goBackToMangeUsersMenu ()
{
    cout << "\n\nPress any key to go back to mange users menu...";
    system("pause>0");
    mangeUsersMenu();
}
void showClientsList (vector<sClient> &vClients)
{
    if(!checkPermission(enMainMenuPermission::PClientList)){
        subMenuHeader("Access Dined\n you are not permission to access to this process");
        return;
    }
    printAllClientsData(vClients);

}

void addClientToBank (vector<sClient> & vClients)
{

    if(!checkPermission(enMainMenuPermission::PAddClient)){
        subMenuHeader("Access Dined\n you are not permission to access to this process");
        return;
    }

    subMenuHeader("Add New Client");

    sClient client;

    do{
        client.accountNumber = readString("please enter an account number: ");
        if(!findClientByAccountNumber(vClients, client.accountNumber, client)){
            addClients(vClients, client.accountNumber);
            return;

        }else{
            cout << "the Account is already exist, ";
        }
    }while(findClientByAccountNumber(vClients, client.accountNumber, client));
}
void deletClientFromBank (vector<sClient> & vClients)
{
    if(!checkPermission(enMainMenuPermission::PDeleteClient)){
        subMenuHeader("Access Dined\n you are not permission to access to this process");
        return;
    }


    subMenuHeader("Delete An Account");

    string accoutnNumber = readString("please enter the account number what would you delete it: ");

    deleleCientByAccountNumber(accoutnNumber, vClients);

}

void updateClientInfoInBank (vector<sClient> & vClients)
{
    if(!checkPermission(enMainMenuPermission::PUpdateClient)){
        subMenuHeader("Access Dined\n you are not permission to access to this process");
        return;
    }

    subMenuHeader("Update Client Info");

    string accoutnNumber = readString("please enter the account number what would you delete it: ");

    updateCientByAccountNumber(accoutnNumber, vClients);

}

void findClientInBank (vector<sClient> vClients)
{
    if(!checkPermission(enMainMenuPermission::PFindClient)){
        subMenuHeader("Access Dined\n you are not permission to access to this process");
        return;
    }

    subMenuHeader("Find Client Info");

    string accoutnNumber = readString("please enter the account number what would you delete it: ");
    sClient client;

    if(findClientByAccountNumber(vClients, accoutnNumber, client))
        printClientData(client);
    else
        cout << "the client is not found :-(" << endl;


}
bool depositBalanceByAccountNumber (vector<sClient> & clients, int amount, string accountNumber)
{
    char answer = 'n';

    cout << "\n\nAre you sure you want perform this transaction ? Y/N ? "; cin >> answer; cout << endl;

    if(toupper(answer) == 'Y'){

        for(sClient & client : clients){
            if(client.accountNumber == accountNumber){
                client.accountBalance += amount;
                saveClientsDataToFile(ClientsFileName, clients);
                cout << "\n\nDone successfully. New balance is: " << client.accountBalance;
                return true;
            }
        }
    }else{
        return false;

    }
}


void depositScreen(vector<sClient> & clients)
{
    subMenuHeader("Deposit screen");

    sClient client;
    string accountNumber = readString("please Enter Account Number: ");

    while(!findClientByAccountNumber(clients, accountNumber, client)){
        cout << "\nClient with [" << accountNumber << "] does not exist. \n";
        accountNumber = readString("please Enter Account Number: ");
    }

    printClientData(client);

    int amount = 0;
    cout << "\nPlease Enter deposit amount: "; cin >> amount; cout << endl;

    depositBalanceByAccountNumber(clients, amount, accountNumber);
}

void withdrawScreen(vector<sClient> & clients)
{
    subMenuHeader("Withdraw Screen");

    sClient client;
    string accountNumber = readString("Please enter the account number: ");

    while(!findClientByAccountNumber(clients, accountNumber, client )){
        cout << "The account with [" << accountNumber << "] dose not found. ";
        accountNumber = readString("Please enter the account number: ");
    }

    printClientData(client);

    int amount = 0;
    cout << "\nPlease Enter withdraw amount: "; cin >> amount; cout << endl;

    while(amount > client.accountBalance)
    {
        cout << "\nAmount Exceeds the balance,  you can withdraw up to: " << client.accountBalance << endl;
        cout << "please Enter another amount: "; cin >> amount; cout << endl;
    }

    depositBalanceByAccountNumber(clients, amount * -1, accountNumber);
}

void usersListMenu ()
{
    printAllUsersData();
}
void addNewUser()
{
    vector <sUser> users = loadDataUsersFromFile(UsersFileName);

    subMenuHeader("Add New User");

    sUser user;

    do{
        user.userName = readString("please Enter userName: ");
        user.password = readString("please Enter password: ");

        if(!findUsersByUsernameAndPassword(user.userName, user.password, user)){
            addUser(user.userName, user.password);
            return;

        }else{
            cout << "the Account is already exist, ";
        }
    }while(findUsersByUsernameAndPassword(user.userName, user.password, user));
}

void DeleteUser()
{
    subMenuHeader("Delete A User");

    string userName = readString("Please Enter the name of user want to delete : ");
    string password = readString("please Enter the password user want to delete : ");

    deleleUserByUserNameAndPassword(userName, password);

}

void UpdateUser()
{
    subMenuHeader("Update User Info");

    string userName = readString("Please Enter the name of user want to update : ");
    string password = readString("please Enter the password user want to update : ");

   updateUserByUserNameAndPassword(userName, password);
}
void findUserBank ()
{

    subMenuHeader("Find User Info");

    string userName = readString("Please Enter the name of user want to find it : ");
    string password = readString("please Enter the password user want to find it : ");
    sUser user;

    if(findUsersByUsernameAndPassword(userName, password, user))
        printUserData(user);
    else
        cout << "the User is not found :-(" << endl;


}
void handleOptionOfMangeUserMenu(int option)
{
    switch(option)
    {
        case enMangeUsers::usersList :
            system("cls");
            usersListMenu();
            goBackToMangeUsersMenu();
            break;

        case enMangeUsers::AddUser :
            system("cls");
            addNewUser();
            goBackToMangeUsersMenu();
            break;

        case enMangeUsers::deleteUser :
            system("cls");
            DeleteUser();
            goBackToMangeUsersMenu();
            break;

        case enMangeUsers::updateUser :
            system("cls");
            UpdateUser();
            goBackToMangeUsersMenu();
            break;

        case enMangeUsers::findUser :
            system("cls");
            findUserBank();
            goBackToMangeUsersMenu();
            break;

        case enMangeUsers::goBack :
            mainMenu();
            break;
    }
}

void mangeUsersMenu ()
{
        if(!checkPermission(enMainMenuPermission::PmangeUsers)){
        subMenuHeader("Access Dined\n you are not permission to access to this process");
        goBackToMainMenu();
    }

        system("cls");

        cout << "=====================================================" << endl;
        cout << "                  Mange Users Menu                   " << endl;
        cout << "=====================================================" << endl;
        cout << "      [1] list Uses.                                 " << endl;
        cout << "      [2] Add New User.                              " << endl;
        cout << "      [3] Delete User.                               " << endl;
        cout << "      [4] Update User.                               " << endl;
        cout << "      [5] Find User.                                 " << endl;
        cout << "      [6] Main Menu.                                 " << endl;
        cout << "=====================================================" << endl;

        int option = readOptionNumber(1, 6);

        handleOptionOfMangeUserMenu(option);

}


void handleOptionOfTransactionMenu (int option, vector<sClient> & clients)
{
    switch (option) {
    case enTransactions::Deposit :
        system("cls");
        depositScreen(clients);
        goBackToTransactionsMenu(clients);
        break;
    case enTransactions::Withdraw :
        system("cls");
        withdrawScreen(clients);
        goBackToTransactionsMenu(clients);
        break;
    case enTransactions::TotalBalance :
        system("cls");
        printAllClientsData(clients);
        goBackToTransactionsMenu(clients);
        break;
    case enTransactions::Main :
        mainMenu();
        break;

    }
}

void transacionsMenu (vector<sClient> & clients)
{
        if(!checkPermission(enMainMenuPermission::PTransactions)){
        subMenuHeader("Access Dined\n you are not permission to access to this process");
        goBackToMainMenu();
    }


        system("cls");
        cout << "=====================================================" << endl;
        cout << "               Transactions menu Screen              " << endl;
        cout << "=====================================================" << endl;
        cout << "      [1] Deposit.                                   " << endl;
        cout << "      [2] Withdraw.                                  " << endl;
        cout << "      [3] Total Balance.                             " << endl;
        cout << "      [4] Main Menu.                                 " << endl;
        cout << "=====================================================" << endl;

        int option = readOptionNumber(1, 4);

        handleOptionOfTransactionMenu(option, clients);
}


void handleOptionOfMianMenu (int option) {

    //loading data form the file
    vector<sClient> vClients = loadDataClientFromFile(ClientsFileName);



    switch(option){

    case enMenuScreen::clientList :
        system("cls");
        showClientsList(vClients);
        goBackToMainMenu();
        break;

    case enMenuScreen::AddClient :
        system("cls");
        addClientToBank(vClients);
        goBackToMainMenu();
        break;

    case enMenuScreen::DeletClient :
        system("cls");
        deletClientFromBank(vClients);
        goBackToMainMenu();
        break;

    case enMenuScreen::updatClient :
        system("cls");
        updateClientInfoInBank(vClients);
        goBackToMainMenu();
        break;

    case enMenuScreen::findClient :
        system("cls");
        findClientInBank(vClients);
        goBackToMainMenu();
        break;

    case enMenuScreen::transacions :
        system("cls");
        transacionsMenu(vClients);
        break;

    case enMenuScreen::mangeUsers :
        system("cls");
        mangeUsersMenu();
        break;

    case enMenuScreen::Exit :
        system("cls");
        login();
        break;
    }


}

void mainMenu(){

        system("cls");

        cout << "=====================================================" << endl;
        cout << "                  Main Menu Screen                   " << endl;
        cout << "=====================================================" << endl;
        cout << "      [1] show clients list.                         " << endl;
        cout << "      [2] Add New Clients.                           " << endl;
        cout << "      [3] Delete Client.                             " << endl;
        cout << "      [4] Update Client Info.                        " << endl;
        cout << "      [5] Find Client.                               " << endl;
        cout << "      [6] Transactions.                              " << endl;
        cout << "      [7] mange Users.                               " << endl;
        cout << "      [8] logout.                                    " << endl;
        cout << "=====================================================" << endl;


        int option = readOptionNumber(1, 8);

        handleOptionOfMianMenu(option);


}

void login()
{
    bool loginFailed = false;
    string userName, password;

    do{
        system("cls");
        cout << "=====================================================" << endl;
        cout << "                    Login screen                     " << endl;
        cout << "=====================================================" << endl;

        if(loginFailed){
            cout << "Invalid userName/password \n";
        }

        cout << "Enter userName: ";
        cin >> userName;

        cout << "Enter password: ";
        cin >> password;

        loginFailed = !loadUsersInfo(userName, password);
    }while(loginFailed);

    mainMenu();
}



int main()
{
    login();
    return 0;
}
