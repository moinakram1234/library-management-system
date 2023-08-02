#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dos.h>
#include <time.h>

#define RETURNTIME 15
#define MAX_BOOKS 100
#define MAX_BOOK_ID_LENGTH 20
#define MAX_STUDENT_NAME_LENGTH 50
#define MAX_STUDENTS 100
struct Book {
    char bookId[10];
    char bookName[50];
    char author[50];
    char quantity[10];
    char price[10];
    char rackNo[10];
};
typedef struct {
    char studentId[10];
    char studentName[MAX_STUDENT_NAME_LENGTH];
    char bookId[MAX_BOOK_ID_LENGTH]; // Add student book ID
    // Add additional student properties here
} Student;
struct Book library[MAX_BOOKS]; // Global array to store the books
int numBooks = 0; // Counter to keep track of the number of books
Student students[MAX_STUDENTS];
int numStudents = 0;
// Global variables
HINSTANCE hInstance;
HWND mainWindow;
HWND addButton, deleteButton, searchButton, issueButton, viewButton, editButton, closeButton,stdButton;
HWND bookIdInput, bookNameInput, authorInput, quantityInput, priceInput, rackNoInput;
HWND statusLabel;

// Function declarations
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void CreateControls();
void AddBook();
void DeleteBook();
void SearchBook();
void IssueBook();
void ViewBooks();
void EditBook();
void CloseApplication();
void display();

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
    hInstance = hInst;

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wc.lpszClassName = "LibraryManagement";

    RegisterClass(&wc);

    mainWindow = CreateWindow("LibraryManagement", "Library Management System",
                              WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                              500, 500, NULL, NULL, hInstance, NULL);

    CreateControls();

    ShowWindow(mainWindow, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_COMMAND:
            if (HIWORD(wParam) == BN_CLICKED)
            {
                if ((HWND)lParam == addButton)
                {
                    AddBook();
                }
                else if ((HWND)lParam == deleteButton)
                {
                    DeleteBook();
                }
                else if ((HWND)lParam == searchButton)
                {
                    SearchBook();
                }
                else if ((HWND)lParam == issueButton)
                {
                    IssueBook();
                }
                else if ((HWND)lParam == viewButton)
                {
                    ViewBooks();
                }
                else if ((HWND)lParam == editButton)
                {
                    EditBook();
                }
                else if ((HWND)lParam == closeButton)
                {
                    CloseApplication();
                }
                 else if ((HWND)lParam == stdButton)
                {
                    display();
                }
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void CreateControls()
{
    // Create buttons
    addButton = CreateWindow("BUTTON", "Add Book", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                             20, 190, 100, 30, mainWindow, NULL, hInstance, NULL);

    deleteButton = CreateWindow("BUTTON", "Delete Book", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                130, 190, 100, 30, mainWindow, NULL, hInstance, NULL);

    searchButton = CreateWindow("BUTTON", "Search Book", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                240, 190, 100, 30, mainWindow, NULL, hInstance, NULL);

    issueButton = CreateWindow("BUTTON", "Issue Book", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                               350, 190, 100, 30, mainWindow, NULL, hInstance, NULL);

    viewButton = CreateWindow("BUTTON", "View Books", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                              20, 220, 100, 30, mainWindow, NULL, hInstance, NULL);

    editButton = CreateWindow("BUTTON", "Edit Book", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                              130, 220, 100, 30, mainWindow, NULL, hInstance, NULL);

    closeButton = CreateWindow("BUTTON", "Close", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                               350, 220, 100, 30, mainWindow, NULL, hInstance, NULL);
stdButton = CreateWindow("BUTTON", "View Student", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                               240, 220, 100, 30, mainWindow, NULL, hInstance, NULL);
    // Create input fields
    CreateWindow("STATIC", "Book ID:", WS_VISIBLE | WS_CHILD,
                 20, 20, 80, 20, mainWindow, NULL, hInstance, NULL);
    bookIdInput = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                               110, 20, 120, 20, mainWindow, NULL, hInstance, NULL);

    CreateWindow("STATIC", "Book Name:", WS_VISIBLE | WS_CHILD,
                 20, 50, 80, 20, mainWindow, NULL, hInstance, NULL);
    bookNameInput = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                 110, 50, 120, 20, mainWindow, NULL, hInstance, NULL);

    CreateWindow("STATIC", "Author:", WS_VISIBLE | WS_CHILD,
                 20, 80, 80, 20, mainWindow, NULL, hInstance, NULL);
    authorInput = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                               110, 80, 120, 20, mainWindow, NULL, hInstance, NULL);

    CreateWindow("STATIC", "Quantity:", WS_VISIBLE | WS_CHILD,
                 20, 110, 80, 20, mainWindow, NULL, hInstance, NULL);
    quantityInput = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                 110, 110, 120, 20, mainWindow, NULL, hInstance, NULL);

    CreateWindow("STATIC", "Price:", WS_VISIBLE | WS_CHILD,
             20, 140, 80, 20, mainWindow, NULL, hInstance, NULL);
priceInput = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                          110, 140, 120, 20, mainWindow, NULL, hInstance, NULL);

