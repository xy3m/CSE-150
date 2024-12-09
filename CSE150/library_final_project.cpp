#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <conio.h> 
#include <cstring>
#include <iomanip>
#include <limits>

using namespace std;

class User;

void login();
void registration();
void displayMenu();
void getPassword(string& password);
void admin_menu1(User user);
void admin_menu2();

class Book {
protected:
    int bookNumber, quantity;
    char bookName[50];
    char authorName[50];
    char publisherName[50];

public:
    void createBook();
    void showBook();
    void showBookList();
    void assignBookNumber(int count);
    int getBookNumber() const;
    const char* getBookName(); 
};

class Student {
public:
    char studentName[25];
    int bookNumber;
    int registrationNumber;
    char department[50];    
    char session[20];      

    void createStudent();
    void showStudent();
    void showStudentList();
    void setBookNumber(int bookNo);
    int getBookNumber() const;
    const char* getStudentName();
};


class User {
public:
    char username[50];
    char password[50];
    Student studentProfile;
};

bool checkStudent(int regNo);
int checkBook(int bookNo, int action);
void addBook();
//void addStudent();
void listStudents();
void listBooks();
void searchBook(const char* bookName);
void deleteBook(const char* bookName);
void searchStudent(int regNo);


void getPassword(string& password) {
    char ch;
    password.clear();
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
            password.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
}

void displayMenu() {
    system("CLS");
    int choice;
    cout << "\t___________        MENU        ___________\n\n";
    cout << "                                                 \n\n\n";
    cout << "\t*****  1.    LOGIN                     *****" << endl;
    cout << "\t*****  2.    REGISTER                  *****" << endl;
    cout << "\n\t Please enter your choice : ";
    cin >> choice;
    cout << endl;

    switch (choice) {
    case 1:
        login();
        break;
    case 2:
        registration();
        break;
    default:
       
        cout << "\n\t\tPlease select from the options given above! \n" << endl;
        system("PAUSE");
        displayMenu();
    }
}

void login() {
    int loginSuccess = 0;
    string inputUsername, inputPassword;
    User user;
    system("CLS");
    cout << "\t\t Please enter the username and password: \n" << endl;
    cout << "\t\t USERNAME: ";
    cin >> inputUsername;
    cout << "\t\t PASSWORD: ";
    getPassword(inputPassword);

    ifstream inputFile("users.bin", ios::in | ios::binary);

    while (inputFile.read(reinterpret_cast<char*>(&user), sizeof(User))) {
        if (inputUsername == user.username && inputPassword == user.password) {
            loginSuccess = 1;
            break;
        }
    }
    inputFile.close();

    if (loginSuccess == 1) {
        cout << "\n\t\t\tYour LOGIN is successful\n\n";
        cout << "\t\t\tWelcome, " << user.studentProfile.getStudentName() << "\n\n";
        admin_menu1(user); 
    } else {
        cout << "\n LOGIN ERROR \n Please check your username and password\n";
        system("PAUSE");
        displayMenu();
    }
}

bool usernameExists(const string& newUsername) {
    ifstream inputFile("users.bin", ios::in | ios::binary);
    User existingUser;

    while (inputFile.read(reinterpret_cast<char*>(&existingUser), sizeof(User))) {
        if (strcmp(existingUser.username, newUsername.c_str()) == 0) {
            inputFile.close();
            return true;
        }
    }

    inputFile.close();
    return false; 
}

void registration() {
    User newUser;
    string newUsername, newPassword;
    
    system("CLS");

    do {
        cout << "\t\t\t Enter the username: ";
        cin >> newUsername;

        if (usernameExists(newUsername)) {
            cout << "\t\t\t Username already exists, please choose another one.\n";
        }
    } while (usernameExists(newUsername));

    cout << "\t\t\t Enter the password: ";
    getPassword(newPassword);

    cout<<"\t\t\t Enter your Department Name :";
    

    strcpy(newUser.username, newUsername.c_str());
    strcpy(newUser.password, newPassword.c_str());

    newUser.studentProfile.createStudent();
    newUser.studentProfile.showStudent();

    ofstream outputFile("users.bin", ios::app | ios::binary);
    outputFile.write(reinterpret_cast<char*>(&newUser), sizeof(User));
    outputFile.close();

    cout << "\n\t\t\t Registration is successful! \n";
    system("PAUSE");
    displayMenu();
}


