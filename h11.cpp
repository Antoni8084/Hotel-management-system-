#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Room {
    int roomNumber;
    string roomType;
    double pricePerNight;
    bool isAvailable;
};

struct Customer {
    string name;
    string phone;
    int roomNumber;
    int nights;
};

vector<Room> rooms = {
    {101, "Single", 100.0, true},
    {102, "Single", 100.0, true},
    {201, "Double", 150.0, true},
    {202, "Double", 150.0, true},
    {301, "Suite", 300.0, true},
    {302, "Suite", 300.0, true}
};

vector<Customer> customers;

string currentUserRole = "guest"; 
const string adminPassword = "admin123"; 

void displayRooms() {
    cout << "\n--- Room Details ---\n";
    for (const auto &room : rooms) {
        cout << "Room " << room.roomNumber << " (" << room.roomType 
             << ") - $" << room.pricePerNight << " per night. Available: " 
             << (room.isAvailable ? "Yes" : "No") << "\n";
    }
}

void searchRooms() {
    int choice;
    cout << "\n--- Search Rooms ---\n";
    cout << "1. Search by room type\n";
    cout << "2. Search by price range\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        string roomType;
        cout << "Enter room type (Single/Double/Suite): ";
        cin >> roomType;

        cout << "\n--- Rooms of Type: " << roomType << " ---\n";
        bool found = false;
        for (const auto &room : rooms) {
            if (room.roomType == roomType) {
                cout << "Room " << room.roomNumber << " - $" << room.pricePerNight 
                     << " per night. Available: " << (room.isAvailable ? "Yes" : "No") << "\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No rooms found for the given type.\n";
        }
    } else if (choice == 2) {
        double minPrice, maxPrice;
        cout << "Enter minimum price: ";
        cin >> minPrice;
        cout << "Enter maximum price: ";
        cin >> maxPrice;

        cout << "\n--- Rooms in Price Range: $" << minPrice << " - $" << maxPrice << " ---\n";
        bool found = false;
        for (const auto &room : rooms) {
            if (room.pricePerNight >= minPrice && room.pricePerNight <= maxPrice) {
                cout << "Room " << room.roomNumber << " (" << room.roomType 
                     << ") - $" << room.pricePerNight << " per night. Available: " 
                     << (room.isAvailable ? "Yes" : "No") << "\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No rooms found in the given price range.\n";
        }
    } else {
        cout << "Invalid choice.\n";
    }
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
        cout << "3. Search Rooms\n"; // Added option for search
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            login();
        } else if (choice == 2) {
            displayRooms();
        } else if (choice == 3) {
            searchRooms();
        }

    } while (choice != 4);

    return 0;
}