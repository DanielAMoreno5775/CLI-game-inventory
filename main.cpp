/*
This program prints a menu for the user, displays the contents of a file, and adds new lines to the file

Added functionality to update a pre-existing entry to increase quantity of that item
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>
using namespace std;

//function prototypes
char displayMenuAndGetInput();
void display_inventory();
void add_item();

int main() {
	char choice = ' ';
	bool shouldContinue = true;

	while (shouldContinue) {
		choice = displayMenuAndGetInput();

		//if the user entered q, quit the loop
		if (choice == 'q') {
			shouldContinue = false;
		}
		else if (choice == 'd') {
			display_inventory();
		}
		else if (choice == 'a') {
			add_item();
		}
	}

	return 0;
}

//this function will display the menu and return a corrected form of the user's input
char displayMenuAndGetInput() {
	string input;
	char choice;

	//clear the screen and then print the menu
	system("cls");
	cout << endl << "*******************************************************************" << endl << endl
		<< "Game Item Inventory" << endl << endl
		<< "*******************************************************************" << endl << endl;

	cout << "[d] Display all the inventory from file." << endl;
	cout << "[a] Append an item to the inventory file." << endl;
	cout << "[q] Quit and commit changes to file." << endl;

	//get the next character that the user inputs
	cout << "Choice (enter upper or lowercase letter option: ";
	getline(cin, input);
	choice = tolower(input[0]);

	while (choice != 'a' && choice != 'd' && choice != 'q') {
		//error message
		cout << endl << "That is not an option" << endl;
		system("pause");

		//clear the screen and then print the menu
		system("cls");
		cout << endl << "*******************************************************************" << endl << endl
			<< "Game Item Inventory" << endl << endl
			<< "*******************************************************************" << endl << endl;

		cout << "[d] Display all the inventory from file." << endl;
		cout << "[a] Append an item to the inventory file." << endl;
		cout << "[q] Quit and commit changes to file." << endl;

		//get the next character that the user inputs
		cout << "Choice (enter upper or lowercase letter option: ";
		getline(cin, input);
		choice = tolower(input[0]);
	}

	return choice;
}

void display_inventory() {
	//initialize variables
	ifstream dataFile;
	string column1, column2, column3;

	//open the file
	dataFile.open("gameinventory.txt", ios::_Nocreate);

	//clear the console window
	system("cls");

	if (dataFile) {
		//print lines as they are extracted from file
		while (dataFile >> column1 >> column2 >> column3) {
			cout << left;
			cout << setw(10) << column1 << setw(10) << column2 << setw(10) << column3 << endl;
		}
	}
	else {
		//print error message
		cout << "The file gameinventory.txt does not already exist." << endl;
	}

	//return to main menu
	cout << endl << "Press a key to return to main menu." << endl;
	dataFile.close();
	system("pause");
}

void add_item() {
	//initialize variables
	fstream tempFile;
	ifstream inputFile;
	ofstream outputFile;
	string name, cost, amount, column1, column2, column3;
	bool doesFileExist = false;
	bool updatedLine = false;

	//clear the console window
	system("cls");

	//test to determine whether gameinventory.txt exists and can be opened
	inputFile.open("gameinventory.txt", ios::_Nocreate);
	doesFileExist = inputFile.good();

	if (doesFileExist) {
		//open the file in append mode
		tempFile.open("gameinventory1.txt", ios::in | ios::out | ios::trunc);

		//get the user input
		cout << "Enter the name for this new item: ";
		getline(cin, name);
		cout << "Enter unit cost for this item: ";
		getline(cin, cost);
		cout << "Enter quantity in stock for this item: ";
		getline(cin, amount);

		//set all letters in the name to lowercase
		for (int i = 0; i < name.length(); i += 1) {
			name[i] = tolower(name[i]);
		}

		//print lines as they are extracted from file
		while (inputFile >> column1 >> column2 >> column3) {
			//if that item already exists in the file, increment the quantity of that item
			if (column1 == name && column2 == cost) {
				tempFile << name << "\t" << cost << "\t" << (stoi(column3) + stoi(amount)) << endl;
				updatedLine = true;
			}
			else {
				tempFile << column1 << "\t" << column2 << "\t" << column3 << endl;
			}
		}
		//if the user's input did not update a pre-existing line, write the new line to the bottom of the file
		if (!updatedLine) {
			tempFile << name << "\t" << cost << "\t" << amount << endl;
		}

		//open actual file to ouput to it and empty out what is already there
		outputFile.open("gameinventory.txt");

		//clear fail/eof bits and reset cursor back to start
		tempFile.clear();
		tempFile.seekg(0);

		//write content of tempFile to outputFile
		while (tempFile >> column1 >> column2 >> column3) {
			outputFile << column1 << "\t" << column2 << "\t" << column3 << endl;
		}

		//successfully added
		cout << "Item added to the inventory!" << endl;
	}
	else {
		//print error message
		cout << "The file gameinventory.txt does not already exist." << endl;
	}

	//close and delete the temporary file from earlier
	tempFile.close();
	remove("gameinventory1.txt");
	inputFile.close();
	outputFile.close();

	//return to main menu
	cout << endl << "Press a key to return to main menu." << endl;
	system("pause");
}