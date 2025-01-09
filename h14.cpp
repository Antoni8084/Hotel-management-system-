#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Room {
    int roomNumber;
    string roomType;
    double pricePerNight;
    bool isAvailable;
    vector<string> waitlist; // Stores customer names waiting for the room
};

struct Customer {
    string name;
    string phone;
    int roomNumber;
    int nights;
    double discountedPrice;
};

vector<Room> rooms = {
    {101, "Single", 100.0, true, {}},
    {102, "Single", 100.0, true, {}},
    {201, "Double", 150.0, true, {}},
    {202, "Double", 150.0, true, {}},
    {301, "Suite", 300.0, true, {}},
    {302, "Suite", 300.0, true, {}}
};

vector<Customer> customers;
vector<Customer> history;

string currentUserRole = "guest";
const string adminPassword = "admin123";

void notifyWaitlist(Room &room) {
    if (!room.waitlist.empty()) {
        cout << "\n--- Notifications for Room " << room.roomNumber << " ---\n";
        for (const auto &name : room.waitlist) {
            cout << "Notifying " << name << ": Room " << room.roomNumber << " is now available.\n";
        }
        room.waitlist.clear(); // Clear the waitlist after notifications
    }
}

void addToWaitlist() {
    string customerName;
    int roomNumber;

    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, customerName);

    cout << "Enter room number to wait for: ";
    cin >> roomNumber;

    for (auto &room : rooms) {
        if (room.roomNumber == roomNumber) {
            if (!room.isAvailable) {
                room.waitlist.push_back(customerName);
                cout << "You have been added to the waitlist for room " << roomNumber << ".\n";
                return;
            } else {
                cout << "Room " << roomNumber << " is already available. You can book it now.\n";
                return;
            }
        }
    }
    cout << "Invalid room number.\n";
}

void checkoutRoom() {
    if (currentUserRole != "admin") {
        cout << "Access denied. Only admin can perform checkout.\n";
        return;
    }

    int roomNumber;
    cout << "Enter room number to checkout: ";
    cin >> roomNumber;

    for (auto &room : rooms) {
        if (room.roomNumber == roomNumber) {
            if (room.isAvailable) {
                cout << "Room is not currently booked.\n";
                return;
            }

            for (const auto &customer : customers) {
                if (customer.roomNumber == roomNumber) {
                    history.push_back(customer);
                    break;
                }
            }

            room.isAvailable = true;

            customers.erase(remove_if(customers.begin(), customers.end(),
                [roomNumber](Customer &customer) {
                    return customer.roomNumber == roomNumber;
                }),
                customers.end());
            cout << "Checkout successful for room " << room.roomNumber << ".\n";

            // Notify waitlist
            notifyWaitlist(room);
            return;
        }
    }
    cout << "Invalid room number.\n";
}

void login() {
    string role;
    cout << "Enter role (admin/staff): ";
    cin >> role;

    if (role == "admin") {
        string password;
        cout << "Enter admin password: ";
        cin >> password;

        if (password == adminPassword) {
            currentUserRole = "admin";
            cout << "Logged in as admin.\n";
        } else {
            cout << "Incorrect password. Defaulting to guest.\n";
            currentUserRole = "guest";
        }
    } else if (role == "staff") {
        currentUserRole = "staff";
        cout << "Logged in as staff.\n";
    } else {
        cout << "Invalid role. Defaulting to guest.\n";
        currentUserRole = "guest";
    }
}

int main() {
    int choice;
    do {
        cout << "--- Hotel Management System ---\n";
        cout << "1. Login\n";
        cout << "2. Display Rooms\n";
        cout << "3. Add to Waitlist\n";
        cout << "4. Checkout Room\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            login();
        } else if (choice == 2) {
            displayRooms();
        } else if (choice == 3) {
            addToWaitlist();
        } else if (choice == 4) {
            checkoutRoom();
        }

    } while (choice != 5);

    return 0;
}