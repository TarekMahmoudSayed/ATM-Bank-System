#include <iostream>

#include <vector>

#include <cmath>

#include <Windows.h>

#include <string>

#include <fstream>

using namespace std;

struct stClient {

	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	
	double AccountBalance = 0.00;

	bool QuickWithdrawExit = false;


};

enum enMainMenuOption {enMainMenu = -1 ,enLogin = 0, enQuickWithdraw =1, enNormalWithdraw = 2, enDeposit = 3,  enCheckBalance = 4 , enLogout = 5};

enum enQuickWithdrawAmount {
	enTwenty = 1,
	enFift = 2,
	enOneHundred = 3,
	enTwoHundred = 4,
	enFourHundred = 5,
	enSixHundred = 6,
	enEightHundred = 7,
	enOneThousand = 8,
	enExit = 9
};

const string ClientsFile = "MyClients.txt";

const int MAX_TRIES = 3;

void loading(const string& Message) {

	cout << Message;
	for (int i = 0; i < 3; i++) {
		cout << ".";
		Sleep(300);
	}

	cout << endl;

}

void setColor(const int color) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

}

void Pause() {
	system ("pause > 0");
}

void clearScreen() {
	system ("cls");
}

void clearLines(int HowMany) {

	for (int i = 0; i < HowMany; i++) {
		cout << "\033[1A\r\033[K";
	}
}

int readIntFromUser(const string& Message) {

	string input;

	while (true) {

		cout << Message;
		cin >> input;

		bool isNumber = true;

		for (char& c : input) {

			if (!isdigit(c)) {
				setColor(4);
				cout << "Invalid input, try again!\n";
				setColor(15);
				isNumber = false;
				break;
			}

		}

		if (isNumber) {
			return stoi(input);
		}
	}

}

double readDoubleFromUser(const string& Message) {

	string input;
	double num;

	while (true) {
		cout << Message;
		getline(cin >> ws, input);

		try {
			size_t pos;
			num = stod(input, &pos);

			if (pos != input.length()) {
				throw invalid_argument("Extra characters");
			}

			break;
		}
		catch (...) {
			cout << "Invalid input, try again!\n";
		}
	}

	return num;

}

string readStringFromUser(const string& Message) {

	string s;

	cout << Message;
	getline(cin >> ws, s);

	return s;

}

char readCharFromUser(const string& Message) {

	char c;

	cout << Message;
	cin >> c;

	return c;

}

void printHeaderScreen(enMainMenuOption MenuOption) {

	switch (MenuOption) {

	case enMainMenuOption::enMainMenu :
		setColor(1);
		cout << "===================================================" << endl;
		cout << "\t\t ATM Main Menue Screen " << endl;
		cout << "===================================================" << endl;
		setColor(15);
		break;
	case enMainMenuOption::enLogin :
		setColor(2);
		cout << "---------------------------------------------------" << endl;
		cout << "\t\t Login Screen " << endl;
		cout << "---------------------------------------------------" << endl;
		setColor(15);
		break;
	case enMainMenuOption::enQuickWithdraw :
		setColor(3);
		cout << "===================================================" << endl;
		cout << "\t\t Quick Withdraw Screen " << endl;
		cout << "===================================================" << endl;
		setColor(15);
		break;
	case enMainMenuOption::enNormalWithdraw :
		setColor(5);

		cout << "===================================================" << endl;
		cout << "\t\t Normal Withdraw Screen " << endl;
		cout << "===================================================" << endl;
		setColor(15);

		break;
	case enMainMenuOption::enDeposit :
		setColor(6);

		cout << "===================================================" << endl;
		cout << "\t\t Deposit Screen " << endl;
		cout << "===================================================" << endl;
		setColor(15);
		break;
	case enMainMenuOption::enCheckBalance :
		setColor(9);
		cout << "===================================================" << endl;
		cout << "\t\t Check Balance Screen " << endl;
		cout << "===================================================" << endl;
		setColor(15);

		break;

	case enMainMenuOption::enLogout:
		setColor(4);

		cout << "---------------------------------------------------" << endl;
		cout << "\t\t Logout Screen " << endl;
		cout << "---------------------------------------------------" << endl;
		setColor(15);

		break;

	default :
		setColor(2);

		cout << "---------------------------------------------------" << endl;
		cout << "\t\t Login Screen " << endl;
		cout << "---------------------------------------------------" << endl;
		setColor(15);

		break;



	}


}

