#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <map>

using namespace std;

// Structure to store expense details
struct Expense {
    double amount;
    string category;
    string description;
};

// Vector to store expenses
vector<Expense> expenses;

// File to store expenses
const string FILE_NAME = "expenses.txt";

// Function to save expenses to a file
void saveExpenses() {
    ofstream file(FILE_NAME);
    if (file.is_open()) {
        for (const auto &exp : expenses) {
            file << exp.amount << "," << exp.category << "," << exp.description << endl;
        }
        file.close();
        cout << "Expenses saved successfully!\n";
    } else {
        cout << "Error saving expenses.\n";
    }
}

// Function to load expenses from a file
void loadExpenses() {
    ifstream file(FILE_NAME);
    if (file.is_open()) {
        Expense exp;
        while (file >> exp.amount) {
            file.ignore(); // Ignore comma
            getline(file, exp.category, ',');
            getline(file, exp.description);
            expenses.push_back(exp);
        }
        file.close();
        cout << "Expenses loaded successfully!\n";
    } else {
        cout << "No previous expenses found.\n";
    }
}

// Function to add an expense
void addExpense() {
    Expense exp;
    cout << "Enter amount: ";
    cin >> exp.amount;
    cin.ignore(); // Ignore newline
    cout << "Enter category (Food, Transport, etc.): ";
    getline(cin, exp.category);
    cout << "Enter description: ";
    getline(cin, exp.description);
    expenses.push_back(exp);
    cout << "Expense added successfully!\n";
    saveExpenses();
}

// Function to display all expenses
void viewExpenses() {
    if (expenses.empty()) {
        cout << "No expenses recorded.\n";
        return;
    }
    cout << "\nAll Expenses:\n";
    cout << "----------------------------------------\n";
    cout << setw(10) << "Amount" << setw(15) << "Category" << setw(25) << "Description" << endl;
    cout << "----------------------------------------\n";
    for (const auto &exp : expenses) {
        cout << setw(10) << exp.amount << setw(15) << exp.category << setw(25) << exp.description << endl;
    }
}

// Function to generate expense reports
void generateReport() {
    if (expenses.empty()) {
        cout << "No expenses to generate a report.\n";
        return;
    }
    map<string, double> categoryTotals;
    double totalSpending = 0;

    for (const auto &exp : expenses) {
        categoryTotals[exp.category] += exp.amount;
        totalSpending += exp.amount;
    }

    cout << "\nExpense Report:\n";
    cout << "----------------------------\n";
    for (const auto &pair : categoryTotals) {
        cout << pair.first << ": $" << fixed << setprecision(2) << pair.second << endl;
    }
    cout << "----------------------------\n";
    cout << "Total Spending: $" << fixed << setprecision(2) << totalSpending << endl;
}

// Main function
int main() {
    loadExpenses(); // Load previous data if available
    int choice;

    do {
        cout << "\nExpense Tracker Menu:\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Generate Report\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore newline

        switch (choice) {
            case 1:
                addExpense();
                break;
            case 2:
                viewExpenses();
                break;
            case 3:
                generateReport();
                break;
            case 4:
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 4);

    return 0;
}
