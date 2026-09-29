#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
	string cashierNotes;

	vector <char> itemCode = { 'A','B','C','D' };
	vector <char> itemSize = { 'S','M','L' };
	vector <string> itemName = { "Lemon Energizer","Cold Brew","Vanilla Latte","Iced Macchiato" };
	vector <double> itemPrice = { 4.50, 3.00, 4.00, 4.00 };

	char reqCode,reqSize,reqMembership;
	int reqQuantity;
	int itemIndex = 0,
		sizeIndex = 0;

	double discount = 0.1,
		sizeMedium = 1.00,
		sizeLarge = 2.00,
		totalPrice, unitPrice;

	bool isMember = false;

	int spacer = 22;				// aesthetic options
	string line(120, '-');

	// menu 
	cout << left << setw(spacer) << "Drink"
		<< setw(spacer) << "Small (S)"
		<< setw(spacer) << "Medium (M)"
		<< setw(spacer) << "Large (L)" << endl;


	for (int i = 0; i < 4; i++) {
		cout << left << itemCode[i] << setw(2) << "." << setw(spacer) << itemName[i]
			<< "$" << setw(spacer - 1) << fixed << setprecision(2) << itemPrice[i]
			<< "$" << setw(spacer - 1) << fixed << setprecision(2) << itemPrice[i] + sizeMedium
			<< "$" << setw(spacer - 1) << fixed << setprecision(2) << itemPrice[i] + sizeLarge
			<< endl;
	}

	cout << "\n" << left << setw(spacer) << "Item Code:";
	cin >> reqCode;
	cout << left << setw(spacer) << "Size:";
	cin >> reqSize;
	cout << left << setw(spacer) << "Amount:";
	cin >> reqQuantity;
	cout << left << setw(spacer) << "Store Member (Y/N):";
	cin >> reqMembership;
	cout << endl;

	if (reqMembership == 'Y' || reqMembership == 'y') {
		isMember = true;
	}
	// matches the reqCode char to a searchable index
	for (int i = 0; i < 4; i++) {
		if (itemCode[i] == reqCode) {
			itemIndex = i;
			break;
		}
	}
 // adjusts price based on reqSize
	switch (reqSize) {
	case 'S':
		totalPrice = unitPrice = itemPrice[itemIndex];
		sizeIndex = 0;
		break;
	case 'M':
		totalPrice = unitPrice = itemPrice[itemIndex] + sizeMedium;
		sizeIndex = 1;
		break;
	case 'L':
		totalPrice = unitPrice = itemPrice[itemIndex] + sizeLarge;
		sizeIndex = 2;
		break;
	default:
		cout << "Unknown Option Entered.";
		return(1);
	}

	if (isMember) {
		totalPrice *= (1 - discount);
	}

// multiplies the price by the reqQuantity
	totalPrice *= reqQuantity;

	cout << "\n" << "Receipt\n"<< line << "\n"
		<< left << setw(spacer) << "Item Name"
		<< setw(spacer) << "Item Size"
		<< setw(spacer) << "Quantity"
		<< setw(spacer) << "Unit Price"
		<< setw(spacer) << "Membership" 
		<< setw(spacer) << "Total\n" <<endl;

	cout << left << setw(spacer) << itemName[itemIndex]
		<< setw(spacer) << itemSize[sizeIndex]
		<< setw(spacer) << reqQuantity
		<< "$" << fixed << setprecision(2) << setw(spacer - 1) << unitPrice;

	if (isMember) {
		cout << setw(spacer) << "Yes";
	}
	else {
		cout << setw(spacer) << "No";
	}

	cout << "$" << fixed << setprecision(2) << setw(spacer - 1) << totalPrice << endl;

	cout << "\nEnter Cashier Notes: ";
	cin.ignore();
	getline(cin, cashierNotes);

	cout << "\n" << "Audit\n" << line << endl;

	cout << left << setw(spacer) << "Item Name"
		<< setw(spacer) << "Item Size"
		<< setw(spacer) << "Quantity"
		<< setw(spacer) << "Unit Price"
		<< setw(spacer) << "Membership"
		<< setw(spacer) << "Total\n" << endl;

	cout << left << setw(spacer) << itemName[itemIndex]
		<< setw(spacer) << itemSize[sizeIndex]
		<< setw(spacer) << reqQuantity
		<< "$" << fixed << setprecision(2) << setw(spacer - 1) << unitPrice;

	if (isMember) {
		cout << setw(spacer) << "Yes";
	}
	else {
		cout << setw(spacer) << "No";
	}

	cout << "$" << fixed << setprecision(2) << setw(spacer - 1) << totalPrice << endl;

	return 0;
}