void Book::createBook() {
    cout << "\n\tEnter the book details:\n";
    cout << "\n\tEnter Book Name: ";
    cin.ignore();
    cin.getline(bookName, 50);
    cout << "\n\tEnter Author Name: ";
    cin.getline(authorName, 50);
    cout << "\n\tEnter Publisher Name: ";
    cin.getline(publisherName, 50);
    cout << "\n\tEnter Quantity: ";
    cin >> quantity;
}

void Book::showBook() {
    cout << "\n\tBook Number: " << bookNumber << "\n";
    cout << "\n\tBook Name: " << bookName << "\n";
    cout << "\n\tAuthor Name: " << authorName << "\n";
    cout << "\n\tPublisher Name: " << publisherName << "\n";
    cout << "\n\tQuantity: " << quantity << "\n";
}

void Book::showBookList() {
    cout << "\n\t" << setw(10) << bookNumber << "\t" 
         << setw(20) << bookName << "\t" 
         << setw(20) << authorName << "\t" 
         << setw(20) << publisherName << "\t";
}
 

void Book::assignBookNumber(int count) {
    bookNumber = 10000 + count;
    while (checkBook(bookNumber, 0)) {
        bookNumber++;
    }
}

int Book::getBookNumber() const {
    return bookNumber;
}

void Student::createStudent() {
    system("CLS");
    cout << "\n\tEnter the student details:\n";
    
    cout << "\n\tEnter Registration Number: ";
    cin >> registrationNumber;

    
     cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (checkStudent(registrationNumber)) {
        cout << "\n\tProfile already exists with this Registration Number.";
        cout << "\n\tEnter a different Registration Number.\n";
        system("PAUSE");
        system("CLS");
        createStudent();
    } else {
        cout << "\n\tEnter Student Name: ";
        cin.getline(studentName, 25);
        
        cout << "\n\tEnter Department: ";  
        cin.getline(department, 50);
        
        cout << "\n\tEnter Session: ";     
        cin.getline(session, 20);

        bookNumber = 0;  
    }
}


void Student::showStudent() {
    cout << "\n\tRegistration Number: " << registrationNumber << "\n";
    cout << "\n\tStudent Name: " << studentName << "\n";
    cout << "\n\tDepartment: " << department << "\n";  
    cout << "\n\tSession: " << session << "\n";        
}



void Student::showStudentList() {
    cout << "\n\t" << registrationNumber << "\t\t" << studentName << "\t\t";
}

void Student::setBookNumber(int bookNo) {
    bookNumber = bookNo;
}

int Student::getBookNumber() const {
    return bookNumber;
}

const char* Book::getBookName() {
    return bookName;
}
const char* Student::getStudentName() {
    return studentName;
}

bool checkStudent(int regNo) {
    User user;  
    ifstream inFile("users.bin", ios::in | ios::binary);
    if (!inFile) {
        return false;
    }

    while (inFile.read(reinterpret_cast<char *>(&user), sizeof(User))) {
        if (user.studentProfile.registrationNumber == regNo) {
            inFile.close();
            return true;
        }
    }

    inFile.close();
    return false;
}


int checkBook(int bookNo, int action) {
    Book book;
    fstream file("books.bin", ios::in | ios::out | ios::binary);
    if (!file) {
        return 0; 
    }

    bool found = false;
    while (file.read(reinterpret_cast<char *>(&book), sizeof(Book))) {
        if (book.getBookNumber() == bookNo) {
            found = true;
            if (action == 1) {
                book.showBook();
            } else if (action == 2) {
                book.showBook();
                file.seekp(-static_cast<int>(sizeof(Book)), ios::cur); 
                file.write(reinterpret_cast<char *>(&book), sizeof(Book));
            }
            break;
        }
    }

    file.close();
    return found ? (action == 1 ? 2 : 1) : 0; 
}

void addBook() {
    Book book;
    ofstream outFile("books.bin", ios::app | ios::binary);
    outFile.seekp(0, ios::end);
    int count = outFile.tellp() / sizeof(Book);
    book.assignBookNumber(count);
    book.createBook();
    book.showBook();
    outFile.write(reinterpret_cast<char *>(&book), sizeof(Book));
    cout << "\n\tBook added successfully";
    outFile.close();
}

