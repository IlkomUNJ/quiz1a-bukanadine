#include <iostream>
#include <vector>
#include <algorithm>
#include "bank_customer.h"
#include "buyer.h"
#include "seller.h"

enum PrimaryPrompt{LOGIN, REGISTER, EXIT, ADMIN_LOGIN};
enum RegisterPrompt{CREATE_BUYER, CREATE_SELLER, BACK};
enum AdminPrompt{VIEW_ALL_BUYERS, VIEW_ALL_SELLERS, VIEW_BUYER_DETAILS, VIEW_SELLER_DETAILS, SEARCH_USER, CREATE_USER, REMOVE_USER, ADMIN_LOGOUT};
using namespace std;

vector<BankCustomer*> bankCustomers;
vector<Buyer*> buyers;
vector<seller*> sellers;

void viewAllBuyers() {
    if (buyers.empty()) {
        cout << "No buyers found." << endl;
        return;
    }
    cout << "All Buyers:" << endl;
    for (size_t i = 0; i < buyers.size(); i++) {
        cout << "ID: " << buyers[i]->getId() << ", Name: " << buyers[i]->getName() << endl;
    }
}

void viewAllSellers() {
    if (sellers.empty()) {
        cout << "No sellers found." << endl;
        return;
    }
    cout << "All Sellers:" << endl;
    for (size_t i = 0; i < sellers.size(); i++) {
        cout << "ID: " << sellers[i]->getId() << ", Name: " << sellers[i]->getName() << endl;
    }
}

void viewBuyerDetails() {
    if (buyers.empty()) {
        cout << "No buyers found." << endl;
        return;
    }
    cout << "Buyer Details:" << endl;
    for (size_t i = 0; i < buyers.size(); i++) {
        cout << "Buyer ID: " << buyers[i]->getId() << ", Name: " << buyers[i]->getName() << endl;
        cout << "Bank Account Details:" << endl;
        buyers[i]->getAccount().printInfo();
        cout << "---" << endl;
    }
}

void viewSellerDetails() {
    if (sellers.empty()) {
        cout << "No sellers found." << endl;
        return;
    }
    cout << "Seller Details:" << endl;
    for (size_t i = 0; i < sellers.size(); i++) {
        cout << "Seller ID: " << sellers[i]->getId() << ", Name: " << sellers[i]->getName() << endl;
        cout << "Bank Account Details:" << endl;
        sellers[i]->getAccount().printInfo();
        cout << "---" << endl;
    }
}

void searchUser() {
    cout << "Search by:" << endl;
    cout << "1. Name" << endl;
    cout << "2. Account ID" << endl;
    cout << "3. Phone Number" << endl;
    cout << "4. Address" << endl;
    int searchChoice;
    cin >> searchChoice;
    
    if (searchChoice == 1) {
        string searchName;
        cout << "Enter name to search: ";
        cin.ignore();
        getline(cin, searchName);
        
        bool found = false;
        cout << "Buyers with name '" << searchName << "':" << endl;
        for (size_t i = 0; i < buyers.size(); i++) {
            if (buyers[i]->getName().find(searchName) != string::npos) {
                cout << "Buyer ID: " << buyers[i]->getId() << ", Name: " << buyers[i]->getName() << endl;
                found = true;
            }
        }
        
        cout << "Sellers with name '" << searchName << "':" << endl;
        for (size_t i = 0; i < sellers.size(); i++) {
            if (sellers[i]->getName().find(searchName) != string::npos) {
                cout << "Seller ID: " << sellers[i]->getId() << ", Name: " << sellers[i]->getName() << endl;
                found = true;
            }
        }
        
        if (!found) {
            cout << "No users found with that name." << endl;
        }
    } else if (searchChoice == 2) {
        int searchId;
        cout << "Enter account ID to search: ";
        cin >> searchId;
        
        bool found = false;
        for (size_t i = 0; i < buyers.size(); i++) {
            if (buyers[i]->getId() == searchId) {
                cout << "Found Buyer - ID: " << buyers[i]->getId() << ", Name: " << buyers[i]->getName() << endl;
                buyers[i]->getAccount().printInfo();
                found = true;
            }
        }
        
        for (size_t i = 0; i < sellers.size(); i++) {
            if (sellers[i]->getId() == searchId) {
                cout << "Found Seller - ID: " << sellers[i]->getId() << ", Name: " << sellers[i]->getName() << endl;
                sellers[i]->getAccount().printInfo();
                found = true;
            }
        }
        
        if (!found) {
            cout << "No user found with that ID." << endl;
        }
    } else if (searchChoice == 3) {
        string searchPhone;
        cout << "Enter phone number to search: ";
        cin.ignore();
        getline(cin, searchPhone);
        cout << "Phone number search feature not implemented yet (requires additional user data fields)." << endl;
    } else if (searchChoice == 4) {
        string searchAddress;
        cout << "Enter address to search: ";
        cin.ignore();
        getline(cin, searchAddress);
        cout << "Address search feature not implemented yet (requires additional user data fields)." << endl;
    } else {
        cout << "Invalid search option." << endl;
    }
}

