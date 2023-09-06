#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <map>

using namespace std;

// Define a struct to represent the subcolumns in columns 4 and 5
struct SubColumn {
    int recycle;
    int plastic;
    int trash;
};

// Define a struct to represent each row in the spreadsheet
struct SpreadsheetRow {
    string date;
    string time;
    string user;
    SubColumn wasteCollected;
    SubColumn wasteDisposed;
    int transported;
    int missing;
    string approval; // Change the data type to string
};

// Define user roles
enum UserRole {
    MANAGER,
    SUPERVISOR,
    WORKER
};

// Define a struct to represent user information
struct User {
    UserRole role;
};

// Define a vector to store user information
vector<User> users;

// Define maps for storing passwords for workers and supervisors
map<string, string> workerPasswords;
map<string, string> supervisorPasswords;

// Define a map for storing worker usernames and corresponding worker numbers
map<string, int> workerNumbers;

// Define a vector to store the spreadsheet data
vector<SpreadsheetRow> spreadsheetData;

// Function to get the current date and time
string getCurrentDateTime() {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    char dateTime[100];
    strftime(dateTime, sizeof(dateTime), "%Y-%m-%d %H:%M:%S", localTime);
    return dateTime;
}

// Function to add a new row to the spreadsheet
void addRow(User& user) {
    SpreadsheetRow newRow;
    newRow.date = getCurrentDateTime();
    newRow.time = newRow.date;

    // Set the user based on their role
    if (user.role == WORKER) {
        newRow.user = "Worker";
    } else if (user.role == SUPERVISOR) {
        newRow.user = "Supervisor";
    } else if (user.role == MANAGER) {
        newRow.user = "Manager";
    }

    // Prompt user for input and populate the newRow struct
    if (user.role == WORKER) {
        cout << "Enter Waste Collected (Recycle, Plastic, Trash): ";
        cin >> newRow.wasteCollected.recycle >> newRow.wasteCollected.plastic >> newRow.wasteCollected.trash;
    } else if (user.role == SUPERVISOR) {
        cout << "Enter Waste Collected (Recycle, Plastic, Trash): ";
        cin >> newRow.wasteCollected.recycle >> newRow.wasteCollected.plastic >> newRow.wasteCollected.trash;
        cout << "Enter Waste Disposed (Recycle, Plastic, Trash): ";
        cin >> newRow.wasteDisposed.recycle >> newRow.wasteDisposed.plastic >> newRow.wasteDisposed.trash;
        cout << "Enter Transported: ";
        cin >> newRow.transported;
        cout << "Enter Missing: ";
        cin >> newRow.missing;
        cout << "You do not have permission to enter Approval." << endl;
    } else if (user.role == MANAGER) {
        cout << "Enter Waste Collected (Recycle, Plastic, Trash): ";
        cin >> newRow.wasteCollected.recycle >> newRow.wasteCollected.plastic >> newRow.wasteCollected.trash;
        cout << "Enter Waste Disposed (Recycle, Plastic, Trash): ";
        cin >> newRow.wasteDisposed.recycle >> newRow.wasteDisposed.plastic >> newRow.wasteDisposed.trash;
        cout << "Enter Transported: ";
        cin >> newRow.transported;
        cout << "Enter Missing: ";
        cin >> newRow.missing;
        cout << "Enter Approval (Y for 'Approved', N for 'Not Approved'): ";
        char approvalInput;
        cin >> approvalInput;

        if (approvalInput == 'Y' || approvalInput == 'y') {
            newRow.approval = "Approved";
        } else if (approvalInput == 'N' || approvalInput == 'n') {
            newRow.approval = "Not Approved";
        } else {
            cout << "Invalid input. Use 'Y' for 'Approved' and 'N' for 'Not Approved'." << endl;
            return;
        }
    }

    spreadsheetData.push_back(newRow);
    cout << "Entry added successfully!" << endl;
}

