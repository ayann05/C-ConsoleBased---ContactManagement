
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

// Global variables
string fname, lname, phone_num;

// Function prototypes
void addContact();
void searchContact();
void viewContacts();
void updateContact();
void deleteContact();
void help();
void self_exit();
bool check_digits(const string&);
bool check_numbers(const string&);

int main() {
    short int choice;

    system("cls");
    system("color 0A");

    while (true) {
        cout << "\n\n\n\t\t\tContact Management.";
        cout << "\n\n\t1. Add Contact\n\t2. Search Contact\n\t3. View Contacts\n\t4. Update Contact\n\t5. Delete Contact\n\t6. Help\n\t7. Exit\n\t> ";
        cin >> choice;

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                searchContact();
                break;
            case 3:
                viewContacts();
                break;
            case 4:
                updateContact();
                break;
            case 5:
                deleteContact();
                break;
            case 6:
                help();
                break;
            case 7:
                self_exit();
                break;
            default:
                cout << "\n\n\tInvalid Input !";
                cout << "\n\tPress Any Key To Continue..";
                cin.ignore();
                cin.get();
                break;
        }
    }

    return 0;
}

void self_exit() {
    system("cls");
    cout << "\n\n\n\t\tThank You For Using !";
    exit(1);
}

void help() {
    cout << "This displays help";
}

void addContact() {
    ofstream phone("number.txt", ios::app);
    system("cls");
    cout << "\n\n\tEnter First Name : ";
    cin >> fname;
    cout << "\n\tEnter Last Name : ";
    cin >> lname;
    cout << "\n\tEnter 10-Digit Phone Number : ";
    cin >> phone_num;

    if (check_digits(phone_num) && check_numbers(phone_num)) {
        if (phone.is_open()) {
            phone << fname << " " << lname << " " << phone_num << endl;
            cout << "\n\tContact Saved Successfully !";
        } else {
            cout << "\n\tError Opening File !";
        }
    } else {
        cout << "\n\tInvalid Phone Number Format.";
    }

    phone.close();
}

void searchContact() {
    bool found = false;
    ifstream myfile("number.txt");
    string keyword;
    cout << "\n\tEnter Name To Search : ";
    cin >> keyword;
    while (myfile >> fname >> lname >> phone_num) {
        if (keyword == fname || keyword == lname) {
            system("cls");
            cout << "\n\n\n\t\tContact details..";
            cout << "\n\n\tFirst Name : " << fname;
            cout << "\n\tLast Name : " << lname;
            cout << "\n\tPhone Number : " << phone_num;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "\n\tNo Such Contact Found";
    }
    myfile.close();
}

void viewContacts() {
    ifstream myfile("number.txt");
    cout << "\n\n\t\tList of Contacts\n";
    while (myfile >> fname >> lname >> phone_num) {
        cout << "\n\tFirst Name: " << fname;
        cout << "\n\tLast Name: " << lname;
        cout << "\n\tPhone Number: " << phone_num << "\n";
    }
    myfile.close();
}

void updateContact() {
    string old_fname, old_lname, new_fname, new_lname, new_phone_num;
    bool found = false;

    ifstream infile("number.txt");
    ofstream temp("temp.txt");

    cout << "\n\tEnter the First Name of the contact to update: ";
    cin >> old_fname;
    cout << "\n\tEnter the Last Name of the contact to update: ";
    cin >> old_lname;

    while (infile >> fname >> lname >> phone_num) {
        if (old_fname == fname && old_lname == lname) {
            found = true;
            cout << "\n\tEnter new First Name: ";
            cin >> new_fname;
            cout << "\n\tEnter new Last Name: ";
            cin >> new_lname;
            cout << "\n\tEnter new Phone Number: ";
            cin >> new_phone_num;
            temp << new_fname << " " << new_lname << " " << new_phone_num << endl;
            cout << "\n\tContact Updated Successfully !";
        } else {
            temp << fname << " " << lname << " " << phone_num << endl;
        }
    }

    if (!found) {
        cout << "\n\tContact not found!";
    }

    infile.close();
    temp.close();

    remove("number.txt");
    rename("temp.txt", "number.txt");
}

void deleteContact() {
    string del_fname, del_lname;
    bool found = false;

    ifstream infile("number.txt");
    ofstream temp("temp.txt");

    cout << "\n\tEnter the First Name of the contact to delete: ";
    cin >> del_fname;
    cout << "\n\tEnter the Last Name of the contact to delete: ";
    cin >> del_lname;

    while (infile >> fname >> lname >> phone_num) {
        if (del_fname == fname && del_lname == lname) {
            found = true;
            cout << "\n\tContact Deleted Successfully !";
        } else {
            temp << fname << " " << lname << " " << phone_num << endl;
        }
    }

    if (!found) {
        cout << "\n\tContact not found!";
    }

    infile.close();
    temp.close();

    remove("number.txt");
    rename("temp.txt", "number.txt");
}

bool check_digits(const string& x) {
    return x.length() == 10;
}

bool check_numbers(const string& x) {
    for (char digit : x) {
        if (!isdigit(digit)) {
            return false;
        }
    }
    return true;
}
