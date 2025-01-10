#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//creation de l'enregistrement 

typedef struct Student {
    int rollNumber;
    char name[50];
    float grade;
    struct Student *next;
} Student;

//fonction pour verifier si l'identifiant est unique dans la liste chainée 

int isUniqueRollNumber(Student *head, int rollNumber) {
    Student *temp = head;
    while (temp != NULL) {
        if (temp->rollNumber == rollNumber) {
            return 0;
        }
        temp = temp->next;
    }
    return 1;
}

//ajout etudiant dans la liste chainée

void addStudent(Student **head, int rollNumber, char name[], float grade) {
    if (!isUniqueRollNumber(*head, rollNumber)) {
        printf("Roll number already exists. Please use a unique roll number.\n");
        return;
    }

    //allocation memoire pour nouveau etudiant 

    Student *newStudent = (Student *)malloc(sizeof(Student));
    newStudent->rollNumber = rollNumber;
    strcpy(newStudent->name, name);
    newStudent->grade = grade;
    newStudent->next = NULL;

    //ajout dans la liste chainée

    if (*head == NULL) {
        *head = newStudent;
    } else {
        Student *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newStudent;
    }
    printf("Student added successfully!\n");
}

//affichage tous les étudiants dans la liste chainée 

void displayStudents(Student *head) {
    if (head == NULL) {
        printf("No students to display.\n");
        return;
    }

    printf("\nRoll Number\tName\t\tGrade\n");
    printf("----------------------------------------\n");
    Student *temp = head;
    while (temp != NULL) {
        printf("%d\t\t%s\t\t%.2f\n", temp->rollNumber, temp->name, temp->grade);
        temp = temp->next;
    }
}

//enregistrer l'etudiant dans un fichier 

void saveToFile(Student *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }

    Student *temp = head;
    while (temp != NULL) {
        fprintf(file, "%d %s %.2f\n", temp->rollNumber, temp->name, temp->grade);
        temp = temp->next;
    }

    fclose(file);
    printf("Data saved to file successfully.\n");
}

//charger données etudiants à partir du fichier

Student *loadFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file for reading. Starting with an empty list.\n");
        return NULL;
    }

    Student *head = NULL, *temp = NULL;
    while (!feof(file)) {
        Student *newStudent = (Student *)malloc(sizeof(Student));
        if (fscanf(file, "%d %s %f", &newStudent->rollNumber, newStudent->name, &newStudent->grade) == 3) {
            newStudent->next = NULL;
            if (head == NULL) {
                head = newStudent;
                temp = head;
            } else {
                temp->next = newStudent;
                temp = temp->next;
            }
        } else {
            free(newStudent);
        }
    }

    fclose(file);
    printf("Data loaded from file successfully.\n");
    return head;
}


//supprimer etudiant à partir de l'identifiant 

void deleteStudent(Student **head, int rollNumber) {
    if (*head == NULL) {
        printf("No students to delete.\n");
        return;
    }

    Student *temp = *head, *prev = NULL;

    if (temp != NULL && temp->rollNumber == rollNumber) {
        *head = temp->next;
        free(temp);
        printf("Student with roll number %d deleted successfully.\n", rollNumber);
        return;
    }

    while (temp != NULL && temp->rollNumber != rollNumber) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student with roll number %d not found.\n", rollNumber);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Student with roll number %d deleted successfully.\n", rollNumber);
}

//tirer les etudiants par nom

