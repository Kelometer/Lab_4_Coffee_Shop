#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	string foodName;
	char itemCode;
	int itemQuantity;
	double discount = 0.1;
	double unitPrice;
	bool isMember;
	string cashierNotes;

	cout << "Enter in a food name: " << endl;
	cin >> foodName;
	cout << "Enter in an item code (one character only): " << endl;
	cin >> itemCode;
	cout << "Enter in a quantity: " << endl;
	cin >> itemQuantity;
	cout << "Enter a price for the item: " << endl;
	cin >> unitPrice;
	cout << "Is the user a member or not? (1/0)" << endl;
	cin >> isMember;

	cout << "\n" << setw(10) << left << "Receipt\n ------------ \n"
		<< "Name: " << foodName << "\n"
		<< "Item Code: " << itemCode << "\n"
		<< "Item Quantity: " << itemQuantity << "\n";
	if (isMember) 
	{
		cout << "Membership: Yes " << "\n";
		unitPrice = unitPrice * (1 - discount);
	}
	else
	{
		cout << "Membership: No " << "\n";
	}
	cout << "Unit Price: " << right << fixed << setprecision(2) << "$" << unitPrice << "\n";
	
	cout << "\n"
	    << "Enter Cashier Notes: ";
	cin >> cashierNotes;
	
	cout << "\n" << setw(10) << left << "Audit\n ------------ \n"
		<< "Name: " << foodName << "\n"
		<< "Item Code: " << itemCode << "\n"
		<< "Item Quantity: " << itemQuantity << "\n"
		<< "Unit Price: " << right << fixed << setprecision(2) << "$" << unitPrice << "\n" << left
		<< "Discount: " << "$" << discount;
}
