#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define FILE_NAME "student_transport_data.txt"

// Structure to store student details
typedef struct {
    int id;
    char name[50];
    int route_no;
    char mobile_no[15];
    int validity; // In months
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

// Function prototypes
void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();
void saveToFile();
void loadFromFile();
void menu();

int main() {
    loadFromFile();
    menu();
    return 0;
}

void menu() {
    int choice;
    do {
        printf("\n--- University Student Transportation Management System ---\n");
        printf("1. Transport Registration\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Delete Student by ID\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                saveToFile();
                printf("Exiting the system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);
}

void addStudent() {
    if (student_count >= MAX_STUDENTS) {
        printf("Cannot add more students. Maximum limit reached.\n");
        return;
    }

    Student s;
    printf("\nEnter Student ID: ");
    scanf("%d", &s.id);
    printf("Enter Student Name: ");
    scanf(" %49[^\n]", s.name); // To accept names with spaces
    printf("***Route Details***\n");
    printf("Route 1 & 2: Dhanmondi to UIU campus\n");
    printf("Route 3: Mirpur to UIU campus\n");
    printf("Route 4: Jatrabari Mor to UIU campus\n");
    printf("Route 5: Palashi to UIU campus\n");
    printf("Route 6: Abdullahpur to UIU campus\n");
    printf("Enter Route Number: ");
    scanf("%d", &s.route_no);
    printf("Enter Mobile Number: ");
    scanf("%14s", s.mobile_no);
    printf("Enter Validity (in months): ");
    scanf("%d", &s.validity);

    students[student_count++] = s;
    printf("\nStudent added successfully!\n");
}

void displayStudents() {
    if (student_count == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("\n%-10s %-30s %-10s %-15s %-10s\n", "ID", "Name", "Route No", "Mobile No", "Validity"); //table
    printf("-----------------------------------------------------------------------------\n");

    for (int i = 0; i < student_count; i++) {
        printf("%-10d %-30s %-10d %-15s %-10d\n",
               students[i].id,
               students[i].name,
               students[i].route_no,
               students[i].mobile_no,
               students[i].validity);
    }
}

void searchStudent() {
    int id;
    printf("\nEnter Student ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            printf("\nStudent found:\n");
            printf("ID: %d\nName: %s\nRoute No: %d\nMobile No: %s\nValidity: %d months\n",
                   students[i].id,
                   students[i].name,
                   students[i].route_no,
                   students[i].mobile_no,
                   students[i].validity);
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}

void deleteStudent() {
    int id;
    printf("\nEnter Student ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            for (int j = i; j < student_count - 1; j++) {
                students[j] = students[j + 1];
            }
            student_count--;
            printf("Student with ID %d deleted successfully.\n", id);
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}

void saveToFile() {
    FILE *file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("Error: Unable to save data to file.\n");
        return;
    }

    fprintf(file, "%d\n", student_count); // Save the number of students
    for (int i = 0; i < student_count; i++) {
        fprintf(file, "%d,%s,%d,%s,%d\n",
                students[i].id,
                students[i].name,
                students[i].route_no,
                students[i].mobile_no,
                students[i].validity);
    }

    fclose(file);
    printf("Data saved to file successfully.\n");
}

void loadFromFile() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No existing data found. Starting fresh.\n");
        return;
    }

    fscanf(file, "%d\n", &student_count); // Read the number of students
    for (int i = 0; i < student_count; i++) {
        fscanf(file, "%d,%49[^,],%d,%14[^,],%d\n",
               &students[i].id,
               students[i].name,
               &students[i].route_no,
               students[i].mobile_no,
               &students[i].validity);
    }

    fclose(file);
    printf("Data loaded from file successfully.\n");
}


