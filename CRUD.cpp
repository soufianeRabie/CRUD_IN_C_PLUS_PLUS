#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>


using namespace std;


enum enCrudActions { ShowClient = 1, AddClient = 2, DeleteClient = 3, UpdateClient = 4, FindClient = 5, Transaction = 6, Exit = 7 };
enum enTransaction {Deposit = 1 , Withdraw =2 , TotalBalance = 3 , Back = 4};

struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkToDelete;

};

string ClientFile = "ClientFile.txt";

void HandleUserActions(); // Function Definition 

// Function to Split String and put it in vector 
vector <string> SplitString(string Line, string Separator)
{
	string sWord;
	int pos;
	vector <string> vString;

	while ((pos = Line.find(Separator)) != string::npos)
	{
		sWord = Line.substr(0, pos);
		vString.push_back(sWord);

		Line.erase(0, pos + Separator.length()); //Delete Word and Separator from Line 
	}

	if (Line != "")
	{
		vString.push_back(Line);
	}

	return vString;
}

//function to convert informations that come as line to struct Client 

sClient ConvertFromOneLineToRecord(string Line)
{
	sClient Client;
	vector <string> vString = SplitString(Line, "/##/");//Split Data ;

	Client.AccountNumber = vString[0];
	Client.PinCode = vString[1];
	Client.Name = vString[2];
	Client.Phone = vString[3];
	Client.AccountBalance = stod(vString[4]);

	return Client;
}


//function to get clients From file 
vector <sClient> getClients(string FileName)
{

	fstream MyFile;

	MyFile.open(FileName, ios::in);
	vector <sClient> Clients;

	if (MyFile.is_open())
	{
		string Line;
		sClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertFromOneLineToRecord(Line);
			Clients.push_back(Client);

		}

		MyFile.close();

	}

	return Clients;

}

//boolean function to check if Client exist or no 
bool IsClientExist(string AccountNumber, string FileName, sClient& Client)
{
	fstream MyFile;

	vector <sClient> vClients = getClients(FileName);

	for (sClient& C : vClients)
	{
		if (AccountNumber == C.AccountNumber)
		{
			Client = C; // Assign the found client information to the Client parameter By reference 
			return true;
		}
	}

	return false;

}


//Read Client Info ;
sClient ReadClientInfo()
{

	string AccountNumbr;
	sClient Client;

	cout << "\nAdding New Client: \n";

	cout << "\nEnter Account Number? ";
	getline(cin >> ws, AccountNumbr);

	//check if Client Already exist 
	while (IsClientExist(AccountNumbr, ClientFile, Client))
	{
		cout << "\n the client already exist ,please enter a ohter account number: ";
		getline(cin, AccountNumbr);

	}

	Client.AccountNumber = AccountNumbr;

	cout << "\n Pin Code: ";
	getline(cin, Client.PinCode);

	cout << "\nClient Name: ";
	getline(cin, Client.Name);

	cout << "\nClient Phone: ";
	getline(cin, Client.Phone);

	cout << "\nClient Account Balance: ";
	cin >> Client.AccountBalance;


	return Client;


}


//Procedure for Show Menu Screen
void MainMenuScreen()
{
	system("cls");
	cout << "|=====================================================|\n";
	cout << "|                   Main Menue Screen                 |\n";
	cout << "|=====================================================|\n";
	cout << "|               [1] Show Client Liste.                |\n";
	cout << "|               [2] Add New Client                    |\n";
	cout << "|               [3] Delete Client.                    |\n";
	cout << "|               [4] Update Clientn Info.              |\n";
	cout << "|               [5] Find Client.                      |\n";
	cout << "|               [6] Transaction.                      |\n";
	cout << "|               [7] Exit.                             |\n";
	cout << "|=====================================================|\n";

}

//boolean function to check user answer status 
bool WrongChoice(int Answer , int From = 1 , int To = 6) {
	return Answer < From || Answer > To;
}

