#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "myStringLib.h"

using namespace std;

enum enMenuScreen {clientList = 1, AddClient = 2, DeletClient = 3, updatClient = 4, findClient = 5, transacions = 6, Exit = 7};
enum enTransactions {Deposit = 1, Withdraw = 2, TotalBalance = 3, Main = 4};

const string fileName = "Clients.txt";

struct sClient {
    string accountNumber;
    string pincode;
    string name;
    string phone;
    int accountBalance;
    bool markForDelet = false;
};
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
    saveDataClientInFile(fileName, convertRecordToData(client, "#//#"));
}
void addClients(vector<sClient> & vClients, string accountNumber)
{
    char addMore = 'Y';

    do{
        system("cls");
        cout << "Add New client: " << endl;

        addNewClient(accountNumber);
        vClients = loadDataClientFromFile(fileName);
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

                saveClientsDataToFile(fileName, vClients);

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
                saveClientsDataToFile(fileName, vClients);

                vClients = loadDataClientFromFile(fileName);

                cout << "\n\nclient Deleted Successfully.";
                return true;
            }
        }else{
            cout << "\nClient with Account Number (" << accountNumber << ") is not found :-(";
            return false;
        }
    }


            //---------------------------------------- Build The Bank Project -------------------------------------------------
void mainMenu();
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
void showClientsList (vector<sClient> &vClients)
{
    printAllClientsData(vClients);

}

void addClientToBank (vector<sClient> & vClients)
{
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
    subMenuHeader("Delete An Account");

    string accoutnNumber = readString("please enter the account number what would you delete it: ");

    deleleCientByAccountNumber(accoutnNumber, vClients);

}

void updateClientInfoInBank (vector<sClient> & vClients)
{
    subMenuHeader("Update Client Info");

    string accoutnNumber = readString("please enter the account number what would you delete it: ");

    updateCientByAccountNumber(accoutnNumber, vClients);

}

void findClientInBank (vector<sClient> vClients)
{
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
                saveClientsDataToFile(fileName, clients);
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
    vector<sClient> vClients = loadDataClientFromFile(fileName);



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
        transacionsMenu(vClients);
        break;

    case enMenuScreen::Exit :
        system("cls");
        subMenuHeader("The program End :-(");
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
        cout << "      [7] Exit.                                      " << endl;
        cout << "=====================================================" << endl;


        int option = readOptionNumber(1, 7);

        handleOptionOfMianMenu(option);


}


int main()
{
    mainMenu();
    return 0;
}
