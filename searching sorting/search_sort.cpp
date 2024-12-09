#include<iostream>
using namespace std;





struct student{
    int rollno;
    string name;
    float sgpa;
};

class studentdb{
    private:
        struct student s[15]; //Array of structure
    public:
        void insert(int);
        void display(int);
        void bubble_sort(int);
        void insertion_sort(int);
        int partition(int , int);
        void quick_sort(int , int);
        void linear_search(int);
        void binary_search(int, int);
};


int main(){
    int n;
    cout<<"Enter the number of students"<<endl;
    cin>>n;
    int flag=1;
    int choice;

    studentdb sb;
    do{
        
        cout<<"Menu:"<<endl;
        cout<<"1 Insert Data"<<endl;
        cout<<"2 Display Data"<<endl;
        cout<<"3 Roll no list (bubble sort)"<<endl;
        cout<<"4 Naming alphabetically (insertion sort)"<<endl;
        cout<<"5 Toppers list (Quick sort)"<<endl;
        cout<<"6 Search SGPA (Linear Search)"<<endl;
        cout<<"7 Search Name (Binary Search)"<<endl;
        cout<<"8 Exit"<<endl;
        cout<<"Enter the choice"<<endl;
        cin>>choice;

        switch(choice){
            case 1:
                sb.insert(n);
                break;
            case 2:
                sb.display(n);
                break;
            case 3:
                sb.bubble_sort(n);
                sb.display(n);
                break;
            case 4:
                sb.insertion_sort(n);
                sb.display(n);
                break;
            case 5:
                sb.quick_sort(0,n-1);
                sb.display(n);
                break;
            case 6:
                sb.linear_search(n);
                break;
            case 7:
                sb.insertion_sort(n);
                sb.binary_search(0,n-1);
                break;
            case 8:
                flag=0;
                exit(0);
                break;
            default:
                cout<<"No case found"<<endl;
                break;
        }
    }while(flag!=0);  
}

void studentdb::insert(int n){
    for(int i=0;i<n;i++){
        cout<<"Enter roll no"<<endl;
        cin>>s[i].rollno;
        cout<<"Enter name "<<endl;
        cin>>s[i].name;
        cout<<"Enter sgpa"<<endl;
        cin>>s[i].sgpa;
        cout<<endl;
    }
}

void studentdb::display(int n){
    for(int i=0;i<n;i++){
        cout<<"Roll no: "<<s[i].rollno<<endl;
        cout<<"Name: "<<s[i].name<<endl;
        cout<<"SGPA: "<<s[i].sgpa<<endl;
        cout<<endl;
    }
}

void studentdb::bubble_sort(int n){
    for(int i=0;i<n-1;i++){         //number of passes total n-1 passes
        for(int j=0;j<n-i-1;j++){
            if(s[j+1].rollno<s[j].rollno){

                int temp=s[j].rollno;
                s[j].rollno=s[j+1].rollno;
                s[j+1].rollno=temp;

                string temp1=s[j].name;
                s[j].name=s[j+1].name;
                s[j+1].name=temp1;

                float temp2=s[j].sgpa;
                s[j].sgpa=s[j+1].sgpa;
                s[j+1].sgpa=temp2;
            }
        }
    }
}

void studentdb::insertion_sort(int n){
    for (int i=1;i<n;i++){      //number of passes
        int j=i-1;
        student temp=s[i];

        while((j>=0) && s[j].name>temp.name){
            s[j+1]=s[j];
            j--;
        }

        s[j+1]=temp;
    }
}

int studentdb::partition(int l, int h){
    int pivot=s[h].sgpa;
    int i=l-1;
     for(int j=l;j<=h;j++){
        if(s[j].sgpa<pivot){
            i++;
            float temp=s[i].sgpa;
            s[i].sgpa=s[j].sgpa;
            s[j].sgpa=temp;

            int temp1=s[i].rollno;
            s[i].rollno=s[j].rollno;
            s[j].rollno=temp1;

            string temp2=s[i].name;
            s[i].name=s[j].name;
            s[j].name=temp2;
        }
     }
    
    float temp=s[i+1].sgpa;
    s[i+1].sgpa=s[h].sgpa;
    s[h].sgpa=temp;

    int temp1=s[i+1].rollno;
    s[i+1].rollno=s[h].rollno;
    s[h].rollno=temp1;

    string temp2=s[i+1].name;
    s[i+1].name=s[h].name;
    s[h].name=temp2;

    return (i+1);

}

void studentdb::quick_sort(int l, int h)
{
    if(l<h){
        int p=partition(l,h);
        quick_sort(l,p-1);
        quick_sort(p+1,h);
    }
}

void studentdb::linear_search(int n){
    float key;
    cout<<"Enter the SGPA to search:"<<endl;
    cin>>key;
    int found=false;
    for(int i=0;i<n;i++){
        if(s[i].sgpa==key){
            cout<<"Data found"<<endl<<endl;
            cout<<"Roll no: "<<s[i].rollno<<endl;
            cout<<"Name: "<<s[i].name<<endl;
            cout<<"SGPA: "<<s[i].sgpa<<endl;

            found=true;
        }
    }

    if(!found){
        cout<<"Not Found"<<endl;
    }
}

void studentdb::binary_search(int l, int h) {
    int found = 0;
    string key;
    cout << "Enter the name to search" << endl;
    cin >> key;

    while (l <= h) {
        int mid = (l + h) / 2;
        if (key == s[mid].name) {
            cout << "Found" << endl;
            cout << "Roll no: " << s[mid].rollno << endl;
            cout << "Name: " << s[mid].name << endl;
            cout << "SGPA: " << s[mid].sgpa << endl;
            found = 1;
            break;
        } else if (key > s[mid].name) {
            l = mid + 1;
        } else {
            h = mid - 1;
        }
    }

    if (!found) {
        cout << "Not Found" << endl;
    }
}








