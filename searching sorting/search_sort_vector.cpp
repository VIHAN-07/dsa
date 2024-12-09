#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;

struct Student {
    int rollNo;
    string name;
    float sgpa;
};

// Function to display the student list
void displayStudents(const vector<Student>& students) {
    cout << left << setw(10) << "Roll No" << setw(20) << "Name" << setw(10) << "SGPA" << endl;
    cout << string(40, '-') << endl;
    for (const auto& student : students) {
        cout << left << setw(10) << student.rollNo << setw(20) << student.name << setw(10) << student.sgpa << endl;
    }
}

// Bubble Sort by Roll No
void bubbleSortByRollNo(vector<Student>& students) {
    int n = students.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].rollNo > students[j + 1].rollNo) {
                swap(students[j], students[j + 1]);
            }
        }
    }
}

// Insertion Sort by Name
void insertionSortByName(vector<Student>& students) {
    int n = students.size();
    for (int i = 1; i < n; i++) {
        Student key = students[i];
        int j = i - 1;
        while (j >= 0 && students[j].name > key.name) {
            students[j + 1] = students[j];
            j--;
        }
        students[j + 1] = key;
    }
}

// Quick Sort by SGPA
int partition(vector<Student>& students, int low, int high) {
    float pivot = students[high].sgpa;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (students[j].sgpa > pivot) { // For top students, sort in descending order
            i++;
            swap(students[i], students[j]);
        }
    }
    swap(students[i + 1], students[high]);
    return i + 1;
}

void quickSort(vector<Student>& students, int low, int high) {
    if (low < high) {
        int pi = partition(students, low, high);
        quickSort(students, low, pi - 1);
        quickSort(students, pi + 1, high);
    }
}

// Search students by SGPA
void searchBySGPA(const vector<Student>& students, float sgpa) {
    cout << "Students with SGPA " << sgpa << ":" << endl;
    bool found = false;
    for (const auto& student : students) {
        if (student.sgpa == sgpa) {
            cout << student.name << " (Roll No: " << student.rollNo << ")" << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No students found with SGPA " << sgpa << "." << endl;
    }
}

// Binary Search for a student by name
int binarySearchByName(const vector<Student>& students, const string& name) {
    int left = 0, right = students.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (students[mid].name == name) {
            return mid; // Found
        } else if (students[mid].name < name) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // Not found
}

int main() {
    vector<Student> students = {
        {101, "Alice", 8.5},
        {102, "Bob", 9.0},
        {103, "Charlie", 7.5},
        {104, "David", 8.0},
        {105, "Eve", 9.5},
        {106, "Frank", 6.5},
        {107, "Grace", 8.2},
        {108, "Heidi", 9.1},
        {109, "Ivan", 7.8},
        {110, "Judy", 8.7},
        {111, "Mallory", 9.3},
        {112, "Niaj", 8.4},
        {113, "Olivia", 7.9},
        {114, "Peggy", 9.2},
        {115, "Sybil", 8.1}
    };

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Sort by Roll No\n";
        cout << "2. Sort by Name\n";
        cout << "3. Display Top Ten Students by SGPA\n";
        cout << "4. Search Students by SGPA\n";
        cout << "5. Search Student by Name\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bubbleSortByRollNo(students);
                cout << "Roll Call List (Sorted by Roll No):" << endl;
                displayStudents(students);
                break;
            case 2:
                insertionSortByName(students);
                cout << "List of Students (Sorted by Name):" << endl;
                displayStudents(students);
                break;
            case 3:
                quickSort(students, 0, students.size() - 1);
                cout << "Top Ten Students (Sorted by SGPA):" << endl;
                displayStudents(vector<Student>(students.begin(), students.begin() + 10));
                break;
            case 4: {
                float searchSGPA;
                cout << "Enter SGPA to search: ";
                cin >> searchSGPA;
                searchBySGPA(students, searchSGPA);
                break;
            }
            case 5: {
                string searchName;
                cout << "Enter name to search: ";
                cin >> searchName;
                int index = binarySearchByName(students, searchName);
                if (index != -1) {
                    cout << "Student found: " << students[index].name << " (Roll No: " << students[index].rollNo << ", SGPA: " << students[index].sgpa << ")" << endl;
                } else {
                    cout << "Student not found." << endl;
                }
                break;
            }
            case 6:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}