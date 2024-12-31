#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef char Str50[50];

struct Customer {
  int id;
  Str50 name;
  int balance;
};

typedef struct Customer CustomerArray[200];
int Read(CustomerArray cus_arr);
void ErrorLog(int err_num, int id, int money,
    CustomerArray cus_arr, int num_of_customer);
void Print(CustomerArray cus_arr, int num_of_customer);
int Process(int id, int money, CustomerArray cus_arr, int num_of_customer);

int main() {
  CustomerArray customer;
  int num_of_customer;
  num_of_customer = Read(customer);
  int id, money, errornum;
  while (1) {
    scanf("%d", &id);
    if (id == -1) break;
    scanf("%d", &money);
    errornum = Process(id, money, customer, num_of_customer);
    ErrorLog(errornum, id, money, customer, num_of_customer);
  }
  Print(customer, num_of_customer);
  return 0;
}
int Read(CustomerArray cus_arr) {
  int count = 0, id, balance;
  char name[100];
  while (1) {
    scanf("%d", &id);
    if (id == -1) break;
    scanf("%s %d", name, &balance);
    int exist = 0;
    for (int i = 0; i < count; i++) {
      if (cus_arr[i].id == id) {
        exist = 1;
        break;
      }
    }
    if (exist != 1) {
      cus_arr[count].id = id;
      for (int i = 0; name[i] != '\0'; i++) {
        cus_arr[count].name[i] = name[i];
      }
      cus_arr[count].balance = balance;
      count++;
    }
  }
  return count;
}
void ErrorLog(int err_num, int id, int money,
    CustomerArray cus_arr, int num_of_customer) {
  int i;
  if (err_num == 0) {
    return;
  }
  if (err_num == 1) {
    printf("No such account: %d\n", id);
  } else if (err_num == 2) {
    for (i = 0; i < num_of_customer; i++) {
      if (cus_arr[i].id == id) {
        printf("%s's balance is %d dollars short.\n",
            cus_arr[i].name, money - cus_arr[i].balance);
        break;
      }
    }
  }
}
void Print(CustomerArray cus_arr, int num_of_customer) {
  for (int i = 0; i < num_of_customer; i++) {
    printf("%d\n%s\n%d\n", cus_arr[i].id, cus_arr[i].name, cus_arr[i].balance);
  }
}
int Process(int id, int money, CustomerArray cus_arr, int num_of_customer) {
  for (int i = 0; i < num_of_customer; i++) {
    if (cus_arr[i].id == id) {
      if (cus_arr[i].balance >= money) {
        cus_arr[i].balance -= money;
        return 0;
      } else {
        return 2;
      }
    }
  }
  return 1;
}
