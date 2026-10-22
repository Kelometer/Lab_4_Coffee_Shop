#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>

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
static void handleTipAmount(double& tipPercentage) {
	if (tipPercentage > 1.0) {
		tipPercentage /= 100;
	}
	else if (tipPercentage <= 0) {
		tipPercentage = 0.00;
	}
}
static void inventoryUpdate(vector <int>& inventory, vector <int>& userItemRecord, vector <int>& userQuantityRecord) {
	for (int i = 0; i < userItemRecord.size(); i++) {		// uses itemRecord to subtract userQuantity from inventory at a specific index
		switch (userItemRecord[i]) {
		case 0:
			inventory[0] -= userQuantityRecord[i];
			break;
		case 1:
			inventory[1] -= userQuantityRecord[i];
			break;
		case 2:
			inventory[2] -= userQuantityRecord[i];
			break;
		case 3:
			inventory[3] -= userQuantityRecord[i];
			break;
		}
	}
}
static void accessMenu(vector <string> &itemLabel, vector <double> &itemPrice1, vector <double> &itemPrice2, vector <double> &itemPrice3) {
	ifstream input;
	input.open("menuInfo.txt");

	string label;
	double price0, price1, price2;

	// reads item info in groups of 4 and appends it to specific vectors
	for (int i = 0; i < 4; i++) {
		getline(input >> ws, label);
		input >> price0;
		input >> price1;
		input >> price2;

		itemLabel.push_back(label);
		itemPrice1.push_back(price0);
		itemPrice2.push_back(price1);
		itemPrice3.push_back(price2);
	}

	input.close();
}
static void outputInventory(vector <int> inventory, vector <string> name) {
	ofstream output;

	output.open("inventoryLog.txt");

	output << left << string(70,'-') << "\nDaily Inventory\n" << string(70, '-') << endl;
	output<< left << setw(25) << "Item Name" << setw(18) << "Start" << setw(18) << "Change" << setw(18) << "End" << endl;
	for (int i = 0; i < inventory.size(); i++) {
		output << left << setw(25) << name[i] << setw(18) << 50 << setw(18) << abs(inventory[i] - 50) << setw(18) << inventory[i] << endl;
	}

	output.close();
}
static void outputReceipt(string username, vector <int> code, vector <string> name, vector <int> sizeRec, vector <char> size, vector <int> amount, vector <double> price, double base, double subtotal,
	double tip, double discount, double taxedTotal, string note, bool membership ) {
	ofstream output;					// gross amount of parameters here but I cannot exactly access them otherwise;
	output.open("receiptLog.txt");		// copies the receipt and abstracts it

	output << left << string(33,'-') << "\nReceipt for: " << username << "\n" << string(33, '-') << "\n"
		<< left << setw(5) << "QTY"
		<< setw(21) << "Item Name"
		<< setw(18) << "Price\n" << endl;

	for (int i = 0; i < code.size(); i++) {
		output<< left << setw(5) << amount[i]
			<< setw(2) << size[sizeRec[i]] << setw(19) << name[code[i]]
			<< "$" << setw(6) << right << fixed << setprecision(2) << price[i] * amount[i] << endl;
	}

	output << string(33, '-') << left << setw(18) << "\nMembership:" << setw(18) << (membership ? "Yes" : "No")
		<< setw(18) << "\nSubtotal:" << "$" << setw(17) << fixed << setprecision(2) << base
		<< setw(18) << "\nSales Tax:" << "$" << setw(17) << fixed << setprecision(2) <<  taxedTotal - subtotal;

	if (membership) {
		output << left << setw(17) << "\nDiscount:" << '-' << "$" << setw(17) << fixed << setprecision(2) << discount;
	}

	output << left << setw(18) << "\nTip:" << "$" << setw(17) << fixed << setprecision(2) << tip
		<< setw(18) << "\nTotal:" << "$" << setw(17) << fixed << setprecision(2) << taxedTotal + tip << "\n" << string(33, '-')
		<< setw(18) << "\nNotes:" << note << endl;

	output.close();
}
static void createConsistentPrice(double &basetotal, double &subtotal, double &taxedTotal, double &taxAmount, double &discountAmount, double &discount, bool membership) {
	basetotal = subtotal;		// ensures that all of my monetary variables match
	if (membership) {
		discountAmount = subtotal * discount;
		subtotal -= discountAmount;
	}
	taxedTotal = subtotal * (1 + taxAmount);
}
static void createTaxMenu(vector <string> taxName, vector <double> taxType, double subtotal) {
	cout << left << setw(25) << "Sales Tax Information" << setw(18) << "Percentage" << "Amount\n" << string(70,'-') << endl;

	for (int i = 0; i < 3; i++) {
		cout << left << setw(25) << taxName[i]
			<< fixed << setprecision(3) << (100 * taxType[i]) << setw(13) << "%"
			<< "$" << fixed << setprecision(2) << subtotal * taxType[i] << endl;
	}
}
static void createTipMenu(vector <char> code, vector <double> tipType, double subtotal) {

	cout << left << "\n" << setw(18) << "Tip Menu" << setw(18) << "Amount" << endl
		<< left << string(30,'-') << endl;

	for (int i = 0; i < tipType.size() + 1; i++) {
		if (i <= tipType.size() - 1) {
			cout << left << code[i] << ". " << 100 * tipType[i] << setw(13) << "%"
				<< "$" << fixed << setprecision(2) << subtotal * (1 + tipType[i]) << endl;
		}
		else {
			cout << left << code[i] << setw(2) << "." << "Other Amount" << endl;
		}
	}
}

