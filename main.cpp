#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;
// error handling for lowercase and unindexable values yayyy
void lowerCaseFix(char &Char) {
	if (islower(Char)) {
		Char = Char - 32;
	}
}
void itemIndexCheck(char &reqChar) {
		if (reqChar != 'A' && reqChar != 'B' && reqChar != 'C' && reqChar != 'D') {
		cout << "Unrecognized Value entered.";
		exit(1);
	}
}
void sizeIndexCheck(char& reqChar) {
	if (reqChar != 'S' && reqChar != 'M' && reqChar != 'L') {
		cout << "Unrecognized Value entered.";
		exit(1);
	}
}
void reqCodeIndexMatch(char &reqChar, vector <char> &code, int &index) {
	for (int i = 0; i < code.size(); i++) {
		if (code[i] == reqChar) {
			index = i;
			break;
		}
	}
}
void tipFix(float& tip) {
	if (tip > 1.0){
		tip /= 100;
	}
}
/*
sorry if this seems arbitrary, my past courses drilled into
my head that I must account for errors and different inputs
*/ 
int main() {
	string cashierNotes;

	vector <char> itemCode = { 'A','B','C','D' };
	vector <char> itemSize = { 'S','M','L' };
	vector <string> itemName = { "Lemon Energizer","Cold Brew","Vanilla Latte","Iced Macchiato" };
	vector <double> itemPrice = { 4.50, 3.00, 4.00, 4.00 };

	char reqCode, reqSize, reqMembership;
	int reqQuantity;
	int itemIndex = 0,
		sizeIndex = 0,
		tipIndex = 0;

	double discount = 0.1,
		sizeMedium = 1.00,
		sizeLarge = 2.00,
		totalPrice, unitPrice, totalTaxPrice;

	vector <string> taxName = { "Arkanas State Tax", "Faulkner County Tax", "Conway Municipal Tax" };
	vector <float>	taxAmount = { 0.065, 0.005, 0.02125 },
					tipAmount = { 0.15, 0.20, 0.25 };
	float taxTotal = taxAmount[0] + taxAmount[1] + taxAmount[2],
		  tipMultiplier;

	bool isMember = false;

	int spacer = 22;				// aesthetic options
	string lineLong(120, '-');
	string lineShort(30, '-');

	// menu 
	cout << left << setw(spacer) << "Drink"
		<< setw(spacer) << "Small (S)"
		<< setw(spacer) << "Medium (M)"
		<< setw(spacer) << "Large (L)" << endl;

	for (int i = 0; i < itemCode.size(); i++) {
		cout << left << itemCode[i] << setw(2) << "." << setw(spacer) << itemName[i]
			<< "$" << setw(spacer - 1) << fixed << setprecision(2) << itemPrice[i]
			<< "$" << setw(spacer - 1) << fixed << setprecision(2) << itemPrice[i] + sizeMedium
			<< "$" << setw(spacer - 1) << fixed << setprecision(2) << itemPrice[i] + sizeLarge
			<< endl;
	}

	cout << "\n" << left << setw(spacer) << "Item Code:";
	cin >> reqCode;
		lowerCaseFix(reqCode);
		itemIndexCheck(reqCode);
		reqCodeIndexMatch(reqCode, itemCode, itemIndex);
	cout << left << setw(spacer) << "Size:";
	cin >> reqSize;
		lowerCaseFix(reqSize);
		sizeIndexCheck(reqSize);
		reqCodeIndexMatch(reqSize, itemSize, sizeIndex);
	cout << left << setw(spacer) << "Amount:";
	cin >> reqQuantity;
	cout << left << setw(spacer) << "Store Member (Y/N):";
	cin >> reqMembership;
	cout << endl;
	
	// updates membership flag
	lowerCaseFix(reqMembership);
	if (reqMembership == 'Y') {
		isMember = true;
	}

	// adjusts totalPrice and unitPrice based on reqSize
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
	}

	if (isMember) {
		totalPrice *= (1 - discount);
	}
	// multiplies the price by the reqQuantity
	totalPrice *= reqQuantity;

	cout << "\n" << "Receipt\n" << lineLong << "\n"
		<< left << setw(spacer) << "Item Name"
		<< setw(spacer) << "Item Size"
		<< setw(spacer) << "Quantity"
		<< setw(spacer) << "Unit Price"
		<< setw(spacer) << "Membership"
		<< setw(spacer) << "Subtotal\n" << endl;

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

	cout << "$" << fixed << setprecision(2) << setw(spacer - 1) << totalPrice << "\n" << endl;

	// tax menu
	cout << "Sales Tax Options\n" << lineShort << endl;
	for (int i = 0; i < 3; i++) {
		cout << left << setw(spacer) << taxName[i] << setw(2) << ":"
			 << fixed << setprecision(2) << (100 * taxAmount[i]) << "%" << endl;
	}
	cout << left << setw(spacer) <<"Total Tax Added" << setw(2) << ":"
		 << fixed << setprecision(2) << (100 * taxTotal) << "%" << endl;

	// tip menu
	cout << left << "\n" << setw(spacer) << "Tip Menu" << setw(spacer) << "Amount" << endl
		 << left <<lineShort << endl;
	for (int i = 0; i < tipAmount.size()+1; i++) {
		if (i <= tipAmount.size()-1) {
			cout << left << itemCode[i] << setw(2) << "." << 100 * tipAmount[i] << setw(spacer-8) << "%"
				 << "$" << fixed << setprecision(2) << totalPrice + (totalPrice * tipAmount[i]) << endl;
		}
		else {
			cout << left << itemCode[i] << setw(2) << "." << "Other Amount" << endl;
		}
	}
	cout << endl;

	cout << left << setw(spacer+1) <<"Tip Option:";
	cin >> reqCode;
		lowerCaseFix(reqCode);
		itemIndexCheck(reqCode);
		reqCodeIndexMatch(reqCode, itemCode, tipIndex);
		if (reqCode == 'D') {
			cout << left << setw(spacer) << "Custom Tip Percentage:";
			cin >> tipMultiplier;
		}
		else {
			tipMultiplier = tipAmount[tipIndex];
		}
	tipFix(tipMultiplier);
	// idk why the syntax here makes me mad
	totalTaxPrice = (totalPrice * tipMultiplier) + (totalPrice * taxTotal) + totalPrice;

	cout << left << setw(spacer) << "Total Price:" << "$" << fixed << setprecision(2) << totalTaxPrice << endl;

	cout << "\nEnter Cashier Notes: ";
	cin.ignore();
	getline(cin, cashierNotes);

	cout << "\n" << "Audit\n" << lineLong << endl;

	cout << left << setw(spacer) << "Item Name"
		<< setw(spacer) << "Item Size"
		<< setw(spacer) << "Quantity"
		<< setw(spacer) << "Unit Price"
		<< setw(spacer) << "Membership"
		<< setw(spacer) << "Total" << endl;

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

	cout << left << "$" << fixed << setprecision(2) << totalTaxPrice << endl;

	return 0;
}
