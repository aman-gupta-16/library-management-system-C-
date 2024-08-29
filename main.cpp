#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class LibraryManagementSystem {
    string id, name, author, search;
    fstream file;

public:
    void addBook();
    void showAll();
    void extractBook();
    bool login();
    void registerUser();
};

int main() {
    LibraryManagementSystem obj;
    char choice;
    if (!obj.login()) {
        return 0;
    }

    do {
        cout << "----------------------------------" << endl;
        cout << "1-Show All Books" << endl;
        cout << "2-Extract Book" << endl;
        cout << "3-Add books(ADMIN)" << endl;
        cout << "4-Exit" << endl;
        cout << "----------------------------------" << endl;
        cout << "Enter Your Choice :: ";
        cin >> choice;

        switch (choice) {
        case '1':
            cin.ignore();
            obj.showAll();
            break;
        case '2':
            cin.ignore();
            obj.extractBook();
            break;
        case '3':
            cin.ignore();
            obj.addBook();
            break;
        case '4':
            cout << "Exiting..." << endl;
            return 0;
        default:
            cout << "Invalid Choice...!" << endl;
        }
    } while (choice != '4');

    return 0;
}

bool LibraryManagementSystem::login() {
    string username, password, storedUsername, storedPassword;
    int attempt = 0;
    char choice;

    while (attempt < 3) {
        cout << "\n1- Login" << endl;
        cout << "2- Register" << endl;
        cout << "Enter Your Choice :: ";
        cin >> choice;

        if (choice == '1') {
            cout << "Enter Username: ";
            cin >> username;
            cout << "Enter Password: ";
            cin >> password;

            file.open("users.txt", ios::in);
            if (file.is_open()) {
                bool isLoggedIn = false;
                while (file >> storedUsername >> storedPassword) {
                    if (username == storedUsername && password == storedPassword) {
                        cout << "Login Successful!" << endl;
                        isLoggedIn = true;
                        break;
                    }
                }
                file.close();

                if (isLoggedIn) {
                    return true;
                } else {
                    cout << "Invalid username or password. Try again." << endl;
                    attempt++;
                }
            }
        } else if (choice == '2') {
            registerUser();
        } else {
            cout << "Invalid choice." << endl;
        }
    }

    cout << "Too many failed attempts. Exiting..." << endl;
    return false;
}

void LibraryManagementSystem::registerUser() {
    string username, password;
    cout << "Register New User" << endl;
    cout << "Enter New Username: ";
    cin >> username;
    cout << "Enter New Password: ";
    cin >> password;

    file.open("users.txt", ios::out | ios::app);
    if (file.is_open()) {
        file << username << " " << password << endl;
        file.close();
        cout << "Registration Successful! You can now login." << endl;
    } else {
        cout << "Error in opening the file!" << endl;
    }
}

void LibraryManagementSystem::addBook() {
    cout << "\nEnter Book ID :: ";
    getline(cin, id);
    cout << "Enter Book Name :: ";
    getline(cin, name);
    cout << "Enter Book's Author name :: ";
    getline(cin, author);

    file.open("bookData.txt", ios::out | ios::app);
    file << id << "*" << name << "*" << author << endl;
    file.close();
}

void LibraryManagementSystem::showAll() {
    file.open("bookData.txt", ios::in);
    getline(file, id, '*');
    getline(file, name, '*');
    getline(file, author, '\n');
    cout << "\n\n";
    cout << "\t\t Book Id \t\t\t Book Name \t\t\t Author's Name" << endl;
    while (!file.eof()) {
        cout << "\t\t " << id << " \t\t\t\t " << name << " \t\t\t " << author << endl;

        getline(file, id, '*');
        getline(file, name, '*');
        getline(file, author, '\n');
    }
    file.close();
}

void LibraryManagementSystem::extractBook() {
    showAll();
    cout << "Enter Book Id :: ";
    getline(cin, search);

    file.open("bookData.txt", ios::in);
    getline(file, id, '*');
    getline(file, name, '*');
    getline(file, author, '\n');

    cout << "\n\n";
    cout << "\t\t Book Id \t\t\t Book Name \t\t\t Author's Name" << endl;
    while (!file.eof()) {
        if (search == id) {
            cout << "\t\t " << id << " \t\t\t " << name << " \t\t\t " << author << endl;
            cout << "Book Extracted Successfully...!" << endl;
        }
        getline(file, id, '*');
        getline(file, name, '*');
        getline(file, author, '\n');
    }
    file.close();
}