int main() {
	vector <string> itemName;
	vector <double> itemSmallPrice, itemMediumPrice, itemLargePrice;

	accessMenu(itemName, itemSmallPrice, itemMediumPrice, itemLargePrice);

	vector <char> itemCode = { 'A','B','C','D','E' },
		itemSize = { 'S','M','L' };

	vector <string> taxName = { "Arkansas State Tax", "Faulkner County Tax", "Conway Municipal Tax" };

	vector <double> taxAmount = { 0.065, 0.005, 0.02125 },
		tipAmount = { 0.15, 0.20, 0.25 };

	vector <int> codeRecord, sizeRecord, quantityRecord,
		shopInventory = { 50,50,50,50 };
	vector <double> priceRecord;

	string userName, cashierNotes;

	char reqCode, reqSize, reqMembership,
		checkoutCode = itemCode.back(); // essentially vector[-1], allows for me to add other items without manually editing checkoutCode.

	int reqQuantity, userPoints, loopCount,
		itemIndex = 0,
		sizeIndex = 0,
		tipIndex = 0,
		spacer = 18,
		bigSpace = 25,
		totalCustomers = 0,
		totalOrders = 0;

	double discount = 0.10,
		baseTotal, userSubtotal, taxedTotal, userTotal, discountAmount, realPrice,
		taxPercentage = taxAmount[0] + taxAmount[1] + taxAmount[2],
		userTip, tipMultiplier,
		grandTotalSales = 0;

	bool isMember = false,
		userCheckout = false,
		dayActive = true,
		validInput = false;

	while (dayActive) {
		baseTotal = 0.0,
		userSubtotal = 0.0,
		taxedTotal = 0.0,
		userTip = 0.0,
		userTotal = 0.0,
		userPoints = 0,
		discountAmount = 0,
		cashierNotes,
		loopCount = 0;
		isMember = false;
		userCheckout = false;

		codeRecord.clear();
		sizeRecord.clear();
		quantityRecord.clear();
		priceRecord.clear();

		cout << left << setw(23) << "Drink"
			<< setw(15) << "Small (S)"
			<< setw(15) << "Medium (M)"
			<< setw(15) << "Large (L)" << endl;

		for (int i = 0; i < itemCode.size() - 1; i++) {
			cout << left << itemCode[i] << setw(2) << "." << setw(20) << itemName[i]
				<< "$" << setw(14) << fixed << setprecision(2) << itemSmallPrice[i]
				<< "$" << setw(14) << fixed << setprecision(2) << itemMediumPrice[i]
				<< "$" << setw(15) << fixed << setprecision(2) << itemLargePrice[i]
				<< endl;
		}
		cout << left << checkoutCode << ". Checkout\n" << endl;
		cout << left << setw(spacer) << "Name: ";
		getline(cin, userName);

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
				validInput = false; // checks for breakout
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
					cout << "\nError: Quantity must be a number greater than 0.\n"; 
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');	// prevents infinite loop on string input
				}
			}
			validInput = false;

		} while (!userCheckout);

		inventoryUpdate(shopInventory, codeRecord, quantityRecord);

		cout << left << setw(spacer) << "Membership (Y/N):";
		cin >> reqMembership;
		lowerCaseFix(reqMembership);

		if (reqMembership == 'Y') {
			isMember = true;
		}
		for (int i = 0; i < priceRecord.size(); i++) {
			userSubtotal += priceRecord[i] * quantityRecord[i];
		}

		createConsistentPrice(baseTotal, userSubtotal, taxedTotal, taxPercentage, discountAmount, discount, isMember);

		// receipt
		cout << left << "\nReceipt for: " << userName << "\n" << string(33,'-') << "\n"
			<< left << setw(5) << "QTY"
			<< setw(spacer + 3) << "Item Name"
			<< setw(spacer) << "Price\n" << endl;

		for (int i = 0; i < codeRecord.size(); i++) {
			cout << left << setw(5) << quantityRecord[i]
				<< setw(2) << itemSize[sizeRecord[i]] << setw(spacer + 1) << itemName[codeRecord[i]]
				<< "$" << setw(6) << right << fixed << setprecision(2) << priceRecord[i] * quantityRecord[i] << endl;

			totalOrders += quantityRecord[i];
		}

		cout << left << setw(spacer) << "\nMembership:" << setw(spacer) << (isMember ? "Yes" : "No")
			<< setw(spacer) << "\nSubtotal:" << "$" << setw(spacer - 1) << fixed << setprecision(2) << baseTotal;

		cout << setw(spacer) << "\nSales Tax:" << "$" << setw(spacer - 1) << fixed << setprecision(2) << userSubtotal * taxPercentage;

		if (isMember) {
			cout << left << setw(spacer - 1) << "\nDiscount:" << '-' << "$" << setw(spacer - 2) << fixed << setprecision(2) << discountAmount;
		}

		cout << left << setw(spacer) << "\nTotal:" << "$" << setw(spacer - 1) << fixed << setprecision(2) << taxedTotal << "\n" << endl;

		createTaxMenu(taxName, taxAmount, userSubtotal);
		createTipMenu(itemCode, tipAmount, userSubtotal);
		
		while (!validInput) {
			cout << left << setw(spacer + 1) << "\nTip Option:";
			cin >> reqCode;
			lowerCaseFix(reqCode);

			switch (reqCode) {
			case 'A':
				tipIndex = 0;
				tipMultiplier = tipAmount[tipIndex];
				validInput = true;
				break;
			case 'B':
				tipIndex = 1;
				tipMultiplier = tipAmount[tipIndex];
				validInput = true;
				break;
			case 'C':
				tipIndex = 2;
				tipMultiplier = tipAmount[tipIndex];
				validInput = true;
				break;
			case 'D':
				cout << left << setw(spacer) << "\nCustom Tip:";
				cin >> tipMultiplier;
				validInput = true;
				break;
			default:
				cout << "\nNo Option Entered.\n";
			}
		}

		handleTipAmount(tipMultiplier);

		userTotal = userSubtotal + (userSubtotal * tipMultiplier);
		userTip = userTotal - userSubtotal;
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

		cout << "\nEnter Cashier Notes: ";
		cin.ignore();
		getline(cin, cashierNotes);

		outputReceipt(userName, codeRecord, itemName, sizeRecord, itemSize, quantityRecord, priceRecord, baseTotal, userSubtotal, userTip, discountAmount, taxedTotal, cashierNotes, isMember);

		cout << left << setw(bigSpace) << "\nNew Customer (Y/N):";
		cin >> reqCode;
		lowerCaseFix(reqCode);

		if (reqCode != 'Y') {
			cout << left << "\nClosing Shop!\n";
			dayActive = false;
			break;
		}
		else {
			cout << "\n" << string(3, '\n') << string(70, '-') << "\n" << endl;
		}
	}

	cout << left << "\n" << string(70, '-') << "\nDaily Shop Audit\n" << string(70, '-') << "\n" << endl;
	cout << left << setw(bigSpace) << "Total Customers:" << right << totalCustomers << endl;
	cout << left << setw(bigSpace) << "Items Sold:" << right << totalOrders << endl;
	cout << left << setw(bigSpace - 1) << "Grand Total Sales:" << right << '$' << fixed << setprecision(2) << grandTotalSales << "\n" << endl;

	cout << left << string(70, '-') << "\nDaily Inventory\n" << string(70, '-') << endl;
	cout << left << setw(bigSpace) << "Item Name" << setw(spacer) << "Start" << setw(spacer) << "Change" << setw(spacer) << "End" << endl;
	for (int i = 0; i < shopInventory.size(); i++) {
		cout << left << setw(bigSpace) << itemName[i] << setw(spacer) << 50 << setw(spacer) << abs(shopInventory[i] - 50) << setw(spacer) << shopInventory[i] << endl;
	}

	outputInventory(shopInventory, itemName);

	return 0;
}