// read user choice 
int UserChoice(int From = 1 , int To = 6)
{

	int Answer;

	do {
		cout << "\nWhat do you want to do? ";

		// Check if the input is an integer
		if (!(cin >> Answer))
		{
			cout << "Please enter a valid integer!" << endl;
			cin.clear();

			cin.ignore(numeric_limits < streamsize>::max(), '\n');
		}
		else if (WrongChoice(Answer)) { //check if the choice is invalid choice 
			cout << "\nInvalid choice! Please enter a valid choice." << endl;
		}

	} while (WrongChoice(Answer));

	cout << endl;
	return Answer;

}


// Print Client Information 
void PrintClientRecord(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;

}

// procedure for return to home 
void GoBackToHome()
{
	cout << "\n\npress any key to back...";
	system("pause>0");
	HandleUserActions();

}

void ShowClientsScreen(vector <sClient> vClients)
{
	cout << "-----------------------------------------------------\n";
	cout << "-----------------------------------------------------\n";
	cout << "                   Show Clients Screen                 \n";
	cout << "-----------------------------------------------------\n";
	cout << "-----------------------------------------------------\n";
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s)."; // number of clients 
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

void PrintAllClients(vector <sClient> vClients)
{
	system("cls");
	ShowClientsScreen(vClients);
	
	//Print Clients Information
	for (sClient Client : vClients)
	{
		PrintClientRecord(Client);
		cout << endl;
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	GoBackToHome();

}

// Print info for one client
void PrintClientInfo(sClient Client)
{
	cout << "\nthe following are the client details: \n";
	cout << "------------------------------------------------------------\n";
	cout << "Account Number   : " << Client.AccountNumber;
	cout << "\nPin Code         : " << Client.PinCode;
	cout << "\nName             : " << Client.Name;
	cout << "\nPhone            : " << Client.Phone;
	cout << "\nAccount Balance  : " << Client.AccountBalance;
	cout << "\n------------------------------------------------------------" << endl;

}

// Convert client information from a structured format(sClient)  to a single line string 
//Using seprator between fields 
string ConvertFromRecordToOneLine(sClient Client, string Separator)
{
	string Line;

	Line += Client.AccountNumber + Separator;
	Line += Client.PinCode + Separator;
	Line += Client.Name + Separator;
	Line += Client.Phone + Separator;
	Line += to_string(Client.AccountBalance);

	return Line;
}


// Display Add Client Screen 
void AddClientScreen()
{
	system("cls");
	cout << "|====================================================|\n";
	cout << "|                  Add Clients Screen                |\n";
	cout << "|====================================================|\n";
}
// Adds new Clients information to the file 
void AddClientToFile(string FileName)
{
	AddClientScreen();
	fstream MyFile;
	char Answer = 'y';

	MyFile.open(FileName, ios::app); // mode append

	// check if the file open successfly 
	if (MyFile.is_open())
	{
		string Line;
		sClient Client;

		vector <sClient> Clients = getClients(FileName);// get existing clients from the file 

		// Continue adding Clients as long as the user wants to 
		while (toupper(Answer) == 'Y')
		{
			AddClientScreen();
			Client = ReadClientInfo(); // Read Client Information 
			Line = ConvertFromRecordToOneLine(Client, "/##/");

			MyFile << Line << endl; // write the line to the file 

			cout << "\nthe client added successfly!\n";
			cout << "\nDo you want t add more client? "; // ask the user if they add more client 
			cin >> Answer;

		}

		MyFile.close(); // close the file

	}

	GoBackToHome(); // Go  back to home page 
}


// Read information for update client
sClient ReadClientForUpdate()
{
	sClient NewClient;

	cout << "\n Pin Code: ";
	getline(cin >> ws, NewClient.PinCode);

	cout << "\nClient Name: ";
	getline(cin, NewClient.Name);

	cout << "\nClient Phone: ";
	getline(cin, NewClient.Phone);

	cout << "\nClient Account Balance: ";
	cin >> NewClient.AccountBalance;


	return NewClient;
}


// Edit client information 
vector <sClient>  EditClient(vector <sClient>& vClients, string ClientAccoutNumber)
{
	sClient NewClient = ReadClientForUpdate();

	for (int i = 0; i < vClients.size(); i++)
	{
		// update client info except Account Number (id)
		if (vClients[i].AccountNumber == ClientAccoutNumber)
		{
			vClients[i].PinCode = NewClient.PinCode;
			vClients[i].Name = NewClient.Name;
			vClients[i].Phone = NewClient.Phone;
			vClients[i].AccountBalance = NewClient.AccountBalance;
		}

	}

	return vClients;
}

// Save Client info when updated succssefly 
void SaveClientsForEdit(vector <sClient>& vclients, string FileName)
{

	fstream MyFile;

	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		string Line;
		for (sClient& C : vclients)
		{
			Line = ConvertFromRecordToOneLine(C, "/##/");

			MyFile << Line << endl;
		}

		MyFile.close();
	}

}

