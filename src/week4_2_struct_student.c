/*
 * Task 2 - Define and use a struct (Student record)
 * No input: fills two Student variables and prints them.
 */
#include <stdio.h>
#include <string.h> /* strcpy */

/* A student record: name, numeric ID and grade */
struct Student {
  char name[50];
  int id;
  float grade;
};

int main(void) {
  struct Student s1, s2;

  /* Arrays cannot be assigned with =, so strings are copied with strcpy */
  strcpy(s1.name, "Alice Johnson");
  s1.id = 1001;
  s1.grade = 9.1f;

  strcpy(s2.name, "Bob Smith");
  s2.id = 1002;
  s2.grade = 8.7f;

  /* Fields are accessed with the dot operator; grade shown with 1 decimal */
  printf("Student 1: %s, ID: %d, Grade: %.1f\n", s1.name, s1.id, s1.grade);
  printf("Student 2: %s, ID: %d, Grade: %.1f\n", s2.name, s2.id, s2.grade);

  return 0;
}