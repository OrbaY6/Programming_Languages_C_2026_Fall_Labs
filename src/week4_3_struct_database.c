/*
 * week4_3_struct_database.c
 * Author: Ismet Orbay Gursoy
 * Student ID: [241ADB156]
 * Description:
 *   Simple in-memory "database" using an array of structs.
 *   Use malloc to allocate space for n Student records,
 *   read each record from the user, print them as a table,
 *   and then free the memory.
 *
 *   Output must match the format in the Week 4 instructions exactly
 *   (it is checked by the autograder).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Same struct definition as in Task 2
struct Student {
  char name[50];
  int id;
  float grade;
};

int main(void) {
  int n;
  struct Student* students = NULL;

  printf("Enter number of students: ");
  if (scanf("%d", &n) != 1 || n <= 0) {
    printf("Invalid number.\n");
    return 1;
  }

  // One contiguous block of memory for n Student records
  students = malloc((size_t)n * sizeof(struct Student));

  // malloc can fail, so the pointer must be checked before use
  if (students == NULL) {
    printf("Memory allocation failed.\n");
    return 1;
  }

  // Read name, id and grade for each student
  for (int i = 0; i < n; i++) {
    printf("Enter data for student %d: ", i + 1);

    // %49s leaves room for '\0' in name[50]; all 3 values must be read
    if (scanf("%49s %d %f", students[i].name, &students[i].id,
              &students[i].grade) != 3) {
      free(students);  // release memory before exiting on error
      printf("Invalid input.\n");
      return 1;
    }
  }

  // Empty line, then the table in input order
  printf("\n");
  printf("%-6s %-11s %s\n", "ID", "Name", "Grade");
  for (int i = 0; i < n; i++) {
    printf("%-6d %-11s %.1f\n", students[i].id, students[i].name,
           students[i].grade);
  }

  // Optional (not autograded): average grade after the table
  float total = 0.0f;
  for (int i = 0; i < n; i++) {
    total += students[i].grade;
  }
  printf("\nAverage grade = %.2f\n", total / n);

  // Every successful malloc needs a matching free
  free(students);

  return 0;
}