// Update Client info operation 
void UpdateClientFromFile(string FileName)
{
	system("cls");

	string ClientAccountNumber;
	sClient Client;
	vector <sClient> vClients = getClients(FileName); 

	system("cls");
	cout << "====================================================\n";
	cout << "|                   Edit Client Screen              |\n";
	cout << "====================================================\n";

	// Prompt the user to enter client number for editing
	cout << "\n enter a Client Number? ";
	cin >> ClientAccountNumber;

	 // check if the user exist before continue the update operation 
	if (IsClientExist(ClientAccountNumber, FileName, Client))
	{
		char ConfirmationUpdateClient = 'Y';
		PrintClientInfo(Client); // Display client info on the screen 

		cout << "\n\n Are you sure for update this client? Y/N ?"; // ask the user to confirm the update operation 
		cin >> ConfirmationUpdateClient;

		// check if the user confirmed the update
		if (toupper(ConfirmationUpdateClient) == 'Y')
		{
			EditClient(vClients, ClientAccountNumber);
			SaveClientsForEdit(vClients, FileName); // save the edited client infromation back to the file

			cout << "\nthe client edited successfly :)\n";
		}
		else
		{
			cout << "\nthe client add operation has been cancelled!\n";
		}
	}
	else
	{
		// Inform the user that the client with the specifed number was not found 
		cout << "the Client With [" << ClientAccountNumber << "] Not Found!";
	}
	//navigate back to the home screen 
	GoBackToHome();

}

// Marks a client for deletion
void MarkClientForDelete(vector <sClient>& vClients, string AccountNumber)
{

	for (sClient& C : vClients)
	{
		// check if the current account number matches the specifed account number
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkToDelete = true; // Mark client form deletion by reference
		}

	}

}

void PerformTransaction(); // Declaration for the TransactionMoney function

// Save Client Info In Delete Operation 
void SaveClientForDelete(string Filename, vector <sClient> vClients)
{

	fstream MyFile;

	MyFile.open(Filename, ios::out);
	if (MyFile.is_open())
	{
		sClient Client;
		string Line;

		for (sClient& C : vClients)

			if (C.MarkToDelete != true)
			{
				Line = ConvertFromRecordToOneLine(C, "/##/");

				MyFile << Line << endl;
			}

		MyFile.close();

	}

}

// Delete Client Operation 
void DeleteClientFormFile(string FileName)
{

	system("cls");
	string ClientAccountNumber;
	sClient Client;
	vector <sClient> vClients = getClients(FileName);

	// show header Delete Client Screen
	system("cls");
	cout << "====================================================\n";
	cout << "|                   Delete Client Screen            |\n";
	cout << "====================================================\n";

	cout << "\nenter Client Number: ";
	cin >> ClientAccountNumber;

	// Delete Client if exist 
	if (IsClientExist(ClientAccountNumber, FileName, Client))
	{
		char ConfirmationDelteClient = 'Y';

		PrintClientInfo(Client);
		// ask the user to confirm the Delete Operation
		cout << "\nAre you sure for delete this client? Y/N ?";
		cin >> ConfirmationDelteClient; // Read user answer 

		//check if the user confirmed the delete 
		if (toupper(ConfirmationDelteClient) == 'Y')
		{
			MarkClientForDelete(vClients, ClientAccountNumber); // Mark Client ready for delete
			SaveClientForDelete(FileName, vClients); // Delete Client From File 
			cout << "\nthe Client Deleted successfly!\n";
		}
		else
		{
			cout << "\nthe client Deleted operation has been cancelled! \n";
		}


	}
	else
	{
		// Inform the user that the client with specifed number was not found 
		cout << "\nthe Client with [" << ClientAccountNumber << "] Account Number not found! ";
	}

	GoBackToHome();
}

