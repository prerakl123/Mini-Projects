// importing libraries
#include <stdio.h>                                                                            // for general purpose I/O, etc
#include <stdlib.h>                                                                           // for general purpose functions involving memory allocation, conversions, etc
#include <conio.h>                                                                            // for console related functions
#include <windows.h>                                                                          // for windows related functions
#include <string.h>                                                                           // for string operations


// List of Global Variable
COORD coord = { 0, 0 };                                                                       // top-left corner of console window


/**
    function: gotoxy
    @param input: (x, y) coordinates
    @param output: moves the cursor to the specified position in console
*/
void gotoxy(int x, int y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


// Login function
void login() {
    int a = 0, i = 0;
    char uname[10], c = ' ';
    char pword[10], code[10];
    char user[10] = "user";
    char pass[10] = "pass";
    do {
        printf("\n  ::::::::::::::::::::::::::  LOGIN FORM  ::::::::::::::::::::::::::  ");
        printf(" \n                       ENTER USERNAME:- ");
        scanf("%s", &uname);
        printf(" \n                       ENTER PASSWORD:- ");
        while (i < 10) {
            pword[i] = getch();
            c = pword[i];
            if (c == 13)
                break;
            else
                printf("*");
            i++;
        }
        pword[i] = '\0';
        i = 0;
        
        if (strcmp(uname, "user") == 0 && strcmp(pword, "pass") == 0) {
            printf("  \n\n\n       WELCOME TO EMPLOYEE RECORD MANAGEMENT SYSTEM ! LOGIN SUCCESSFUL !!");
            printf("\n LOADING PLEASE WAIT");
            for (i = 0; i < 3; i++) {
                printf(".");
                Sleep(500);
            }
            printf("\n\n\n\t\t\t\tPress any key to continue...");
            getch();                                                                          // holds the screen
            break;
        } 
        else {
            printf("\n        LOGIN UNSUCCESSFUL");
            a++;
            getch();                                                                          // holds the screen

        }
    }
    while (a <= 2);
        if (a > 2) {
            printf("\nYou have entered the wrong username and password four times!!!");
        getch();
        }
    system("cls");
}


int main() {
    int i = 0;
    login();
    FILE *fp, *ft;                                                                            // file pointers
    char another, choice;

    /** structure representing an employee */
    struct emp {
        char name[40];                                                                        // name of employee
        int age;                                                                              // age of employee
        char address[20];                                                                     // address of employee
        float bs;                                                                             // basic salary of employee
    };
    struct emp e;                                                                             // structure variable creation
    char empname[40];                                                                         // string to store name of the employee
    long int recsize;                                                                         // size of each record of employee

    /** 
     * Open the file in binary read-write mode.
     * If the file EMP.DAT already exists, open that file in read-write mode.
     * If the file doesn't exist, simply create a new copy.
    */
    fp = fopen("EMP.DAT", "rb+");
    if (fp == NULL) {
        fp = fopen("EMP.DAT", "wb+");
        if (fp == NULL) {
            printf("Connot open file");
            exit(1);
        }
    }
    
    recsize = sizeof(e);                                                                      // size of each record i.e. size of struct e
    
    while (1) {                                                                               // infinite loop continues untile the break statement encounter
        system("cls");                                                                        // clear the console window 
        
        printf(" \n  ::::::::::::::::::::::::::  |EMPLOYEES RECORD MANAGEMENT|  :::::::::::::::::::::::::: \n");
        gotoxy(30, 05);                                                                       // move the cursor to postion (30, 10) from top-left corner
        printf("<1> Add Employee's Records");                                                 // option for add record
        gotoxy(30, 07);
        printf("<2> List Employee's Records");                                                // option for showing existing record
        gotoxy(30, 9);
        printf("<3> Modify Employee's Records");                                              // option for editing record
        gotoxy(30, 11);
        printf("<4> Delete Employee's Records");                                              // option for deleting record
        gotoxy(30, 13);
        printf("<5> Exit System");                                                            // exit from the program
        gotoxy(30, 15);
        printf("Your Choice: ");                                                              // enter the choice: 1, 2, 3, 4 or 5
        fflush(stdin);                                                                        // flush the input buffer
        choice = getche();                                                                    // get the input from keyboard

        switch(choice) {
            case '1':                                                                         // if user presses 1
                system("cls");
                // search the file and move the cursor to the end of the file
                fseek(fp, 0, SEEK_END);                                                       // here 0 indicates moving 0 distance from the end of the file
                another = 'y';
                while (another == 'y') {                                                      // if the user wants to add another record
                    fflush(stdin);
                    printf("\nEnter name: ");
                    scanf("%s", e.name);
                    fflush(stdin);
                    printf("\nEnter age: ");
                    scanf("%d", &e.age);
                    fflush(stdin);
                    printf("\nEnter Address: ");
                    scanf("%[^\n]", e.address);
                    fflush(stdin);
                    printf("\nEnter basic salary: ");
                    scanf("%f", &e.bs);
                    fwrite(&e, recsize, 1, fp);                                               // write the record in the file
                    printf("\nAdd another record(y/n): ");
                    fflush(stdin);
                    another = getche();
                }
                break;
            case '2':
                system("cls");
                printf("EMPLOYEE's RECORD LIST\n\n Name\t\tAge\t\tAddress\t\t\tSalary");
                rewind(fp);                                                                   // this moves the cursor to the start of the file
                
                while (fread(&e, recsize, 1, fp) == 1) {                                      // read the file and fetch the records - one record per fetch
                    printf("\n\n%s\t\t%d\t\t%s\t\t%.2f", e.name, e.age, e.address, e.bs);     // print the name, age and basic salary
                }
                getch();
                break;
            case '3':                                                                         // if user press 3 then do editing existing record
                system("cls");
                another = 'y';
                while (another == 'y') {
                    printf("Enter the employee name to modify: ");
                    scanf("%s", empname);
                    rewind(fp);
                    while (fread(&e, recsize, 1, fp) == 1) {                                  // fetch all record from file
                        if (strcmp(e.name, empname) == 0) {                                   // if entered name matches with that in file
                            fflush(stdin);
                            printf("\nEnter new Name: ");
                            scanf("%s", e.name, &e.age, &e.address, &e.bs);
                            fflush(stdin);
                            printf("\nEnter new Age: ");
                            scanf("%d", &e.age);
                            fflush(stdin);
                            printf("\nEnter new Address: ");
                            scanf("%[^\n]", &e.address);
                            fflush(stdin);
                            printf("\nEnter new Basic Salary: ");
                            scanf("%f", &e.bs);
                            fseek(fp, -recsize, SEEK_CUR);                                    // move the cursor 1 step back from current position
                            fwrite(&e, recsize, 1, fp);                                       // override the record
                            break;
                        }
                    }
                    printf("\nModify another record(y/n): ");
                    fflush(stdin);
                    another = getche();
                }
                break;
            case '4':
                system("cls");
                another = 'y';
                while (another == 'y') {
                    printf("\nEnter name of employee to delete: ");
                    scanf("%s", empname);
                    ft = fopen("Temp.dat", "wb");                                             // create a intermediate file for temporary storage
                    rewind(fp);                                                               // move record to starting of file
                    while (fread(&e, recsize, 1, fp) == 1) {                                  // read all records from file
                        if (strcmp(e.name, empname) != 0) {                                   // if the entered record match
                            fwrite(&e, recsize, 1, ft);                                       // move all records except the one that is to be deleted to temp file
                        }
                    }
                    fclose(fp);
                    fclose(ft);
                    remove("EMP.DAT");                                                        // remove the orginal file
                    rename("Temp.dat", "EMP.DAT");                                            // rename the temp file to original file name
                    fp = fopen("EMP.DAT", "rb+");
                    printf("Delete another record(y/n): ");
                    fflush(stdin);
                    another = getche();
                }
                break;
            case '5':
                fclose(fp);                                                                   // close the file
                exit(0);                                                                      // exit from the program
        }
    }
    return 0;
}