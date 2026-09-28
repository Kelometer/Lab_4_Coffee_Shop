#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
	string foodName,
		cashierNotes,
		itemSize;
	int itemCode,
		itemQuantity;
	double discount = 0.1,
		unitPrice;
	bool isMember;
	int spacer = 20;
	// item options
	string item_one = "A. Lemon Energizer",
		item_two = "B. Cold Brew",
		item_three = "C. Vanilla Latte",
		item_four = "D. Iced Macchiato";

	double price_one = 4.50,
		price_two = 3.00,
		price_three = 4.00,
		price_four = 4.00;

	double med_size = 1.00,
		large_size = 2.00;
	// tax options
	double arkansas = 0.065,
		faulkner = 0.05,
		conway = 0.02125;

	cout << left << setw(spacer) << "Drink"
		<< setw(spacer) << "Small"
		<< setw(spacer) << "Medium"
		<< setw(spacer) << "Large\n" << endl;

	cout << left << setw(spacer) << item_one
		<< setw(spacer) << fixed << setprecision(2) << price_one
		<< setw(spacer) << fixed << setprecision(2) << price_one + med_size
		<< setw(spacer) << fixed << setprecision(2) << price_one + large_size
		<< endl;

	cout << left << setw(spacer) << item_two
		<< setw(spacer) << fixed << setprecision(2) << price_two
		<< setw(spacer) << fixed << setprecision(2) << price_two + med_size
		<< setw(spacer) << fixed << setprecision(2) << price_two + large_size
		<< endl;

	cout << left << setw(spacer) << item_three
		<< setw(spacer) << fixed << setprecision(2) << price_three
		<< setw(spacer) << fixed << setprecision(2) << price_three + med_size
		<< setw(spacer) << fixed << setprecision(2) << price_three + large_size
		<< endl;

	cout << left << setw(spacer) << item_four
		<< setw(spacer) << fixed << setprecision(2) << price_four
		<< setw(spacer) << fixed << setprecision(2) << price_four + med_size
		<< setw(spacer) << fixed << setprecision(2) << price_four + large_size
		<< setw(spacer) << endl;

	cout << "Enter in an item code (one character only): " << endl;
	cin >> itemCode;
	cout << "Enter in a size (S, M, L): " << endl;
	cin >> itemSize;
	cout << "Enter in a quantity: " << endl;
	cin >> itemQuantity;
	cout << "Membership Active: (1/0)" << endl;
	cin >> isMember;

	// receipt start

	cout << "\n" << "Receipt\n--------------------------------------------------------\n"
		<< left << setw(15) << "Name"
		<< setw(15) << "Item Code"
		<< setw(15) << "Quantity"
		<< setw(15) << "Unit Price"
		<< setw(15) << "Membership\n" << endl;

	cout << right << foodName
		<< setw(15) << itemCode
		<< setw(15) << itemQuantity;

	if (isMember) {
		cout << right << setw(14) << "$" << fixed << setprecision(2) << unitPrice * (1 - discount)
			<< right << setw(15) << "Yes\n";
	}

	else {
		cout << right << "$" << setw(14) << fixed << setprecision(2) << unitPrice
			<< right << setw(15) << "No\n";
	}

	// receipt end
















	// audit

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
