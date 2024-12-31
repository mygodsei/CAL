/*  11327240
    林佳融  */
#include <stdio.h>
#include <time.h>

void bubble_sort(int array[], int n);

void insertion_sort(int array[], int n);

void execute(int bubble[], int insertion[], int n);

int main() {
  int n = 20;
  int array[20], i;

  printf("輸入不重複的整數數列共 20 個:\n");
  for (i = 0; i < n; i++) {
    scanf("%d", &array[i]);
  }

  int bubble_array[20], insertion_array[20];
  for (i = 0; i < n; i++) {
    bubble_array[i] = array[i];
    insertion_array[i] = array[i];
  }

  execute(bubble_array, insertion_array, n);

  return 0;
}

void bubble_sort(int array[], int n) {
  int i, j, temp, swap;
  for (i = 0; i < n - 1; i++) {
    swap = 0;
    for (j = 0; j < n - i - 1; j++) {
      if (array[j] > array[j + 1]) {
        temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
        swap++;
      }
    }
    printf("Pass %d: ", i + 1);
    for (j = 0; j < n; j++) {
      printf("%d ", array[j]);
    }
    printf("swap = %d\n", swap);
    if (swap == 0) break;
  }
}

void insertion_sort(int array[], int n) {
  int i, j, num, swap;
  for (i = 1; i < n; i++) {
    num = array[i];
    j = i - 1;
    swap = 0;
    while (j >= 0 && array[j] > num) {
      array[j + 1] = array[j];
      j--;
      swap++;
    }
    array[j + 1] = num;
    printf("Pass %d: ", i);
    for (j = 0; j < n; j++) {
      printf("%d ", array[j]);
    }
    printf("swap = %d\n", swap);
  }
}

void execute(int bubble[], int insertion[], int n) {
  clock_t start, end;

  printf("Bubble Sort:\n");
  start = clock();
  bubble_sort(bubble, n);
  end = clock();
  printf("Execution time: %.6f s\n", (double)(end - start) / CLOCKS_PER_SEC);

  printf("\nInsertion Sort:\n");
  start = clock();
  insertion_sort(insertion, n);
  end = clock();
  printf("Execution time: %.6f s\n", (double)(end - start) / CLOCKS_PER_SEC);
}
