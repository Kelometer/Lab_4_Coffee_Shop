#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	string foodName;
	char itemCode;
	int itemQuantity;
	double unitPrice;
	bool isMember;

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
		<< "Item Quantity: " << itemQuantity << "\n"
		<< "Unit Price: " << right  << fixed << setprecision(2) << "$" << unitPrice << "\n" << left;
		if (isMember) 
		{
			cout << "Membership: No " << "\n";
		}
		else
		{
			cout << "Membership: Yes " << "\n";
		}
}