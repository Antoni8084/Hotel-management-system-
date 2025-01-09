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
    double discountedPrice; // Stores the final price after applying discounts
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
vector<Customer> history;

string currentUserRole = "guest";
const string adminPassword = "admin123";

double calculateDiscountedPrice(double pricePerNight, int nights) {
    double totalPrice = pricePerNight * nights;
    if (nights > 10) {
        return totalPrice * 0.8; // 20% discount
    } else if (nights > 5) {
        return totalPrice * 0.9; // 10% discount
    }
    return totalPrice;
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

            double discountedPrice = calculateDiscountedPrice(room.pricePerNight, nights);

            room.isAvailable = false;
            customers.push_back({customerName, customerPhone, roomNumber, nights, discountedPrice});
            cout << "Room " << room.roomNumber << " booked successfully.\n";
            cout << "Total price after discount: $" << discountedPrice << "\n";
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
        cout << "Name: " << customer.name 
             << ", Phone: " << customer.phone 
             << ", Room: " << customer.roomNumber 
             << ", Nights: " << customer.nights 
             << ", Total Price: $" << customer.discountedPrice << "\n";
    }
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
        cout << "3. Book Room\n";
        cout << "4. Display Customer Details\n";
        cout << "5. Checkout Room\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            login();
        } else if (choice == 2) {
            displayRooms();
        } else if (choice == 3) {
            bookRoom();
        } else if (choice == 4) {
            displayCustomerDetails();
        } else if (choice == 5) {
            checkoutRoom();
        }

    } while (choice != 6);

    return 0;
}