vector <string> splitString(string s, string separator = "#//#") {

	vector <string> vec;

	size_t pos = s.find(separator);

	string sWord = "";

	size_t star = 0;

	while ((pos = s.find(separator, star)) != string::npos) {

		sWord = s.substr(star, pos - star);

		if (sWord != "") {
			vec.push_back(sWord);
		}

		star = pos + separator.length();

	}

	sWord = s.substr(star);

	if (sWord != "") {
		vec.push_back(sWord);
	}

	return vec;


}

stClient convertLineToRecord(string Line) {

	vector <string> vec = splitString(Line);

	stClient client = stClient();

	if (vec.size() < 5)
		return stClient();

	client.AccountNumber = vec[0];
	client.PinCode = vec[1];
	client.Name = vec[2];
	client.Phone = vec[3];
	client.AccountBalance = stod(vec[4]);

	return client;

}

string convertRecordToLine(stClient client, string separator = "#//#") {

	string s = "";

	s += client.AccountNumber + separator;
	s += client.PinCode + separator;
	s += client.Name + separator;
	s += client.Phone + separator;
	s += to_string(client.AccountBalance);

	return s;

}

vector <stClient> LoadClientDataFromFile(const string& FileName) {

	vector <stClient> vec;

	fstream MyFile;

	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {

		string line;
		while (getline(MyFile, line)) {

			vec.push_back(convertLineToRecord(line));

		}

		MyFile.close();
	}

	return vec;

}

void SaveClientsDataToFile(vector <stClient>& vec ,const string& filename) {

	fstream MyFile;

	MyFile.open(filename, ios::out);

	if (MyFile.is_open()) {

		for (stClient& C : vec) {

			MyFile << convertRecordToLine(C) << endl;

		}

		MyFile.close();

	}

}

bool isFoundByAccountNumber(string AccountNumber, string Pincode, stClient& Client, vector <stClient>& vec) {

	for (stClient C : vec) {

		if (C.AccountNumber == AccountNumber && C.PinCode == Pincode) {

			Client = C;
			return true;

		}

	}

	return false;
}

bool loadClientDate(string AccountNumber, string Pincode, stClient& Client, vector <stClient>& vec) {

	return isFoundByAccountNumber(AccountNumber, Pincode, Client, vec);

}

void updateBalanceToClientByAccountNumber(stClient& CurrentClient, double DepositAmount, vector <stClient>& vec) {

	CurrentClient.AccountBalance += DepositAmount;

	for (stClient& C : vec) {

		if (C.AccountNumber == CurrentClient.AccountNumber) {
			C.AccountBalance = CurrentClient.AccountBalance;
			break;
		}

	}

	SaveClientsDataToFile(vec, ClientsFile);

}

void printQuickWithdrawAmounts() {

	cout << "\t[1] 20 \t [2] 50" << endl;
	cout << "\t[3] 100\t [4] 200" << endl;
	cout << "\t[5] 400\t [6] 600" << endl;
	cout << "\t[7] 800\t [8] 1000" << endl;
	cout << "\t[9] Exit" << endl;

}

int readQuickWithdrawChoice() {

	int Choice = readIntFromUser("Choose what to Withdraw from [1] to [9] ? ");

	cout << "---------------------------------------------------" << endl;

	loading("Processing Your Choice");
	clearLines(3);

	while (Choice < 1 || Choice > 9) {
		setColor(4);
		cout << "\n\nFalid To get Your Choice, Please Try Again" << endl;
		setColor(15);

		clearLines(1);

		Choice = readIntFromUser("Choose what to Withdraw from [1] to [9] ? ");
	}

	if (Choice == 9) {

		return -1;

	}


	return Choice;

}

double getQuickWithdrawAmount(int choice) {

	switch (choice) {

	case 1 :
		return 20.00;
	case 2 :
		return 50.00;
	case 3 :
		return 100.00;
	case 4 :
		return 200.00;
	case 5 :
		return 400.00;
	case 6 :
		return 600.00;
	case 7 :
		return 800.00;
	case 8 :
		return 1000.00;
	default :
		return 0.00;

	}

}

void printQuickWithDrawBalance(const stClient & CurrentClient) {

	cout << "---------------------------------------------------" << endl;
	cout << "Your Balance is : " << CurrentClient.AccountBalance << endl;

	cout << "---------------------------------------------------" << endl;
}

bool isSufficientBalance(double Amount, double AccountBalance) {

	return Amount <= AccountBalance;

}

bool validateQuickWithdraw(const stClient& CurrentClient, int Choice) {

	double Amount = getQuickWithdrawAmount(Choice);

	if (!isSufficientBalance(Amount, CurrentClient.AccountBalance)) {

		return false;
	}

	return true;

}

