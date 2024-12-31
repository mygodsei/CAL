#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef char Str40[40];
typedef char Str24[24];
typedef char Str9[9];

typedef struct {
  bool non_negative;
  int decimal;
  int int_of_fraction;
  int num_digits;
} FloatInfo;

FloatInfo FractionStrAnalysis(Str40 float_str);
void DecimalToBinary(int input_num, Str40 output_num);
void FractionToBinary(int int_of_fraction, int num_digits, Str40 output_bin);
int FindMantissaExponent(Str40 input_decimal, Str40 input_fraction,
    Str24 mantissa);
void DecimalToExcess127(int exponent, Str9 excess127);

int main() {
  const char* zero = {"000000 00000000000000000000000"};
  Str40 input_string = "";
  Str24 binary_mantissa = "";
  Str9 binary_excess127 = "";
  scanf("%s", input_string);
  FloatInfo float_info = FractionStrAnalysis(input_string);
  bool is_positive = (input_string[0] != '-');
  if (float_info.decimal == 0 && float_info.int_of_fraction == 0) {
    printf("%c %s", is_positive ? '0' : '1', zero);
    return 0;
  }
  Str40 integer_binary = "";
  DecimalToBinary(float_info.decimal, integer_binary);
  Str40 fraction_binary = "";
  FractionToBinary(float_info.int_of_fraction,
      float_info.num_digits, fraction_binary);
  int exponent = FindMantissaExponent(integer_binary,
      fraction_binary, binary_mantissa);
  DecimalToExcess127(exponent, binary_excess127);
  if (is_positive)
    printf("0 %s %s", binary_excess127 ,  binary_mantissa);
  else
    printf("1 %s %s", binary_excess127 ,  binary_mantissa);

  return 0;
}
void DecimalToBinary(int input_num, Str40 output_num) {
  int index = 0;
  while (input_num > 0) {
    output_num[index++] = (input_num % 2) + '0';
    input_num /= 2;
  }

  if (index == 0) {
    output_num[index++] = '0';
  }
  output_num[index] = '\0';

  for (int i = 0, j = index - 1; i < j; i++, j--) {
    char temp = output_num[i];
    output_num[i] = output_num[j];
    output_num[j] = temp;
  }
}
FloatInfo FractionStrAnalysis(Str40 float_str) {
  FloatInfo result = {true, 0, 0, 0};
  int len = strlen(float_str);
  int point_index = -1;
  if (float_str[0] == '-') {
    result.non_negative = false;
    float_str++;
    len--;
  }
  for (int i = 0; i < len; i++) {
    if (float_str[i] == '.') {
      point_index = i;
      break;
    }
  }
  if (point_index == -1) {
    result.decimal = atoi(float_str);
  } else {
    char temp[40];
    strncpy(temp, float_str, point_index);
    temp[point_index] = '\0';
    result.decimal = atoi(temp);
  }
  if (point_index != -1 && point_index < len - 1) {
    result.num_digits = len - point_index - 1;
    result.int_of_fraction = atoi(&float_str[point_index + 1]);
  }
  return result;
}
void FractionToBinary(int int_of_fraction, int num_digits, Str40 output_bin) {
  strcpy(output_bin, "");
  if (num_digits <= 0 || int_of_fraction < 0) {
    return;
  }
  double fraction = 0.0;
  int multiplier = 1;
  for (int i = 0; i < num_digits; i++) {
    multiplier *= 10;
  }
  fraction = (double)int_of_fraction / multiplier;
  int digit_count = 0;
  while (fraction > 0 && digit_count < 10) {
    fraction *= 2;
    if (fraction >= 1) {
      strcat(output_bin, "1");
      fraction -= 1;
    } else {
      strcat(output_bin, "0");
    }
    digit_count++;
    if (fraction == 0) {
      break;
    }
  }
}
int FindMantissaExponent(Str40 input_decimal, Str40 input_fraction,
    Str24 mantissa) {
  int exponent = 0;
  char normalized[80] = "";
  strcpy(mantissa, "");
  strcat(normalized, input_decimal);
  strcat(normalized, input_fraction);
  int len = strlen(normalized);
  if (len == 0) return 0;
  int first = -1;
  for (int i = 0; i < len; i++) {
    if (normalized[i] == '1') {
      first = i;
      break;
    }
  }
  if (first == -1) return 0;
  exponent = strlen(input_decimal) - first - 1;
  int mantissa_start = first + 1;
  int mantissa_copy_count = 0;
  for (int i = mantissa_start; i < len && mantissa_copy_count < 23; i++) {
    char temp[2] = {normalized[i], '\0'};
    strcat(mantissa, temp);
    mantissa_copy_count++;
  }
  while (strlen(mantissa) < 23) {
    strcat(mantissa, "0");
  }
  return exponent;
}
void DecimalToExcess127(int exponent, Str9 excess127) {
  int better_exponent = exponent + 127;
  strcpy(excess127, "");
  for (int i = 7; i >= 0; i--) {
    excess127[7-i] = ((better_exponent >> i) & 1) + '0';
  }
  excess127[8] = '\0';
}