void createUser() {
    cout << "Create:" << endl;
    cout << "1. Buyer Account" << endl;
    cout << "2. Seller Account" << endl;
    cout << "3. Bank Account" << endl;
    int createChoice;
    cin >> createChoice;
    
    if (createChoice == 1) {
        int id;
        string name;
        double balance;
        
        cout << "Enter buyer ID: ";
        cin >> id;
        cout << "Enter buyer name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter initial balance: ";
        cin >> balance;
        
        BankCustomer* newBankCustomer = new BankCustomer(id, name, balance);
        bankCustomers.push_back(newBankCustomer);
        
        Buyer* newBuyer = new Buyer(id, name, *newBankCustomer);
        buyers.push_back(newBuyer);
        
        cout << "Buyer account created successfully." << endl;
    } else if (createChoice == 2) {
        int buyerId, sellerId;
        string sellerName;
        
        cout << "Enter buyer ID to upgrade to seller: ";
        cin >> buyerId;
        
        bool buyerFound = false;
        for (size_t i = 0; i < buyers.size(); i++) {
            if (buyers[i]->getId() == buyerId) {
                cout << "Enter seller ID: ";
                cin >> sellerId;
                cout << "Enter seller name: ";
                cin.ignore();
                getline(cin, sellerName);
                
                seller* newSeller = new seller(*buyers[i], sellerId, sellerName);
                sellers.push_back(newSeller);
                
                cout << "Seller account created successfully." << endl;
                buyerFound = true;
                break;
            }
        }
        
        if (!buyerFound) {
            cout << "Buyer with ID " << buyerId << " not found." << endl;
        }
    } else if (createChoice == 3) {
        int id;
        string name;
        double balance;
        
        cout << "Enter bank customer ID: ";
        cin >> id;
        cout << "Enter bank customer name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter initial balance: ";
        cin >> balance;
        
        BankCustomer* newBankCustomer = new BankCustomer(id, name, balance);
        bankCustomers.push_back(newBankCustomer);
        
        cout << "Bank account created successfully." << endl;
    }
}

void removeUser() {
    int userId;
    cout << "Enter user ID to remove: ";
    cin >> userId;
    
    bool removed = false;
    
    for (size_t i = 0; i < buyers.size(); i++) {
        if (buyers[i]->getId() == userId) {
            delete buyers[i];
            buyers.erase(buyers.begin() + i);
            cout << "Buyer removed successfully." << endl;
            removed = true;
            break;
        }
    }
    
    for (size_t i = 0; i < sellers.size(); i++) {
        if (sellers[i]->getId() == userId) {
            delete sellers[i];
            sellers.erase(sellers.begin() + i);
            cout << "Seller removed successfully." << endl;
            removed = true;
            break;
        }
    }
    
    for (size_t i = 0; i < bankCustomers.size(); i++) {
        if (bankCustomers[i]->getId() == userId) {
            delete bankCustomers[i];
            bankCustomers.erase(bankCustomers.begin() + i);
            cout << "Bank customer removed successfully." << endl;
            removed = true;
            break;
        }
    }
    
    if (!removed) {
        cout << "User with ID " << userId << " not found." << endl;
    }
}

