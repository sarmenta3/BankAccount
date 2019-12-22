#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <fstream>

using namespace std;
//==============type struct===============
struct account {
	int accountNum, passIter = 0;
	string last, first, passWord;
	double deposit = 0, withdraw = 0,totalAmount = 0, pastActivity[300];
};

//===========functions============================
int start();
void createAccount(account name[], int &diter);
string check(string &yN);
void deposti(account in[], int &check, int accountN);
void withdraw(account out[], int accountNum, int accountN);
int accountNumber(int check);
void pastActivity(account past[], int iter, int accountN);
string forgotPw(account num[], int &iter, int accNum);
double checkNum();
void startupInput(ifstream &bankInput, account newAccount[], int iter);
void closingOutput(ofstream &outPut, ofstream &pw, account newAccount[], int iter);
void accountOptions(account newAccount[], int iter);

//============functions===========================
#define  MAXOPTIONS 3;


// start of main
int main() {
	ifstream iterF("iter.txt");
	ifstream inPassW("passWord.txt");
	ifstream bankInput("bank.txt");
	string again = "y";
	account newAccount[100];

	int iter;
	iterF >> iter;

	if (iter < 0)
		iter = 0;
	else {
		startupInput(bankInput, newAccount, iter);
	}

	ofstream iterO("iter.txt");
	ofstream outPut("bank.txt");
	ofstream passW("passWord.txt");

	//closingOutput(outPut, passW, newAccount, iter);
	cout << "this is the iter: " << iter << "\n";
	if (iter == 0) {
		createAccount(newAccount, iter);
		cout << "Would you like to make another transaction?\n";
		getline(cin, again);
		check(again);
		if (again == "y" || again == "yes")
		accountOptions(newAccount, iter);
	}
		
	else {
		cout << "Do you Already have an account [Y][N]?\n";
		getline(cin, again);
		check(again);

		if (again == "y" || again =="yes") {
			accountOptions(newAccount, iter);
		}
		else {
			cout << "Are you starting a new Account [Y][N]?\n";
			getline(cin, again);
			check(again);
			if (again == "y" || again == "yes") {
				createAccount(newAccount, iter);
				cout << "Do you want to manage your account [Y][N]?\n";
				getline(cin, again);
				check(again);
				if(again == "y" || again == "yes")
				accountOptions(newAccount, iter);
			}	
			else cout << "GoodBye\n";

		}
	}

	closingOutput(outPut, passW, newAccount, iter);
	
	iterO << iter;
	outPut.close();
	passW.close();
	inPassW.close();
	system("pause");
} //end main
//================start menu=========
 int start() {
	 int option = 0;
	 cout << "\nPlease pick a option\n";
	 cout << "1: Deposit\n";
	 cout << "2: Withdraw\n";
	 cout << "3: Past Activities\n";
	 cout << "4: Exit\n";

	 cout << "Enter option: ";
	 option = checkNum();
	 cin.ignore(numeric_limits<streamsize>::max(), '\n');
	 cout << endl;
	 while (option < -1 || option >= 5) {
		 cout << "Yout did not enter a valid option\n Enter again!";
		 cout << "\nPlease pick a option\n";
		 cout << "1: Deposit\n";
		 cout << "2: Withdraw\n";
		 cout << "3: Past Activities\n";
		 cout << "4: Exit\n";

		 option = checkNum();
		 cin.ignore(numeric_limits<streamsize>::max(), '\n');
		 cout << endl;
	 }
	 return option;
}