// Find Client Opertion 
void FindClientFromClient(string FileName)
{
	system("cls");
	vector <sClient> vClients = getClients(FileName);
	sClient Client;
	string ClientAccountNumber;

	system("cls");
	cout << "====================================================\n";
	cout << "|                   Find Client Screen              |\n";
	cout << "====================================================\n";

	cout << "Please enter an Account Number: ";
	cin >> ClientAccountNumber;

	// check if the use with specifed number exist in the file 
	if (IsClientExist(ClientAccountNumber, ClientFile, Client))
	{
		// Print the client information 
		PrintClientInfo(Client);
	}
	else
	{
		// Inform the user the client with specifed number was not found 
		cout << "the Client with [" << ClientAccountNumber << "] Account Number not found! ";
	}

	GoBackToHome();
}

// End the program screen 
void EndTheProgram()
{
	system("cls");
	cout << "-----------------------------------------------------\n";
	cout << "-----------------------------------------------------\n";
	cout << "              the program end thank you :)          \n";
	cout << "-----------------------------------------------------\n";
	cout << "-----------------------------------------------------\n";

	cout << endl;
}

// Procedure to navigat back to TransactionMenu Screen
void GoBackToTransactionMenu()
{

	cout << "\npress any key to back...";
	system("pause>0");
	PerformTransaction();

}

// Transaction Menu Screen 
void TransactionMenuScreen()
{
	system("cls");
	cout << "=====================================================\n";
	cout << "              Transaction Screen                      \n\n";
	cout << "=====================================================\n";
	cout << "                  [1] Deposit                         \n";
	cout << "                  [2] Withraw                         \n";
	cout << "                  [3] Total Balance                   \n";
	cout << "                  [4] Exit                         \n";
	cout << "=====================================================\n\n";

}

// Read the amount of the money be to deposited from user
double ReadMoneyToDeposit()
{
	double BalanceToDeposit;
	cout << "\nPlease enter how much do you want to deposit: ";
	cin >> BalanceToDeposit;

	return BalanceToDeposit;
}

// Read the amount of the money be to withdrawn from the user
double ReadMoneyToWithrawal()
{
	double BalanceoWithraw;
	cout << "\nPlease enter how much do you want to Withraw: ";
	cin >> BalanceoWithraw;

	return BalanceoWithraw;
}

// Deposit the balance to the account with the matchig account number
void DeposInAccount(vector <sClient> &Clients , string AccountNumber ,double BalanceToDeposit)
{
	
	for (sClient& Client : Clients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			Client.AccountBalance = Client.AccountBalance + BalanceToDeposit;
		}
	}
}

// Withraw the balance to the account with the matchig account number
void WithDrawInAccount(vector <sClient>& Clients, string AccountNumber , double BalanceToWithraw)
{

	for (sClient& Client : Clients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			Client.AccountBalance = Client.AccountBalance - BalanceToWithraw;
		}
	}
}

// Save the client data (deposit and withdraw)
void SaveClientData(vector <sClient> vClients, string FileName)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out); // mode append

	if (MyFile.is_open())
	{
		string Line;

			for (sClient& C : vClients)
			{
					Line = ConvertFromRecordToOneLine(C, "/##/");

					MyFile << Line << endl;
			}

		MyFile.close();
	}

}

