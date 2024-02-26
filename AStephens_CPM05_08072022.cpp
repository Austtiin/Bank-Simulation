#include <iostream>
#include <fstream>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
using namespace std;

// deques to hold the names
deque<string> firstNames;
deque<string> lastNames;

// class definition for customers
class Customer
{
	public:
		Customer(string, string, int);
		void displayInfo();
		string first, last;
		int arrivalTime, leavingTime, serviceTime, serviceType;
		double startingBalance, endingBalance;
		// generate random numbers for the starting balance and ending balance based on the service type
		// generate the float coefficient for the decimal numbers
		double decimals = (double)rand() / RAND_MAX;
		double deposit, withdrawal; // declares variables for deposits and withdrawals	
};

// customer constructor
Customer::Customer(string f, string l, int a)
{
	first = f;
	last = l;
	arrivalTime = a;
	
	// generate random value for service type
	serviceType = 1 + rand() % 4; // between 1 and 4 (for the type of service)
	serviceTime = 2 + rand() % 6; // between 2 and 6 minutes
	
	// leaving time
	leavingTime = arrivalTime + serviceTime;
	
	// display info function
	displayInfo();
}

// display the information about each customer
void Customer::displayInfo()
{
	cout << "Name: ";
	cout << first << " " << last;
	if((first.length() + last.length()) >= 15) 
		cout << "\t";
	else if((first.length() + last.length()) >= 7)
		cout << "\t\t";
	else
		cout << "\t\t\t";
		
	cout << endl;
	cout << "Activity: ";	
	
	switch(serviceType)
	{
		case 1: cout << "open account";
				// set the starting balance to 0
				startingBalance = 0.00;
				// set the ending balance between 1 and $10000
				endingBalance = 1 + decimals * (10000);
			break;
		case 2: cout << "deposit money";
				// set the starting balance between 1 and $10000
				startingBalance = 0 + decimals * (10000);
				deposit = 1 + decimals * (10000);
				// set the ending balance 
				endingBalance = startingBalance + deposit;
			break;
		case 3: cout << "close account";
				// set the starting balance between 1 and $10000
				startingBalance = 0 + decimals * (10000);
				// set the ending balance to 0
				endingBalance = 0.00;
			break;
		case 4: cout << "withdraw money";
				// set the starting balance between 1 and $10000
				startingBalance = 0 + decimals * (10000);
				withdrawal = 1 + decimals * (startingBalance);
				// set the ending balance 
				endingBalance = startingBalance - withdrawal;
			break;
		default: cout << "something else";
			break;	
	}
	cout << endl;
	cout << "Arrival Time: ";
	if(arrivalTime < 60)
	{
		if(arrivalTime < 10)
			cout << "10:0" << arrivalTime << " AM" << endl;
		else
			cout << "10:" << arrivalTime << " AM" << endl;  
	}
	else if(arrivalTime >= 60 and arrivalTime < 120)
	{
		if(arrivalTime < 70)
			cout << "11:0" << (arrivalTime - 60) << " AM" << endl;
		else
			cout << "11:" << (arrivalTime - 60) << " AM" << endl;
	}
	else
	{
		if(arrivalTime < 130)
			cout << "12:0" << (arrivalTime - 120) << " PM" << endl;
		else if(arrivalTime < 180)
			cout << "12:" << (arrivalTime - 120) << " PM" << endl;
		else
			cout << "1:0" << (arrivalTime - 180) << " PM" << endl;
	}
	
	cout << "Service Time: " << serviceTime << " minutes \n";
	
	cout << "Leaving Time: ";
	if(leavingTime < 60)
	{
		if(leavingTime < 10)
			cout << "10:0" << leavingTime << " AM" << endl;
		else
			cout << "10:" << leavingTime << " AM" << endl;  
	}
	else if(leavingTime >= 60 and leavingTime < 120)
	{
		if(leavingTime < 70)
			cout << "11:0" << (leavingTime - 60) << " AM" << endl;
		else
			cout << "11:" << (leavingTime - 60) << " AM" << endl;
	}
	else
	{
		if(leavingTime < 130)
			cout << "12:0" << (leavingTime - 120) << " PM" << endl;
		else if(leavingTime < 180)
			cout << "12:" << (leavingTime - 120) << " PM" << endl;
		else if(leavingTime < 190)
			cout << "1:0" << (leavingTime - 180) << " PM" << endl;
		else
			cout << "1:" << (leavingTime - 180) << " PM" << endl;
	}
	
	if(serviceType != 1)
		cout << "Starting Balance: $" << startingBalance << "\t Ending Balance: $" << endingBalance << "\n\n";
	else
		cout << "Starting Balance: $" << startingBalance << "\t\t Ending Balance: $" << endingBalance << "\n\n";
		
	cout << endl;
}

