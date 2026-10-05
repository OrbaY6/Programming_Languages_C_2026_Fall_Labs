/*
 * Task 3 - In-memory database (dynamic array of structs)
 * Reads N students (name id grade) and prints them as a table.
 */
#include <stdio.h>
#include <stdlib.h> /* malloc, free */

/* Same struct as in Task 2 */
struct Student {
  char name[50];
  int id;
  float grade;
};

int main(void) {
  int n;

  printf("Enter number of students: ");

  /* Reject non-numbers and non-positive counts */
  if (scanf("%d", &n) != 1 || n <= 0) {
    printf("Invalid number.\n");
    return 1;
  }

  /* One block of memory holding n Student records */
  struct Student* students = malloc((size_t)n * sizeof(struct Student));
  if (students == NULL) {
    printf("Memory allocation failed.\n");
    return 1;
  }

  for (int i = 0; i < n; i++) {
    printf("Enter data for student %d: ", i + 1);

    /* %49s leaves room for '\0' in name[50]; all 3 fields must be read */
    if (scanf("%49s %d %f", students[i].name, &students[i].id,
              &students[i].grade) != 3) {
      free(students); /* clean up before exiting on error */
      printf("Invalid input.\n");
      return 1;
    }
  }

  /* Empty line, then the table */
  printf("\n");
  printf("%-6s %-11s %s\n", "ID", "Name", "Grade");
  for (int i = 0; i < n; i++) {
    printf("%-6d %-11s %.1f\n", students[i].id, students[i].name,
           students[i].grade);
  }

  /* Optional bonus: average grade, printed after the required table */
  float total = 0.0f;
  for (int i = 0; i < n; i++) {
    total += students[i].grade;
  }
  printf("\nAverage grade = %.2f\n", total / n);

  free(students);
  return 0;
}