//============= create account===========
 void createAccount(account accountInfo[], int &iter) {
	string yN;
	int cinCheck = 0;
	while (iter <= 100) {
		cout << "This is cinCheck: " << cinCheck << "\n";
		if (cinCheck > 0) {
			cout << "yup its cleared.\n ";
			cin.clear();
			
	}//check to see if cin needs to be cleared
			

		//input first name
		accountInfo[iter].accountNum = iter;
		cout << "Enter First name of the new account holder \n";
		getline(cin, accountInfo[iter].first);
		accountInfo[iter].first[0] = toupper(accountInfo[iter].first[0]);
	

		//input last name
		cout << "Enter Last name of the new account holder\n";
		getline(cin, accountInfo[iter].last);
		accountInfo[iter].last[0] = toupper(accountInfo[iter].last[0]);
		
		// input deposit	
			cout << "Please make your first deposit:$";
			accountInfo[iter].deposit = checkNum();
			while (accountInfo[iter].deposit < 0) {
				cout << "\nThat is not a valid withdraw amount.\n";
				cout << "Please deposit:$";
				accountInfo[iter].deposit = checkNum();
			}
			
		//add deposit to account
		accountInfo[iter].totalAmount = accountInfo[iter].deposit;

		cout << "\nAccount info\n";

		cout.fill('0');
		cout << "Your New account number is: " << setw(4) << accountInfo[iter].accountNum << "\nAccount holder name is: "
			<< accountInfo[iter].last << ", " << accountInfo[iter].first
			<< "\nYou deposit and current ammount is:$" << setprecision(2) << fixed
			<< accountInfo[iter].deposit << endl;
		cin.clear();
		//cin.ignore(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
		cout << "\nIs the information on the screen correct press [Y]/[N]\n";
		getline(cin, yN);

		check(yN);
		
		if (yN == "n") {
			cout << ("Lets try to create your account again\n");
			cinCheck++;
		}
		else { 
			bool check = false;
			string checkS;

			while (!check) {
				cout << "Please Create a Password\n";
				cin >> accountInfo[iter].passWord;
				cin.ignore();
				cout << "Please enter the Password Again\n";
				cin >> checkS;
				cin.ignore();
				if (checkS != accountInfo[iter].passWord) {
					cout << "Those Passwords did not match try agian\n";
				}
				else check = true;
			}
			break; }//if acount info is correct and passwords match then break the "while" accont creation loop
		} //Account creation loop

	   // add deposit to total account 
		accountInfo[iter].pastActivity[accountInfo[iter].passIter] = accountInfo[iter].deposit;
		accountInfo[iter].passIter++;

		//set for next account
		iter++;
		
} //end create accoune

//============= deposit ==================
void deposti(account in[], int &check, int accountNum) {

	cout << in[accountNum].first << ", " << in[accountNum].last << " Please deposit:$";
	in[accountNum].deposit = checkNum();
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while (in[accountNum].deposit < 0) {
		cout << "\nThat is not a valid withdraw amount.\n";
		cout << "Please deposit:$";
		in[accountNum].deposit = checkNum();
	}
	in[accountNum].totalAmount += in[accountNum].deposit;
	in[accountNum].pastActivity[in[accountNum].passIter] = in[accountNum].deposit;
	in[accountNum].passIter++;

	cout << "\nName on accont: " << in[accountNum].last << ", " << in[accountNum].first 
		<< "\nYou have deposit:$" << in[accountNum].deposit 
		<< "\nTotal in account is: $" << in[accountNum].totalAmount << endl;
}

//==============withdraw =================
void withdraw(account out[], int check, int accountNum) {
	bool toMuch = true;
	
	while (toMuch) {
		toMuch = false;
		cout << "Enter amount to withdraw:$";
		out[accountNum].withdraw = checkNum();
		if (out[accountNum].withdraw > out[accountNum].totalAmount) {
			cout << "\nYou do not have sufficient funds to widthdraw:$" << out[accountNum].withdraw;
			cout << "\nYour current balance is:$" << out[accountNum].totalAmount << endl;
			toMuch = true;
		}
	}
	out[accountNum].totalAmount -= out[accountNum].withdraw;
	out[accountNum].pastActivity[out[accountNum].passIter] = 0;
	out[accountNum].pastActivity[out[accountNum].passIter] -= out[accountNum].withdraw;
	out[accountNum].passIter++;
	cout << "\nName on accont: " << out[accountNum].last << ", " << out[accountNum].first
		<< "\nYou have withdrew:$" << out[accountNum].withdraw;
	cout << "\nYout current balance is:$" << out[accountNum].totalAmount << endl;

}

