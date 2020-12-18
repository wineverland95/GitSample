//Samuel Cruz
// 12/18/2020
//final test cis-265
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
using namespace std;

/*
* Structs
*/
struct Person {
    string firstName;
    string lastName;
    int age;
    int IDnumber;
};

/*
* Prototypes
*/
void loadFileContent();
void printMenu();
void createFile();
void checkFileExist();
void populateFile();
void displayContents();
void appendRecord();
void deleteRecord();
void searchRecord();
void modifyRecord();
void sortFile();
void wipeOutFile();

/*
* global Variables
*/
vector<Person> employees;
bool RUNNING = true;
bool fileExist = false;

int main() {

    int option;

    // we want to load file content if there is one at beginning of the program.
    checkFileExist();
    if (fileExist)
    {
        loadFileContent();
    }

    while (RUNNING)
    {
        printMenu();
        do
        {
            cout << "Please Enter your option " << endl;
            cin >> option;

        } while (option > 11 && option < 1);

        switch (option)
        {

        case 1:
            system("CLS");
            cout << "---------- Option 1 ----------" << endl;
            createFile();
            break;

        case 2:
            system("CLS");
            cout << "---------- Option 2 ----------" << endl;
            checkFileExist();
            if (fileExist)
            {
                cout << "file exists" << endl;
            }
            else
            {
                cout << "file doesn't exist" << endl;
            }
            break;

        case 3:
            system("CLS");
            cout << "---------- Option 3 ----------" << endl;
            populateFile();
            break;

        case 4:
            system("CLS");
            cout << "---------- Option 4 ----------" << endl;
            displayContents();
            break;

        case 5:
            system("CLS");
            cout << "---------- Option 5 ----------" << endl;
            appendRecord();
            break;

        case 6:
            system("CLS");
            cout << "---------- Option 6 ----------" << endl;
            deleteRecord();
            break;

        case 7:
            system("CLS");
            cout << "---------- Option 7 ----------" << endl;
            searchRecord();
            break;

        case 8:
            system("CLS");
            cout << "---------- Option 8 ----------" << endl;
            modifyRecord();
            break;

        case 9:
            system("CLS");
            cout << "---------- Option 9 ----------" << endl;
            sortFile();
            break;

        case 10:
            system("CLS");
            cout << "---------- Option 10 ----------" << endl;
            wipeOutFile();
            break;

        case 11:
            RUNNING = false;
            break;
        }

    }

    return 0;
}

void loadFileContent()
{
    employees.clear(); // empty list 

    Person* y = new Person;

    ifstream myFile;
    myFile.open("data.bin", ios::in);
    if (myFile.is_open())
    {
        myFile.seekg(0);
        while (!myFile.eof())
        {
            myFile.read((char*)y, sizeof(Person));
            employees.push_back(*y);
        }
        myFile.close();

        employees.pop_back(); // Get Rid of Last element -> duplicate
    }
}

void printMenu()
{
    cout << "--------------------------------" << endl;
    cout << "**           MENU             **" << endl;
    cout << "--------------------------------" << endl;
    cout << "1.  Create Binary File " << endl;
    cout << "2.  Check if Binary File exist " << endl;
    cout << "3.  Populate Binary File " << endl;
    cout << "4.  Display Contents " << endl;
    cout << "5.  Append a Record " << endl;
    cout << "6.  Delete Record " << endl;
    cout << "7.  Search Record " << endl;
    cout << "8.  Modify a Record " << endl;
    cout << "9.  Sort File " << endl;
    cout << "10. Wipe Out File " << endl;
    cout << "11. Exit Program " << endl;
    cout << "--------------------------------" << endl;
}

void createFile()
{
    if (!fileExist)
    {
        ofstream myFile;
        myFile.open("data.bin", ios::binary);
        myFile.close();
        cout << "File Has Been Created." << endl;
    }
    else
    {
        cout << "File Already Exists " << endl;
    }
}

void checkFileExist()
{
    ifstream ifile;
    ifile.open("data.bin");
    if (ifile) {
        fileExist = true;
    }
    else {
        fileExist = false;
    }
    ifile.close();
}

void populateFile()
{
    ofstream myFile;

    myFile.open("data.bin", ios::out);
    if (!myFile.is_open())
    {
        cout << "Error while opening File " << endl;
    }
    else
    {
        for (auto& element : employees)
        {
            myFile.write((char*)&element, sizeof(Person));
        }
    }
    myFile.close();
}

void displayContents()
{
    loadFileContent();

    if (!employees.empty())
    {
        int counter = 1;
        for (auto& element : employees)
        {
            cout << counter << ". " << element.firstName << " " << element.lastName << " Age : " << element.age << " ID : " << element.IDnumber << endl;
            counter++;
        }
    }
}

void appendRecord()
{
    loadFileContent();

    Person tmp;

    cout << "Please Enter First Name " << endl;
    cin >> tmp.firstName;

    cout << "Please Enter Last Name " << endl;
    cin >> tmp.lastName;

    cout << "Please Enter Age " << endl;
    cin >> tmp.age;

    // Making my own key
    tmp.IDnumber = tmp.firstName.length() + tmp.lastName.length() + tmp.age + (rand() % 5000 + 1000);

    employees.push_back(tmp);
    populateFile(); // write it to file
}

void deleteRecord()
{
    loadFileContent();

    int search;
    int deleteThisElement;
    cout << "Please Enter ID Number of Employee " << endl;
    cin >> search;

    if (!employees.empty())
    {
        int tmpCounter = 0;
        for (auto& element : employees)
        {
            if (element.IDnumber == search)
            {
                deleteThisElement = tmpCounter;
            }
            tmpCounter++;
        }
        employees.erase(employees.begin() + deleteThisElement);
    }
    populateFile();

}

void searchRecord()
{
    loadFileContent();

    int search;
    cout << "Please Enter ID Number of Employee " << endl;
    cin >> search;

    for (auto& element : employees)
    {
        if (element.IDnumber == search)
        {
            cout << "Found -> " << element.firstName << " " << element.lastName << " Age : " << element.age << " ID : " << element.IDnumber << endl;
        }
    }
}

void modifyRecord()
{
    loadFileContent();

    int search;
    string name;
    string lastName;
    int age;
    int tmpCounter = 0;

    cout << "Please Enter ID Number of Employee " << endl;
    cin >> search;

    for (auto& element : employees)
    {
        if (element.IDnumber == search)
        {
            cout << "Found -> " << element.firstName << " " << element.lastName << " Age : " << element.age << " ID : " << element.IDnumber << endl;

            cout << "Please Enter UPDATED Name " << endl;
            cin >> name;
            employees[tmpCounter].firstName = name;

            cout << "Please Enter UPDATED Last Name " << endl;
            cin >> lastName;
            employees[tmpCounter].lastName = lastName;

            cout << "Please Enter UPDATED Age " << endl;
            cin >> age;
            employees[tmpCounter].age = age;
        }
        tmpCounter++;
    }

    // Write new Updated File
    populateFile();
}

void sortFile()
{
    cout << "** Not Implemented Yet **" << endl;
}

void wipeOutFile()
{
    string confirmation;
    cout << "All records would be lost " << endl;
    cout << "Do you want to proceed - type (Yes or No) " << endl;
    cin >> confirmation;

    if (strcmp(confirmation.c_str(), "Yes") == 0) // Comparing two strings
    {
        employees.clear();
        populateFile();
        cout << "All Records were deleted. " << endl;
    }
}