void sortStudentsByName(Student **head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    int swapped;
    Student *ptr1;
    Student *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (strcasecmp(ptr1->name, ptr1->next->name) > 0) {
                int tempRoll = ptr1->rollNumber;
                char tempName[50];
                float tempGrade = ptr1->grade;

                strcpy(tempName, ptr1->name);

                ptr1->rollNumber = ptr1->next->rollNumber;
                strcpy(ptr1->name, ptr1->next->name);
                ptr1->grade = ptr1->next->grade;

                ptr1->next->rollNumber = tempRoll;
                strcpy(ptr1->next->name, tempName);
                ptr1->next->grade = tempGrade;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}


//chercher etudiant par identifiant 

void searchStudentByRollNumber(Student *head, int rollNumber) {
    Student *temp = head;
    while (temp != NULL) {
        if (temp->rollNumber == rollNumber) {
            printf("\nStudent Found:\n");
            printf("Roll Number: %d\n", temp->rollNumber);
            printf("Name: %s\n", temp->name);
            printf("Grade: %.2f\n", temp->grade);
            return;
        }
        temp = temp->next;
    }
    printf("Student with roll number %d not found.\n", rollNumber);
}

//charcher etudiant 

void searchStudentByName(Student *head, char name[]) {
    Student *temp = head;
    int found = 0;
    while (temp != NULL) {
        if (strcasecmp(temp->name, name) == 0) {
            if (!found) {
                printf("\nStudents Found:\n");
                printf("Roll Number\tName\t\tGrade\n");
                printf("----------------------------------------\n");
            }
            printf("%d\t\t%s\t\t%.2f\n", temp->rollNumber, temp->name, temp->grade);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("No students found with name %s.\n", name);
    }
}

//ajouter note entre 0 et 100

float validateGrade() {
    float grade;
    while (1) {
        printf("Enter Grade (0.0 - 100.0): ");
        scanf("%f", &grade);
        if (grade >= 0.0 && grade <= 100.0) {
            return grade;
        }
        printf("Invalid grade. Please enter a value between 0.0 and 100.0.\n");
    }
}


//compter notre des etudiants 

void countStudents(Student *head) {
    int count = 0;
    Student *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    printf("Total number of students: %d\n", count);
}



//calculer moyenne de classe 

void calculateAverageGrade(Student *head) {
    if (head == NULL) {
        printf("No students available to calculate the average grade.\n");
        return;
    }
    float totalGrade = 0;
    int count = 0;
    Student *temp = head;
    while (temp != NULL) {
        totalGrade += temp->grade;
        count++;
        temp = temp->next;
    }
    printf("Average grade of students: %.2f\n", totalGrade / count);
}

//fonction principale 

int main() {
    system("cat banner.txt");

    Student *head = NULL;
    int choice, rollNumber;
    char name[50];
    float grade;
    const char *filename = "students.txt";

    head = loadFromFile(filename);

    while (1) {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Delete Student\n");
        printf("4. Save to File\n");
        printf("5. Sort Students by Name\n");
        printf("6. Search Student by Roll Number\n");
        printf("7. Search Student by Name\n");
        printf("8. Count Total Students\n");
        printf("9. Calculate Average Grade\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Roll Number: ");
                scanf("%d", &rollNumber);
                printf("Enter Name: ");
                scanf("%s", name);
                grade = validateGrade();
                addStudent(&head, rollNumber, name, grade);
                break;

            case 2:
                displayStudents(head);
                break;

            case 3:
                printf("Enter Roll Number to delete: ");
                scanf("%d", &rollNumber);
                deleteStudent(&head, rollNumber);
                break;

            case 4:
                saveToFile(head, filename);
                break;

            case 5:
                sortStudentsByName(&head);
                printf("Students sorted by name successfully.\n");
                break;

            case 6:
                printf("Enter Roll Number to search: ");
                scanf("%d", &rollNumber);
                searchStudentByRollNumber(head, rollNumber);
                break;

            case 7:
                printf("Enter Name to search: ");
                scanf("%s", name);
                searchStudentByName(head, name);
                break;

            case 8:
                countStudents(head);
                break;

            case 9:
                calculateAverageGrade(head);
                break;

            case 10:
                saveToFile(head, filename);
                printf("Exiting the program. Goodbye!\n");
                while (head != NULL) {
                    Student *temp = head;
                    head = head->next;
                    free(temp);
                }
                exit(0);

            default:
                printf("Invalid choice. Please enter a number between 1 and 10.\n");
        }
    }

    return 0;
}
