#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
using namespace std;

class Bill {
private:
    string item;
    int rate, quantity;

public:
    Bill() : item(""), rate(0), quantity(0) {}

    void setItem(const string& i) { item = i; }
    void setRate(int r) { rate = r; }
    void setQuantity(int q) { quantity = q; }

    string getItem() { return item; }
    int getRate() { return rate; }
    int getQuantity() { return quantity; }
};

void addItem(Bill& b) {
    bool close = false;
    while (!close) {
        int choice;
        cout << "Enter 1 to add\nEnter 2 to close\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            system("cls");
            string item;
            int rate, quantity;
            cout << "\tEnter item name: ";
            cin >> item;
            b.setItem(item);

            cout << "\tEnter item cost: ";
            cin >> rate;
            b.setRate(rate);

            cout << "\tEnter item quantity: ";
            cin >> quantity;
            b.setQuantity(quantity);

            ofstream out("C:\\Users\\ASUS\\OneDrive\\Desktop\\bill.txt", ios::app);
            if (!out) {
                cout << "\tError: file can't open!" << endl;
            } else {
                out << b.getItem() << ":" << b.getRate() << ":" << b.getQuantity() << endl;
                out.close();
                cout << "\tItem added successfully!" << endl;
                Sleep(3000);
            }
        } else if (choice == 2) {
            system("cls");
            close = true;
            cout << "Back to main menu." << endl;
            Sleep(3000);
        } else {
            cout << "Invalid choice!" << endl;
        }
    }
}

void printBill() {
    system("cls");
    int count = 0;
    bool close = false;

    while (!close) {
        int choice;
        cout << "Enter 1 to add bill\nEnter 2 to close session\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            string item;
            int quantity;
            cout << "Enter item: ";
            cin >> item;
            cout << "Enter quantity: ";
            cin >> quantity;

            ifstream in("C:\\Users\\ASUS\\OneDrive\\Desktop\\bill.txt");
            ofstream out("C:\\Users\\ASUS\\OneDrive\\Desktop\\bill_temp.txt");

            string line;
            bool found = false;

            while (getline(in, line)) {
                stringstream ss(line);
                string itemName;
                int itemRate, itemQuantity;
                char colon1, colon2;

                ss >> itemName >> colon1 >> itemRate >> colon2 >> itemQuantity;

                if (item == itemName) {
                    found = true;
                    if (quantity <= itemQuantity) {
                        int amount = itemRate * quantity;
                        cout << "\nItem\tRate\tQuantity\tAmount\n";
                        cout << itemName << "\t" << itemRate << "\t" << quantity << "\t\t" << amount << endl;
                        count += amount;

                        itemQuantity -= quantity;
                        out << itemName << ":" << itemRate << ":" << itemQuantity << endl;
                    } else {
                        cout << "\tSorry, insufficient quantity!" << endl;
                        out << line << endl;
                    }
                } else {
                    out << line << endl;
                }
            }

            if (!found) {
                cout << "Item not available." << endl;
            }

            in.close();
            out.close();
            remove("C:\\Users\\ASUS\\OneDrive\\Desktop\\bill.txt");
            rename("C:\\Users\\ASUS\\OneDrive\\Desktop\\bill_temp.txt", "C:\\Users\\ASUS\\OneDrive\\Desktop\\bill.txt");
        } else if (choice == 2) {
            close = true;
            cout << "Counting total bill..." << endl;
            Sleep(2000);
        } else {
            cout << "Invalid choice!" << endl;
        }
    }

    system("cls");
    cout << "\n\nTotal bill: " << count << endl;
    cout << "Thanks for shopping!" << endl;
    Sleep(5000);
}

int main() {
    Bill b;
    bool exit = false;

    while (!exit) {
        system("cls");
        int val;

        cout << "\tWelcome to Bineet's Market Billing System" << endl;
        cout << "\t*********************" << endl;
        cout << "\t1. Add Item" << endl;
        cout << "\t2. Print Bill" << endl;
        cout << "\t3. Exit" << endl;
        cout << "\tEnter choice: ";
        cin >> val;

        switch (val) {
        case 1:
            system("cls");
            addItem(b);
            break;
        case 2:
            printBill();
            break;
        case 3:
            system("cls");
            exit = true;
            cout << "Goodbye!" << endl;
            Sleep(3000);
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
