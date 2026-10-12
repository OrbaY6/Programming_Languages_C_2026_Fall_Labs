// week5_task2_struct_save_load.c
// Name: Ismet Orbay  Surname: Gursoy  Student ID: 241ADB156
//
// Task 2: Save and load structured records from a file
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task2_struct_save_load

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct Student {
  char name[MAX_NAME_LEN];
  int age;
  float gpa;
} Student;

// Function prototypes (do not change these signatures – the autograder calls
// them directly)
int save_student(const Student* s,
                 const char* filename);  // 0 on success, -1 on error
int load_student(const char* filename,
                 Student* out);  // 0 on success, -1 on error

int main(void) {
  Student s1 = {0};
  strcpy(s1.name, "Alice");
  s1.age = 21;
  s1.gpa = 3.75f;

  Student loaded = {0};
  const char* filename = "student.txt";

  printf("Saving student to file...\n");
  if (save_student(&s1, filename) != 0) {
    fprintf(stderr, "Error: could not save student to %s\n", filename);
    return EXIT_FAILURE;
  }

  printf("Loading student from file...\n");
  if (load_student(filename, &loaded) != 0) {
    fprintf(stderr, "Error: could not load student from %s\n", filename);
    return EXIT_FAILURE;
  }

  printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age,
         loaded.gpa);

  return EXIT_SUCCESS;
}

// Saves one student as a single line "name age gpa".
// Returns 0 on success, -1 on error.
int save_student(const Student* s, const char* filename) {
  FILE* fp = fopen(filename, "w");
  if (fp == NULL) {
    perror(filename);
    return -1;
  }

  fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa);

  fclose(fp);
  return 0;
}

// Loads one student from a file written by save_student().
// Returns 0 on success, -1 if the file cannot be opened or the data is invalid.
int load_student(const char* filename, Student* out) {
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    perror(filename);
    return -1;
  }

  // %49s limits the name to 49 chars + '\0' so it cannot overflow name[50]
  int fields = fscanf(fp, "%49s %d %f", out->name, &out->age, &out->gpa);

  fclose(fp);  // close the file in every case

  if (fields != 3) {
    return -1;
  }
  return 0;
}