// void addStudent() {
//     Student student;
//     ofstream outFile("students.bin", ios::app | ios::binary);
//     outFile.seekp(0, ios::end);
//     student.createStudent();
//     student.showStudent();
//     outFile.write(reinterpret_cast<char *>(&student), sizeof(Student));
//     cout << "\n\tStudent added successfully";
//     outFile.close();
// }

void listStudents() {
    User user;
    ifstream inFile("users.bin", ios::in | ios::binary);
    if (!inFile) {
        cout << "\n\tUnable to open file";
        return;
    }

    cout << "\n\tList of Students:\n";
    cout << "\n\tReg. No.\t\tName\n";
    while (inFile.read(reinterpret_cast<char *>(&user), sizeof(User))) {
        user.studentProfile.showStudentList();
    }

    inFile.close();
    cout << endl;
}


void listBooks() {
    Book book;
    ifstream inFile("books.bin", ios::in | ios::binary);
    inFile.seekg(0, ios::beg);
    if (!inFile) {
        cout << "\n\tFile not found";
    } else {
        cout << "\n\t***** Book Details *****\n\n";
        cout << "\n\t" << setw(10) << "Book No:" 
             << setw(20) << "Name:" 
             << setw(30) << "Author Name:" 
             << setw(25) << "Publisher Name:";
        while (inFile.read(reinterpret_cast<char *>(&book), sizeof(Book))) {
            book.showBookList();
        }
    }
    inFile.close();
}


void searchBook(const char* bookName) {
    Book book;
    int found = 0;
    ifstream inFile("books.bin", ios::in | ios::binary);
    inFile.seekg(0, ios::beg);
    if (!inFile) {
        cout << "\n\tFile not found\n";
    } else {
        while (inFile.read(reinterpret_cast<char *>(&book), sizeof(Book))) {
            if (strcmp(book.getBookName(), bookName) == 0) {
                found++;
                cout << "\n\tBook found!\n";
                book.showBook();
                break;
            }
        }
        if (found == 0) {
            cout << "\n\t\tNo such book exists\n";
        }
    }
    inFile.close();
}