// Function to display the entire spreadsheet
void displaySpreadsheet(User& user) {
    cout << "Date\tTime\tUser\tWaste Collected (Recycle, Plastic, Trash)\tWaste Disposed (Recycle, Plastic, Trash)\tTransported\tMissing\tApproval" << endl;

    for (const auto& row : spreadsheetData) {
        // Check if the approval status is "Approved" and prevent editing
        if (row.approval == "Approved") {
            cout << row.date << "\t" << row.time << "\t" << row.user << "\t"
                 << row.wasteCollected.recycle << ", " << row.wasteCollected.plastic << ", " << row.wasteCollected.trash << "\t"
                 << row.wasteDisposed.recycle << ", " << row.wasteDisposed.plastic << ", " << row.wasteDisposed.trash << "\t"
                 << row.transported << "\t" << row.missing << "\t" << row.approval << " (Locked)" << endl;
        } else {
            cout << row.date << "\t" << row.time << "\t" << row.user << "\t"
                 << row.wasteCollected.recycle << ", " << row.wasteCollected.plastic << ", " << row.wasteCollected.trash << "\t"
                 << row.wasteDisposed.recycle << ", " << row.wasteDisposed.plastic << ", " << row.wasteDisposed.trash << "\t"
                 << row.transported << "\t" << row.missing << "\t" << row.approval << endl;
        }
    }
}

// Function to allow supervisors and managers to edit previous entries
void editEntry(User& user) {
    int entryNumber;
    cout << "Enter the entry number you want to edit: ";
    cin >> entryNumber;

    if (entryNumber < 1 || entryNumber > spreadsheetData.size()) {
        cout << "Invalid entry number." << endl;
        return;
    }

    SpreadsheetRow& entry = spreadsheetData[entryNumber - 1];

    // Check if the approval status is "Approved" and prevent editing
    if (entry.approval == "Approved") {
        cout << "This entry is already approved and cannot be edited." << endl;
        return;
    }

    if (user.role == SUPERVISOR || user.role == MANAGER) {
        cout << "Editing entry #" << entryNumber << endl;
        cout << "Existing Values:" << endl;
        cout << "Date: " << entry.date << endl;
        cout << "Time: " << entry.time << endl;
        cout << "User: " << entry.user << endl;
        cout << "Waste Collected (Recycle, Plastic, Trash): " << entry.wasteCollected.recycle << ", " << entry.wasteCollected.plastic << ", " << entry.wasteCollected.trash << endl;
        cout << "Waste Disposed (Recycle, Plastic, Trash): " << entry.wasteDisposed.recycle << ", " << entry.wasteDisposed.plastic << ", " << entry.wasteDisposed.trash << endl;
        cout << "Transported: " << entry.transported << endl;
        cout << "Missing: " << entry.missing << endl;

        cout << "Enter Waste Collected (Recycle, Plastic, Trash): ";
        cin >> entry.wasteCollected.recycle >> entry.wasteCollected.plastic >> entry.wasteCollected.trash;
        cout << "Enter Waste Disposed (Recycle, Plastic, Trash): ";
        cin >> entry.wasteDisposed.recycle >> entry.wasteDisposed.plastic >> entry.wasteDisposed.trash;
        cout << "Enter Transported: ";
        cin >> entry.transported;
        cout << "Enter Missing: ";
        cin >> entry.missing;

        if (user.role == MANAGER) {
            cout << "Approval (Y for 'Approved', N for 'Not Approved'): ";
            char approvalInput;
            cin >> approvalInput;

            if (approvalInput == 'Y' || approvalInput == 'y') {
                entry.approval = "Approved";
            } else if (approvalInput == 'N' || approvalInput == 'n') {
                entry.approval = "Not Approved";
            } else {
                cout << "Invalid input. Use 'Y' for 'Approved' and 'N' for 'Not Approved'." << endl;
                return;
            }
        }

        // Ask for final confirmation
        char confirm;
        cout << "Are the values correct? (Y/N): ";
        cin >> confirm;

        if (confirm == 'Y' || confirm == 'y') {
            cout << "Entry #" << entryNumber << " edited successfully!" << endl;
        } else {
            cout << "Editing of entry #" << entryNumber << " canceled. Values reverted." << endl;
            // Revert to the previous values
            // You can add the code to revert the changes here if needed
        }
    } else {
        cout << "You do not have permission to edit entries." << endl;
    }
}

