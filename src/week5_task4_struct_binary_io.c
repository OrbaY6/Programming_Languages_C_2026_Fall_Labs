// week5_task4_struct_binary_io.c   (BONUS)
// Name: Ismet Orbay  Surname: Gursoy  Student ID: 241ADB156
//
// Task 4: Save and load a struct in binary format with fwrite()/fread()
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task4_struct_binary_io

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
int save_student_binary(const Student* s,
                        const char* filename);  // 0 on success, -1 on error
int load_student_binary(const char* filename,
                        Student* out);  // 0 on success, -1 on error
long file_size(const char* filename);   // bytes, -1 on error

int main(void) {
  Student s1 = {
      0};  // zero-initialised so unused name bytes are not garbage on disk
  strcpy(s1.name, "Alice");
  s1.age = 21;
  s1.gpa = 3.75f;

  Student loaded = {0};
  const char* bin_file = "student.bin";
  const char* txt_file = "student.txt";

  printf("Saving student in binary format...\n");
  if (save_student_binary(&s1, bin_file) != 0) {
    fprintf(stderr, "Error: could not save student to %s\n", bin_file);
    return EXIT_FAILURE;
  }

  // Save the same record as text ("name age gpa") for comparison
  FILE* txt = fopen(txt_file, "w");
  if (txt == NULL) {
    perror(txt_file);
    return EXIT_FAILURE;
  }
  fprintf(txt, "%s %d %.2f\n", s1.name, s1.age, s1.gpa);
  fclose(txt);

  printf("Loading student from binary file...\n");
  if (load_student_binary(bin_file, &loaded) != 0) {
    fprintf(stderr, "Error: could not load student from %s\n", bin_file);
    return EXIT_FAILURE;
  }

  printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age,
         loaded.gpa);
  printf("Text file size: %ld bytes\n", file_size(txt_file));
  printf("Binary file size: %ld bytes\n", file_size(bin_file));

  return EXIT_SUCCESS;
}

// Writes the whole struct to a binary file. Returns 0 on success, -1 on error.
int save_student_binary(const Student* s, const char* filename) {
  FILE* fp = fopen(filename, "wb");
  if (fp == NULL) {
    perror(filename);
    return -1;
  }

  size_t written = fwrite(s, sizeof(Student), 1,
                          fp);  // write 1 element of sizeof(Student) bytes
  fclose(fp);

  return (written == 1) ? 0 : -1;
}

// Reads one struct back from a binary file. Returns 0 on success, -1 on error.
int load_student_binary(const char* filename, Student* out) {
  FILE* fp = fopen(filename, "rb");
  if (fp == NULL) {
    perror(filename);
    return -1;
  }

  size_t read = fread(out, sizeof(Student), 1,
                      fp);  // read 1 element of sizeof(Student) bytes
  fclose(fp);

  return (read == 1) ? 0 : -1;
}

// Returns the size of a file in bytes, or -1 on error.
long file_size(const char* filename) {
  FILE* fp = fopen(filename, "rb");
  if (fp == NULL) {
    perror(filename);
    return -1;
  }

  if (fseek(fp, 0, SEEK_END) != 0) {  // jump to the end of the file
    fclose(fp);
    return -1;
  }
  long size = ftell(fp);  // current position = number of bytes
  fclose(fp);

  return size;
}