CreateWindow("STATIC", "Rack No:", WS_VISIBLE | WS_CHILD,
             20, 170, 80, 20, mainWindow, NULL, hInstance, NULL);
rackNoInput = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                           110, 170, 120, 20, mainWindow, NULL, hInstance, NULL);

// Create status label
statusLabel = CreateWindow("STATIC", "", WS_VISIBLE | WS_CHILD,
                           20, 250, 430, 20, mainWindow, NULL, hInstance, NULL);
}

void AddBook()
{
    // Retrieve the book information from the input fields
    GetWindowText(bookIdInput, library[numBooks].bookId, sizeof(library[numBooks].bookId));
    GetWindowText(bookNameInput, library[numBooks].bookName, sizeof(library[numBooks].bookName));
    GetWindowText(authorInput, library[numBooks].author, sizeof(library[numBooks].author));
    GetWindowText(quantityInput, library[numBooks].quantity, sizeof(library[numBooks].quantity));
    GetWindowText(priceInput, library[numBooks].price, sizeof(library[numBooks].price));
    GetWindowText(rackNoInput, library[numBooks].rackNo, sizeof(library[numBooks].rackNo));

    // Increment the number of books counter
    numBooks++;

    // Display a message to indicate the book has been added
    MessageBox(mainWindow, "Book added successfully!", "Success", MB_OK | MB_ICONINFORMATION);
}

void DeleteBook()
{
    char bookIdInput[MAX_BOOK_ID_LENGTH];
    printf("Enter the book ID to delete: ");
    fgets(bookIdInput, sizeof(bookIdInput), stdin);
    bookIdInput[strcspn(bookIdInput, "\n")] = '\0'; // Remove newline character

    int deleteIndex = -1; // Variable to store the index of the book to be deleted

    // Search for the book with the matching book ID in the library array
    int i;
    for (i = 0; i < numBooks; i++) {
        if (strcmp(bookIdInput, library[i].bookId) == 0) {
            deleteIndex = i;
            break;
        }
    }

    if (deleteIndex != -1) {
        // Book found, perform the deletion
        // Shift the remaining books in the array
        for (i = deleteIndex; i < numBooks - 1; i++) {
            library[i] = library[i + 1];
        }

        numBooks--; // Decrement the number of books

        // Display a message to indicate the book has been deleted
        MessageBox(NULL, "Book deleted successfully!", "Success", MB_OK | MB_ICONINFORMATION);
    } else {
        // Book not found, display an error message
        MessageBox(NULL, "Book not found!", "Error", MB_OK | MB_ICONERROR);
    }
}

void SearchBook()
{
    char bookIdInput[MAX_BOOK_ID_LENGTH];
    printf("Enter the book ID to search: ");
    fgets(bookIdInput, sizeof(bookIdInput), stdin);
    bookIdInput[strcspn(bookIdInput, "\n")] = '\0'; // Remove newline character

    int searchIndex = -1; // Variable to store the index of the book to be searched

    // Search for the book with the matching book ID in the library array
    int i;
    for (i = 0; i < numBooks; i++) {
        if (strcmp(bookIdInput, library[i].bookId) == 0) {
            searchIndex = i;
            break;
        }
    }

    if (searchIndex != -1) {
        // Book found, prepare the message with all book data
        char message[500]; // Adjust the size as per your requirements
        snprintf(message, sizeof(message), "Book ID: %s\nBook Name: %s\nAuthor: %s\nQuantity: %s\nPrice: %s\nRack No: %s",
                 library[searchIndex].bookId, library[searchIndex].bookName, library[searchIndex].author,
                 library[searchIndex].quantity, library[searchIndex].price, library[searchIndex].rackNo);

        MessageBox(NULL, message, "Book Found", MB_OK | MB_ICONINFORMATION);
    } else {
        // Book not found, display an error message
        MessageBox(NULL, "Book not found!", "Error", MB_OK | MB_ICONERROR);
    }
}

