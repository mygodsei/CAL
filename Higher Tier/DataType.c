#include <stdio.h>

int IsInt(const char* str);
int IsFloat(const char* str);
int IsIdentifier(const char* str);

int main() {
  int i = 0;
  char input[21];
  const char* type[4] = {"is an integer.", "is a floating number.",
                         "is an identifier.", "is a string."};
  scanf("%20s", input);
  if (IsInt(input)) i = 0;
  else if (IsFloat(input)) i = 1;
  else if (IsIdentifier(input)) i = 2;
  else i = 3;
  printf("%s %s", input, type[i]);
  return 0;
}

int IsInt(const char* str) {
  int i = 0;
  if (str[0] == '+' || str[0] == '-') i = 1;
  if (str[i] == '\0') return 0;
  for (; str[i] != '\0'; i++) {
    if (str[i] < '0' || str[i] > '9') return 0;
  }
  return 1;
}
int IsFloat(const char* str) {
  int i = 0, dot_count = 0, has_digit_before = 0, has_digit_after = 0;
  if (str[0] == '-') i = 1;
  for (; str[i] != '\0'; i++) {
    if (str[i] == '.') {
      dot_count++;
      if (dot_count > 1) return 0;
    } else if (str[i] >= '0' && str[i] <= '9') {
      if (dot_count == 0) has_digit_before = 1;
      else has_digit_after = 1;
    } else {
      return 0;
    }
  }
  return (dot_count == 1) && has_digit_before && has_digit_after;
}
int IsIdentifier(const char* str) {
  if (!((str[0] >= 'a' && str[0] <= 'z') || 
        (str[0] >= 'A' && str[0] <= 'Z') || 
        str[0] == '_')) return 0;
  for (int i = 1; str[i] != '\0'; i++) {
    if (!((str[i] >= 'a' && str[i] <= 'z') || 
          (str[i] >= 'A' && str[i] <= 'Z') || 
          (str[i] >= '0' && str[i] <= '9'))) return 0;
  }
  return 1;
}