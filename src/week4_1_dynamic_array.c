/*
 * Task 1 - Dynamic array with malloc
 * Reads N integers into a heap-allocated array, prints their sum and average.
 */
#include <stdio.h>
#include <stdlib.h> /* malloc, free */

int main(void) {
  int n;

  /* Ask for the number of elements (no newline after the prompt) */
  printf("Enter number of elements: ");

  /* scanf returns 1 only if an integer was read; size must be positive */
  if (scanf("%d", &n) != 1 || n <= 0) {
    printf("Invalid size.\n");
    return 1;
  }

  /* Allocate exactly n ints on the heap */
  int* arr = malloc((size_t)n * sizeof(int));
  if (arr == NULL) {
    /* malloc can fail, so we must never use the pointer unchecked */
    printf("Memory allocation failed.\n");
    return 1;
  }

  printf("Enter %d integers: ", n);

  /* Read each value; numbers may be on one line or on separate lines */
  for (int i = 0; i < n; i++) {
    if (scanf("%d", &arr[i]) != 1) {
      free(arr); /* release memory before exiting on error */
      printf("Invalid input.\n");
      return 1;
    }
  }

  /* long long avoids overflow when adding many large ints */
  long long sum = 0;
  for (int i = 0; i < n; i++) {
    sum += arr[i];
  }

  /* Cast to double so the division is not integer division (7 8 -> 7.50) */
  double average = (double)sum / n;

  printf("Sum = %lld\n", sum);
  printf("Average = %.2f\n", average);

  /* Every successful malloc needs a matching free */
  free(arr);
  return 0;
}