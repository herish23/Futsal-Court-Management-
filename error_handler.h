#include <iostream>
#ifndef ERROR_HANDLER
#define ERROR_HANDLER
using namespace std;
#pragma once

class error_handler
{



public:
	void invalid_option();
	void mainmenu();
	void server_down();
	void invalid_details(int);
	void exit_msg();
	void directory(int);
	

};


//handles error on invalid input set-up in default: in Switch Statements
void error_handler::invalid_option()
{

	cout << "Invalid option\n";	
	system("PAUSE");
	
}

void error_handler::mainmenu()
{
	cout << "Logging out";//fix main to here

	
}


void error_handler::server_down()
{

	cout << "Server down"; //
}

void error_handler::invalid_details(int num)
{	
	/// if (!isdigit(admin.phone[i]) || admin.ic.length() < 12 || admin.phone.length() > 12) 
	if (num == 1)
	{
		cout << "Invalid IC number\n";
	}

	// if (!isdigit(admin.phone[i]) || admin.phone.length() < 10 || admin.phone.length() > 11) 
	else if (num == 2)
	{
		cout << "Invalid phone number\n";

	}

	// if id entered by user and id in SQl is same (==) 
	else if (num == 3)
	{
		cout << "Id has been taken\n";
	}


	// if no data mathches in the SQL 
	else if (num == 4)
	{
		cout << "No data available\n";
				
	}

	// password <8 || >8 
	else if (num == 5)
	{
		cout << "Invalid password length" << endl;
	}


	else if (num == 6)
	{
		cout << "No existing data\n";
	}


	// data wasnt deleted from system
	else if (num == 7)
	{
		cout << "\nNo data was deleted\n";
	}

	else if (num == 8)
	{
		cout << "\nInvalid time has been chosen\n";
	}
	
}
void error_handler::exit_msg()
{
	system("PAUSE");
	cout << "\nExiting program";
}


void error_handler::directory(int dir)
{
	if (dir == 1)
	{
		cout << "\nEnter 1->4 to choose :";
	}
	else if (dir == 2)
	{
		cout << "\nEnter 1->5 to choose :";
	}

	else if (dir == 3)
	{
		cout << "\nEnter 1->3 to choose :";
	}
	else if (dir == 4)
	{
		cout << "\nEnter 1->2 to choose :";
	}
}



#endif