void IssueBook()
{
    char bookIdInput[MAX_BOOK_ID_LENGTH];
    printf("Enter the book ID to issue: ");
    fgets(bookIdInput, sizeof(bookIdInput), stdin);
    bookIdInput[strcspn(bookIdInput, "\n")] = '\0'; // Remove newline character

    // Search for the book with the matching book ID in the library array
    int i;
    int issueIndex = -1;
    for (i = 0; i < numBooks; i++) {
        if (strcmp(bookIdInput, library[i].bookId) == 0) {
            issueIndex = i;
            break;
        }
    }

    if (issueIndex != -1) {
        // Book found, prompt for student ID and name
        char studentIdInput[10];
        printf("Enter student ID: ");
        fgets(studentIdInput, sizeof(studentIdInput), stdin);
        studentIdInput[strcspn(studentIdInput, "\n")] = '\0'; // Remove newline character

        char studentNameInput[MAX_STUDENT_NAME_LENGTH];
        printf("Enter student name: ");
        fgets(studentNameInput, sizeof(studentNameInput), stdin);
        studentNameInput[strcspn(studentNameInput, "\n")] = '\0'; // Remove newline character

        // Create a new student and assign the book
        Student newStudent;
        strcpy(newStudent.studentId, studentIdInput);
        strcpy(newStudent.studentName, studentNameInput);
        strcpy(newStudent.bookId, bookIdInput); // Store the book ID

        // Store the new student in the array
        students[numStudents++] = newStudent;

        // Perform the book issuing process (e.g., updating book quantity, storing student information)
        // Add your code here...

        // Display a success message
        MessageBox(NULL, "Book issued successfully!", "Success", MB_OK | MB_ICONINFORMATION);
    } else {
        // Book not found, display an error message
        MessageBox(NULL, "Book not found!", "Error", MB_OK | MB_ICONERROR);
    }
}


	
void display() {
    char message[5000]; // Adjust the size as per your requirements
    snprintf(message, sizeof(message), "Student data:\n");
    int i;
    for (i = 0; i < numStudents; i++) {
        char studentData[200]; // Adjust the size as per your requirements
        snprintf(studentData, sizeof(studentData), "Student ID: %s\nStudent Name: %s\nBook ID: %s\n\n",
                 students[i].studentId, students[i].studentName, students[i].bookId);

        strcat(message, studentData);
    }

    MessageBox(NULL, message, "Student Data", MB_OK | MB_ICONINFORMATION);

}
void ViewBooks()
{
    if (numBooks == 0) {
        MessageBox(mainWindow, "No books available.", "Empty Library", MB_OK | MB_ICONINFORMATION);
        return;
    }

    char message[500]; // Buffer to store the message

    strcpy(message, "Book List:\n\n");

    // Declare the variable outside the for loop
    int i;
    // Iterate over the books in the library array and append their information to the message
    for (i = 0; i < numBooks; i++) {
        char bookInfo[250]; // Buffer to store the book information for each book

        snprintf(bookInfo, sizeof(bookInfo), "Book %d:\n", i + 1);
        strcat(message, bookInfo);

        snprintf(bookInfo, sizeof(bookInfo), "Book ID: %s\n", library[i].bookId);
        strcat(message, bookInfo);

        snprintf(bookInfo, sizeof(bookInfo), "Book Name: %s\n", library[i].bookName);
        strcat(message, bookInfo);

        snprintf(bookInfo, sizeof(bookInfo), "Author: %s\n", library[i].author);
        strcat(message, bookInfo);

        snprintf(bookInfo, sizeof(bookInfo), "Quantity: %s\n", library[i].quantity);
        strcat(message, bookInfo);

        snprintf(bookInfo, sizeof(bookInfo), "Price: %s\n", library[i].price);
        strcat(message, bookInfo);

        snprintf(bookInfo, sizeof(bookInfo), "Rack No: %s\n\n", library[i].rackNo);
        strcat(message, bookInfo);
    }

    // Display the message with book information in a message box
    MessageBox(mainWindow, message, "Book List", MB_OK | MB_ICONINFORMATION);
}



void EditBook()
{
    char bookIdInput[MAX_BOOK_ID_LENGTH];
    printf("Enter the book ID to edit: ");
    fgets(bookIdInput, sizeof(bookIdInput), stdin);
    bookIdInput[strcspn(bookIdInput, "\n")] = '\0'; // Remove newline character

    // Search for the book with the matching book ID in the library array
    int editIndex = -1;
    int i;
    for (i = 0; i < numBooks; i++) {
        if (strcmp(bookIdInput, library[i].bookId) == 0) {
            editIndex = i;
            break;
        }
    }

    if (editIndex != -1) {
        // Book found, prompt for new book properties
        printf("Enter new book name: ");
        fgets(library[editIndex].bookName, sizeof(library[editIndex].bookName), stdin);
        library[editIndex].bookName[strcspn(library[editIndex].bookName, "\n")] = '\0'; // Remove newline character

        printf("Enter new author: ");
        fgets(library[editIndex].author, sizeof(library[editIndex].author), stdin);
        library[editIndex].author[strcspn(library[editIndex].author, "\n")] = '\0'; // Remove newline character

        printf("Enter new quantity: ");
        fgets(library[editIndex].quantity, sizeof(library[editIndex].quantity), stdin);
        library[editIndex].quantity[strcspn(library[editIndex].quantity, "\n")] = '\0'; // Remove newline character

        printf("Enter new price: ");
        fgets(library[editIndex].price, sizeof(library[editIndex].price), stdin);
        library[editIndex].price[strcspn(library[editIndex].price, "\n")] = '\0'; // Remove newline character

        printf("Enter new rack number: ");
        fgets(library[editIndex].rackNo, sizeof(library[editIndex].rackNo), stdin);
        library[editIndex].rackNo[strcspn(library[editIndex].rackNo, "\n")] = '\0'; // Remove newline character

        // Display a success message
        MessageBox(NULL, "Book edited successfully!", "Success", MB_OK | MB_ICONINFORMATION);
    } else {
        // Book not found, display an error message
        MessageBox(NULL, "Book not found!", "Error", MB_OK | MB_ICONERROR);
    }
}


void CloseApplication()
{
    DestroyWindow(mainWindow);
}