int main() {
    // Initialize user roles and passwords
    users.push_back({MANAGER});
    users.push_back({SUPERVISOR});

    // Initialize worker usernames and passwords
    for (int i = 1; i <= 12; ++i) {
        string password = "9988" + to_string(i);
        workerPasswords[password] = password;
        users.push_back({WORKER});
    }

    // Initialize supervisor passwords
    supervisorPasswords["1010"] = "1010";
    supervisorPasswords["1212"] = "1212";

    // Login screen
    cout << "Garbage Disposal Database Management System" << endl;
    cout << "Press Enter to continue/Esc to exit" << endl;

    while (true) {
        char key = cin.get();
        if (key == 27) { // ASCII code for Esc key
            cout << "Exiting the application..." << endl;
            break;
        } else if (key == '\n') {
            // Display options after 3 seconds
            cout << "Select an option:" << endl;
            cout << "1. Worker" << endl;
            cout << "2. Supervisor" << endl;
            cout << "3. Manager" << endl;

            int choice;
            cin >> choice;

            if (choice == 1) {
                // Worker login
                cout << "Enter your password: ";
                string password;
                cin >> password;

                if (workerPasswords.find(password) != workerPasswords.end()) {
                    User worker = {WORKER};
                    cout << "Correct Passcode - Access Granted" << endl;
                    // Allow the worker to make entries or view previous entries
                    while (true) {
                        cout << "Select an option:" << endl;
                        cout << "1. Make a new entry" << endl;
                        cout << "2. View previous entries" << endl;
                        cout << "3. Exit" << endl;
                        cin >> choice;
                        if (choice == 1) {
                            addRow(worker);
                        } else if (choice == 2) {
                            displaySpreadsheet(worker);
                        } else if (choice == 3) {
                            break;
                        } else {
                            cout << "Invalid choice." << endl;
                        }
                    }
                } else {
                    cout << "Incorrect password. Access denied." << endl;
                }
            } else if (choice == 2) {
                // Supervisor login
                cout << "Enter your password: ";
                string password;
                cin >> password;

                if (supervisorPasswords.find(password) != supervisorPasswords.end()) {
                    User supervisor = {SUPERVISOR};
                    cout << "Correct Passcode - Access Granted" << endl;
                    // Allow the supervisor to make entries or view previous entries
                    while (true) {
                        cout << "Select an option:" << endl;
                        cout << "1. Make a new entry" << endl;
                        cout << "2. View previous entries" << endl;
                        cout << "3. Edit previous entries" << endl;
                        cout << "4. Exit" << endl;
                        cin >> choice;
                        if (choice == 1) {
                            addRow(supervisor);
                        } else if (choice == 2) {
                            displaySpreadsheet(supervisor);
                        } else if (choice == 3) {
                            editEntry(supervisor);
                        } else if (choice == 4) {
                            break;
                        } else {
                            cout << "Invalid choice." << endl;
                        }
                    }
                } else {
                    cout << "Incorrect password. Access denied." << endl;
                }
            } else if (choice == 3) {
                // Manager login
                cout << "Enter your password: ";
                string password;
                cin >> password;

                // Assume a single password for the manager
                if (password == "2121") {
                    User manager = {MANAGER};
                    cout << "Correct Passcode - Access Granted" << endl;
                    // Allow the manager to make entries or view previous entries
                    while (true) {
                        cout << "Select an option:" << endl;
                        cout << "1. Make a new entry" << endl;
                        cout << "2. View previous entries" << endl;
                        cout << "3. Edit previous entries" << endl;
                        cout << "4. Exit" << endl;
                        cin >> choice;
                        if (choice == 1) {
                            addRow(manager);
                        } else if (choice == 2) {
                            displaySpreadsheet(manager);
                        } else if (choice == 3) {
                            editEntry(manager);
                        } else if (choice == 4) {
                            break;
                        } else {
                            cout << "Invalid choice." << endl;
                        }
                    }
                } else {
                    cout << "Incorrect password for manager. Access denied." << endl;
                }
            } else {
                cout << "Invalid choice." << endl;
            }
        }
    }

    return 0;
}
