#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {MATH, HISTORY, ENGLISH, SCIENCE} subject_t;

typedef struct {
    subject_t subject;
    int value;
} grade_t;

typedef struct {
    char name[128];
    int age;
    grade_t* grades;
    int grade_count;
} student_t;

// TODO:
// Create a function the constructs a Student (returns a pointer to a new student)
// It should take it's name and it's age as parameter
// It should allocate 5 grades
// It should set the grade_count to 0

struct student_t *add_student(char *a_name, int age)
{
    student_t *new_student = (student_t*)malloc(sizeof(student_t));
    grade_t* the_grades = (grade_t*)calloc(5, sizeof(grade_t));
    strcpy(new_student->name, a_name);
    new_student->age = age;
    new_student->grades = the_grades;
    new_student->grade_count = 0;

    return new_student;
};

// TODO:
// Create a function that takes 3 parameters:
// A pointer to a Student
// A Subject
// An int (1-5)
// It should set the last grade's values with the given arguments

struct student_t *add_grades(student_t *student, subject_t a_subject, int a_grade)
{
    student->grades[student->grade_count].subject = a_subject;
    student->grades[student->grade_count].value = a_grade;
    student->grade_count++;

    return student;
};

// TODO:
// Create a function that takes a Student as a pointer and returns the subject
// that the student has worst grade in

int find_worst_grade(student_t *student)
{
    int worst_grade = 5;
    int bad_grade_index;
    for (int i = 0; i < student->grade_count; i++) {
        if (student->grades[i].value < worst_grade) {
            worst_grade = student->grades[i].value;
            bad_grade_index = i;
        }
    }

    if (worst_grade == 5) {
        return -1; //give -1, if the student has no grades worse than 5
    } else {
         return student->grades[bad_grade_index].subject;
    }
}

// TODO:
// Create a function that deconstructs a Student
// It should take a pointer that points to the student
// It should free each Grade and the Student itself

void deconstruct_student(student_t *student)
{
    free(student->grades);
    free(student);
}

int main()
{
    //create student and add grades
    char a_name[] = "Laura";
    int age = 27;
    student_t *laura_p = add_student(a_name, age);

    add_grades(laura_p, SCIENCE, 5);
    add_grades(laura_p, MATH, 5);
    add_grades(laura_p, HISTORY, 4);
    add_grades(laura_p, ENGLISH, 3);

    //print info
    printf("Name:\t %s\n", laura_p->name);
    printf("Age:\t %d\n", laura_p->age);
    printf("Number of grades:\t %d\n", laura_p->grade_count);

    //get and print worst grade
    int worst_grade = find_worst_grade(laura_p);
    printf("%s has the worst grade in:\t", laura_p->name);
    switch(worst_grade) {

        case 0:
            printf("Math");
            break;
        case 1:
            printf("History");
            break;
        case 2:
            printf("English");
            break;
        case 3:
            printf("Science");
            break;
        case -1:
            printf("No bad grades. All grades are 5.");
            break;
        default:
            printf("Couldn't find the worst grade.");
            break;
    }

    //free memory
    deconstruct_student(laura_p);

    return 0;
}