bool confirmTransaction() {

	char c = readCharFromUser("\n\nAre you sure you want perfrom this transaction ? y/n ? ");

	return (tolower(c) == 'y' );

}

bool QuickWithdraw(vector <stClient>& vec, stClient& CurrentClient) {

	loading("Quick Withdraw Loading ");

	clearScreen();

	printHeaderScreen(enMainMenuOption::enQuickWithdraw);

	printQuickWithdrawAmounts();

	printQuickWithDrawBalance(CurrentClient);

	int Choice = readQuickWithdrawChoice();

	if (Choice == -1) {

		CurrentClient.QuickWithdrawExit = true;
		return false;

	}

	if (!validateQuickWithdraw(CurrentClient, Choice)) {

		setColor(4);
		cout << "\n\nTransaction failed: Insufficient balance.\n";
		setColor(15);

		return false;
	}

	if (confirmTransaction()) {

		updateBalanceToClientByAccountNumber(CurrentClient, -1 * getQuickWithdrawAmount(Choice), vec);

		return true;

	}

	return false;

	



}

bool isMultipleOfFive(double Amount) {

	return (int) Amount %  5 == 0;

}

bool NormalWithdraw(vector <stClient>& vec, stClient& CurrentClient) {

	loading("Normal Withdraw Loading ");

	clearScreen();

	printHeaderScreen(enMainMenuOption::enNormalWithdraw);

	int CounterToClearLines = 1;

	double Amount = readDoubleFromUser("Enter an amount multiple of 5's ? ");

	while (!isMultipleOfFive(Amount) || Amount <= 0) {

		CounterToClearLines += 2;
		Amount = readDoubleFromUser("\nEnter an amount multiple of 5's ? ");

	}

	clearLines(CounterToClearLines);

	if (!isSufficientBalance (Amount, CurrentClient.AccountBalance)) {

		setColor(4);
		cout << "\n\nTransaction failed: Insufficient balance.\n";
		setColor(15);

		return false;
	}

	if (confirmTransaction()) {

		updateBalanceToClientByAccountNumber(CurrentClient, -1 * Amount, vec);

		
		return true;

	}

	return false;

}

bool Deposit(vector <stClient>& vec, stClient& CurrentClient) {

	loading("Deposit Loading ");

	clearScreen();

	printHeaderScreen(enMainMenuOption::enDeposit);

	int CounterToClearLines = 1;

	double Amount = readDoubleFromUser("Enter a postive Deposit Amount ? ");

	while (Amount <= 0) {

		CounterToClearLines += 2;
		Amount = readDoubleFromUser("\nEnter a postive Deposit Amount ? ");

	}

	clearLines(CounterToClearLines);

	if (confirmTransaction()) {

		updateBalanceToClientByAccountNumber(CurrentClient, Amount, vec);
		
		return true;

	}

	return false;

}

void CheckBalance(stClient& CurrentClient) {

	loading("Check Balance Loading ");

	clearScreen();

	printHeaderScreen(enMainMenuOption::enCheckBalance);

	setColor(2);
	cout << "\n\t\tYour Balance is " << CurrentClient.AccountBalance << endl;
	setColor(15);
	cout << "\n---------------------------------------------------" << endl;

}

void Logout() {

	setColor(6);
	cout << "\n=====================================\n";

	setColor(4);
	cout << "             LOGOUT\n";

	setColor(6);
	cout << "=====================================\n\n";

	setColor(15);
	cout << "You have been logged out successfully.\n";
	cout << "Thank you for using our ATM system.\n\n";

	setColor(6);
	cout << "=====================================\n";

	setColor(2);
	cout << "         Have a nice day!\n";

	setColor(6);
	cout << "=====================================\n";

	setColor(15);

}

void printMenuOption() {

	setColor(2);
	cout << "\t[1] Quick Withdraw. " << endl;
	setColor(3);
	cout << "\t[2] Normal Withdraw. " << endl;
	setColor(4);
	cout << "\t[3] Deposit. " << endl;
	setColor(5);
	cout << "\t[4] Check Account Balance. " << endl;
	setColor(6);
	cout << "\t[5] logout. " << endl;
	setColor(15);

}

int readUserChoice() {

	cout << "---------------------------------------------------" << endl;

	int Choice = readIntFromUser("Choose what do you want to do ? [1 to 5 ] ? ");

	cout << "---------------------------------------------------" << endl;

	loading("loading Your Choice"); 

	clearScreen();

	return Choice;

}

void GoingBackToMainMenu() {

	cout << "\n\nPress any key to go back main menue  ";
	Pause();
	clearScreen();
	loading("Going back to main menue");
	clearScreen();

}