// Deposit money into the account 
void DepositMoney()
{
	system("cls");
	cout << "=====================================================\n";
	cout << "              Deposit Screen                         \n";
	cout << "=====================================================\n";
	string AccountNumber;
	vector <sClient> vClients = getClients(ClientFile);
	sClient Client;
	char Answer;

	do
	{
		cout << "Please enter account number: ";
		cin >> AccountNumber;

	} while (!(IsClientExist(AccountNumber, ClientFile, Client))); // check if the user Exist 

		PrintClientInfo(Client);
		double BalanceToDeposit = ReadMoneyToDeposit();

		// ask user to confirm the deposit operation
		cout << "\nAre you sure for deposit for this account Y/N ? ";
		cin >> Answer;

		// Complete the deposit process
		if (toupper(Answer) == 'Y')
		{
			DeposInAccount(vClients, AccountNumber , BalanceToDeposit);
			SaveClientData(vClients, ClientFile);
			cout << "\nthe Deposit added successfly!\n";
		}
		else
		{
			// Inform the user the deposit operation has been cancelled
			cout << "\n Your deposit has been cancelled\n";
		}
		
		GoBackToTransactionMenu();
}

// Withdraw Money from the account 
void WihtDrawMoney()
{
	system("cls");
	cout << "=====================================================\n";
	cout << "|              Withraw Screen                        |\n";
	cout << "=====================================================\n";
	string AccountNumber;
	vector <sClient> vClients = getClients(ClientFile);
	sClient Client;
	char Answer = 'Y';

	do
	{
		cout << "Please enter account number: ";
		cin >> AccountNumber;
	} while (!(IsClientExist(AccountNumber, ClientFile, Client))); // chekc if the exist 
	

	PrintClientInfo(Client); // Print Client info 
	double BalanceToWithraw = ReadMoneyToDeposit();// Read the amount of money to be withdrawal from the user 

	// ask the use to confirm the withdraw operation
	cout << "\nAre you sure for withdraw for this account Y/N ? ";
	cin >> Answer;

	// check if the user confirmed the withdrawal
	if (toupper(Answer) == 'Y')
	{
		// Complete the withdraw process
		WithDrawInAccount(vClients, AccountNumber , BalanceToWithraw);
		SaveClientData(vClients, ClientFile);
		cout << "\nthe Wihtraw Done successfly!\n";
	}
	else
	{
		// Inform the user the withdraw operation has been cancelled
		cout << "\n Your deposit has been cancelled\n";
	}

	GoBackToTransactionMenu();
}

// Display Total Balance of the account

void DisplayTotalBalance()
{
	system("cls");
	cout << "=====================================================\n";
	cout << "|             Total Balance Screen                   |\n";
	cout << "=====================================================\n";

	string AccountNumber;

	sClient Client;
	do
	{
		// ask user to prompt the user account balance
		cout << "Please enter account number: ";
		cin >> AccountNumber;
	} while (!(IsClientExist(AccountNumber, ClientFile, Client)));// check if the user with account number exist 

	cout << "Total Balance: " << Client.AccountBalance; 

	GoBackToTransactionMenu();

}

// Initiates the transaction process , allowing the user choice between deposit , withdraw  and Display Total Balance
void PerformTransaction()
{
	TransactionMenuScreen();

	 int Answer = UserChoice( 1 , 4);
	 enTransaction UserAnswer = (enTransaction)Answer;

	 switch (UserAnswer)
	 {
	 case enTransaction::Deposit:
		 DepositMoney();
		 break;
		
	 case enTransaction::Withdraw :
		 WihtDrawMoney();
		 break;

	 case enTransaction::TotalBalance:
		 DisplayTotalBalance();
	 case enTransaction::Back:
		 HandleUserActions();
	 }

}

// Handle the user actions and initiates the appropriate process based on user input
void HandleUserActions()
{
	
	MainMenuScreen();
	int Answer = UserChoice();

	vector <sClient> vClients = getClients(ClientFile);

	switch (Answer)
	{
	case enCrudActions::ShowClient:

		PrintAllClients(vClients);

		break;

	case  enCrudActions::AddClient:

		AddClientToFile(ClientFile);

		break;
	case enCrudActions::UpdateClient:

		UpdateClientFromFile(ClientFile);

		break;

	case enCrudActions::DeleteClient:

		DeleteClientFormFile(ClientFile);
	
		case enCrudActions::FindClient:

			FindClientFromClient(ClientFile);

		break;

		case enCrudActions::Transaction:
			PerformTransaction();
			break;
		case enCrudActions::Exit:
			EndTheProgram();
		break;
	}

}


int main()
{
	// Call the function to handle user actions and manage programe flow
	HandleUserActions();

}