void deleteBook(const char* bookName) {
    Book book;
    int found = 0;
    ifstream inFile("books.bin", ios::in | ios::binary);
    inFile.seekg(0, ios::beg);
    if (!inFile) {
        cout << "\n\tFile not found\n";
    } else {
        ofstream outFile("temp.bin", ios::app | ios::binary);
        while (inFile.read(reinterpret_cast<char *>(&book), sizeof(Book))) {
            if (strcmp(book.getBookName(), bookName) == 0) {
                found++;
            } else {
                outFile.write(reinterpret_cast<char *>(&book), sizeof(Book));
            }
        }
        inFile.close();
        outFile.close();
        if (found == 0) {
            remove("temp.bin");
            cout << "\n\t\tNo such book exists\n";
        } else {
            remove("books.bin");
            rename("temp.bin", "books.bin");
            cout << "\n\t\tBook deleted successfully\n";
        }
    }
}
void searchStudent(int regNo) {
    User user;
    ifstream inFile("users.bin", ios::in | ios::binary);
    if (!inFile) {
        cout << "\n\tUnable to open file";
        return;
    }

    bool found = false;
    while (inFile.read(reinterpret_cast<char *>(&user), sizeof(User))) {
        if (user.studentProfile.registrationNumber == regNo) {
            user.studentProfile.showStudent();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\n\tStudent not found";
    }

    inFile.close();
}
void admin_menu2() {
    fine:
    system("PAUSE");
    system("CLS");
    int opt;
    cout << "\n\n\n\t\t\t******LIBRARIAN MENU******";
    cout << "\n\n\t1.\tDISPLAY ALL STUDENTS PROFILE";
    cout << "\n\n\t2.\tDISPLAY SPECIFIC STUDENT PROFILE ";
    cout << "\n\n\t3.\tCREATE BOOK ";
    cout << "\n\n\t4.\tDISPLAY ALL BOOKS ";
    cout << "\n\n\t5.\tDISPLAY SPECIFIC BOOK ";
    cout << "\n\n\t6.\tDELETE BOOK ";
    cout << "\n\n\t7.\tBACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-7) ";
    cin >> opt;
    if (opt == 1) {
        system("CLS");
        listStudents();
        cout << endl;
        goto fine;
    } else if (opt == 2) {
        system("CLS");
        int ad;
        cout << "\n\n\n\t\tEnter the Registration no. of the student: ";
        cin >> ad;
        searchStudent(ad);
        cout << endl;
        goto fine;
    } else if (opt == 3) {
        system("CLS");
        addBook();
        cout << endl;
        goto fine;
    } else if (opt == 4) {
        system("CLS");
        listBooks();
        cout << endl;
        goto fine;
    } else if (opt == 5) {
        system("CLS");
        char bookName[50];
        cout << "\n\n\n\t\tEnter the name of the book: ";
        cin.ignore();  
        cin.getline(bookName, 50);
        searchBook(bookName);
        cout << endl;
        goto fine;
    } else if (opt == 6) {
         system("CLS");
        char bookName[50];
        cout << "\n\n\n\t\tEnter the name of the book: ";
        cin.ignore();  
        cin.getline(bookName, 50);
        deleteBook(bookName);
        cout << endl;
        goto fine;
    } else if (opt == 7)
        return;
    else {
        cout << "\n\t\tEnter correct option";
        cout << endl;
        goto fine;
    }
}
void admin_menu1(User user) {
fine:
    system("PAUSE");
    system("CLS");
    int opt;
    cout << "\n\n\n\t\t\t******STUDENT MENU******";
    cout << "\n\n\t1.\tVIEW YOUR PROFILE";
    cout << "\n\n\t2.\tDISPLAY ALL BOOKS ";
    cout << "\n\n\t3.\tDISPLAY SPECIFIC BOOK ";
    cout << "\n\n\t4.\tBACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-4) ";
    cin >> opt;
    if (opt == 1) {
        system("CLS");
        cout << "\n\n\n\t\t\t******YOUR PROFILE******";
        cout << "\n\n\tUsername: " << user.username;
        cout << "\n\tRegistration Number: " << user.studentProfile.registrationNumber;
        cout << "\n\tName: " << user.studentProfile.studentName;
        cout << "\n\tUsername: " << user.username;
        cout << "\n\tDepartment: " << user.studentProfile.department;  
        cout << "\n\tSession: " << user.studentProfile.session << endl; 

        goto fine;
    } else if (opt == 2) {
        system("CLS");
        listBooks();
        cout << endl;
        goto fine;
    } else if (opt == 3) {
        system("CLS");
        char bookName[50];
        cout << "\n\n\n\t\tEnter the book name of the book: ";
        cin.ignore();
        cin.getline(bookName, 50);
        searchBook(bookName);
        cout << endl;
        goto fine;
    } else if (opt == 4)
        return;
    else {
        cout << "\n\t\tEnter correct option";
        cout << endl;
        goto fine;
    }
}


bool passwords(const char* expectedPassword) {
    int i = 0;
    char ch, st[21];
    cout << "\n\tEnter Password: ";
    while (1) {
        ch = getch();
        if (ch == 13) { 
            st[i] = '\0';
            break;
        } else if (ch == 8 && i > 0) { 
            i--;
            cout << "\b \b";
        } else {
            cout << "*";
            st[i] = ch;
            i++;
        }
    }
    for (i = 0; st[i] == expectedPassword[i] && st[i] != '\0' && expectedPassword[i] != '\0'; i++);
    return (st[i] == '\0' && expectedPassword[i] == '\0');
}


int main() {
    cout << "\n\n\t\t\t*******************************************";
    cout << "\n\t\t\t------------------------------------------";
    cout << "\n\t\t\t\t\tSUST LIBRARY";
    cout << "\n\t\t\t------------------------------------------";
    cout << "\n\t\t\t*******************************************\n";
    
    start:
    system("PAUSE");
    system("CLS");
    int opt;
    cout << "\n\n\t\t\t------------------------------------------";
    cout << "\n\t\t\t\t\tSUST LIBRARY";
    cout << "\n\t\t\t------------------------------------------";
    cout << "\n\t\t\t1.\tSTUDENT";
    cout << "\n\t\t\t2.\tLIBRARIAN";
    cout << "\n\t\t\t3.\tEXIT";
    cout << "\n\n Choose your option: ";
    cin >> opt;
    
    if (opt == 1) {
        displayMenu();
        goto start;
    } else if (opt == 2) {
        if (passwords("1111")) {
            system("CLS");
            admin_menu2();
        } else {
            cout << "\n\tWrong password!\n\n";
        }
        goto start;
    } else if (opt == 3) {
        
        exit(0);
    } else {
        cout << "\n\t\tPlease enter correct option\n\n";
        goto start;
    }
}