void showTransactionStatue(const bool& success, const stClient& client) {

	if (success) {

		setColor(2);
		cout << "\n\nTransaction completed successfully, ";
		setColor(15);
		cout << "New Balance is : " << client.AccountBalance << endl;

	}
	else {

		setColor(4);
		cout << "\n\nTransaction failed. Please try again later." << endl;
		setColor(15);

	}

}

bool performMainMenuOption(vector <stClient>& vec, stClient& CurrentClient) {

	int Choice = readUserChoice();

	bool isSuccess = false;

	switch (Choice) {

	case 1:

		isSuccess = QuickWithdraw(vec, CurrentClient);

		if (CurrentClient.QuickWithdrawExit) {

			CurrentClient.QuickWithdrawExit = false;
			GoingBackToMainMenu();
			break;

		}

		showTransactionStatue(isSuccess, CurrentClient);

		GoingBackToMainMenu();

		break;

	case 2:

		isSuccess = NormalWithdraw(vec, CurrentClient);

		showTransactionStatue(isSuccess, CurrentClient);

		GoingBackToMainMenu();

		break;

	case 3:

		isSuccess = Deposit(vec, CurrentClient);

		showTransactionStatue(isSuccess, CurrentClient);

		GoingBackToMainMenu();

		break;

	case 4:

		CheckBalance(CurrentClient);

		GoingBackToMainMenu();

		break;

	case 5:

		loading("Exiting ");

		Logout();
		return false;

	default:
		clearScreen();
		setColor(4);
		cout << "\nFaild To Loading Choice, Try Again " << endl;
		setColor(15);
		Pause();
		GoingBackToMainMenu();
		break;

	}

	return true;


}

void MainMenu() {

	printHeaderScreen(enMainMenuOption::enMainMenu);

	printMenuOption();

}

void showMainMenu(vector <stClient>& vec, stClient &CurrentClient) {


	bool isRunning = true;

	while (isRunning) {

		clearScreen();

		MainMenu();

		isRunning = performMainMenuOption(vec, CurrentClient);

	}

}

void showWelcome(string name) {

	clearScreen();

	setColor(2);
	cout << "=====================================\n";

	setColor(3);
	cout << "        WELCOME TO ATM SYSTEM\n";

	setColor(2);
	cout << "=====================================\n\n";

	setColor(15);
	cout << "Hello, ";

	setColor(6);
	cout << name << "\n\n";

	setColor(15);
	cout << "We are happy to serve you today.\n\n";

	setColor(2);
	cout << "=====================================\n";

	setColor(15);

	Pause();

	loading("Loading your account");

	clearScreen();
}

void BlockMessage() {

	clearScreen();

	setColor(4);
	cout << "\n=====================================\n";
	cout << "           ACCOUNT LOCKED\n";
	cout << "=====================================\n\n";

	cout << "You have entered the wrong PIN 3 times.\n";
	cout << "For your security, access is blocked.\n\n";

	cout << "Please contact your bank or try later.\n\n";

	cout << "=====================================\n";
	setColor(15);
}

void LoginSuccess(vector <stClient>& vec, stClient CurrentClient) {

	clearScreen();
	setColor(2);
	loading("Login Success ");
	setColor(15);

	clearScreen();

	showWelcome(CurrentClient.Name);

	showMainMenu(vec, CurrentClient);

}

void Login() {

	stClient CurrentClient = stClient();

	printHeaderScreen(enMainMenuOption::enLogin);

	vector <stClient> ClientsDate = LoadClientDataFromFile(ClientsFile);

	string AccountNumber = readStringFromUser("Enter Account Number ? ");
	string Pincode = readStringFromUser("Enter Pin ? ");

	int Tries = 1;

	bool LodginFalied = !loadClientDate(AccountNumber, Pincode, CurrentClient, ClientsDate);

	while (LodginFalied && Tries != MAX_TRIES) {

		Tries++;

		clearScreen();

		printHeaderScreen(enMainMenuOption::enLogin);

		setColor(4);
		cout << "\nInvalid AccountNumber/Pincode ! , Attempts remaining: " << (MAX_TRIES - Tries) + 1 << "\n\n";
		setColor(15);


		AccountNumber = readStringFromUser("Enter Account Number ? ");
		Pincode = readStringFromUser("Enter Pin ? ");

		LodginFalied = !loadClientDate(AccountNumber, Pincode, CurrentClient, ClientsDate);


	}

	if (MAX_TRIES == Tries ) {
		BlockMessage();
		return;
	}

	if (!LodginFalied) {

		LoginSuccess(ClientsDate, CurrentClient);

	}


}

int main() {

	Login();

	Pause();

	return 0;
}