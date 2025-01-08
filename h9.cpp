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

string currentUserRole = "admin"; // Default: admin. Options: "admin" or "staff".

void displayRooms() {
    cout << "\n--- Room Details ---\n";
    for (const auto &room : rooms) {
        cout << "Room " << room.roomNumber << " (" << room.roomType 
             << ") - $" << room.pricePerNight << " per night. Available: " 
             << (room.isAvailable ? "Yes" : "No") << "\n";
    }
}

void bookRoom() {
    if (currentUserRole != "admin" && currentUserRole != "staff") {
        cout << "Access denied. Only admin or staff can book a room.\n";
        return;
    }

    int roomNumber, nights;
    string customerName, customerPhone;

    cout << "Enter room number to book: ";
    cin >> roomNumber;
    cin.ignore();

    for (auto &room : rooms) {
        if (room.roomNumber == roomNumber) {
            if (!room.isAvailable) {
                cout << "Room already booked.\n";
                return;
            }
            cout << "Enter customer name: ";
            getline(cin, customerName);
            cout << "Enter customer phone number: ";
            getline(cin, customerPhone);
            cout << "Enter number of nights: ";
            cin >> nights;

            room.isAvailable = false;
            customers.push_back({customerName, customerPhone, roomNumber, nights});
            cout << "Room " << room.roomNumber << " booked successfully.\n";
            return;
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
            room.isAvailable = true;

            customers.erase(remove_if(customers.begin(), customers.end(),
                [roomNumber](Customer &customer) {
                    return customer.roomNumber == roomNumber;
                }),
                customers.end());
            cout << "Checkout successful for room " << room.roomNumber << ".\n";
            return;
        }
    }
    cout << "Invalid room number.\n";
}

void displayCustomerDetails() {
    if (customers.empty()) {
        cout << "No customers have booked rooms.\n";
        return;
    }
    cout << "\n--- Customer Details ---\n";
    for (const auto &customer : customers) {
        cout << "Name: " << customer.name << ", Phone: " << customer.phone
             << ", Room: " << customer.roomNumber 
             << ", Nights: " << customer.nights << "\n";
    }
}

void generateRevenueReport() {
    if (currentUserRole != "admin") {
        cout << "Access denied. Only admin can generate revenue reports.\n";
        return;
    }

    if (customers.empty()) {
        cout << "No rooms have been booked yet.\n";
        return;
    }

    double totalRevenue = 0.0;
    for (const auto &customer : customers) {
        for (const auto &room : rooms) {
            if (room.roomNumber == customer.roomNumber) {
                totalRevenue += room.pricePerNight * customer.nights;
                break;
            }
        }
    }

    cout << "\n--- Revenue Report ---\n";
    cout << "Total Revenue Generated: $" << totalRevenue << "\n";
}

void login() {
    string role;
    cout << "Enter role (admin/staff): ";
    cin >> role;

    if (role == "admin" || role == "staff") {
        currentUserRole = role;
        cout << "Logged in as " << role << ".\n";
    } else {
        cout << "Invalid role. Defaulting to admin.\n";
        currentUserRole = "admin";
    }
}

int main() {
    int choice;
    do {
        cout << "--- Hotel Management System ---\n";
        cout << "1. Login\n";
        cout << "2. Display Rooms\n";
        cout << "3. Book Room\n";
        cout << "4. Checkout Room\n";
        cout << "5. Display Customer Details\n";
        cout << "6. Generate Revenue Report\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            login();
        } else if (choice == 2) {
            displayRooms();
        } else if (choice == 3) {
            bookRoom();
        } else if (choice == 4) {
            checkoutRoom();
        } else if (choice == 5) {
            displayCustomerDetails();
        } else if (choice == 6) {
            generateRevenueReport();
        }

    } while (choice != 7);

    return 0;
}