//============check past activity===============
void pastActivity(account past[], int iter, int accountNum) {
	cout << "\nYour past transactions are\n";
	for (int i = 0; i < past[accountNum].passIter; i++) {
		cout << past[accountNum].pastActivity[i] << endl;
	}
}
//===========forgot pw==================
string forgotPw(account num[], int &iter, int accNum) {
	string pwNum = num[accNum].passWord, inputPw, again = "n";
	int ite = 4;
	cout << pwNum;
	while (ite > 0 && again =="n" ) {
		cout << "\nInput Your Password: ";
		cin >> inputPw;
		if (pwNum == inputPw) {
			again = "y";
		}
			
		else {
			ite--;
			cout << "\nThat was wrong Password you have " << ite << " more tries\n";
		}
	}
	return again;
}
//==============check if yes no===================
string check(string &yN) {
	bool found = false;
	while (!found) {
		
			yN = tolower(yN[0]);
			cout << yN;
		if (yN == "y" || yN == "n" ) {
			found = true;
			
		}	

		else {
			cout << "\nPlease press [Y]/[N]\n";
			getline(cin, yN);
		}
	}
	return yN;
}
//===============get account number ===================
int accountNumber(int check) {
	int accountNum = -1;

	cout << "Please enter your account number\n";
	while (!(cin >> accountNum) || accountNum > (check -1)) {//this will be true if an error occurs. It could be while( cin.fail() )
		cout << "\nYou did not enter a valid number";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nPlease enter you account number: ";
	}
	return accountNum;
}

//========== Check to see if number is valid ========
double checkNum() {
	double num = 0;
	while (!((cin >> num))) {//this will be true if an error occurs. It could be while( cin.fail() )
		cout << "\nYou did not enter a valid number";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		num = 0;
		cout << "\nPlease enter a number: ";
	}
	return num;
}

void startupInput(ifstream &bankInput, account newAccount[], int iter) {
	int count = 0;
	while (count < iter) {
		bankInput >> newAccount[count].accountNum >> newAccount[count].passWord >> newAccount[count].last >> newAccount[count].first
			>> newAccount[count].totalAmount >> newAccount[count].passIter;
		for (int i = 0; i < newAccount[count].passIter; i++)
			bankInput >> newAccount[count].pastActivity[i];
		count++;
	}
	
}

void closingOutput(ofstream &outPut, ofstream &pw, account newAccount[], int iter) {
	int counter1 = 0;
	while (counter1 < iter) {
		outPut << newAccount[counter1].accountNum << " " << newAccount[counter1].passWord << " " << newAccount[counter1].last << " " << newAccount[counter1].first
			<< " " << newAccount[counter1].totalAmount << " " << newAccount[counter1].passIter << " " << endl << endl;
		for (int i = 0; i < newAccount[counter1].passIter; i++)
			outPut << " " << newAccount[counter1].pastActivity[i] << " ";
		counter1++;
		outPut << endl << endl;
	}
	
	for (int i = 0; i < iter; i++)
		pw << newAccount[i].accountNum << " " << newAccount[i].passWord << endl << endl;
}

void accountOptions(account newAccount[], int iter) {
	
	int accountNum = accountNumber(iter);
	string again = forgotPw(newAccount, iter, accountNum);

	while (again == "y" || again == "yes") {
		int option = start();

		switch (option) {
		case 1: deposti(newAccount, iter, accountNum);
			break;
		case 2: withdraw(newAccount, iter, accountNum);
			break;
		case 3: pastActivity(newAccount, iter, accountNum);
			break;
		default: 
			break;
		}
		cout << "\nWould you like to make a transaction[Y][N]?\n";
		cin >> again;
		check(again);
	}
}