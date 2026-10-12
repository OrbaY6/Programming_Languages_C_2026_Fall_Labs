// week5_task3_student_management_system.c
// Name: Ismet Orbay  Surname: Gursoy  Student ID: 241ADB156
//
// Task 3: Mini-project – Student management system with file persistence
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task3_student_management_system

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define LINE_LEN 256
#define DATA_FILE "students.txt"

typedef struct Student {
  char name[NAME_LEN];
  int id;
  float gpa;
} Student;

// Function prototypes (do not change these signatures – the autograder calls
// them directly)
int load_students(Student arr[], int max);  // returns number of records loaded
int save_students(const Student arr[], int count);  // 0 on success, -1 on error
void add_student(Student arr[], int* count);
void list_students(const Student arr[], int count);
int read_line(const char* prompt, char* buf, size_t size);

int main(void) {
  Student students[MAX_STUDENTS];
  int count = 0;
  char input[LINE_LEN];
  int running = 1;

  // Load existing data from the file (0 students on first run)
  count = load_students(students, MAX_STUDENTS);
  printf("Loaded %d student(s) from %s\n", count, DATA_FILE);

  while (running) {
    printf("\n=== Student Management System ===\n");
    printf("1. List students\n");
    printf("2. Add student\n");
    printf("3. Save and Exit\n");

    int choice;
    if (read_line("Select an option: ", input, sizeof input) != 0) {
      choice = 3;  // end of input: save and exit instead of looping forever
    } else {
      char* end;
      long value = strtol(input, &end, 10);
      choice = (end != input && *end == '\0')
                   ? (int)value
                   : 0;  // non-numbers become invalid
    }

    switch (choice) {
      case 1:
        list_students(students, count);
        break;
      case 2:
        add_student(students, &count);
        break;
      case 3:
        if (save_students(students, count) != 0) {
          fprintf(stderr, "Error: could not save data to %s\n", DATA_FILE);
        } else {
          printf("Data saved. Goodbye!\n");
        }
        running = 0;
        break;
      default:
        printf("Invalid option. Try again.\n");
    }
  }

  return EXIT_SUCCESS;
}

// Provided helper – prints a prompt and reads one line from stdin into buf.
// The trailing newline is removed. Returns 0 on success, -1 on end of input
// (EOF).
int read_line(const char* prompt, char* buf, size_t size) {
  printf("%s", prompt);
  fflush(stdout);
  if (fgets(buf, (int)size, stdin) == NULL) {
    return -1;
  }
  size_t len = strcspn(buf, "\r\n");
  if (buf[len] == '\0' && len == size - 1) {
    // Line was longer than the buffer: discard the rest of it.
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
  }
  buf[len] = '\0';
  return 0;
}

// Loads students from DATA_FILE into arr (at most max records).
// A missing file is not an error (first run). Blank or malformed lines are
// skipped. Returns the number of students loaded.
int load_students(Student arr[], int max) {
  FILE* fp = fopen(DATA_FILE, "r");
  if (fp == NULL) {
    return 0;  // no file yet -> start with an empty list
  }

  char line[LINE_LEN];
  int count = 0;

  while (count < max && fgets(line, sizeof line, fp) != NULL) {
    Student s = {0};
    // %49[^,] reads up to 49 characters that are not commas (the name may
    // contain spaces)
    if (sscanf(line, "%49[^,],%d,%f", s.name, &s.id, &s.gpa) == 3) {
      arr[count] = s;
      count++;
    }
    // lines where sscanf did not read all 3 fields are skipped
  }

  fclose(fp);
  return count;
}

// Writes all students to DATA_FILE (overwriting it), one "name,id,gpa" line
// each. Returns 0 on success, -1 if the file cannot be opened.
int save_students(const Student arr[], int count) {
  FILE* fp = fopen(DATA_FILE, "w");
  if (fp == NULL) {
    perror(DATA_FILE);
    return -1;
  }

  for (int i = 0; i < count; i++) {
    fprintf(fp, "%s,%d,%.2f\n", arr[i].name, arr[i].id, arr[i].gpa);
  }

  fclose(fp);
  return 0;
}

// Asks the user for a name, ID and GPA, validates them and adds the student.
void add_student(Student arr[], int* count) {
  char name_buf[LINE_LEN];
  char id_buf[LINE_LEN];
  char gpa_buf[LINE_LEN];

  if (*count >= MAX_STUDENTS) {
    printf("Cannot add more students (limit reached).\n");
    return;
  }

  // Read all three inputs first, so a bad value does not shift the following
  // input lines
  if (read_line("Enter name: ", name_buf, sizeof name_buf) != 0) return;
  if (read_line("Enter ID: ", id_buf, sizeof id_buf) != 0) return;
  if (read_line("Enter GPA: ", gpa_buf, sizeof gpa_buf) != 0) return;

  // Name: not empty, no comma (comma is the file separator), must fit into
  // name[]
  int name_ok = name_buf[0] != '\0' && strchr(name_buf, ',') == NULL &&
                strlen(name_buf) < NAME_LEN;

  // ID: the whole string must be an integer that fits into an int
  char* end;
  long id = strtol(id_buf, &end, 10);
  int id_ok = end != id_buf && *end == '\0' && id >= INT_MIN && id <= INT_MAX;

  // GPA: the whole string must be a number between 0.0 and 4.0
  float gpa = strtof(gpa_buf, &end);
  int gpa_ok = end != gpa_buf && *end == '\0' && gpa >= 0.0f && gpa <= 4.0f;

  if (!name_ok || !id_ok || !gpa_ok) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  Student* s = &arr[*count];
  strcpy(s->name, name_buf);  // safe: length was checked above
  s->id = (int)id;
  s->gpa = gpa;
  (*count)++;

  printf("Student added successfully!\n");
}

// Prints all students as a table, or "No students found." if the list is empty.
void list_students(const Student arr[], int count) {
  if (count == 0) {
    printf("No students found.\n");
    return;
  }

  printf("%-5s %-20s %s\n", "ID", "Name", "GPA");
  for (int i = 0; i < count; i++) {
    printf("%-5d %-20s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
  }
}