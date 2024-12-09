#include<iostream> 
#include<fstream> 
#include<sstream> 
using namespace std; 
struct student 
{ 
 int rollNo; 
 string name; 
 string div; 
}; 
class studentdetails 
{ 
 fstream file; 
 public: 
 void insertdata(); 
 void addNewRecord(); 
 void display(); 
 void deleteDB(string key); 
 void search(string); 
 void modifyRecord(string); 
 studentdetails() //Crea ng a base file 
 { 
 file.open("studentdb.txt",ios::out); 
 file<<"RollNo\t\tName\t\tDivision\n"; 
 file.close(); 
 } 
}; 
//Func on to insert data 
void studentdetails:: insertdata() 
{ 
 file.open("studentdb.txt",ios::out|ios::app); 
 int n; 
 cout<<"How many students?\n"; 
 cin>>n; 
 student s[n]; 
 for(int i = 0;i<n;i++) { 
 cout<<"Enter Name:"<<endl; 
 cin>>s[i].name; 
 cout<<"Enter Roll number:"<<endl; 
 cin>>s[i].rollNo; 
 cout<<"Enter Division:"<<endl; 
 cin>>s[i].div; 
 file<<s[i].rollNo<<"\t\t"<<s[i].name<<"\t\t"<<s[i].div<<"\t\t\n"; 
 } 
 file.close(); 
} 
//Func on to search a parOcular student by their roll number or name 
void studentdetails:: search(string key) 
{ 
 file.open("studentdb.txt",ios::in); 
 string rollNo; 
 string name,div; 
 bool found = false; 
 while(file>>rollNo>>name>>div) { 
 if(rollNo==key || name == key) { 
 found=true; 
 cout<<"Student Found!\n"; 
 cout<<"RollNo\t\tName\t\tDivision\n"; 
 cout<<rollNo<<"\t\t"<<name<<"\t\t"<<div<<"\n"; 
 } 
 } 
 file.close(); 
 if (!found) { 
 cout<<"Entry not found !"<<endl; 
 } 
} 
//Func on to display all records in the current file 
void studentdetails::display() 
{ 
 file.open("studentdb.txt",ios::in); 
 while(file) { 
 string line; 
 getline(file,line); 
 cout<<line<<endl; 
 } 
 file.close(); 
} 
//Func on to Modify a par cular record by roll number or name 
void studentdetails::modifyRecord(string key) 
{ 
 file.open("studentdb.txt",ios::in | ios::out); 
 fstream file2; 
 file2.open("temp.txt",ios::out ); 
 string rollNo; 
 string name,div,temp; 
 int choice; 
 bool found = false; 
 while(file) { 
 while(file>>rollNo>>name>>div) { 
 if(rollNo == key || name == key) { 
 found = true; 
 cout<<"Current Information :"<<endl; 
 cout<<"RollNo\t\tName\t\tDivision\n"; 
 cout<<rollNo<<"\t\t"<<name<<"\t\t"<<div<<"\n"; 
 cout<<"Enter field to change: "<<endl; 
 cout<<"Menu\n1.Roll number\n2.Name\n3.DIV"<<endl; 
 do { 
 cout<<"Enter a valid choice :"<<endl; 
 cin>>choice; 
 } while (choice!=1 && choice!=2 && choice!=3); 
 switch(choice) { 
 case 1: 
 cout<<"Enter the new roll number : "<<endl; 
 cin>>rollNo; 
 break; 
 case 2: 
 cout<<"Enter the new name : "<<endl; 
 cin>>name; 
 break; 
 case 3: 
 cout<<"Enter the new div : "<<endl; 
 cin>>div; 
 break; 
 } 
 } 
 file2<<rollNo<<"\t\t"<<name<<"\t\t"<<div<<"\n"; 
 } 
 } 
 file.close(); 
 file2.close(); 
 remove("studentdb.txt"); 
 rename("temp.txt","studentdb.txt"); 
 if(!found) 
 { 
 cout<<"Entry not found !"<<endl; 
 } 
} 
//Func on to delete a record of a student by their roll number or name 
void studentdetails::deleteDB(string key) 
{ 
 file.open("studentdb.txt",ios::in | ios::out); 
 fstream file2; 
 file2.open("temp.txt",ios::out ); 
 string rollNo; 
 string name,div,temp; 
 int choice; 
 bool found; 
 while(file>>rollNo>>name>>div) { 
 if(rollNo == key || name == key) { 
 cout<<"This Informa on is deleted:"<<endl; 
 cout<<"RollNo\t\tName\t\tAddress\n"; 
 cout<<rollNo<<"\t\t"<<name<<"\t\t"<<div<<"\n\n"; 
 found = true; 
 } 
 else { 
 file2<<rollNo<<"\t\t"<<name<<"\t\t"<<div<<"\n"; 
 } 
 } 
 file.close(); 
 file2.close(); 
 remove("studentdb.txt"); 
 rename("temp.txt","studentdb.txt"); 
 if(!found) { 
 cout<<"Entry not found!"<<endl; 
 } 
} 
//Func on to add a single record to end of the file 
void studentdetails ::addNewRecord() { 
 file.open("studentdb.txt",ios::app); 
 student s1; 
 if(file) { 
 cout<<"Enter the Details of the new student: "<<endl; 
 cout<<"Enter Name:"<<endl; 
 cin>>s1.name; 
 cout<<"Enter Roll number:"<<endl; 
 cin>>s1.rollNo; 
 cout<<"Enter Address:"<<endl; 
 cin>>s1.div; 
 file<<s1.rollNo<<"\t\t"<<s1.name<<"\t\t"<<s1.div<<"\t\t\n"; 
 file.close(); 
 } 
 else { 
 cout<<"Error opening the file."; 
 } 
} 
int main() { 
 studentdetails DB1; 
 cout<<"Enter the details of students: "<<endl; 
 DB1.insertdata(); //In ally entering students to the file 
 cout<<endl; 
 int choice; 
 string temp; 
 do { 
 cout<<"Menu:"<<endl;
 cout<<"1.AddnewRecords"<<endl;
 cout<<"2.Display all records"<<endl;
 cout<<"3.Modify exisOng record"<<endl;
 cout<<"4.Delete a record"<<endl;
 cout<<"5.Search a record"<<endl;
 cout<<"6.Exit"<<endl; 
 cout<<"Enter a valid choice"<<endl; 
 cin>>choice; 
 switch(choice) { 
 case 1: 
 DB1.insertdata(); 
 break; 
 case 2: 
 DB1.display(); 
 break; 
 case 3: 
 cout<<"Enter the Roll number / Name of the student to modify his record : "<<endl; 
 cin>>temp; 
 DB1.modifyRecord(temp); 
 break; 
 case 4: 
 cout<<"Enter the Roll number / Name of the student to delete his record : "<<endl; 
 cin>>temp; 
 DB1.deleteDB(temp); 
 break; 
 case 5: 
 cout<<"Enter the Roll number / Name of the student to search his record : "<<endl; 
 cin>>temp; 
 DB1.search(temp); 
 case 6: 
 cout<<"Exit"; 
 break; 
 } 
 } while (choice!=6); 
} 
