#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;
// found a way to merge the size and char index checker
void lowerCaseFix(char& Char) {
	if (islower(Char)) {
		Char = Char - 32;
	}
}
void indexCheck(char& reqChar, vector <char>& code) {
	bool indexFound = false;
	for (int i = 0; i <= code.size(); i++) {
		if (code[i] == reqChar) {
			indexFound = true;
			break;
		}
	}
	if (!indexFound) {
		cout << "Error: No Code Entered. Exiting...";
		exit(1);
	}
}
void reqCodeIndexMatch(char& reqChar, vector <char> &code, int& index, vector <int>& reqList) {
	for (int i = 0; i < code.size(); i++) {
		if (code[i] == reqChar) {
			index = i;
			reqList.push_back(index);
			break;
		}
	}
}
void tipFix(double& tip) {
	if (tip > 1.0) {
		tip /= 100;
	}
}

int main() {
	string cashierNotes;
	vector <char> itemCode = { 'A','B','C','D','E' },
		itemSize = { 'S','M','L' };

	vector <string> itemName = { "Lemon Energizer","Cold Brew","Vanilla Latte","Iced Macchiato", "Checkout" },
		taxName = { "Arkansas State Tax", "Faulkner County Tax", "Conway Municipal Tax" };

	vector <double> itemPrice = { 4.50, 3.00, 4.00, 4.00 },
		taxAmount = { 0.065, 0.005, 0.02125 },
		tipAmount = { 0.15, 0.20, 0.25 },

	vector <int> codeRecord, sizeRecord, quantityRecord;
	vector <double> priceRecord;

	string userName,
		lineLong(70, '-'),
		lineShort(30, '-');

	char reqCode, reqSize, reqMembership;
	int reqQuantity,
		itemIndex = 0,
		sizeIndex = 0,
		tipIndex = 0,
		loopCount = 0,
		spacer = 18,
		bigSpace = 25;

	double discount = 0.10,
		sizeMedium = 1.00,
		sizeLarge = 2.00,
		userSubtotal = 0.0,
		realPrice, userTotal;

	double taxTotal = taxAmount[0] + taxAmount[1] + taxAmount[2],
		tipMultiplier;

	bool isMember = false,
		userCheckout = false;


	cout << left << setw(spacer) << "Drink"
		<< setw(spacer) << "Small (S)"
		<< setw(spacer) << "Medium (M)"
		<< setw(spacer) << "Large (L)" << endl;

	for (int i = 0; i < itemCode.size() - 1; i++) {
		cout << left << itemCode[i] << setw(2) << "." << setw(spacer) << itemName[i]
			<< "$" << setw(spacer - 1) << fixed << setprecision(2) << itemPrice[i]
			<< "$" << setw(spacer - 1) << fixed << setprecision(2) << itemPrice[i] + sizeMedium
			<< "$" << setw(spacer - 1) << fixed << setprecision(2) << itemPrice[i] + sizeLarge
			<< endl;
	}
	cout << left << "E. Checkout" << endl;
	do {
		cout << "\n" << left << setw(spacer) << "Item Code:";
		cin >> reqCode;
		lowerCaseFix(reqCode);
		if (reqCode == itemCode.back() && loopCount >= 1) {
			cout << left << "\nLoading checkout screen...\n" << endl;
			userCheckout = true;
			break;
		}
		else if (reqCode == itemCode.back() && loopCount < 1) {
			cout << left << "\nCannot checkout with zero items.\n";
			exit(1);
		}
		indexCheck(reqCode, itemCode);

		reqCodeIndexMatch(reqCode, itemCode, itemIndex, codeRecord);
		
		cout << left << setw(spacer) << "Size:";
		cin >> reqSize;
		lowerCaseFix(reqSize);
		indexCheck(reqSize, itemSize);
		reqCodeIndexMatch(reqSize, itemSize, sizeIndex, sizeRecord);
		switch (reqSize) {
		case 'S':
			realPrice = itemPrice[itemIndex];
			break;
		case 'M':
			realPrice = itemPrice[itemIndex] + sizeMedium;
			break;
		case 'L':
			realPrice = itemPrice[itemIndex] + sizeLarge;
			break;
		default:
			cout << left << setw(spacer) << "Error: No Size Selected. Exiting..." << endl;
		}

		cout << left << setw(spacer) << "Quantity:";
		cin >> reqQuantity;

		if (reqQuantity > 0) {
			quantityRecord.push_back(reqQuantity);
		}
		else {
			cout << "Error: No Quantity Entered. Exiting...";
			exit(1);
		}
		priceRecord.push_back(realPrice);
		loopCount++;
	} while (!userCheckout);

	cout << left << setw(spacer) << "Membership (Y/N):";
	cin >> reqMembership;
	lowerCaseFix(reqMembership);

	if (reqMembership == 'Y') {
		isMember = true;
	}
	for (int i = 0; i < priceRecord.size(); i++) {
		userSubtotal += priceRecord[i];
	}
	
	cout << left << "\nPayment Receipt for Customer: " << userName << '.\n' << lineLong << "\n"
		<< left << setw(spacer) << "Item Name"
		<< setw(spacer) << "Item Size"
		<< setw(spacer) << "Quantity"
		<< setw(spacer) << "Price\n" << endl;

	for (int i = 0; i < codeRecord.size(); i++) {
		cout << left << setw(spacer) << itemName[codeRecord[i]]
			<< setw(spacer) << itemSize[sizeRecord[i]]
			<< setw(spacer) << quantityRecord[i]
			<< "$" << setw(spacer - 1) << fixed << setprecision(2) << priceRecord[i] * quantityRecord[i] << endl;
	}

	cout << left << setw(spacer) << "\nMembership" << setw(spacer) << (isMember ? "Yes" : "No")
		<< setw(spacer) << "\nSubtotal" << "$" << setw(spacer - 1) << fixed << setprecision(2) << userSubtotal
		<< setw(spacer) << "\nTax" << "$" << setw(spacer - 1) << fixed << setprecision(2) << userSubtotal * taxTotal;
	if (isMember) {
		cout << left << setw(spacer) << "\nDiscount" << "$" << '-' << setw(spacer - 2) << fixed << setprecision(2) << userSubtotal * discount;
	}
	cout << left << setw(spacer) << "\nTotal" << "$" << setw(spacer - 1) << fixed << setprecision(2) << userSubtotal * (1 + taxTotal) << "\n" << endl;
	
	// tax menu
	cout << left << setw(bigSpace) << "Sales Tax Information" << setw(spacer) << "Percentage" << "Amount\n" << lineLong << endl;
	for (int i = 0; i < 3; i++) {
		cout << left << setw(bigSpace) << taxName[i]
			<< fixed << setprecision(2) << (100 * taxAmount[i]) << setw(spacer-4) << "%" 
			 << "$" << fixed << setprecision(2) << userSubtotal * taxAmount[i] << endl;
	}

	// tip menu
	cout << left << "\n" << setw(spacer) << "Tip Menu" << setw(spacer) << "Amount" << endl
		<< left << lineShort << endl;

	for (int i = 0; i < tipAmount.size() + 1; i++) {
		if (i <= tipAmount.size() - 1) {
			cout << left << itemCode[i] << setw(2) << "." << 100 * tipAmount[i] << setw(spacer - 7) << "%"
				<< "$" << fixed << setprecision(2) << realPrice * (1 + tipAmount[i]) << endl;
		}
		else {
			cout << left << itemCode[i] << setw(2) << "." << "Other Amount" << endl;
		}
	}
	
	cout << left << setw(spacer + 1) << "Tip Option:";
	cin >> reqCode;
	lowerCaseFix(reqCode);
	switch (reqCode) {
	case 'A':
		tipIndex = 0;
		tipMultiplier = tipAmount[tipIndex];
		break;
	case 'B':
		tipIndex = 1;
		tipMultiplier = tipAmount[tipIndex];
		break;
	case 'C':
		tipIndex = 2;
		tipMultiplier = tipAmount[tipIndex];
		break;
	case 'D':
		cout << left << setw(spacer) << "Custom Tip:";
		cin >> tipMultiplier;
		break;
	default:
		cout << "Incorrect Option Entered.";
		exit(1);
	}

	tipFix(tipMultiplier);
	if(isMember) {
		userTotal = (userSubtotal * tipMultiplier) + (userSubtotal * (1 + taxTotal)) - (userSubtotal * discount);
	}
	else {
	userTotal = (userSubtotal * tipMultiplier ) + (userSubtotal * (1 + taxTotal));
	}
	
	cout << left << setw(spacer) << "Total Price:" << "$" << fixed << setprecision(2) << userTotal;
	
	/*	
	cout << "\nEnter Cashier Notes: ";
	cin.ignore();
	getline(cin, cashierNotes);
	cout << left << "$" << fixed << setprecision(2) << userTotal << endl;*/

	return 0;
}