bool checkRootLogin(const string& username, const string& password) {
    const string ADMIN_USERNAME = "root";
    const string ADMIN_PASSWORD = "toor";
    return (username == ADMIN_USERNAME && password == ADMIN_PASSWORD);
}

void adminMenu() {
    AdminPrompt adminPrompt = VIEW_ALL_BUYERS;
    
    while (adminPrompt != ADMIN_LOGOUT) {
        cout << "\nAdmin Menu:" << endl;
        cout << "1. View All Buyers" << endl;
        cout << "2. View All Sellers" << endl;
        cout << "3. View All Buyer Details" << endl;
        cout << "4. View All Seller Details" << endl;
        cout << "5. Search User" << endl;
        cout << "6. Create User" << endl;
        cout << "7. Remove User" << endl;
        cout << "8. Logout" << endl;
        
        int choice;
        cin >> choice;
        adminPrompt = static_cast<AdminPrompt>(choice - 1);
        
        switch (adminPrompt) {
            case VIEW_ALL_BUYERS:
                viewAllBuyers();
                break;
            case VIEW_ALL_SELLERS:
                viewAllSellers();
                break;
            case VIEW_BUYER_DETAILS:
                viewBuyerDetails();
                break;
            case VIEW_SELLER_DETAILS:
                viewSellerDetails();
                break;
            case SEARCH_USER:
                searchUser();
                break;
            case CREATE_USER:
                createUser();
                break;
            case REMOVE_USER:
                removeUser();
                break;
            case ADMIN_LOGOUT:
                cout << "Logging out from admin panel." << endl;
                break;
            default:
                cout << "Invalid option." << endl;
                break;
        }
    }
}

void cleanupMemory() {
    for (size_t i = 0; i < buyers.size(); i++) {
        delete buyers[i];
    }
    for (size_t i = 0; i < sellers.size(); i++) {
        delete sellers[i];
    }
    for (size_t i = 0; i < bankCustomers.size(); i++) {
        delete bankCustomers[i];
    }
    buyers.clear();
    sellers.clear();
    bankCustomers.clear();
}

int main() {
    PrimaryPrompt prompt = LOGIN;
    RegisterPrompt regPrompt = CREATE_BUYER;
    string username, password;

    while (prompt != EXIT) {
        cout << "Select an option: " << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cout << "4. Admin Login" << endl;
        int choice;
        cin >> choice;
        prompt = static_cast<PrimaryPrompt>(choice - 1);
        switch (prompt) {
            case LOGIN:
                cout << "Login selected." << endl;
                break;
            case REGISTER:
                regPrompt = CREATE_BUYER;
                while (regPrompt != BACK){
                    cout << "Register selected. " << endl;
                    cout << "Select an option: " << endl;
                    cout << "1. Create Buyer Account" << endl;
                    cout << "2. Create Seller Account" << endl;
                    cout << "3. Back" << endl;
                    int regChoice;
                    cin >> regChoice;
                    regPrompt = static_cast<RegisterPrompt>(regChoice - 1);
                    switch (regPrompt) {
                        case CREATE_BUYER:
                            cout << "Create Buyer Account selected." << endl;
                            break;
                        case CREATE_SELLER:
                            cout << "Create Seller Account selected." << endl;
                            break;
                        case BACK:
                            cout << "Back selected." << endl;
                            break;
                        default:
                            cout << "Invalid option." << endl;
                            break;
                    }
                }
                break;
            case EXIT:
                cout << "Exiting." << endl;
                cleanupMemory();
                break;
            case ADMIN_LOGIN:
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;
                
                if (checkRootLogin(username, password)) {
                    cout << "Admin login successful!" << endl;
                    adminMenu();
                } else {
                    cout << "Invalid credentials. Access denied." << endl;
                }
                break;
            default:
                cout << "Invalid option." << endl;
                break;
        }
        cout << endl;
    }

    return 0;
}