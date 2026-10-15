#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

static void lowerCaseFix(char& Char) {
	if (islower(Char)) {
		Char = Char - 32;
	}
}
static bool indexCheck(char& reqChar, vector <char>& code) {
	bool indexFound = false;
	for (int i = 0; i < code.size(); i++) {
		if (reqChar == code[i]) {
			indexFound = true;
		}
	}
	if (!indexFound) 
		cout << "Error: Incorrect Code Input\n";
	return indexFound;
}
static void reqCodeIndexMatch(char& reqChar, vector <char>& code, int& index, vector <int>& reqList) {
	for (int i = 0; i < code.size(); i++) {
		if (code[i] == reqChar) {
			index = i;
			reqList.push_back(index);
		}
	}

}
static void tipFix(double& tip) {
	if (tip > 1.0) {
		tip /= 100;
	}
	else if (tip <= 0) {
		tip = 0.00;
	}
}
static double displayDiscountCheck(double discount, double price, double tax, bool status) {
	if (status)
		price = price * (1 - discount);
	price = price * (1 + tax);
	return price;
}

int main() {
	ifstream inputFile;
	string label;
	double price0, price1, price2;

	vector <string> itemName = {};
	vector <double> itemSmallPrice = {},
		itemMediumPrice = {},
		itemLargePrice = {};

	inputFile.open("menuInfo.txt");

	for (int i = 0; i < 4; i++) {
		getline(inputFile >> ws,label);
		inputFile >> price0;
		inputFile >> price1;
		inputFile >> price2;

		itemName.push_back(label);
		itemSmallPrice.push_back(price0);
		itemMediumPrice.push_back(price1);
		itemLargePrice.push_back(price2);
	}
	inputFile.close();


	vector <char> itemCode = { 'A','B','C','D','E' },
		itemSize = { 'S','M','L' };

	vector <string> taxName = { "Arkansas State Tax", "Faulkner County Tax", "Conway Municipal Tax" };

	vector <double> taxAmount = { 0.065, 0.005, 0.02125 },
		tipAmount = { 0.15, 0.20, 0.25 };

	vector <int> codeRecord, sizeRecord, quantityRecord;
	vector <double> priceRecord;

	string userName, cashierNotes,
		lineLong(70, '-'),
		lineShort(30, '-');

	char reqCode, reqSize, reqMembership,
		checkoutCode = 'E';

	int reqQuantity, userPoints,
		itemIndex = 0,
		sizeIndex = 0,
		tipIndex = 0,
		loopCount,
		spacer = 18,
		bigSpace = 25,
		totalCustomers = 0,
		totalOrders = 0;

	double discount = 0.10,
		userSubtotal = 0.0,
		realPrice, userTotal, grandTotalSales = 0.0;

	double taxTotal = taxAmount[0] + taxAmount[1] + taxAmount[2],
		tipMultiplier;

	bool isMember = false,
		userCheckout = false,
		dayActive = true,
		validInput = false;

	while (dayActive) {

		userSubtotal = 0.0;
		userTotal = 0.0;
		userPoints = 0;
		loopCount = 0;
		isMember = false;
		userCheckout = false;

		codeRecord.clear();
		sizeRecord.clear();
		quantityRecord.clear();
		priceRecord.clear();

		cout << left << setw(spacer) << "Drink"
			<< setw(spacer) << "Small (S)"
			<< setw(spacer) << "Medium (M)"
			<< setw(spacer) << "Large (L)" << endl;

		for (int i = 0; i < itemCode.size() - 1; i++) {
			cout << left << itemCode[i] << setw(2) << "." << setw(spacer) << itemName[i]
				<< "$" << setw(spacer - 1) << fixed << setprecision(2) << itemSmallPrice[i]
				<< "$" << setw(spacer - 1) << fixed << setprecision(2) << itemMediumPrice[i]
				<< "$" << setw(spacer - 1) << fixed << setprecision(2) << itemLargePrice[i] 
				<< endl;
		}
		cout << left << "E. Checkout\n" << endl;
		cout << left << setw(spacer) << "Name: ";
		cin >> userName;

		do {
			while (!validInput) {
				bool earlyCheckout = false;
				cout << "\n" << left << setw(spacer) << "Item Code:";
				cin >> reqCode;
				lowerCaseFix(reqCode);
				if (reqCode == checkoutCode && loopCount >= 1) {
					cout << left << "\nLoading checkout screen...\n" << endl;
					userCheckout = true;
					validInput = true;
					break;
				}
				else if (reqCode == checkoutCode && loopCount < 1) {
					cout << left << "\nCannot checkout with zero items.\n";
					earlyCheckout = true;
				}

				if (indexCheck(reqCode, itemCode) && !earlyCheckout)
					validInput = true;
			}
			if (userCheckout) {
				validInput = false;
				break;
			}
			reqCodeIndexMatch(reqCode, itemCode, itemIndex, codeRecord);
			validInput = false;

			while (!validInput) {
				cout << left << setw(spacer) << "Size:";
				cin >> reqSize;
				lowerCaseFix(reqSize);

				if (indexCheck(reqSize, itemSize))
					validInput = true;
			}

			reqCodeIndexMatch(reqSize, itemSize, sizeIndex, sizeRecord);
			validInput = false;

			switch (reqSize) {
			case 'S':
				realPrice = itemSmallPrice[itemIndex];
				break;
			case 'M':
				realPrice = itemMediumPrice[itemIndex];
				break;
			case 'L':
				realPrice = itemLargePrice[itemIndex];
				break;
			}
			while (!validInput) {
				cout << left << setw(spacer) << "Quantity:";
				cin >> reqQuantity;

				if (reqQuantity > 0) {
					quantityRecord.push_back(reqQuantity);
					priceRecord.push_back(realPrice);
					validInput = true;
					loopCount++;
				}
				else {
					cout << "Error: No Quantity Entered.";
				}
			}
			validInput = false;
			
		} while (!userCheckout);

		cout << left << setw(spacer) << "Membership (Y/N):";
		cin >> reqMembership;
		lowerCaseFix(reqMembership);

		if (reqMembership == 'Y') {
			isMember = true;
		}
		for (int i = 0; i < priceRecord.size(); i++) {
			userSubtotal += priceRecord[i] * quantityRecord[i];
		}

		cout << left << "\nPayment Receipt for Customer: " << userName << "\n" << lineLong << "\n"
			<< left << setw(spacer) << "Item Name"
			<< setw(spacer) << "Item Size"
			<< setw(spacer) << "Quantity"
			<< setw(spacer) << "Price\n" << endl;

		for (int i = 0; i < codeRecord.size(); i++) {
			cout << left << setw(spacer) << itemName[codeRecord[i]]
				<< setw(spacer) << itemSize[sizeRecord[i]]
				<< setw(spacer) << quantityRecord[i]
				<< "$" << setw(spacer - 1) << fixed << setprecision(2) << priceRecord[i] * quantityRecord[i] << endl;
			totalOrders += quantityRecord[i];
		}

		cout << left << setw(spacer) << "\nMembership:" << setw(spacer) << (isMember ? "Yes" : "No")
			<< setw(spacer) << "\nSubtotal:" << "$" << setw(spacer - 1) << fixed << setprecision(2) << userSubtotal
			<< setw(spacer) << "\nSales Tax:" << "$" << setw(spacer - 1) << fixed << setprecision(2) << userSubtotal * taxTotal;
		if (isMember) {
			cout << left << setw(spacer - 1) << "\nDiscount:" << '-' << "$" << setw(spacer - 2) << fixed << setprecision(2) << userSubtotal * discount;
		}
		cout << left << setw(spacer) << "\nTotal:" << "$" << setw(spacer - 1) << fixed << setprecision(2) << displayDiscountCheck(discount, userSubtotal, taxTotal, isMember) << "\n" << endl;


		// tax menu
		cout << left << setw(bigSpace) << "Sales Tax Information" << setw(spacer) << "Percentage" << "Amount\n" << lineLong << endl;
		for (int i = 0; i < 3; i++) {
			cout << left << setw(bigSpace) << taxName[i]
				<< fixed << setprecision(3) << (100 * taxAmount[i]) << setw(spacer - 5) << "%"
				<< "$" << fixed << setprecision(2) << displayDiscountCheck(discount, userSubtotal, taxTotal, isMember) * taxAmount[i] << endl;
		}

		// tip menu
		cout << left << "\n" << setw(spacer) << "Tip Menu" << setw(spacer) << "Amount" << endl
			<< left << lineShort << endl;

		for (int i = 0; i < tipAmount.size() + 1; i++) {
			if (i <= tipAmount.size() - 1) {
				cout << left << itemCode[i] << ". " << 100 * tipAmount[i] << setw(spacer - 8) << "%"
					<< "$" << fixed << setprecision(2) << displayDiscountCheck(discount, userSubtotal, taxTotal, isMember) + (userSubtotal * tipAmount[i]) << endl;
			}
			else {
				cout << left << itemCode[i] << setw(2) << "." << "Other Amount" << endl;
			}
		}

		cout << left << setw(spacer + 1) << "\nTip Option:";
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

		userTotal = displayDiscountCheck(discount, userSubtotal, taxTotal, isMember) * (1 + tipMultiplier);
		userPoints = floor(userTotal / 3);

		cout << left << setw(spacer) << "\nTotal:" << "$" << fixed << setprecision(2) << userTotal << endl;
		cout << left << setw(spacer) << "Loyalty Points:";
		if (userPoints > 0) {
			cout << string(userPoints, '*') << endl;
		}
		else {
			cout << "None" << endl;
		}
		totalCustomers++;
		grandTotalSales += userTotal;

		cout << left << setw(bigSpace) << "\nNew Customer (Y/N):";
		cin >> reqCode;
		lowerCaseFix(reqCode);
		if (reqCode != 'Y') {
			cout << left << "\nClosing Shop!\n";
			dayActive = false;
			break;
		}
		else {
			cout << "\n" << string(3, '\n') << lineLong << "\n" << endl;
		}
	}

	cout << "\nEnter Cashier Notes: ";
	cin.ignore();
	getline(cin, cashierNotes);

	cout << left << "\n" << lineShort << "\nDaily Shop Audit\n" << lineShort << "\n" << endl;
	cout << left << setw(bigSpace) << "Total Customers:" << right << totalCustomers << endl;
	cout << left << setw(bigSpace) << "Items Sold:" << right << totalOrders << endl;
	cout << left << setw(bigSpace - 1) << "Grand Total Sales:" << right << '$' << fixed << setprecision(2) << grandTotalSales << endl;

	return 0;
}
