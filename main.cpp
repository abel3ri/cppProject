#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Account {
    int accountNumber;
    string name;
    string password;
    double balance;
};
Account createNewAccount(){
    cout << "\n************* 1. Create new account ****************\n\n";
    vector<Account> accounts;
    Account newAccount;
    string name, password, accName, accPass;
    double balance, accBalance;
    int accountNumber;
    cout << " Please enter your account name: ";
    cin >> name;
    cout << "\n Please enter your account password: ";
    cin >> password;
    cout << "\n Please enter you first deposit amount: ";
    cin >> balance;
    balance < 0 ? balance = 0 : balance;
    ifstream accountsIFile("accounts.txt");
    if(!accountsIFile.is_open()){
        accountNumber = 1;
        newAccount = {accountNumber, name, password, balance};
        cout << "\n Account created successfully! \n\n";
        cout << " Your account number is " << accountNumber << "\n\n";
    } else {
       while(accountsIFile >> accountNumber >> accName >> accPass >> accBalance){
            accounts.push_back({accountNumber, accName, accPass, accBalance});
        }
        accountNumber = accounts.size() + 1;
        newAccount = {accountNumber, name, password, balance};
        cout << "\n Account created successfully! \n\n";
        cout << " Your account number is " << accountNumber << "\n\n";
        accountsIFile.close();
    }

    return newAccount;
}
void checkAccountStatus(int &accNumber, string &name, string &password){
    bool accountFound = false;
    string accName, accPass;
    int accNum;

    double balance;
    ifstream accountsIFile("accounts.txt", ios::in);
    if(accountsIFile.is_open()){
        while(accountsIFile >> accNum >> accName >> accPass >> balance){
                if(accName == name && accPass == password && accNumber == accNum){
                    cout << "\n Hello " << accName << ", Your account balance is ";
                    cout << balance << " ETB.\n\n ";
                    accountFound = true;
            }
        }
            if(!accountFound){
                    cout << "\n We could not find your account, ";
                    cout << "Please make sure that the account name and password combinations are correct.\n\n";
                }
            } else {
            cout << "\n Error opening the file!\n";
    }
}
void deposit(int* accNumber, string* accPass, double* amount){
    vector<Account> accounts;
    bool accountFound = false;
    string accName, pass;
    double balance, newBalance = 0;
    int accNum;
    ifstream accountsFile("accounts.txt", ios::in);
    if(accountsFile.is_open()){
        while(accountsFile >> accNum >> accName >> pass >> balance){
            accounts.push_back({accNum, accName, pass, balance});
        }
        accountsFile.close();
    } else cout << "\n Error opening the file!\n";

    for(int i = 0; i < accounts.size(); i++){
        if(accounts[i].accountNumber == *accNumber && accounts[i].password == *accPass){
                accounts[i].balance += *amount;
                newBalance = accounts[i].balance;
                accountFound = true;
                break;
        }
    }
     if(!accountFound){
        cout << "\n We could not find your account, ";
        cout << "Please make sure that the account number, name, and password combinations are correct.\n\n";
        return;
    }
    ofstream accountsOFile("accounts.txt", ios::out);
    if(accountsOFile.is_open()){
        for(int i = 0; i < accounts.size(); i++){
            accountsOFile << accounts[i].accountNumber << " " << accounts[i].name << " " << accounts[i].password << " " << accounts[i].balance << "\n";
        }
        cout << "\n You have successfully deposited " << *amount << " ETB to your account. Your account balance is now " << newBalance <<" ETB.\n\n";
        accountsOFile.close();
    } else cout << "Error opening the file!";

}
void transerMoney(int* tAccNumber, string* tPass, int* rAccNumber, double* tAmount){
    int accNum;
    string accName, accPass;
    double balance;
    vector<Account> accounts;

    ifstream accountsIFile("accounts.txt");
        if(accountsIFile.is_open()){
            while(accountsIFile >> accNum >> accName >> accPass >> balance){
                accounts.push_back({accNum, accName, accPass, balance});
            }
            for(int i = 0; i < accounts.size(); i++){
                if(*tAccNumber == accounts[i].accountNumber && *tPass == accounts[i].password){
                    if(accounts[i].balance < *tAmount){
                        cout << "\n The transfer amount should not exceed your account balance\n\n";
                        break;
                    } else {
                        accounts[i].balance -= *tAmount;
                    }
                }
                if(*rAccNumber == accounts[i].accountNumber){
                    accounts[i].balance += *tAmount;
                }
            }
            ofstream accountsOFile("accounts.txt");
            if(accountsOFile.is_open()){
                for(int i = 0; i < accounts.size(); i++){
                    accountsOFile << accounts[i].accountNumber << " " << accounts[i].name << " " << accounts[i].password << " " << accounts[i].balance << "\n";
                }
                cout << "\n You have successfully transfered " << *tAmount << " ETB to the account number ";
                cout << *rAccNumber << ".\n\n";
                accountsOFile.close();
            } else cout << "\n Error opening the file\n\n";

//            for(int i = 0; i < accounts.size(); i++){
//                cout << accounts[i].name << "  " << accounts[i].accountNumber << endl;
//            }
            accountsIFile.close();
        } else cout << "\n Error opening the file!\n\n";

}
void withdrawal(int* accNumber, string* accPass, double* amount){
    vector<Account> accounts;
    bool accountFound = false;
    string accName, pass;
    double balance, newBalance = 0;
    int accNum;
    ifstream accountsFile("accounts.txt", ios::in);
    if(accountsFile.is_open()){
        while(accountsFile >> accNum >> accName >> pass >> balance){
            accounts.push_back({accNum, accName, pass, balance});
        }
        accountsFile.close();
    } else cout << "\n Error opening a file!\n";

    for(int i = 0; i < accounts.size(); i++){
        if(accounts[i].accountNumber == *accNumber && accounts[i].password == *accPass){
                if(accounts[i].balance < *amount){
                    cout << "\n Your withdrawal amount should not exceed your account balance\n\n";
                   return;
                }
                else { accounts[i].balance -= *amount;
                newBalance = accounts[i].balance;
                accountFound = true;
                break;
                }
        }
    }
     if(!accountFound){
        cout << "\n We could not find your account, ";
        cout << "Please make sure that the account number, name, and password combinations are correct.\n\n";
        return;
    }
    ofstream accountsOFile("accounts.txt", ios::out);
    if(accountsOFile.is_open()){
        for(int i = 0; i < accounts.size(); i++){
            accountsOFile << accounts[i].accountNumber << " " << accounts[i].name << " " << accounts[i].password << " " << accounts[i].balance << "\n";
        }
        cout << "\n You have successfully withdrawn " << *amount << " ETB from your account. Your account balance is now " << newBalance <<" ETB.\n\n";
        accountsOFile.close();
    } else cout << "Error opening the file!";

}
int main()
{
    int choice;
    while(choice != 5){

    // Welcome screen
    cout << " ************** WELCOME TO G2 BANK *****************\n\n";
    cout << " *       1. Create new account                     *\n";
    cout << " *       2. Perform bank operations                *\n";
    cout << " *       3. Check account status                   *\n";
    cout << " *       4. About the project                      *\n";
    cout << " *       5. Exit                                   *\n\n";
    cout << " ***************************************************\n";
    cin >> choice;
    system("cls");

    //Create new account

    if(choice == 1){
        Account acc = createNewAccount();
        ofstream accountsOFile("accounts.txt", ios::app);
        if(accountsOFile.is_open()){
            accountsOFile << acc.accountNumber << " " << acc.name << " " << acc.password << " " << acc.balance << "\n";
            accountsOFile.close();
        } else {
            cout << "\n Error opening the file!\n";
        }
    } else if(choice == 2){

        // Perform bank operations

        int choice;
        cout << "******* Perform bank operations *******\n\n";
        cout << "       1. Deposit to account\n";
        cout << "       2. Transfer to another account\n";
        cout << "       3. Make a withdrawal\n\n";
        cout << "****************************************\n";
        cin >> choice;
        system("cls");

        if(choice == 1){
        cout << "********* 1. Deposit to account ************\n\n";
        // Deposit to account

        int accNum;
        string  accPass;
        double amount;

        cout << " Please enter your account number: ";
        cin >> accNum;
        cout << "\n Please enter your account password: ";
        cin >> accPass;
        label:
        cout << "\n Please enter your deposit amount: ";
        cin >> amount;
        if(amount <= 0) {
            cout << "\nYou can only enter positive values!\n";
            goto label;
        }
        deposit(&accNum, &accPass, &amount);
    } else if(choice == 2){
        cout << "******* 2. Transfer to another account ********\n\n";
        // Transfer to another account

        string  tPass;
        int tAccNum, rAccNum;
        double amount;
        cout << "\n Please enter your account number: ";
        cin >> tAccNum;
        cout << " \nPlease enter your account password: ";
        cin >> tPass;
        cout << " \nPlease enter receiver's account number: ";
        cin >> rAccNum;
        lable:
        cout << " \nPlease enter the transfer amount: ";
        cin >> amount;
        if(amount <= 0){
            cout << "\n You can only enter positive values!\n";
            goto lable;
        }
        transerMoney(&tAccNum, &tPass, &rAccNum, &amount);
    } else if(choice == 3){
        cout << "*********** 3. Make a withdrawal **************\n\n";
        // Make a withdrawal
        int accNum;
        string accPass;
        double amount;
        cout << " Please enter your account number: ";
        cin >> accNum;
        cout << "\n Please enter your account password: ";
        cin >> accPass;
        lable2:
        cout << "\n Please enter your withdrawal amount: ";
        cin >> amount;
        if(amount < 0){
            cout << "\n Your withdrawal amount should be greater than 0!\n\n";
            goto lable2;
        }
        withdrawal(&accNum, &accPass, &amount);
    }
    } else if(choice == 3){

        // Check account status

        string accName, accPass;
        int accNum;
        cout << "\n Please enter your account name: ";
        cin >> accName;
        cout << "\n Please enter your account number: ";
        cin >> accNum;
        cout << "\n Please enter your password: ";
        cin >> accPass;
        checkAccountStatus(accNum, accName, accPass);
    }

    else if(choice == 4){
        cout << "\n**********  Developed by Group two members ************\n\n";
        cout << "   --Name--                                    ID Number\n\n";
        cout << "  Abel Merete                               DBUR/0032/13\n";
        cout << "  Fikade Tibebe                             DBUR/0032/13\n";
        cout << "  Mikias Bayle                              DBUR/0262/13\n";
        cout << "  Samuel Kifle                              DBUR/0698/13\n";
        cout << "  Tarik Dabot                               DBUR/1400100/13\n";
        cout << "  Dawit Bekele                              DBUR/0952/13\n";
        cout << "  Muse Madalcho                             DBUR/3720/13\n";
        cout << "  Yohanes Tamirat                           DBUR/0786/13\n";
        cout << "  Abdulaziz Musa                            DBUR/0597/13\n\n";
    }
    }
    return 0;

}
/* NOTE : Due to its flexibility, dynamicity and also the fact that
they have no to little difference, we have used 'vector' instead of 'array'
even though we were ordered to practice what we have learned, which was array.
*/
