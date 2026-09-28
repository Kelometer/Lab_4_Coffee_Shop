#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main(){
	string foodName;
	string cashierNotes;
	char itemCode;
	int itemQuantity;
	double discount = 0.1;
	double unitPrice;
	bool isMember;

	cout << "Enter in a food name: " << endl;
	getline(cin, foodName);
	cout << "Enter in an item code (one character only): " << endl;
	cin >> itemCode;
	cout << "Enter in a quantity: " << endl;
	cin >> itemQuantity;
	cout << "Enter a price for the item: " << endl;
	cin >> unitPrice;
	cout << "Membership Active: (1/0)" << endl;
	cin >> isMember;
	
	cout << "\n" << "Receipt\n--------------------------------------------------------\n"
		<< left << setw(15) <<"Name"
		<< setw(15) << "Item Code"
		<< setw(15) << "Quantity"
		<< setw(15) << "Unit Price"
		<< setw(15) << "Membership\n" << endl;

	cout << right << foodName
		<< setw(15) << itemCode
		<< setw(15) << itemQuantity;

	if (isMember){
		cout << right << setw(14) << "$" << fixed << setprecision(2) << unitPrice * (1 - discount)
			 << right << setw(15) << "Yes\n";
	}

	else {
		cout << right << "$" << setw(14) << fixed << setprecision(2) << unitPrice
			 << right << setw(15) << "No\n";
	}

	cout << "\nEnter Cashier Notes: ";
	cin.ignore();
	getline(cin, cashierNotes);
	cout << "\n" << left << "Audit\n--------------------------------------------------------" << endl;

	cout << left << setw(15) << "Name"
		<< setw(15) << "Item"
		<< setw(15) << "Quantity"
		<< setw(15) << "Unit Price"
		<< setw(15) << "Discount\n" << endl;

	cout << left << setw(15) << foodName
		<< setw(15) << itemCode
		<< setw(15) << itemQuantity
		<< "$" << setw(14) << fixed << setprecision(2) << unitPrice
		<< setw(15) << (isMember ? "Yes" : "No") << "\n";

	return 0;
}
