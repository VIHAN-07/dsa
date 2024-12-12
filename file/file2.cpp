#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
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
        file.open("studentdb.txt", ios::out | ios::app);
        file.close();
    }

    void insertData();
    void display();
    void deleteDB(int rollNo);
    void search(int rollNo);
    void modifyRecord(int rollNo);
};

void StudentDetails::insertData() {
    file.open("studentdb.txt", ios::out | ios::app);

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    Student s;
    cout << "Enter Name: ";
    cin >> s.name;
    cout << "Enter Roll number: ";
    cin >> s.rollNo;
    cout << "Enter Division: ";
    cin >> s.div;

    file << s.rollNo << "\t" << s.name << "\t" << s.div << "\n";
    file.close();
}

void StudentDetails::display() {
    file.open("studentdb.txt", ios::in);

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    int rollNo;
    string name, div;

    cout << "RollNo\tName\tDivision\n";
    while (file >> rollNo >> name >> div) {
        cout << rollNo << "\t" << name << "\t" << div << endl;
    }

    file.close();
}

void StudentDetails::search(int rollNo) {
    file.open("studentdb.txt", ios::in);

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    int fileRollNo;
    string name, div;
    bool found = false;

    while (file >> fileRollNo >> name >> div) {
        if (fileRollNo == rollNo) {
            found = true;
            cout << "Record Found:\n";
            cout << "RollNo\tName\tDivision\n";
            cout << fileRollNo << "\t" << name << "\t" << div << endl;
            break; // Exit loop once the record is found
        }
    }

    file.close();

    if (!found) {
        cout << "Entry not found!\n";
    }
}

void StudentDetails::modifyRecord(int rollNo) {
    file.open("studentdb.txt", ios::in);
    fstream tempFile("temp.txt", ios::out);

    if (!file || !tempFile) {
        cout << "Error opening file!\n";
        return;
    }

    int fileRollNo;
    string name, div;
    bool found = false;

    while (file >> fileRollNo >> name >> div) {
        if (fileRollNo == rollNo) {
            found = true;
            cout << "Current Record: " << fileRollNo << "\t" << name << "\t" << div << endl;

            // Input new data
            cout << "Enter new Name: ";
            cin >> name;
            cout << "Enter new Division: ";
            cin >> div;

            // Write updated record
            tempFile << fileRollNo << "\t" << name << "\t" << div << "\n";
        } else {
            // Write unmodified record
            tempFile << fileRollNo << "\t" << name << "\t" << div << "\n";
        }
    }

    file.close();
    tempFile.close();
    remove("studentdb.txt");
    rename("temp.txt", "studentdb.txt");

    if (!found) {
        cout << "Entry not found!\n";
    }
}


void StudentDetails::deleteDB(int rollNo) {
    file.open("studentdb.txt", ios::in);
    fstream tempFile("temp.txt", ios::out);

    if (!file || !tempFile) {
        cout << "Error opening file!\n";
        return;
    }

    int fileRollNo;
    string name, div;
    bool found = false;

    while (file >> fileRollNo >> name >> div) {
        if (fileRollNo == rollNo) {
            found = true;
            cout << "Deleted Record: " << fileRollNo << "\t" << name << "\t" << div << endl;
        } else {
            tempFile << fileRollNo << "\t" << name << "\t" << div << "\n";
        }
    }

    file.close();
    tempFile.close();
    remove("studentdb.txt");
    rename("temp.txt", "studentdb.txt");

    if (!found) {
        cout << "Entry not found!\n";
    }
}


int main() {
    StudentDetails DB;
    int choice, rollNo;

    do {
        cout << "Menu:\n";
        cout << "1. Add Record\n";
        cout << "2. Display Records\n";
        cout << "3. Modify Record\n";
        cout << "4. Delete Record\n";
        cout << "5. Search Record\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                DB.insertData();
                break;
            case 2:
                DB.display();
                break;
            case 3:
                cout << "Enter Roll Number to Modify: ";
                cin >> rollNo;
                DB.modifyRecord(rollNo);
                break;
            case 4:
                cout << "Enter Roll Number to Delete: ";
                cin >> rollNo;
                DB.deleteDB(rollNo);
                break;
            case 5:
                cout << "Enter Roll Number to Search: ";
                cin >> rollNo;
                DB.search(rollNo);
                break;
            case 6:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
