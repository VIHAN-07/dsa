#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Student {
    int rollNo;
    string name;
    string div;
};

class StudentDetails {
    fstream file;

public:
    StudentDetails() {
        // Creating a base file
        file.open("studentdb.txt", ios::out);
        file << "RollNo\t\tName\t\tDivision\n";
        file.close();
    }

    void insertData();
    void addNewRecord();
    void display();
    void deleteDB(string key);
    void search(string key);
    void modifyRecord(string key);
};

// Function to insert data
void StudentDetails::insertData() {
    file.open("studentdb.txt", ios::out | ios::app);
    int n;
    cout << "How many students?\n";
    cin >> n;
    vector<Student> students(n); // Use vector for dynamic sizing

    for (int i = 0; i < n; i++) {
        cout << "Enter Name: ";
        cin.ignore(); // Clear the newline character from the input buffer
        getline(cin, students[i].name);
        cout << "Enter Roll number: ";
        cin >> students[i].rollNo;
        cout << "Enter Division: ";
        cin >> students[i].div;
        file << students[i].rollNo << "\t\t" << students[i].name << "\t\t" << students[i].div << "\n";
    }
    file.close();
}

// Function to search a particular student by their roll number or name
void StudentDetails::search(string key) {
    file.open("studentdb.txt", ios::in);
    string rollNo, name, div;
    bool found = false;

    while (file >> rollNo >> name >> div) {
        if (rollNo == key || name == key) {
            found = true;
            cout << "Student Found!\n";
            cout << "RollNo\t\tName\t\tDivision\n";
            cout << rollNo << "\t\t" << name << "\t\t" << div << "\n";
            break; // Exit loop after finding the student
        }
    }
    file.close();
    if (!found) {
        cout << "Entry not found!\n";
    }
}

// Function to display all records in the current file
void StudentDetails::display() {
    file.open("studentdb.txt", ios::in);
    string line;

    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

// Function to modify a particular record by roll number or name
void StudentDetails::modifyRecord(string key) {
    file.open("studentdb.txt", ios::in | ios::out);
    fstream file2;
    file2.open("temp.txt", ios::out);
    string rollNo, name, div , temp;
    int choice;
    bool found = false;

    while (file >> rollNo >> name >> div) {
        if (rollNo == key || name == key) {
            found = true;
            cout << "Current Information:\n";
            cout << "RollNo\t\tName\t\tDivision\n";
            cout << rollNo << "\t\t" << name << "\t\t" << div << "\n";
            cout << "Enter field to change:\n";
            cout << "Menu\n1. Roll number\n2. Name\n3. Division\n";
            do {
                cout << "Enter a valid choice: ";
                cin >> choice;
            } while (choice < 1 || choice > 3);

            switch (choice) {
                case 1:
                    cout << "Enter the new roll number: ";
                    cin >> rollNo;
                    break;
                case 2:
                    cout << "Enter the new name: ";
                    cin.ignore();
                    getline(cin, name);
                    break;
                case 3:
                    cout << "Enter the new division: ";
                    cin >> div;
                    break;
            }
        }
        file2 << rollNo << "\t\t" << name << "\t\t" << div << "\n";
    }
    file.close();
    file2.close();
    remove("studentdb.txt");
    rename("temp.txt", "studentdb.txt");

    if (!found) {
        cout << "Entry not found!\n";
    }
}

// Function to delete a record of a student by their roll number or name
void StudentDetails::deleteDB(string key) {
    file.open("studentdb.txt", ios::in | ios::out);
    fstream file2;
    file2.open("temp.txt", ios::out);
    string rollNo, name, div;
    bool found = false;

    while (file >> rollNo >> name >> div) {
        if (rollNo == key || name == key) {
            cout << "This information is deleted:\n";
            cout << "RollNo\t\tName\t\tDivision\n";
            cout << rollNo << "\t\t" << name << "\t\t" << div << "\n\n";
            found = true;
        } else {
            file2 << rollNo << "\t\t" << name << "\t\t" << div << "\n";
        }
    }
    file.close();
    file2.close();
    remove("studentdb.txt");
    rename("temp.txt", "studentdb.txt");

    if (!found) {
        cout << "Entry not found!\n";
    }
}

// Function to add a single record to the end of the file
void StudentDetails::addNewRecord() {
    file.open("studentdb.txt", ios::app);
    Student s1;

    if (file) {
        cout << "Enter the details of the new student:\n";
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, s1.name);
        cout << "Enter Roll number: ";
        cin >> s1.rollNo;
        cout << "Enter Division: ";
        cin >> s1.div;
        file << s1.rollNo << "\t\t" << s1.name << "\t\t" << s1.div << "\n";
        file.close();
    } else {
        cout << "Error opening the file.\n";
    }
}

int main() {
    StudentDetails DB1;
    cout << "Enter the details of students:\n";
    DB1.insertData(); // Initially entering students to the file
    cout << endl;

    int choice;
    string temp;

    do {
        cout << "Menu:\n";
        cout << "1. Add new Records\n";
        cout << "2. Display all records\n";
        cout << "3. Modify existing record\n";
        cout << "4. Delete a record\n";
        cout << "5. Search a record\n";
        cout << "6. Exit\n";
        cout << "Enter a valid choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                DB1.insertData();
                break;
            case 2:
                DB1.display();
                break;
            case 3:
                cout << "Enter the Roll number / Name of the student to modify their record: ";
                cin >> temp;
                DB1.modifyRecord(temp);
                break;
            case 4:
                cout << "Enter the Roll number / Name of the student to delete their record: ";
                cin >> temp;
                DB1.deleteDB(temp);
                break;
            case 5:
                cout << "Enter the Roll number / Name of the student to search their record: ";
                cin >> temp;
                DB1.search(temp);
                break;
            case 6:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}