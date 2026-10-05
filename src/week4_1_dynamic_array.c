/*
 * week4_1_dynamic_array.c
 * Author: Ismet Orbay Gursoy
 * Student ID: [241ADB156]
 * Description:
 *   Demonstrates creation and usage of a dynamic array using malloc.
 *   Allocate memory for n integers, read them from the user,
 *   print their sum and average, and then free the memory.
 *
 *   Output must match the format in the Week 4 instructions exactly
 *   (it is checked by the autograder).
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int n;
  int* arr = NULL;

  printf("Enter number of elements: ");
  if (scanf("%d", &n) != 1 || n <= 0) {
    printf("Invalid size.\n");
    return 1;
  }

  // Allocate memory for n integers on the heap
  arr = malloc((size_t)n * sizeof(int));

  // malloc can fail, so the pointer must be checked before use
  if (arr == NULL) {
    printf("Memory allocation failed.\n");
    return 1;
  }

  // Read n integers (on one line or on separate lines)
  printf("Enter %d integers: ", n);
  for (int i = 0; i < n; i++) {
    if (scanf("%d", &arr[i]) != 1) {
      free(arr);  // release memory before exiting on error
      printf("Invalid input.\n");
      return 1;
    }
  }

  // long long avoids overflow when adding many large values
  long long sum = 0;
  for (int i = 0; i < n; i++) {
    sum += arr[i];
  }

  // Cast to double so the division is not integer division (7 8 -> 7.50)
  double average = (double)sum / n;

  printf("Sum = %lld\n", sum);
  printf("Average = %.2f\n", average);

  // Every successful malloc needs a matching free
  free(arr);

  return 0;
}