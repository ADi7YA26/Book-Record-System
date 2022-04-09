#include <iostream>
#include <fstream>
#include <iomanip> // to use setw function;
using namespace std;

class Record{
    string Book_id, Book_price, Book_name , Book_author_name;
    
    public:
        void menu();
        void insert();
        void display();
        void modify();
        void search();
        void deleted();
};

void Record::menu(){
    menu:
        int choice;
        char x;
        cout << "|---------------------------|" << endl;
        cout << "|     BOOKS RECORD SYSTEM   |" << endl;
        cout << "|---------------------------|" << endl;
        cout << " 1. Enter New Record" << endl;
        cout << " 2. Display all Records" << endl;
        cout << " 3. Modify Record" << endl;
        cout << " 4. Search Record" << endl;
        cout << " 5. Exit\n"<< endl; 
        
        cout<<"Select an option : ";
        cin >> choice;
        
        switch (choice){
            case 1:
                do{
                    insert();
                    cout <<endl<<"Do you want to add another Record (Y/N) : ";
                    cin >> x;
                } while (x == 'y' || x == 'Y');
                break;
            case 2:
                display();
                break;
            case 3:
                modify();
                break;
            case 4:
                search();
                break;
            case 5:
                cout << "\n\t Program Is Exit";
                exit(0);
            default:
                cout << "\n\n Invalid Choice... Try Again...\n"<<endl;
        }
        goto menu;
}

void Record::insert(){
    fstream file;
    cout<<"\nEnter Book id : ";
    cin >> Book_id;    
    cin.ignore();
    cout<<"Enter the Book name : ";
    getline(cin, Book_name);
    cout<<"Enter the Author name : ";
    getline(cin, Book_author_name);
    cout<<"Enter the Price : ";
    cin >> Book_price;    
    file.open("record.txt", ios::app | ios::out);
    //setw() method to set the field width; 
    file << " " << Book_id << setw(30) << Book_name << setw(30) << Book_author_name << setw(10) << Book_price << endl;
    file.close();
}

void Record::display(){
    fstream file;
    file.open("record.txt", ios::in);
    if (!file){
        cout << "\nNo Data is Present... "<<endl<<endl;
    }
    else{
        string content;
        cout<<endl<<"------------------Book Records--------------------"<<endl;
        while (!file.eof()){
            getline(file,content);
            cout<< content <<endl;
        }
    }
    file.close();
}

void Record::modify(){
    string id, lineContent;
    fstream file, temp;
    cout << "\nEnter the book Id which you want to Modify: ";
    cin >> id;    
    
    file.open("record.txt", ios::in);
    temp.open("tmp.txt", ios::app | ios::out);
    file >> Book_id;

    while (getline(file,lineContent)){
        if (id != Book_id)
            temp << " " << Book_id << lineContent << endl;
        else{
            cout<<"\nEnter Book id : ";
            cin >> Book_id;    
            cin.ignore();
            cout<<"Enter the Book name : ";
            getline(cin, Book_name);
            cout<<"Enter the Author name : ";
            getline(cin, Book_author_name);
            cout<<"Enter the Price : ";
            cin >> Book_price;    
            temp << " " << Book_id << setw(30) << Book_name << setw(30) << Book_author_name << setw(10) << Book_price << endl;
        }
        file >> Book_id;
    }  
    file.close();
    temp.close();
    remove("record.txt");
    rename("tmp.txt", "record.txt");
}

void Record::search(){
    string id, line;
    fstream file;
    file.open("record.txt", ios::in);
    cout<<"Enter the Id number of the book : ";
    cin >> id;
    
    file >> Book_id ;
    while(getline(file, line)){
        if (id == Book_id)
            cout << " " << Book_id << line << endl;
        else        
            file >> Book_id;
    }
    file.close();
}


int main()
{
    Record r;
    r.menu();
    
    return 0;
}