// class definition for tellers
class Teller
{
	public:
		Teller(string, string);
		void displayTellerInfo();
		string firstName, lastName;
		deque<Customer> customers;
		
};

Teller::Teller(string f, string l)
{
	firstName = f;
	lastName = l;
	
	displayTellerInfo();
}

void Teller::displayTellerInfo()
{
	cout << "Teller Name: " << firstName << " " << lastName << endl << endl;
}

// function that loads the names into the deques
void loadNames()
{
	// names
	ifstream file;
	file.open("names.txt");		
	
	// strings to hold the first and last names
	string firstName, lastName;
	
	srand(time(0));
	int random;
	
	// loads the names into the name deques for selection
	while(file >> firstName)
	{
		random = 1 + rand() % 4;
		
		file >> lastName;
		
		if(random == 1)
		{
			firstNames.push_front(firstName);
			lastNames.push_front(lastName);
		}
		else if(random == 2)
		{
			firstNames.push_front(firstName);
			lastNames.push_back(lastName);
		}
		else if(random == 3)
		{
			firstNames.push_back(firstName);
			lastNames.push_front(lastName);
		}
		else
		{
			firstNames.push_back(firstName);
			lastNames.push_back(lastName);
		}	
	}
}

int main()
{
	srand(time(0));
	cout << setprecision(2) << showpoint << fixed;
	
	// load the names into the deques
	loadNames();
	
	int rand1, rand2, rand3, rand4, minute = 0;	
	
	string firstName, lastName;
	
	deque<Teller> tellers;
	deque<Teller> customers;
	do
	{
		if(tellers.size() < 3)
		{
			// if this is the first teller, add a teller
			if(tellers.size() == 0)
			{
				cout << "Teller Added: " << endl << endl;
				rand1 = 1 + rand() % (firstNames.size() - 1);
				rand2 = 1 + rand() % (lastNames.size() - 1);
	
				firstName = firstNames[rand1];
				lastName = lastNames[rand2];
			
				Teller T(firstName, lastName);
				tellers.push_back(T);
			}
			else if(customers.size() < 4 && tellers.size() > 2)
			{
				cout << "Teller Added: " << endl << endl;
				rand1 = 1 + rand() % (firstNames.size() - 1);
				rand2 = 1 + rand() % (lastNames.size() - 1);
	
				firstName = firstNames[rand1];
				lastName = lastNames[rand2];
			
				Teller T(firstName, lastName);
				tellers.push_back(T);
			}
			else if(customers.size() < 7 && tellers.size() > 3)
			{
				cout << "Teller Added: " << endl << endl;
				rand1 = 1 + rand() % (firstNames.size() - 1);
				rand2 = 1 + rand() % (lastNames.size() - 1);
	
				firstName = firstNames[rand1];
				lastName = lastNames[rand2];
			
				Teller T(firstName, lastName);
				tellers.push_back(T);
			}
			else if(customers.size() < 8 && tellers.size() > 2)
			{
				cout << "Teller Removed " << endl << endl;
				tellers.pop_front();
			}

			else if(customers.size() < 4 && tellers.size() > 1)
			{
				cout << "Teller Removed " << endl << endl;
				tellers.pop_front();
			}
			else
			{
				for(int t = 0; t < tellers.size(); t++)
				{
					if(tellers[t].customers.size() < 4)
					{
						rand3 = 1 + rand() % (firstNames.size() - 1);
						rand4 = 1 + rand() % (lastNames.size() - 1);
						
						Customer c(firstNames[rand3], lastNames[rand4], minute);
						tellers[t].customers.push_back(c);
						minute++;
					}
					else
					{
						minute += tellers[t].customers[0].serviceTime;
						tellers[t].customers.pop_front();
					}

				}

			}
			cout << customers.size() << ":  Line Length\n\n";
		}	
		
		minute++;
		
	}while(minute <= 180);
		
}
