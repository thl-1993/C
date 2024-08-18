#include <check.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

#define S21_INFINITY 1.0 / 0.0L

START_TEST(s21_memchrTest) {
  // 1
  char str1_1[] = "1234567890";
  int c1 = '4';
  size_t n1 = 11;
  ck_assert_ptr_eq(s21_memchr(str1_1, c1, n1), memchr(str1_1, c1, n1));

  // 2
  char str1_2[] = "Hello, world!";
  int c2 = 101;
  s21_size_t n2 = strlen(str1_2);
  ck_assert_ptr_eq(memchr(str1_2, c2, n2), s21_memchr(str1_2, c2, n2));

  // 3
  char str1_3[] = "69917020";
  int c3 = '\0';
  s21_size_t n3 = 9;
  ck_assert_ptr_eq(memchr(str1_3, c3, n3), s21_memchr(str1_3, c3, n3));

  // 4
  char str1_4[20] = " \n";
  int c4 = 0;
  size_t n4 = 10;
  ck_assert_ptr_eq(s21_memchr(str1_4, c4, n4), memchr(str1_4, c4, n4));
}
END_TEST

// 2
START_TEST(s21_memcmpTest) {
  // 1
  char str1_1[] = "zterstr1";
  char str2_1[] = "zterstr1";
  int p = 0;
  ck_assert_int_eq(memcmp(str1_1, str2_1, p), s21_memcmp(str1_1, str2_1, p));

  // 2
  char str1_2[] = "zterstr1";
  char str2_2[] = "\0";
  p = 1;
  ck_assert_int_eq(memcmp(str1_2, str2_2, p), s21_memcmp(str1_2, str2_2, p));

  // 3
  char str1_3[] = "2";
  char str2_3[] = "2";
  p = 1;
  ck_assert_int_eq(memcmp(str1_3, str2_3, p), s21_memcmp(str1_3, str2_3, p));
}
END_TEST

// 3

START_TEST(s21_memcpyTest) {
  // 1
  char str1_1[] = "Hello world";
  char str2_1[20] = "";
  char s21_str1_1[] = "Hello world";
  char s21_str2_1[20] = "";
  int p = 5;
  memcpy(str2_1, str1_1, p);
  s21_memcpy(s21_str2_1, s21_str1_1, p);
  ck_assert_mem_eq(str2_1, s21_str2_1, p);

  // 2
  char str1_2[] = "Hello";
  char str2_2[20] = "";
  char s21_str1_2[] = "Hello";
  char s21_str2_2[20] = "";
  p = 6;
  memcpy(str2_2, str1_2, p);
  s21_memcpy(s21_str2_2, s21_str1_2, p);
  ck_assert_mem_eq(str2_2, s21_str2_2, p);

  // 3
  char str1_3[20] = "";
  char str2_3[] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'd', '!'};
  char s21_str1_3[10] = "";
  char s21_str2_3[] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'd', '!'};
  p = 10;
  memcpy(str2_3, str1_3, p);
  s21_memcpy(s21_str2_3, s21_str1_3, p);
  ck_assert_mem_eq(str2_3, s21_str2_3, p);
}
END_TEST

// 4
START_TEST(s21_memsetTest) {
  // 1
  char str1_1[] = "helloworld";
  char s21_str1_1[] = "helloworld";
  int s = 116;
  int p = 4;
  ck_assert_str_eq(memset(str1_1, s, p), s21_memset(s21_str1_1, s, p));

  // 2
  char str1_2[] = "hellost";
  char s21_str1_2[] = "hellost";
  s = 116;
  p = 0;
  ck_assert_str_eq(memset(str1_2, s, p), s21_memset(s21_str1_2, s, p));

  // 3
  char str1_3[2] = "";
  char s21_str1_3[2] = "";
  s = 116;
  p = 1;
  ck_assert_str_eq(memset(str1_3, s, p), s21_memset(s21_str1_3, s, p));
}
END_TEST

// 5
START_TEST(s21_strncatTest) {
  // 1
  char str1_1[20] = "Gocjslrn: ";
  char str2_1[] = "brhdvsyr";
  char s21_str1_1[20] = "Gocjslrn: ";
  char s21_str2_1[] = "brhdvsyr";
  int p = 3;
  ck_assert_str_eq(strncat(str1_1, str2_1, p),
                   s21_strncat(s21_str1_1, s21_str2_1, p));

  // 2
  char str1_2[20] = "Gocjslrn: ";
  char str2_2[] = "brhdvsyr";
  char s21_str1_2[20] = "Gocjslrn: ";
  char s21_str2_2[] = "brhdvsyr";
  p = 20;
  ck_assert_str_eq(strncat(str1_2, str2_2, p),
                   s21_strncat(s21_str1_2, s21_str2_2, p));

  // 3
  char str1_3[20] = "Gocjslrn: ";
  char str2_3[] = "brhdvsyr";
  char s21_str1_3[20] = "Gocjslrn: ";
  char s21_str2_3[] = "brhdvsyr";
  p = 0;
  ck_assert_str_eq(strncat(str1_3, str2_3, p),
                   s21_strncat(s21_str1_3, s21_str2_3, p));
}
END_TEST

// 6
START_TEST(s21_strchrTest) {
  // 1
  char str1_1[] = "Pops-up-hars-d-xsew-mxkfor";
  int s1 = '0';
  ck_assert_ptr_eq(s21_strchr(str1_1, s1), strchr(str1_1, s1));

  // 2
  char str1_2[] = "Pops-up-hars-d-xsew-mxkfor";
  int s2 = '\0';
  ck_assert_ptr_eq(s21_strchr(str1_2, s2), strchr(str1_2, s2));

  // 3
  char str1_3[] = "Pops-up-hars-d-xsew-mxkfor";
  int s3 = 'b';
  ck_assert_ptr_eq(s21_strchr(str1_3, s3), strchr(str1_3, s3));
}
END_TEST

// 7
START_TEST(s21_strncmpTest) {
  // 1
  char str1[] = "Reen nike";
  char str2[] = "Reen Nike";
  int p = 5;
  ck_assert_int_eq(strncmp(str1, str2, p), s21_strncmp(str1, str2, p));

  // 2
  p = 2;
  ck_assert_int_eq(strncmp(str1, str2, p), s21_strncmp(str1, str2, p));

  // 3
  p = 0;
  ck_assert_int_eq(strncmp(str1, str2, p), s21_strncmp(str1, str2, p));
}
END_TEST

// 8
START_TEST(s21_strncpyTest) {
  // 1
  char str1_1[] = "net voin";
  char str2_1[] = "geh ed";
  char s21_str1_1[] = "net voin";
  char s21_str2_1[] = "geh ed";
  int p = 3;
  ck_assert_str_eq(strncpy(str2_1, str1_1, p),
                   s21_strncpy(s21_str2_1, s21_str1_1, p));

  // 2
  char str1_2[] = "net voin";
  char str2_2[] = "geh ed";
  char s21_str1_2[] = "net voin";
  char s21_str2_2[] = "geh ed";
  p = 0;
  ck_assert_str_eq(strncpy(str2_2, str1_2, p),
                   s21_strncpy(s21_str2_2, s21_str1_2, p));

  // 3
  char str1_3[] = "net";
  char str2_3[] = "geh ed";
  char s21_str1_3[] = "net";
  char s21_str2_3[] = "geh ed";
  p = 4;
  ck_assert_str_eq(strncpy(str2_3, str1_3, p),
                   s21_strncpy(s21_str2_3, s21_str1_3, p));

  // 4
  char str1_4[] = "";
  char str2_4[] = "geh ed";
  char s21_str1_4[] = "";
  char s21_str2_4[] = "geh ed";
  p = 4;
  ck_assert_str_eq(strncpy(str2_4, str1_4, p),
                   s21_strncpy(s21_str2_4, s21_str1_4, p));
}
END_TEST

// 9
START_TEST(s21_strcspnTest) {
  // 1
  char str1_1[] = "0123456789";
  char str2_1[] = "5478";
  ck_assert_int_eq(strcspn(str1_1, str2_1), s21_strcspn(str1_1, str2_1));

  // 2
  char str1_2[] = "0123456789";
  char str2_2[] = "ABCD";
  ck_assert_int_eq(strcspn(str1_2, str2_2), s21_strcspn(str1_2, str2_2));

  // 3
  char str1_3[10] = "";
  char str2_3[] = "ABCD";
  ck_assert_int_eq(strcspn(str1_3, str2_3), s21_strcspn(str1_3, str2_3));

  // 4
  char str1_4[] = "01ABCD";
  char str2_4[10] = "";
  ck_assert_int_eq(strcspn(str1_4, str2_4), s21_strcspn(str1_4, str2_4));
}
END_TEST

// 10
START_TEST(s21_strerrorTest) {
  // 1
  int p = 2;
  ck_assert_str_eq(strerror(p), s21_strerror(p));

  // 2
  p = 135;
  ck_assert_str_eq(strerror(p), s21_strerror(p));

  // 3
  for (p = 0; p < 106; p++) {
    ck_assert_str_eq(strerror(p), s21_strerror(p));
  }
}
END_TEST

// 11
START_TEST(s21_strlenTest) {
  // 1
  char str1[] = "Proti Voini";
  ck_assert_int_eq(s21_strlen(str1), strlen(str1));

  // 2
  char str2[10] = "";
  ck_assert_int_eq(s21_strlen(str2), strlen(str2));
}
END_TEST

// 12
START_TEST(s21_strpbrkTest) {
  // 1
  char str1_1[] = "Yt ghsko hgdu bdu";
  char str2_1[] = "md";
  ck_assert_ptr_eq(strpbrk(str1_1, str2_1), s21_strpbrk(str1_1, str2_1));

  // 2
  char str1_2[] = "Yt ghsko hgdu bdu";
  char str2_2[] = "p";
  ck_assert_ptr_eq(strpbrk(str1_2, str2_2), s21_strpbrk(str1_2, str2_2));

  // 3
  char str1_3[] = "Yt ghsko hgdu bdu";
  char str2_3[] = "PTYO";
  ck_assert_ptr_eq(strpbrk(str1_3, str2_3), s21_strpbrk(str1_3, str2_3));
}
END_TEST

// 13
START_TEST(s21_strrchrTest) {
  // 1
  char str1_1[] = "Pops-up-hars-d-xsew-mxkfor";
  int s1 = '-';
  ck_assert_ptr_eq(s21_strrchr(str1_1, s1), strrchr(str1_1, s1));

  // 2
  char str1_2[] = "Pops-up-hars-d-xsew-mxkfor";
  int s2 = '\0';
  ck_assert_ptr_eq(s21_strrchr(str1_2, s2), strrchr(str1_2, s2));

  // 3
  char str1_3[] = "Pops-up-hars-d-xsew-mxkfor";
  int s3 = 'b';
  ck_assert_ptr_eq(s21_strrchr(str1_3, s3), strrchr(str1_3, s3));
}
END_TEST

// 14
START_TEST(s21_strstrTest) {
  // 1
  char str1_1[] = "0123456789";
  char str2_1[] = "234";
  ck_assert_ptr_eq(strstr(str1_1, str2_1), s21_strstr(str1_1, str2_1));

  // 2
  char str1_2[] = "Kolla idiii, I cuda idiii!";
  char str2_2[] = "idiii";
  ck_assert_ptr_eq(strstr(str1_2, str2_2), s21_strstr(str1_2, str2_2));

  // 3
  char str1_3[10] = "";
  char str2_3[] = "idiii";
  ck_assert_ptr_eq(strstr(str1_3, str2_3), s21_strstr(str1_3, str2_3));

  // 4
  char str1_4[] = "Kolla idiii, I cuda idiii!";
  char str2_4[10] = "";
  ck_assert_ptr_eq(strstr(str1_4, str2_4), s21_strstr(str1_4, str2_4));
}
END_TEST

// 15
START_TEST(s21_strtokTest) {
  // 1
  char str1_1[] = "Yu kjswl hjas ldf";
  char str2_1[] = "d";
  char *rt1;
  char s21_str1_1[] = "Yu kjswl hjas ldf";
  char s21_str2_1[] = "d";
  char *rt2;

  rt1 = strtok(str1_1, str2_1);
  rt2 = s21_strtok(s21_str1_1, s21_str2_1);
  while (rt1 != NULL && rt2 != NULL) {
    ck_assert_str_eq(rt1, rt2);
    rt1 = strtok(NULL, str2_1);
    rt2 = s21_strtok(NULL, s21_str2_1);
  }

  // 2
  char str1_2[] = "Yu kjswl hjas ldf";
  char str2_2[] = "TREW";
  char s21_str1_2[] = "Yu kjswl hjas ldf";
  char s21_str2_2[] = "TREW";

  rt1 = strtok(str1_2, str2_2);
  rt2 = s21_strtok(s21_str1_2, s21_str2_2);
  ck_assert_str_eq(rt1, rt2);

  // 3
  char str1_3[] = "Yu kjswl hjas ldf";
  char str2_3[] = "Jt";
  char s21_str1_3[] = "Yu kjswl hjas ldf";
  char s21_str2_3[] = "Jt";

  rt1 = strtok(str1_3, str2_3);
  rt2 = s21_strtok(s21_str1_3, s21_str2_3);
  while (rt1 != NULL && rt2 != NULL) {
    ck_assert_str_eq(rt1, rt2);
    rt1 = strtok(NULL, str2_3);
    rt2 = s21_strtok(NULL, s21_str2_3);
  }
}
END_TEST

// 16
START_TEST(s21_to_upperTest) {
  char str1[] = "qwe";
  char *d1 = s21_to_upper(str1);
  ck_assert_pstr_eq(d1, "QWE");
  free(d1);

  char str2[] = "aFsd";
  char *d2 = s21_to_upper(str2);
  ck_assert_pstr_eq(d2, "AFSD");
  free(d2);

  char *str3 = s21_NULL;
  ck_assert_pstr_eq(s21_to_upper(str3), s21_NULL);
}
END_TEST

// 17
START_TEST(s21_to_lowerTest) {
  char str1[] = "QWE";
  char *d1 = s21_to_lower(str1);
  ck_assert_pstr_eq(d1, "qwe");
  free(d1);

  char str2[] = "AfSD";
  char *d2 = s21_to_lower(str2);
  ck_assert_pstr_eq(d2, "afsd");
  free(d2);

  char *str3 = s21_NULL;
  ck_assert_pstr_eq(s21_to_lower(str3), s21_NULL);
}

// 18
START_TEST(s21_insertTest) {
  char text[64] = "Hello ! ";
  char *d1 = s21_insert(text, "Woreeld", 6);
  ck_assert_str_eq(d1, "Hello Woreeld! ");
  free(d1);

  char *str3 = s21_NULL;
  ck_assert_pstr_eq(s21_insert(str3, "Woreeld", 6), s21_NULL);
}
END_TEST

// 19
START_TEST(s21_trimTest) {
  char str[] = "";
  char trim_ch[] = "";
  char expected[] = "";
  char *got = s21_trim(str, trim_ch);
  ck_assert_str_eq(got, expected);
  if (got) free(got);

  char str1[] = "+!0-aeoi2o3i23iuhuhh3O*YADyagsduyoaweq213";
  char trim_ch1[] = "+!0-aeoi2o3i23iuhuhh3O*YADyagsduyoaweq213";
  char expected1[] = "";
  char *got1 = s21_trim(str1, trim_ch1);
  ck_assert_str_eq(got1, expected1);
  if (got1) free(got1);

  char str2[] = "+!!++Abo+ba++00";
  char trim_ch2[] = "+!0-";
  char expected2[] = "Abo+ba";
  char *got2 = (char *)s21_trim(str2, trim_ch2);
  ck_assert_str_eq(got2, expected2);
  if (got2) free(got2);
}
END_TEST

// 20
START_TEST(s21_strcatTest) {
  // 1
  char str1_1[11] = "Jolb";
  char str2_1[] = " nike";
  char s21_str1_1[11] = "Jolb";
  char s21_str2_1[] = " nike";
  ck_assert_str_eq(strcat(str1_1, str2_1), s21_strcat(s21_str1_1, s21_str2_1));

  // 2
  char str1_2[11] = "Jolb";
  char str2_2[] = "";
  char s21_str1_2[11] = "Jolb";
  char s21_str2_2[] = "";
  ck_assert_str_eq(strcat(str1_2, str2_2), s21_strcat(s21_str1_2, s21_str2_2));

  // 3
  char str1_3[11] = "";
  char str2_3[] = " nike";
  char s21_str1_3[11] = "";
  char s21_str2_3[] = " nike";
  ck_assert_str_eq(strcat(str1_3, str2_3), s21_strcat(s21_str1_3, s21_str2_3));
}
END_TEST

// 21
START_TEST(s21_strcpyTest) {
  // 1
  char str1_1[] = "tir fool";
  char str2_1[] = "wou popo";
  char s21_str1_1[] = "tir fool";
  char s21_str2_1[] = "wou popo";
  strcpy(str2_1, str1_1);
  s21_strcpy(s21_str2_1, s21_str1_1);
  ck_assert_str_eq(str2_1, s21_str2_1);

  // 2
  char str1[] = "tir fool";
  char str2[] = "wou popopopopopo";
  char s21_str1[] = "tir fool";
  char s21_str2[] = "wou popopopopopo";
  strcpy(str2, str1);
  s21_strcpy(s21_str2, s21_str1);
  ck_assert_str_eq(str2, s21_str2);

  // 3
  char str1_3[] = "";
  char str2_3[] = "wou popo";
  char s21_str1_3[] = "";
  char s21_str2_3[] = "wou popo";
  strcpy(str2_3, str1_3);
  s21_strcpy(s21_str2_3, s21_str1_3);
  ck_assert_str_eq(str2_3, s21_str2_3);
}
END_TEST

START_TEST(s21_sprintfTest) {
  char str1[100];
  char str2[100];
  char *str3 = "%6.4c Test %-6.4c Test %4.10lc Test %-4.10lc Test %-0lc";
  int a = 10;
  unsigned long int b = 10;
  unsigned long int c = 10;
  ck_assert_int_eq(sprintf(str1, str3, a, a, b, c, c),
                   s21_sprintf(str2, str3, a, a, b, c, c));
  ck_assert_pstr_eq(str1, str2);

  char *str399 = "Test %ls Test2";
  wchar_t *val99 = L"3wtf80";
  sprintf(str1, str399, val99);
  s21_sprintf(str2, str399, val99);
  ck_assert_int_eq(sprintf(str1, str399, val99),
                   s21_sprintf(str2, str399, val99));
  ck_assert_pstr_eq(str1, str2);

  char str11[BUFF_SIZE];
  char str21[BUFF_SIZE];
  char *format1 = "This is a simple value %d";
  int val1 = 69;
  ck_assert_int_eq(s21_sprintf(str11, format1, val1),
                   sprintf(str21, format1, val1));
  ck_assert_str_eq(str11, str21);

  char str12[BUFF_SIZE];
  char str22[BUFF_SIZE];
  char *format2 = "%.5i";
  int val2 = 69;
  ck_assert_int_eq(s21_sprintf(str12, format2, val2),
                   sprintf(str22, format2, val2));
  ck_assert_str_eq(str12, str22);

  char str13[BUFF_SIZE];
  char str23[BUFF_SIZE];
  char *format3 = "%5d";
  int val3 = 69;
  ck_assert_int_eq(s21_sprintf(str13, format3, val3),
                   sprintf(str23, format3, val3));
  ck_assert_str_eq(str13, str23);

  char str14[BUFF_SIZE];
  char str24[BUFF_SIZE];
  char *format4 = "%-5i";
  int val4 = 69;
  ck_assert_int_eq(s21_sprintf(str14, format4, val4),
                   sprintf(str24, format4, val4));
  ck_assert_str_eq(str14, str24);

  char str15[BUFF_SIZE];
  char str25[BUFF_SIZE];
  char *format5 = "%+12d";
  int val5 = 69;
  ck_assert_int_eq(s21_sprintf(str15, format5, val5),
                   sprintf(str25, format5, val5));
  ck_assert_str_eq(str15, str25);

  char str16[BUFF_SIZE];
  char str26[BUFF_SIZE];

  char *format6 = "%012i";
  int val6 = 69;
  ck_assert_int_eq(s21_sprintf(str16, format6, val6),
                   sprintf(str26, format6, val6));

  ck_assert_str_eq(str16, str26);

  char str17[BUFF_SIZE];
  char str27[BUFF_SIZE];
  char *format7 = "%+5.31li";
  long int val7 = 698518581899;
  ck_assert_int_eq(s21_sprintf(str17, format7, val7),
                   sprintf(str27, format7, val7));
  ck_assert_str_eq(str17, str27);

  char str18[BUFF_SIZE];
  char str28[BUFF_SIZE];
  char *format8 = "%-16.9hi";
  short int val8 = 6958;
  ck_assert_int_eq(s21_sprintf(str18, format8, val8),
                   sprintf(str28, format8, val8));
  ck_assert_str_eq(str18, str28);

  char str19[BUFF_SIZE];
  char str29[BUFF_SIZE];
  char *format9 = "%.0d";
  int val9 = 0;
  ck_assert_int_eq(s21_sprintf(str19, format9, val9),
                   sprintf(str29, format9, val9));
  ck_assert_str_eq(str19, str29);

  char str10[BUFF_SIZE];
  char str20[BUFF_SIZE];
  char *format0 = "% d";
  int val0 = 0;
  ck_assert_int_eq(s21_sprintf(str10, format0, val0),
                   sprintf(str20, format0, val0));
  ck_assert_str_eq(str10, str20);

  char str111[BUFF_SIZE];
  char str211[BUFF_SIZE];
  char *format11 = "%u";
  unsigned int val11 = 14140;
  ck_assert_int_eq(s21_sprintf(str111, format11, val11),
                   sprintf(str211, format11, val11));
  ck_assert_str_eq(str111, str211);

  char str112[BUFF_SIZE];
  char str212[BUFF_SIZE];
  char *format12 = "%-16u";
  unsigned int val12 = 14140;
  ck_assert_int_eq(s21_sprintf(str112, format12, val12),
                   sprintf(str212, format12, val12));
  ck_assert_str_eq(str112, str212);

  char str113[BUFF_SIZE];
  char str213[BUFF_SIZE];
  char *format13 = "%hu";
  unsigned short val13 = 14140;
  ck_assert_int_eq(s21_sprintf(str113, format13, val13),
                   sprintf(str213, format13, val13));
  ck_assert_str_eq(str113, str213);

  char str114[BUFF_SIZE];
  char str214[BUFF_SIZE];
  char *format14 = "%lu, %u, %hu, %.5u, %5.u";
  unsigned long int val14 = 949149114140;
  ck_assert_int_eq(
      s21_sprintf(str114, format14, val14, 14, 1441, 14414, 9681),
      sprintf(str214, format14, val14, (unsigned)14, (unsigned short)1441,
              (unsigned)14414, (unsigned)9681));
  ck_assert_str_eq(str114, str214);

  char str115[BUFF_SIZE];
  char str215[BUFF_SIZE];
  char *format15 = "%c";
  char val15 = 'X';
  ck_assert_int_eq(s21_sprintf(str115, format15, val15),
                   sprintf(str215, format15, val15));
  ck_assert_str_eq(str115, str215);

  char str116[BUFF_SIZE];
  char str216[BUFF_SIZE];
  char *format16 = "% -5c";
  char val16 = 'c';
  ck_assert_int_eq(s21_sprintf(str116, format16, val16),
                   sprintf(str216, format16, val16));
  ck_assert_str_eq(str116, str216);

  char str117[BUFF_SIZE];
  char str217[BUFF_SIZE];
  char *format17 = "%15c";
  char val17 = 'c';
  ck_assert_int_eq(s21_sprintf(str117, format17, val17),
                   sprintf(str217, format17, val17));
  ck_assert_str_eq(str117, str217);

  char str118[BUFF_SIZE];
  char str218[BUFF_SIZE];
  char *format18 = "%s";
  char *val18 = "Hello world!";
  ck_assert_int_eq(s21_sprintf(str118, format18, val18),
                   sprintf(str218, format18, val18));
  ck_assert_str_eq(str118, str218);

  char str119[BUFF_SIZE];
  char str219[BUFF_SIZE];
  char *format19 = "%.15s";
  char *val19 = "Hello world!";
  ck_assert_int_eq(s21_sprintf(str119, format19, val19),
                   sprintf(str219, format19, val19));
  ck_assert_str_eq(str119, str219);

  char str120[BUFF_SIZE];
  char str220[BUFF_SIZE];
  char *format20 = "%-15.9s";
  char *val20 = "Hello World!";
  ck_assert_int_eq(s21_sprintf(str120, format20, val20),
                   sprintf(str220, format20, val20));
  ck_assert_str_eq(str120, str220);

  char str121[BUFF_SIZE];
  char str221[BUFF_SIZE];
  char *format21 = "%s%s%s%s";
  char *val21 =
      "Lorem Ipsum is simply dummy text of the printing and typesetting "
      "industry.";
  char *s121 = "";
  char *s221 = "87418347813748913749871389480913";
  char *s321 = "Lorem Ipsum";
  ck_assert_int_eq(s21_sprintf(str121, format21, val21, s121, s221, s321),
                   sprintf(str221, format21, val21, s121, s221, s321));
  ck_assert_str_eq(str121, str221);

  char str122[BUFF_SIZE];
  char str222[BUFF_SIZE];
  char *val22 = "kjafdiuhfjahfjdahf";
  char *format22 = "%120s";
  ck_assert_int_eq(s21_sprintf(str122, format22, val22),
                   sprintf(str222, format22, val22));
  ck_assert_str_eq(str122, str222);

  char str123[BUFF_SIZE];
  char str223[BUFF_SIZE];
  char *format23 = "%Lf";
  long double val23 = 513515.131513515151351;
  ck_assert_int_eq(s21_sprintf(str123, format23, val23),
                   sprintf(str223, format23, val23));
  ck_assert_str_eq(str123, str223);

  char str124[BUFF_SIZE];
  char str224[BUFF_SIZE];
  char *format24 = "%.0Lf";
  long double val24 = 15.35;
  ck_assert_int_eq(s21_sprintf(str124, format24, val24),
                   sprintf(str224, format24, val24));
  ck_assert_str_eq(str124, str224);

  char str125[BUFF_SIZE];
  char str225[BUFF_SIZE];
  char *format25 = "%.Lf";
  long double val25 = 15.35;
  ck_assert_int_eq(s21_sprintf(str125, format25, val25),
                   sprintf(str225, format25, val25));
  ck_assert_str_eq(str125, str225);

  char str126[BUFF_SIZE];
  char str226[BUFF_SIZE];
  char *format26 = "%.15Lf";
  long double val26 = -15.35581134;
  ck_assert_int_eq(s21_sprintf(str126, format26, val26),
                   sprintf(str226, format26, val26));
  ck_assert_str_eq(str126, str226);

  char str127[BUFF_SIZE];
  char str227[BUFF_SIZE];
  char *format27 = "% f";
  float val27 = 0;
  ck_assert_int_eq(s21_sprintf(str127, format27, val27),
                   sprintf(str227, format27, val27));
  ck_assert_str_eq(str127, str227);

  char str128[BUFF_SIZE];
  char str228[BUFF_SIZE];
  char *format28 = "% .0f %.lf %Lf %f %lf %Lf";
  float val28 = 0;
  double val128 = 0;
  long double val228 = 3515315.153151;
  float val328 = 5.5;
  double val428 = 9851.51351;
  long double val528 = 95919539159.53151351131;
  ck_assert_int_eq(
      s21_sprintf(str128, format28, val28, val128, val228, val328, val428,
                  val528),
      sprintf(str228, format28, val28, val128, val228, val328, val428, val528));
  ck_assert_str_eq(str128, str228);

  char str129[BUFF_SIZE];
  char str229[BUFF_SIZE];
  ck_assert_int_eq(s21_sprintf(str129, "abc"), sprintf(str229, "abc"));
  ck_assert_str_eq(str129, str229);

  char str130[BUFF_SIZE];
  char str230[BUFF_SIZE];
  ck_assert_int_eq(s21_sprintf(str130, "%d", 666), sprintf(str230, "%d", 666));
  ck_assert_str_eq(str130, str230);

  char str131[BUFF_SIZE];
  char str231[BUFF_SIZE];
  ck_assert_int_eq(s21_sprintf(str131, "%d%d%d%d", -999, 0, 666, -100),
                   sprintf(str231, "%d%d%d%d", -999, 0, 666, -100));
  ck_assert_str_eq(str131, str231);

  char str132[BUFF_SIZE];
  char str232[BUFF_SIZE];
  ck_assert_int_eq(s21_sprintf(str132, "%i", -0), sprintf(str232, "%i", -0));
  ck_assert_str_eq(str132, str232);

  char str133[BUFF_SIZE];
  char str233[BUFF_SIZE];
  ck_assert_int_eq(s21_sprintf(str133, "%f", 0.0001),
                   sprintf(str233, "%f", 0.0001));
  ck_assert_str_eq(str133, str233);

  char str134[BUFF_SIZE];
  char str234[BUFF_SIZE];
  ck_assert_int_eq(
      s21_sprintf(str134, "%f%f%f%f", -999.666, 0.0001, 666.999, -100.001),
      sprintf(str234, "%f%f%f%f", -999.666, 0.0001, 666.999, -100.001));
  ck_assert_str_eq(str134, str234);

  char str135[BUFF_SIZE];
  char str235[BUFF_SIZE];
  ck_assert_int_eq(s21_sprintf(str135, "%u", 100),
                   sprintf(str235, "%u", (unsigned)100));
  ck_assert_str_eq(str135, str235);

  char str136[BUFF_SIZE];
  char str236[BUFF_SIZE];
  ck_assert_int_eq(s21_sprintf(str136, "%-8c", '\t'),
                   sprintf(str236, "%-8c", '\t'));
  ck_assert_str_eq(str136, str236);

  char str137[BUFF_SIZE];
  char str237[BUFF_SIZE];
  ck_assert_int_eq(
      s21_sprintf(str137, "%3c%-11c%10c%-2c%c", '\t', '\n', '0', 'S', 's'),
      sprintf(str237, "%3c%-11c%10c%-2c%c", '\t', '\n', '0', 'S', 's'));
  ck_assert_str_eq(str137, str237);

  char str138[BUFF_SIZE];
  char str238[BUFF_SIZE];
  char format38[] = "%10ld";
  ck_assert_int_eq(s21_sprintf(str138, format38, 1),
                   sprintf(str238, format38, 1));
  ck_assert_str_eq(str138, str238);

  char str139[BUFF_SIZE];
  char str239[BUFF_SIZE];
  char *val39 = "kjafdiuhfjahfjdahf";
  char *format39 = "%120s";
  ck_assert_int_eq(s21_sprintf(str139, format39, val39),
                   sprintf(str239, format39, val39));
  ck_assert_str_eq(str139, str239);

  char str140[BUFF_SIZE];
  char str240[BUFF_SIZE];
  char format40[] = "%li%ld%lu";
  ck_assert_int_eq(s21_sprintf(str140, format40, 666666666666, 777, 111),
                   sprintf(str240, format40, 666666666666, 777, 111));
  ck_assert_str_eq(str140, str240);

  char str141[BUFF_SIZE];
  char str241[BUFF_SIZE];
  char format41[] = "%+li%+lu%+d%+lf";
  ck_assert_int_eq(s21_sprintf(str141, format41, -123, 321, -5555, -1213.123),
                   sprintf(str241, format41, -123, 321, -5555, -1213.123));
  ck_assert_str_eq(str141, str241);

  char str142[BUFF_SIZE];
  char str242[BUFF_SIZE];
  char format42[] = "%-11.11li%-35.5lu%-3.5ld%33.6Lf";
  long double k42 = 333.33213;
  ck_assert_int_eq(
      s21_sprintf(str142, format42, 66666666666, 5555555555, 44444444444, k42),
      sprintf(str242, format42, 66666666666, 5555555555, 44444444444, k42));
  ck_assert_str_eq(str142, str242);

  char str143[BUFF_SIZE];
  char str243[BUFF_SIZE];
  char format43[] = "%+li %+10d %+09i %10.7d";
  ck_assert_int_eq(s21_sprintf(str143, format43, -123, 321, -5555, -1213),
                   sprintf(str243, format43, -123, 321, -5555, -1213));
  ck_assert_str_eq(str143, str243);

  char str144[BUFF_SIZE];
  char str244[BUFF_SIZE];
  char format44[] = "%-15f %0020.8f %3.3f %10f %+.10f %.3f";
  ck_assert_int_eq(s21_sprintf(str144, format44, -123.452, 321.34653, -5555.22,
                               -1213.0, 0, -0.2),
                   sprintf(str244, format44, -123.452, 321.34653, -5555.22,
                           -1213.0, 0, -0.2));
  ck_assert_str_eq(str144, str244);

  char str145[BUFF_SIZE];
  char str245[BUFF_SIZE];
  char format45[] = "% 0.0li% 0.0lu% 0.0ld % 0.0lf";
  ck_assert_int_eq(
      s21_sprintf(str145, format45, 1, 222, 33333333333, -166513.1232),
      sprintf(str245, format45, 1, 222, 33333333333, -166513.1232));
  ck_assert_str_eq(str145, str245);
}
END_TEST

/*----------%c----------*/
START_TEST(test_s21_sscanf) {
  char str[100] = "bcd";
  char c1;
  char d1;
  char e1;
  char c2;
  char d2;
  char e2;
  /*раскоментить ассерт после починки*/
  ck_assert_int_eq(sscanf(str, "%c%c%c", &c1, &d1, &e1),
                   s21_sscanf(str, "%c%c%c", &c2, &d2, &e2));
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(e1, e2);
}
END_TEST

START_TEST(test_s21_sscanf_2) {
  char str[100] = "b cd";
  char c1;
  char d1;
  char e1;
  char c2;
  char d2;
  char e2;
  ck_assert_int_eq(sscanf(str, "%c%c%c", &c1, &d1, &e1),
                   s21_sscanf(str, "%c%c%c", &c2, &d2, &e2));
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(e1, e2);
}
END_TEST

START_TEST(test_s21_sscanf_3) {
  char str[100] = "bc d";
  char c1;
  char d1;
  char e1;
  char c2;
  char d2;
  char e2;
  ck_assert_int_eq(sscanf(str, "%c%c%c", &c1, &d1, &e1),
                   s21_sscanf(str, "%c%c%c", &c2, &d2, &e2));
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(e1, e2);
}
END_TEST

START_TEST(test_s21_sscanf_4) {
  char str[100] = "bcd";
  char c1;
  char d1;
  char e1;
  char c2;
  char d2;
  char e2;
  ck_assert_int_eq(sscanf(str, "%c%c%c", &c1, &d1, &e1),
                   s21_sscanf(str, "%c%c%c", &c2, &d2, &e2));
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(e1, e2);
}
END_TEST

START_TEST(test_s21_sscanf_5) {
  char str[100] = "b 1d";
  char c1;
  char d1;
  char e1;
  char c2;
  char d2;
  char e2;
  ck_assert_int_eq(sscanf(str, "%c%c%c", &c1, &d1, &e1),
                   s21_sscanf(str, "%c%c%c", &c2, &d2, &e2));
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(e1, e2);
}
END_TEST

START_TEST(test_s21_sscanf_6) {
  char str[100] = "bc ";
  char c1;
  char d1;
  char e1;
  char c2;
  char d2;
  char e2;
  ck_assert_int_eq(sscanf(str, "%c%c%c", &c1, &d1, &e1),
                   s21_sscanf(str, "%c%c%c", &c2, &d2, &e2));
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(e1, e2);
}
END_TEST

START_TEST(test_s21_sscanf_7) {
  char str[100] = " cd";
  char c1;
  char d1;
  char e1;
  char c2;
  char d2;
  char e2;
  ck_assert_int_eq(sscanf(str, "%c%c%c", &c1, &d1, &e1),
                   s21_sscanf(str, "%c%c%c", &c2, &d2, &e2));
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(e1, e2);
}
END_TEST

START_TEST(test_s21_sscanf_8) {
  char str[100] = "1cd";
  char c1;
  char d1;
  char e1;
  char c2;
  char d2;
  char e2;
  ck_assert_int_eq(sscanf(str, "%c%c%c", &c1, &d1, &e1),
                   s21_sscanf(str, "%c%c%c", &c2, &d2, &e2));
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(e1, e2);
}
END_TEST

START_TEST(test_s21_sscanf_9) {
  char str[100] = "bc1";
  char c1;
  char d1;
  char e1;
  char c2;
  char d2;
  char e2;
  ck_assert_int_eq(sscanf(str, "%c%c%c", &c1, &d1, &e1),
                   s21_sscanf(str, "%c%c%c", &c2, &d2, &e2));
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(e1, e2);
}
END_TEST

START_TEST(test_s21_sscanf_10) {
  char str[100] = "b1d";
  char c1;
  char d1;
  char e1;
  char c2;
  char d2;
  char e2;
  ck_assert_int_eq(sscanf(str, "%c%c%c", &c1, &d1, &e1),
                   s21_sscanf(str, "%c%c%c", &c2, &d2, &e2));
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(e1, e2);
}
END_TEST

START_TEST(test_s21_sscanf_11) {
  char str[100] = "b c d";
  char c1;
  char d1;
  char e1;
  char c2;
  char d2;
  char e2;
  ck_assert_int_eq(sscanf(str, "%c%c%c", &c1, &d1, &e1),
                   s21_sscanf(str, "%c%c%c", &c2, &d2, &e2));
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(e1, e2);
}
END_TEST

START_TEST(test_s21_sscanf_12) {
  char str[100] = "^123";
  char c1;
  char d1;
  char e1;
  char c2;
  char d2;
  char e2;
  ck_assert_int_eq(sscanf(str, "%c%c%c", &c1, &d1, &e1),
                   s21_sscanf(str, "%c%c%c", &c2, &d2, &e2));
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(e1, e2);
}
END_TEST

START_TEST(test_s21_sscanf_13) {
  char str[100] = "○ ! ╕ ";
  char c1;
  char d1;
  char e1;
  char c2;
  char d2;
  char e2;
  ck_assert_int_eq(sscanf(str, "%c%c%c", &c1, &d1, &e1),
                   s21_sscanf(str, "%c%c%c", &c2, &d2, &e2));
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(e1, e2);
}
END_TEST

START_TEST(test_s21_sscanf_14) {
  char str[100] = "чx╝";
  char c1;
  char d1;
  char e1;
  char c2;
  char d2;
  char e2;
  ck_assert_int_eq(sscanf(str, "%c%c%c", &c1, &d1, &e1),
                   s21_sscanf(str, "%c%c%c", &c2, &d2, &e2));
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(e1, e2);
}
END_TEST

START_TEST(test_s21_sscanf_15) {
  char str[100] = "kЪ♥";
  char c1;
  char d1;
  char e1;
  char c2;
  char d2;
  char e2;
  ck_assert_int_eq(sscanf(str, "%c%c%c", &c1, &d1, &e1),
                   s21_sscanf(str, "%c%c%c", &c2, &d2, &e2));
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(e1, e2);
}
END_TEST

/*----------%d----------*/
START_TEST(test_s21_sscanf_16) {
  char one_[] = "324354541";
  // int two = 2147483647;
  // int three = -2147483648;
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%d%d%d", &a1, &b1, &c1),
                   s21_sscanf(one_, "%d%d%d", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_17) {
  char one_[] = "2147483648, -2147483648, 3.55";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%d%d%d", &a1, &b1, &c1),
                   s21_sscanf(one_, "%d%d%d", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_18) {
  char one_[] = "0, --0, 0.0";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%d%d%d", &a1, &b1, &c1),
                   s21_sscanf(one_, "%d%d%d", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_19) {
  char one_[] = "0 -0 0.0";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%d%d%d", &a1, &b1, &c1),
                   s21_sscanf(one_, "%d%d%d", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}

START_TEST(test_s21_sscanf_20) {
  char one_[] = "1 2 3";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%d%d%d", &a1, &b1, &c1),
                   s21_sscanf(one_, "%d%d%d", &a2, &b2, &c2));
  /*валится из-за пробела возможно, если в s21_sscanf сделать %d %d %d
  то всё норм, тест проходит*/
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_21) {
  char one_[] = "321651.32131 00000.123 -99999999";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%d%d%d", &a1, &b1, &c1),
                   s21_sscanf(one_, "%d%d%d", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_22) {
  char one_[] = "321321 asdasd 3215";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%d%d%d", &a1, &b1, &c1),
                   s21_sscanf(one_, "%d%d%d", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_23) {
  char one_[] = "-lksda2222 +asd222 0/0";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%d%d%d", &a1, &b1, &c1),
                   s21_sscanf(one_, "%d%d%d", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_24) {
  char one_[] = "";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%d%d%d", &a1, &b1, &c1),
                   s21_sscanf(one_, "%d%d%d", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_25) {
  char one_[] = "                       ";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%d%d%d", &a1, &b1, &c1),
                   s21_sscanf(one_, "%d%d%d", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_26) {
  char one_[] = "\0 \0 \0";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%d%d%d", &a1, &b1, &c1),
                   s21_sscanf(one_, "%d%d%d", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_27) {
  char one_[] = "21474836479 21474836479 -92147483647";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%d%d%d", &a1, &b1, &c1),
                   s21_sscanf(one_, "%d%d%d", &a2, &b2, &c2));
  /*результат стандартного sscanf a1=-1 b1=-1 c1=-1953170431 */
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_28) {
  char one_[] = "EOF \n 1";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%d%d%d", &a1, &b1, &c1),
                   s21_sscanf(one_, "%d%d%d", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_29) {
  char one_[] = "123456";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%5d%d%d", &a1, &b1, &c1),
                   s21_sscanf(one_, "%5d%d%d", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_30) {
  char one_[] = "1ф2а3й4ы5ч6я";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%5d%2d6%d", &a1, &b1, &c1),
                   s21_sscanf(one_, "%5d%2d%6d", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_31) {
  char one_[] = ". . .";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%5d%2d6%d", &a1, &b1, &c1),
                   s21_sscanf(one_, "%5d%2d%6d", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_32) {
  char one_[] = "123.456 -4556.55555 -456asd";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%5d%2d%6d", &a1, &b1, &c1),
                   s21_sscanf(one_, "%5d%2d%6d", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_33) {
  char one_[] = "123456.654321 -123456.654321 0as124++6517Ed";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%52d%2d6%d", &a1, &b1, &c1),
                   s21_sscanf(one_, "%52d%2d%6d", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

/*-----------%ld------------*/
START_TEST(test_s21_sscanf_34) {
  char one_[999999] = "922337203 -922337203 92233720";
  long int a1 = 0;
  long int b1 = 0;
  long int c1 = 0;
  long int a2 = 0;
  long int b2 = 0;
  long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%ld%ld%ld", &a1, &b1, &c1),
                   s21_sscanf(one_, "%ld%ld%ld", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_35) {
  char one_[] = "9223372036854775807 -9223372036854775808 92233720368547758071";
  long int a1 = 0;
  long int b1 = 0;
  long int c1 = 0;
  long int a2 = 0;
  long int b2 = 0;
  long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%2ld%3ld%4ld", &a1, &b1, &c1),
                   s21_sscanf(one_, "%2ld%3ld%4ld", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_36) {
  char one_[9999] = "922337203 -9223375808 92233728071";
  long int a1 = 0;
  long int b1 = 0;
  long int c1 = 0;
  long int a2 = 0;
  long int b2 = 0;
  long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%22ld%33ld%44ld", &a1, &b1, &c1),
                   s21_sscanf(one_, "%22ld%33ld%44ld", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_37) {
  char one_[9999] = "9223372 -922337203 92233720368";
  long int a1 = 0;
  long int b1 = 0;
  long int c1 = 0;
  long int a2 = 0;
  long int b2 = 0;
  long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%55ld%33ld%444ld", &a1, &b1, &c1),
                   s21_sscanf(one_, "%55ld%33ld%444ld", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_38) {
  char one_[] = "1 2 3";
  long int a1 = 0;
  long int b1 = 0;
  long int c1 = 0;
  long int a2 = 0;
  long int b2 = 0;
  long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%5ld%3ld%ld", &a1, &b1, &c1),
                   s21_sscanf(one_, "%5ld%3ld%ld", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_39) {
  char one_[] = "-и123 +asd321 /@п99999999999999999999999";
  long int a1 = 0;
  long int b1 = 0;
  long int c1 = 0;
  long int a2 = 0;
  long int b2 = 0;
  long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%5ld%3ld%444ld", &a1, &b1, &c1),
                   s21_sscanf(one_, "%5ld%3ld%444ld", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_40) {
  char one_[99999] =
      "92233727.922337203071 "
      "-92234775808.92233808 "
      "92233771.92233851";
  long int a1 = 0;
  long int b1 = 0;
  long int c1 = 0;
  long int a2 = 0;
  long int b2 = 0;
  long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%55ld%33ld%444ld", &a1, &b1, &c1),
                   s21_sscanf(one_, "%55ld%33ld%444ld", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_41) {
  char one_[99999] =
      "922307.9258071 "
      "-922375808.922375808 "
      "9223378071.92233771";
  long int a1 = 0;
  long int b1 = 0;
  long int c1 = 0;
  long int a2 = 0;
  long int b2 = 0;
  long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%ld%ld%ld", &a1, &b1, &c1),
                   s21_sscanf(one_, "%ld%ld%ld", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_42) {
  char one_[] = "aaaa3aaaa bbbb6bbbbbb ccccccc2cccccc";
  long int a1 = 0;
  long int b1 = 0;
  long int c1 = 0;
  long int a2 = 0;
  long int b2 = 0;
  long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%ld%ld%ld", &a1, &b1, &c1),
                   s21_sscanf(one_, "%ld%ld%ld", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_43) {
  char one_[] =
      "9223372036854775807 -9223372036854775808 "
      "92233720368547758071";
  long int a1 = 0;
  long int b1 = 0;
  long int c1 = 0;
  long int a2 = 0;
  long int b2 = 0;
  long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%55ld%33ld%444ld", &a1, &b1, &c1),
                   s21_sscanf(one_, "%55ld%33ld%444ld", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

/*-----------%lld------------*/
START_TEST(test_s21_sscanf_44) {
  char one_[] = "1 2 3";
  long long int a1 = 0;
  long long int b1 = 0;
  long long int c1 = 0;
  long long int a2 = 0;
  long long int b2 = 0;
  long long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%lld%lld%lld", &a1, &b1, &c1),
                   s21_sscanf(one_, "%lld%lld%lld", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_45) {
  char one_[] = "92207 -922337208 1.1111111";
  long long int a1 = 0;
  long long int b1 = 0;
  long long int c1 = 0;
  long long int a2 = 0;
  long long int b2 = 0;
  long long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%lld%lld%lld", &a1, &b1, &c1),
                   s21_sscanf(one_, "%lld%lld%lld", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_46) {
  char one_[] = "9223372036854775807 -9223372036854775808 1.11111111111";
  long long int a1 = 0;
  long long int b1 = 0;
  long long int c1 = 0;
  long long int a2 = 0;
  long long int b2 = 0;
  long long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%2lld%3lld%4lld", &a1, &b1, &c1),
                   s21_sscanf(one_, "%2lld%3lld%4lld", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_47) {
  char one_[9999] =
      "92233744 -92233833 "
      "1111111111.111";
  long long int a1 = 0;
  long long int b1 = 0;
  long long int c1 = 0;
  long long int a2 = 0;
  long long int b2 = 0;
  long long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%22lld%33lld%44lld", &a1, &b1, &c1),
                   s21_sscanf(one_, "%22lld%33lld%44lld", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_48) {
  char one_[] =
      "9223377580744 -9227580833 "
      "bbbbbaaaS]>╛";
  long long int a1 = 0;
  long long int b1 = 0;
  long long int c1 = 0;
  long long int a2 = 0;
  long long int b2 = 0;
  long long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%2222lld%33lld%44lld", &a1, &b1, &c1),
                   s21_sscanf(one_, "%2222lld%33lld%44lld", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_49) {
  char one_[] = "-и123 +asd321 /@п99999999999999999999999.0000000000001";
  long long int a1 = 0;
  long long int b1 = 0;
  long long int c1 = 0;
  long long int a2 = 0;
  long long int b2 = 0;
  long long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%lld%lld%lld", &a1, &b1, &c1),
                   s21_sscanf(one_, "%lld%lld%lld", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_50) {
  char one_[] = "0.9223372036854775807 0.-9223372036854775808";
  long long int a1 = 0;
  long long int b1 = 0;
  long long int c1 = 0;
  long long int a2 = 0;
  long long int b2 = 0;
  long long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%lld%lld%lld", &a1, &b1, &c1),
                   s21_sscanf(one_, "%lld%lld%lld", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_51) {
  char one_[] =
      "92233775807."
      "922337658071 "
      "-922336807154775808."
      "922339254775808 "
      "92233720758071.92233729758071";
  long long int a1 = 0;
  long long int b1 = 0;
  long long int c1 = 0;
  long long int a2 = 0;
  long long int b2 = 0;
  long long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%lld%lld%lld", &a1, &b1, &c1),
                   s21_sscanf(one_, "%lld%lld%lld", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_52) {
  char one_[] = "aaaa3aaaa bbbb6bbbbbb ccccccc2cccccc";
  long long int a1 = 0;
  long long int b1 = 0;
  long long int c1 = 0;
  long long int a2 = 0;
  long long int b2 = 0;
  long long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%1lld%2lld%3lld", &a1, &b1, &c1),
                   s21_sscanf(one_, "%1lld%2lld%3lld", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_53) {
  char one_[] =
      "9223372036854775807 -9223372036854775808 "
      "92233720368547758071";
  long long int a1 = 0;
  long long int b1 = 0;
  long long int c1 = 0;
  long long int a2 = 0;
  long long int b2 = 0;
  long long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%1lld%2lld%3lld", &a1, &b1, &c1),
                   s21_sscanf(one_, "%1lld%2lld%3lld", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

/*-----------%hi-%hd------------*/
START_TEST(test_s21_sscanf_54) {
  char one_[] = "32767 −32767 32767";
  short int a1 = 0;
  short int b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%hi%hi%hi", &a1, &b1, &c1),
                   s21_sscanf(one_, "%hi%hi%hi", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_55) {
  char one_[] = "32767 −32767 32767";
  short int a1 = 0;
  short int b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%hd%hd%hd", &a1, &b1, &c1),
                   s21_sscanf(one_, "%hd%hd%hd", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_56) {
  char one_[] = "3276732767 −3276732767 3276732767";
  short int a1 = 0;
  short int b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%hi%hi%hi", &a1, &b1, &c1),
                   s21_sscanf(one_, "%hi%hi%hi", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_57) {
  char one_[] = "3276732767 −3276732767 3276732767";
  short int a1 = 0;
  short int b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%hd%hd%hd", &a1, &b1, &c1),
                   s21_sscanf(one_, "%hd%hd%hd", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_58) {
  char one_[] = "0.3276732767 −000.3276732767 0000000.3276732767";
  short int a1 = 0;
  short int b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%hi%hi%hi", &a1, &b1, &c1),
                   s21_sscanf(one_, "%hi%hi%hi", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_59) {
  char one_[] = "0.3276732767 −000.3276732767 0000000.3276732767";
  short int a1 = 0;
  short int b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%hd%hd%hd", &a1, &b1, &c1),
                   s21_sscanf(one_, "%hd%hd%hd", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_60) {
  char one_[] = "a3a2767 −32767bb //**//32767.0000";
  short int a1 = 0;
  short int b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%hi%hi%hi", &a1, &b1, &c1),
                   s21_sscanf(one_, "%hi%hi%hi", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_61) {
  char one_[] = "a3a2767 −32767bb //**//32767.0000";
  short int a1 = 0;
  short int b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%hd%hd%hd", &a1, &b1, &c1),
                   s21_sscanf(one_, "%hd%hd%hd", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_62) {
  char one_[] = "0000000032767 −0000000000032767 000000000.32767";
  short int a1 = 0;
  short int b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%hi%hi%hi", &a1, &b1, &c1),
                   s21_sscanf(one_, "%hi%hi%hi", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_63) {
  char one_[] = "0000000032767 −0000000000032767 000000000.32767";
  short int a1 = 0;
  short int b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%hd%hd%hd", &a1, &b1, &c1),
                   s21_sscanf(one_, "%hd%hd%hd", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_64) {
  char one_[] = "3276732767 −3276732767 3276732767";
  short int a1 = 0;
  short int b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%2hi%3hi%4hi", &a1, &b1, &c1),
                   s21_sscanf(one_, "%2hi%3hi%4hi", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_65) {
  char one_[] = "3276732767 −3276732767 3276732767";
  short int a1 = 0;
  short int b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%2hd%3hd%4hd", &a1, &b1, &c1),
                   s21_sscanf(one_, "%2hd%3hd%4hd", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_66) {
  char one_[] = "3276732767 −3276732767 3276732767";
  short int a1 = 0;
  short int b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%111hi%222hi%333hi", &a1, &b1, &c1),
                   s21_sscanf(one_, "%111hi%222hi%333hi", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_67) {
  char one_[] = "3276732767 −3276732767 3276732767";
  short int a1 = 0;
  short int b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%111hd%222hd%333hd", &a1, &b1, &c1),
                   s21_sscanf(one_, "%111hd%222hd%333hd", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_68) {
  char one_[] = "3276732767 −3276732767 3276732767";
  short int a1 = 0;
  short int b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%5hi%4hi%3hi", &a1, &b1, &c1),
                   s21_sscanf(one_, "%5hi%4hi%3hi", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_69) {
  char one_[] = "3276732767 −3276732767 3276732767";
  short int a1 = 0;
  short int b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%5hd%4hd%3hd", &a1, &b1, &c1),
                   s21_sscanf(one_, "%5hd%4hd%3hd", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_70) {
  char one_[] = "3276732767 −3276732767 3276732767";
  short int a1 = 0;
  short int b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%1hi%hi%1hi", &a1, &b1, &c1),
                   s21_sscanf(one_, "%1hi%hi%1hi", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_71) {
  char one_[] = "3276732767 −3276732767 3276732767";
  short int a1 = 0;
  short int b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%1hd%hd%1hd", &a1, &b1, &c1),
                   s21_sscanf(one_, "%1hd%hd%1hd", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

/*-----------%f------------*/
START_TEST(test_s21_sscanf_72) {
  char one_[] = "3.40282347e+38 1.17549435e-38 b";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%f%f%f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%f%f%f", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_73) {
  char one_[] = "3.402282347e+38 13.17549435e-38 0000.00000000";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%f%f%f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%f%f%f", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_74) {
  char one_[] = "113.40282347e+38 111.17549435e-38 1111b111";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%f%f%f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%f%f%f", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_75) {
  char one_[] = "3.40282347e+38 1.17549435e-38 b";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%1f%2f%3f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%1f%2f%3f", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_76) {
  char one_[] = "3.40282347e+38 1.17549435e-38 b";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%11f%22f%33f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%11f%22f%33f", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_77) {
  char one_[] = "";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%f%f%f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%f%f%f", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_78) {
  char one_[] = "1 2 3";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%f%f%f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%f%f%f", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_79) {
  char one_[] = "0 -0 +0";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%f%f%f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%f%f%f", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_80) {
  char one_[] = "0.000000000 0000000000000000.0 9999999999999999";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%f%f%f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%f%f%f", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_81) {
  char one_[] = "0.000000000 0000000000000000.0 9999999999999999";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%5f%f%6f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%5f%f%6f", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_82) {
  char one_[] = "abc";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%f%f%f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%f%f%f", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_83) {
  char one_[] = "02.a 033.as 054.0999yt";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%f%f%f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%f%f%f", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_84) {
  char one_[] = "3.40282347e+38 1.17549435e-38 b";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%f%f%f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%f%f%f", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_85) {
  char one_[] =
      "9223372036854775807 -9223372036854775808 "
      "92233720368547758071";

  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%f%f%f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%f%f%f", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_86) {
  char one_[] = "  ";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%f%f%f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%f%f%f", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_87) {
  char one_[] = "3.40282347e+38  \0";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%111f%222f%333f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%111f%222f%333f", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_88) {
  char one_[] = "-111111.1111111 +11111111.111111111 \n";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%f%f%f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%f%f%f", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

/*-----------%i------------*/
START_TEST(test_s21_sscanf_89) {
  char one_[] = "0123 0XFFFF 0xFFFF";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%i%i%i", &a1, &b1, &c1),
                   s21_sscanf(one_, "%i%i%i", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_90) {
  char one_[] = "0123 011111 023165444";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%i%i%i", &a1, &b1, &c1),
                   s21_sscanf(one_, "%i%i%i", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_91) {
  char one_[] = "0xabcdef 0XFAFA 0xFFFF";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%i%i%i", &a1, &b1, &c1),
                   s21_sscanf(one_, "%i%i%i", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_92) {
  char one_[] = "0xffffff 0XFFFFF 0xfFFF";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%i%i%i", &a1, &b1, &c1),
                   s21_sscanf(one_, "%i%i%i", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_93) {
  char one_[] = "0x7FFFFFFF 0x80000000 0xFfAaBb";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%i%i%i", &a1, &b1, &c1),
                   s21_sscanf(one_, "%i%i%i", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_94) {
  char one_[] = "2a72d9 2b23 ffffff6e";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%i%i%i", &a1, &b1, &c1),
                   s21_sscanf(one_, "%i%i%i", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_95) {
  char one_[] = "2a72d9 2b23 ffffff6e";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%2i%3i%4i", &a1, &b1, &c1),
                   s21_sscanf(one_, "%2i%3i%4i", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

/*-----------%e------------*/
START_TEST(test_s21_sscanf_96) {
  char one_[] = "1.79769313e+308 2.22507386e-308 3.22507386e-308";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%e%e%e", &a1, &b1, &c1),
                   s21_sscanf(one_, "%e%e%e", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}

START_TEST(test_s21_sscanf_106) {
  char one_[] = "0.79763e+308 1.22586e-308 1.22386e-308";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%e%e%e", &a1, &b1, &c1),
                   s21_sscanf(one_, "%e%e%e", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_97) {
  char one_[] =
      "asd 0000000000.0000000000000000 0000000000000.00000000000000001";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%e%e%e", &a1, &b1, &c1),
                   s21_sscanf(one_, "%e%e%e", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_98) {
  char one_[] = "1.79769313e+3081 2.22507386e-3082 3.22507386e-3086";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%e%e%e", &a1, &b1, &c1),
                   s21_sscanf(one_, "%e%e%e", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_99) {
  char one_[] = "1.79769313 2.22507386 3.22507386";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%e%e%e", &a1, &b1, &c1),
                   s21_sscanf(one_, "%e%e%e", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_100) {
  char one_[] = "-1.79769313e+308 -2.22507386e-308 -3.22507386e-308";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%e%e%e", &a1, &b1, &c1),
                   s21_sscanf(one_, "%e%e%e", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_101) {
  char one_[] = "1 2 3";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%e%e%e", &a1, &b1, &c1),
                   s21_sscanf(one_, "%e%e%e", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_102) {
  char one_[] = "11111111111111111111 222222222222222222 3333333333333333333";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%e%e%e", &a1, &b1, &c1),
                   s21_sscanf(one_, "%e%e%e", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_103) {
  char one_[] =
      "00000000000000000000001 0000000000000000000002 000000000000000000000003";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%e%e%e", &a1, &b1, &c1),
                   s21_sscanf(one_, "%e%e%e", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_104) {
  char one_[] = "0f1234 0x12445 09876";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%e%e%e", &a1, &b1, &c1),
                   s21_sscanf(one_, "%e%e%e", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_105) {
  char one_[] =
      "1.00002220444444440555555 -0.220000000000000000000001 "
      "-0.3000000000000000002";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%e%e%e", &a1, &b1, &c1),
                   s21_sscanf(one_, "%e%e%e", &a2, &b2, &c2));
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
}
END_TEST

/*-----------%LE------------*/
// START_TEST(test_s21_sscanf_107) {
//   char one_[] = "1.79769313 2.22507386 2.22507386";
//   long double a1 = 0;
//   long double b1 = 0;
//   long double c1 = 0;
//   long double a2 = 0;
//   long double b2 = 0;
//   long double c2 = 0;
//   ck_assert_int_eq(sscanf(one_, "%LE%LE%LE", &a1, &b1, &c1),
//                    s21_sscanf(one_, "%LE%LE%LE", &a2, &b2, &c2));
//   ck_assert_double_eq(a1, a2);
//   ck_assert_double_eq(b1, b2);
//   ck_assert_double_eq(c1, c2);
// }
// END_TEST

START_TEST(test_s21_sscanf_108) {
  char one_[] = "1.79769313e+301118 2.22507386e-302228 2.22507386e-3082222888";
  long double a1 = 0;
  long double b1 = 0;
  long double c1 = 0;
  long double a2 = 0;
  long double b2 = 0;
  long double c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%LE%LE%LE", &a1, &b1, &c1),
                   s21_sscanf(one_, "%LE%LE%LE", &a2, &b2, &c2));
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_109) {
  char one_[] = "1 2 3";
  long double a1 = 0;
  long double b1 = 0;
  long double c1 = 0;
  long double a2 = 0;
  long double b2 = 0;
  long double c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%LE%LE%LE", &a1, &b1, &c1),
                   s21_sscanf(one_, "%LE%LE%LE", &a2, &b2, &c2));
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_110) {
  char one_[] = "a b c ";
  long double a1 = 0;
  long double b1 = 0;
  long double c1 = 0;
  long double a2 = 0;
  long double b2 = 0;
  long double c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%LE%LE%LE", &a1, &b1, &c1),
                   s21_sscanf(one_, "%LE%LE%LE", &a2, &b2, &c2));
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ;
}
END_TEST

START_TEST(test_s21_sscanf_111) {
  char one_[] = "ef1.79769313e+308 sa2a.22507386e-308 xzzx2.22507386e-308888";
  long double a1 = 0;
  long double b1 = 0;
  long double c1 = 0;
  long double a2 = 0;
  long double b2 = 0;
  long double c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%LE%LE%LE", &a1, &b1, &c1),
                   s21_sscanf(one_, "%LE%LE%LE", &a2, &b2, &c2));
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_112) {
  char one_[] = "11111.79769313e+308 22222.22507386e-308 2321.22507386e-308888";
  long double a1 = 0;
  long double b1 = 0;
  long double c1 = 0;
  long double a2 = 0;
  long double b2 = 0;
  long double c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%LE%LE%LE", &a1, &b1, &c1),
                   s21_sscanf(one_, "%LE%LE%LE", &a2, &b2, &c2));
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_113) {
  char one_[] = "0f12345 0.000000000000000000000000000000000001 0101";
  long double a1 = 0;
  long double b1 = 0;
  long double c1 = 0;
  long double a2 = 0;
  long double b2 = 0;
  long double c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%LE%LE%LE", &a1, &b1, &c1),
                   s21_sscanf(one_, "%LE%LE%LE", &a2, &b2, &c2));
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_114) {
  char one_[] =
      "1.79769313e+1111308 2.22507386e-1111308 2.22507386e-111111308888";
  long double a1 = 0;
  long double b1 = 0;
  long double c1 = 0;
  long double a2 = 0;
  long double b2 = 0;
  long double c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%LE%LE%LE", &a1, &b1, &c1),
                   s21_sscanf(one_, "%LE%LE%LE", &a2, &b2, &c2));
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_115) {
  char one_[] = "0.1 0.2 0.3";
  long double a1 = 0;
  long double b1 = 0;
  long double c1 = 0;
  long double a2 = 0;
  long double b2 = 0;
  long double c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%LE%LE%LE", &a1, &b1, &c1),
                   s21_sscanf(one_, "%LE%LE%LE", &a2, &b2, &c2));
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_116) {
  char one_[] = "0.001.002 0.002.003 0.003.004";
  long double a1 = 0;
  long double b1 = 0;
  long double c1 = 0;
  long double a2 = 0;
  long double b2 = 0;
  long double c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%LE%LE%LE", &a1, &b1, &c1),
                   s21_sscanf(one_, "%LE%LE%LE", &a2, &b2, &c2));
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
}
END_TEST

/*-----------lf%------------*/
START_TEST(test_s21_sscanf_117) {
  char one_[] = "1.7e-308 1.7e+308 1.7e308";
  double a1 = 0;
  double b1 = 0;
  double c1 = 0;
  double a2 = 0;
  double b2 = 0;
  double c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%lf%lf%lf", &a1, &b1, &c1),
                   s21_sscanf(one_, "%lf%lf%lf", &a2, &b2, &c2));
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_118) {
  char one_[] = "1.7e-30876767 1.7e+3035345348 1.7e345645608";
  double a1 = 0;
  double b1 = 0;
  double c1 = 0;
  double a2 = 0;
  double b2 = 0;
  double c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%lf%lf%lf", &a1, &b1, &c1),
                   s21_sscanf(one_, "%lf%lf%lf", &a2, &b2, &c2));
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_119) {
  char one_[] = "11.7e-305558 12.7e+3048 13.7e32208";
  double a1 = 0;
  double b1 = 0;
  double c1 = 0;
  double a2 = 0;
  double b2 = 0;
  double c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%lf%lf%lf", &a1, &b1, &c1),
                   s21_sscanf(one_, "%lf%lf%lf", &a2, &b2, &c2));
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_120) {
  char one_[] = "";
  double a1 = 0;
  double b1 = 0;
  double c1 = 0;
  double a2 = 0;
  double b2 = 0;
  double c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%lf%lf%lf", &a1, &b1, &c1),
                   s21_sscanf(one_, "%lf%lf%lf", &a2, &b2, &c2));
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_121) {
  char one_[] = "a b c";
  double a1 = 0;
  double b1 = 0;
  double c1 = 0;
  double a2 = 0;
  double b2 = 0;
  double c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%lf%lf%lf", &a1, &b1, &c1),
                   s21_sscanf(one_, "%lf%lf%lf", &a2, &b2, &c2));
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_122) {
  char one_[] = "                         ";
  double a1 = 0;
  double b1 = 0;
  double c1 = 0;
  double a2 = 0;
  double b2 = 0;
  double c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%lf%lf%lf", &a1, &b1, &c1),
                   s21_sscanf(one_, "%lf%lf%lf", &a2, &b2, &c2));
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_123) {
  char one_[] = "01.0000000000e-333333 -000000.0000000000000e99999999 1";
  double a1 = 0;
  double b1 = 0;
  double c1 = 0;
  double a2 = 0;
  double b2 = 0;
  double c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%lf%lf%lf", &a1, &b1, &c1),
                   s21_sscanf(one_, "%lf%lf%lf", &a2, &b2, &c2));
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_124) {
  char one_[] = "‼ §=`╔◙ Г@>╛";
  double a1 = 0;
  double b1 = 0;
  double c1 = 0;
  double a2 = 0;
  double b2 = 0;
  double c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%lf%lf%lf", &a1, &b1, &c1),
                   s21_sscanf(one_, "%lf%lf%lf", &a2, &b2, &c2));
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_125) {
  char one_[] = "1.7e-308 1.7e+308 1.7e308";
  double a1 = 0;
  double b1 = 0;
  double c1 = 0;
  double a2 = 0;
  double b2 = 0;
  double c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%1lf%2lf%333lf", &a1, &b1, &c1),
                   s21_sscanf(one_, "%1lf%2lf%333lf", &a2, &b2, &c2));
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_126) {
  char one_[] = "\n1.7e-308 \t1.7e+308 EOF1.7e308";
  double a1 = 0;
  double b1 = 0;
  double c1 = 0;
  double a2 = 0;
  double b2 = 0;
  double c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%lf%lf%lf", &a1, &b1, &c1),
                   s21_sscanf(one_, "%lf%lf%lf", &a2, &b2, &c2));
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_127) {
  char one_[] = "1.7e-308 1.7e+308 1.7e308";
  double a1 = 0;
  double b1 = 0;
  double c1 = 0;
  double a2 = 0;
  double b2 = 0;
  double c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%111lf%222lf%2lf", &a1, &b1, &c1),
                   s21_sscanf(one_, "%111lf%222lf%2lf", &a2, &b2, &c2));
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
}
END_TEST

/*-----------%E------------*/
START_TEST(test_s21_sscanf_128) {
  char one_[] = "-3.4e38 3.4e38 3.4e-38";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%E%E%E", &a1, &b1, &c1),
                   s21_sscanf(one_, "%E%E%E", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_129) {
  char one_[] = "-3.4e233238 233.41e322228 0.4e-38";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%E%E%E", &a1, &b1, &c1),
                   s21_sscanf(one_, "%E%E%E", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_130) {
  char one_[] = "";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%E%E%E", &a1, &b1, &c1),
                   s21_sscanf(one_, "%E%E%E", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_131) {
  char one_[] = "a v c";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%E%E%E", &a1, &b1, &c1),
                   s21_sscanf(one_, "%E%E%E", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_132) {
  char one_[] = "                    ";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%E%E%E", &a1, &b1, &c1),
                   s21_sscanf(one_, "%E%E%E", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_133) {
  char one_[] = "                         ";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%E%E%E", &a1, &b1, &c1),
                   s21_sscanf(one_, "%E%E%E", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_134) {
  char one_[] = "4babcb3b4 0.ndf32fj ndsf00011200.000000bb";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%E%E%E", &a1, &b1, &c1),
                   s21_sscanf(one_, "%E%E%E", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_135) {
  char one_[] = "‼ §=`╔◙ Г @ >╛";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%E%E%E", &a1, &b1, &c1),
                   s21_sscanf(one_, "%E%E%E", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_136) {
  char one_[] = "-3.4e38 3.4e38 3.4e-38";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%1E%2E%3E", &a1, &b1, &c1),
                   s21_sscanf(one_, "%1E%2E%3E", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_137) {
  char one_[] = "-3.4e38 3.4e38 3.4e-38";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%111E%222E%333E", &a1, &b1, &c1),
                   s21_sscanf(one_, "%111E%222E%333E", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_138) {
  char one_[] = "\n \t EOF";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%E%E%E", &a1, &b1, &c1),
                   s21_sscanf(one_, "%E%E%E", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

/*-----------%g------------*/
START_TEST(test_s21_sscanf_139) {
  char one_[] = "111.111 222.222 333.333";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%g%g%g", &a1, &b1, &c1),
                   s21_sscanf(one_, "%g%g%g", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_140) {
  char one_[] = "-3.4e38 3.4e38 3.4e-38";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%g%g%g", &a1, &b1, &c1),
                   s21_sscanf(one_, "%g%g%g", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_141) {
  char one_[] = "-3.4e233238 233.41e322228 0.4e-38";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%g%g%g", &a1, &b1, &c1),
                   s21_sscanf(one_, "%g%g%g", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_142) {
  char one_[] = "0.0000000000000000000000000001 0.00001 0.0";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%g%g%g", &a1, &b1, &c1),
                   s21_sscanf(one_, "%g%g%g", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_143) {
  char one_[] = "5.555e999999 0.01-e555555555 -0.1e999999999999999";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%g%g%g", &a1, &b1, &c1),
                   s21_sscanf(one_, "%g%g%g", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_144) {
  char one_[] = "";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%g%g%g", &a1, &b1, &c1),
                   s21_sscanf(one_, "%g%g%g", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_145) {
  char one_[] = "                              ";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%g%g%g", &a1, &b1, &c1),
                   s21_sscanf(one_, "%g%g%g", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_146) {
  char one_[] = "                             ";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%g%g%g", &a1, &b1, &c1),
                   s21_sscanf(one_, "%g%g%g", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_147) {
  char one_[] = "0.as22.sa 0.1s 1.s294949";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%g%g%g", &a1, &b1, &c1),
                   s21_sscanf(one_, "%g%g%g", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_148) {
  char one_[] =
      "9223372036854775807 -9223372036854775808 "
      "92233720368547758071";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%g%g%g", &a1, &b1, &c1),
                   s21_sscanf(one_, "%g%g%g", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_149) {
  char one_[] = "9999999999.999999999999999999 1.2 1.3";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%g%g%g", &a1, &b1, &c1),
                   s21_sscanf(one_, "%g%g%g", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_150) {
  char one_[] = "9999999999.999999999999999999 1.2 1.3";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%1g%2g%3g", &a1, &b1, &c1),
                   s21_sscanf(one_, "%1g%2g%3g", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_151) {
  char one_[] = "9999999999.999999999999999999 1.2 1.3";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%111g%222g%333g", &a1, &b1, &c1),
                   s21_sscanf(one_, "%111g%222g%333g", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_152) {
  char one_[] = "12.3456 -1.987654321 -0.987654321";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%133g%12g%11g", &a1, &b1, &c1),
                   s21_sscanf(one_, "%133g%12g%11g", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

/*-----------%G------------*/
START_TEST(test_s21_sscanf_153) {
  char one_[] = "12.3456 -1.987654321 -0.987654321";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%G%G%G", &a1, &b1, &c1),
                   s21_sscanf(one_, "%G%G%G", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_154) {
  char one_[] = "111.111 222.222 333.333";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%G%G%G", &a1, &b1, &c1),
                   s21_sscanf(one_, "%G%G%G", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_155) {
  char one_[] = "-3.4e38 3.4e38 3.4e-38";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%G%G%G", &a1, &b1, &c1),
                   s21_sscanf(one_, "%G%G%G", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_156) {
  char one_[] = "-3.4e233238 233.41e322228 0.4e-38";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%G%G%G", &a1, &b1, &c1),
                   s21_sscanf(one_, "%G%G%G", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_157) {
  char one_[] = "0.0000000000000000000000000001 0.00001 0.0";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%G%G%G", &a1, &b1, &c1),
                   s21_sscanf(one_, "%G%G%G", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_158) {
  char one_[] = "5.555e999999 0.01-e555555555 -0.1e999999999999999";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%G%G%G", &a1, &b1, &c1),
                   s21_sscanf(one_, "%G%G%G", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_159) {
  char one_[] = "";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%G%G%G", &a1, &b1, &c1),
                   s21_sscanf(one_, "%G%G%G", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_160) {
  char one_[] = "                              ";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%G%G%G", &a1, &b1, &c1),
                   s21_sscanf(one_, "%G%G%G", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_161) {
  char one_[] = "                             ";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%G%G%G", &a1, &b1, &c1),
                   s21_sscanf(one_, "%G%G%G", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_162) {
  char one_[] = "0.as22.sa 0.1s 1.s294949";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%G%G%G", &a1, &b1, &c1),
                   s21_sscanf(one_, "%G%G%G", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_163) {
  char one_[] =
      "9223372036854775807 -9223372036854775808 "
      "92233720368547758071";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%G%G%G", &a1, &b1, &c1),
                   s21_sscanf(one_, "%G%G%G", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_164) {
  char one_[] = "9999999999.999999999999999999 1.2 1.3";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%G%G%G", &a1, &b1, &c1),
                   s21_sscanf(one_, "%G%G%G", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_165) {
  char one_[] = "9999999999.999999999999999999 1.2 1.3";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%1G%2G%3G", &a1, &b1, &c1),
                   s21_sscanf(one_, "%1G%2G%3G", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_166) {
  char one_[] = "9999999999.999999999999999999 1.2 1.3";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%111G%222G%333G", &a1, &b1, &c1),
                   s21_sscanf(one_, "%111G%222G%333G", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_167) {
  char one_[] = "12.3456 -1.987654321 -0.987654321";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%133G%12G%11G", &a1, &b1, &c1),
                   s21_sscanf(one_, "%133G%12G%11G", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

/*-----------%o------------*/
START_TEST(test_s21_sscanf_168) {
  char one_[9999] = "01234 0123456789 01234567";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%o%o%o", &a1, &b1, &c1),
                   s21_sscanf(one_, "%o%o%o", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_169) {
  char one_[9999] = "0000000 0123456 01234";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%o%o%o", &a1, &b1, &c1),
                   s21_sscanf(one_, "%o%o%o", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_170) {
  char one_[9999] = "01234 0x0123 0x12345";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%o%o%o", &a1, &b1, &c1),
                   s21_sscanf(one_, "%o%o%o", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_171) {
  char one_[9999] = "01234 0123456789 01234567";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%o%o%o", &a1, &b1, &c1),
                   s21_sscanf(one_, "%o%o%o", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_172) {
  char one_[9999] = "01.0123 00.123 0123";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%o%o%o", &a1, &b1, &c1),
                   s21_sscanf(one_, "%o%o%o", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_173) {
  char one_[9999] = "0654321 07654321 0999999";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%o%o%o", &a1, &b1, &c1),
                   s21_sscanf(one_, "%o%o%o", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_174) {
  char one_[9999] = "0999999999 0987654321 098765";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%o%o%o", &a1, &b1, &c1),
                   s21_sscanf(one_, "%o%o%o", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_175) {
  char one_[9999] = "a b c";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%o%o%o", &a1, &b1, &c1),
                   s21_sscanf(one_, "%o%o%o", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_176) {
  char one_[999999] =
      "999999999999 999999999999999999999 9999999999999999999999999999";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%o%o%o", &a1, &b1, &c1),
                   s21_sscanf(one_, "%o%o%o", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_177) {
  // пробелы
  char one_[999] = "                  ";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%o%o%o", &a1, &b1, &c1),
                   s21_sscanf(one_, "%o%o%o", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_178) {
  // табы
  char one_[9999] = "                         ";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%o%o%o", &a1, &b1, &c1),
                   s21_sscanf(one_, "%o%o%o", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_179) {
  char one_[99999] = "01234 012345 012";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%o%o%o", &a1, &b1, &c1),
                   s21_sscanf(one_, "%o%o%o", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_180) {
  char one_[9999] = "0123 01234 0123456789";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%1o%2o%3o", &a1, &b1, &c1),
                   s21_sscanf(one_, "%1o%2o%3o", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_181) {
  char one_[9999] = "0123 01234 0123456789";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%11o%22o%33o", &a1, &b1, &c1),
                   s21_sscanf(one_, "%11o%22o%33o", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_182) {
  char one_[9999] = "0123 01234 0123456789";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%111o%222o%333o", &a1, &b1, &c1),
                   s21_sscanf(one_, "%111o%222o%333o", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

/*-----------%s------------*/
START_TEST(test_s21_sscanf_183) {
  char one_[9999] = "stroka eshestroka ieshestrochka inlkxmlxvcnibfw";
  char a1[111] = {0};
  char b1[111] = {0};
  char c1[111] = {0};
  char a2[111] = {0};
  char b2[111] = {0};
  char c2[111] = {0};
  ck_assert_int_eq(sscanf(one_, "%9s%*s%9s%2s", a1, b1, c1),
                   s21_sscanf(one_, "%9s%*s%9s%2s", a2, b2, c2));
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_184) {
  char one_[111] = "stroka eshestroka ieshestrochka";
  char a1[111] = {0};
  char b1[111] = {0};
  char c1[111] = {0};
  char a2[111] = {0};
  char b2[111] = {0};
  char c2[111] = {0};
  ck_assert_int_eq(sscanf(one_, "%11s%12s%13s", a1, b1, c1),
                   s21_sscanf(one_, "%11s%12s%13s", a2, b2, c2));
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_185) {
  char one_[111] = "111111111111111111111111 eshestroka ieshestrochka";
  char a1[111] = {0};
  char b1[111] = {0};
  char c1[111] = {0};
  char a2[111] = {0};
  char b2[111] = {0};
  char c2[111] = {0};
  ck_assert_int_eq(sscanf(one_, "%3s%3s%3s", a1, b1, c1),
                   s21_sscanf(one_, "%3s%3s%3s", a2, b2, c2));
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_186) {
  char one_[111] = "123456 0Xffffff qwerty";
  char a1[111] = {0};
  char b1[111] = {0};
  char c1[111] = {0};
  char a2[111] = {0};
  char b2[111] = {0};
  char c2[111] = {0};
  ck_assert_int_eq(sscanf(one_, "%3s%3s%3s", a1, b1, c1),
                   s21_sscanf(one_, "%3s%3s%3s", a2, b2, c2));
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_187) {
  char one_[111] = "stroka\n eshestroka\n ieshestrochka\0";
  char a1[111] = {0};
  char b1[111] = {0};
  char c1[111] = {0};
  char a2[111] = {0};
  char b2[111] = {0};
  char c2[111] = {0};
  ck_assert_int_eq(sscanf(one_, "%3s%3s%3s", a1, b1, c1),
                   s21_sscanf(one_, "%3s%3s%3s", a2, b2, c2));
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_188) {
  char one_[111] = "stroka eshestroka ieshestrochka";
  char a1[1111] = {0};
  char b1[1111] = {0};
  char c1[1111] = {0};
  char a2[1111] = {0};
  char b2[1111] = {0};
  char c2[1111] = {0};
  ck_assert_int_eq(sscanf(one_, "%111s%222s%333s", a1, b1, c1),
                   s21_sscanf(one_, "%111s%222s%333s", a2, b2, c2));
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_189) {
  char one_[111] = "  stroka      eshestroka     ieshestrochka";
  char a1[111] = {0};
  char b1[111] = {0};
  char c1[111] = {0};
  char a2[111] = {0};
  char b2[111] = {0};
  char c2[111] = {0};
  ck_assert_int_eq(sscanf(one_, "%3s%3s%3s", a1, b1, c1),
                   s21_sscanf(one_, "%3s%3s%3s", a2, b2, c2));
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_190) {
  char one_[111] = "                      ";
  char a1[111] = {0};
  char b1[111] = {0};
  char c1[111] = {0};
  char a2[111] = {0};
  char b2[111] = {0};
  char c2[111] = {0};
  ck_assert_int_eq(sscanf(one_, "%3s%3s%3s", a1, b1, c1),
                   s21_sscanf(one_, "%3s%3s%3s", a2, b2, c2));
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_191) {
  // tab
  char one_[111] = "                          ";
  char a1[111] = {0};
  char b1[111] = {0};
  char c1[111] = {0};
  char a2[111] = {0};
  char b2[111] = {0};
  char c2[111] = {0};
  ck_assert_int_eq(sscanf(one_, "%3s%3s%3s", a1, b1, c1),
                   s21_sscanf(one_, "%3s%3s%3s", a2, b2, c2));
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_192) {
  char one_[111] = "ADC ФВС adc";
  char a1[111] = {0};
  char b1[111] = {0};
  char c1[111] = {0};
  char a2[111] = {0};
  char b2[111] = {0};
  char c2[111] = {0};
  ck_assert_int_eq(sscanf(one_, "%3s%3s%3s", a1, b1, c1),
                   s21_sscanf(one_, "%3s%3s%3s", a2, b2, c2));
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_193) {
  char one_[111] = "asd asd asd asd asd asd asd    ";
  char a1[111] = {0};
  char b1[111] = {0};
  char c1[111] = {0};
  char a2[111] = {0};
  char b2[111] = {0};
  char c2[111] = {0};
  ck_assert_int_eq(sscanf(one_, "%3s%3s%3s", a1, b1, c1),
                   s21_sscanf(one_, "%3s%3s%3s", a2, b2, c2));
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_194) {
  char one_[111] = "EOF asd 123";
  char a1[111] = {0};
  char b1[111] = {0};
  char c1[111] = {0};
  char a2[111] = {0};
  char b2[111] = {0};
  char c2[111] = {0};
  ck_assert_int_eq(sscanf(one_, "%3s%3s%3s", a1, b1, c1),
                   s21_sscanf(one_, "%3s%3s%3s", a2, b2, c2));
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_195) {
  char one_[111] = "01234 012345 012";
  char a1[111] = {0};
  char b1[111] = {0};
  char c1[111] = {0};
  char a2[111] = {0};
  char b2[111] = {0};
  char c2[111] = {0};
  ck_assert_int_eq(sscanf(one_, "%3s%3s%3s", a1, b1, c1),
                   s21_sscanf(one_, "%3s%3s%3s", a2, b2, c2));
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_196) {
  char one_[99999] =
      "stroka1eshe2stroka3i4eshe5strochka6stroka7eshe8stroka9i10eshe11strochka1"
      "2stroka13eshe14st15 rokaieshestrochkastrokaeshestrokaieshestrochka "
      "strokaeshestrokaieshestrochka strokaeshestrokaieshestrochka";
  char a1[99999] = {0};
  char b1[99999] = {0};
  char c1[99999] = {0};
  char a2[99999] = {0};
  char b2[99999] = {0};
  char c2[99999] = {0};
  ck_assert_int_eq(sscanf(one_, "%1s%1s%1s", a1, b1, c1),
                   s21_sscanf(one_, "%1s%1s%1s", a2, b2, c2));
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_197) {
  char one_[9999] =
      "strokaeshestrokaieshestrochkastrokaeshestrokaieshestrochkastrokaeshest"
      "rokaieshestrochkastrokaeshestrokaieshestrochka "
      "strokaeshestrokaieshestrochka strokaeshestrokaieshestrochka";
  char a1[111] = {0};
  char b1[111] = {0};
  char c1[111] = {0};
  char a2[111] = {0};
  char b2[111] = {0};
  char c2[111] = {0};
  ck_assert_int_eq(sscanf(one_, "%12s%13s%14s", a1, b1, c1),
                   s21_sscanf(one_, "%12s%13s%14s", a2, b2, c2));
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
}
END_TEST

/*-----------%u------------*/
START_TEST(test_s21_sscanf_198) {
  char one_[9999] = "123 1234 12345";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%u%u%u", &a1, &b1, &c1),
                   s21_sscanf(one_, "%u%u%u", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_199) {
  char one_[9999] = "123456789 987654321 -123456789";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%u%u%u", &a1, &b1, &c1),
                   s21_sscanf(one_, "%u%u%u", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_200) {
  char one_[] = "-123456 -654321 -987";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%u%u%u", &a1, &b1, &c1),
                   s21_sscanf(one_, "%u%u%u", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_201) {
  char one_[] = "999999999999999999999 -999999999999999999999 0123456";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%u%u%u", &a1, &b1, &c1),
                   s21_sscanf(one_, "%u%u%u", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_202) {
  char one_[] = "abc 1234 bac";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%u%u%u", &a1, &b1, &c1),
                   s21_sscanf(one_, "%u%u%u", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_203) {
  char one_[] = "123\t 321\n -123\0";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%u%u%u", &a1, &b1, &c1),
                   s21_sscanf(one_, "%u%u%u", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_204) {
  char one_[] = "a1b2c3 1d2r3t -0";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%u%u%u", &a1, &b1, &c1),
                   s21_sscanf(one_, "%u%u%u", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_205) {
  char one_[] = "            "; /*пробелы*/
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%u%u%u", &a1, &b1, &c1),
                   s21_sscanf(one_, "%u%u%u", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_206) {
  char one_[] = "                         "; /*табы*/
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%u%u%u", &a1, &b1, &c1),
                   s21_sscanf(one_, "%u%u%u", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_207) {
  char one_[] = "123 1234 12345";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%1u%2u%3u", &a1, &b1, &c1),
                   s21_sscanf(one_, "%1u%2u%3u", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_208) {
  char one_[99999] = "-123 1234 12345";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%11u%22u%33u", &a1, &b1, &c1),
                   s21_sscanf(one_, "%11u%22u%33u", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_209) {
  char one_[99999] = "-987654321 987654321 123456789";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%111u%222u%3333u", &a1, &b1, &c1),
                   s21_sscanf(one_, "%111u%222u%3333u", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

/*-----------%x------------*/
START_TEST(test_s21_sscanf_210) {
  char one_[] = "-987654321 987654321 123456789";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%x%x%x", &a1, &b1, &c1),
                   s21_sscanf(one_, "%x%x%x", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_211) {
  char one_[] = "1e240 E1740 75BCD15";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%x%x%x", &a1, &b1, &c1),
                   s21_sscanf(one_, "%x%x%x", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_212) {
  char one_[] = "-1e240 -E1740 -75BCD15";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%x%x%x", &a1, &b1, &c1),
                   s21_sscanf(one_, "%x%x%x", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_220) {
  char one_[] = "5F5E0FF 174876E7FF 5AF3107A3FFF";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%x%x%x", &a1, &b1, &c1),
                   s21_sscanf(one_, "%x%x%x", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_213) {
  char one_[] = "5F5E0FF 174876E7FF 5AF3107A3FFF";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%1x%2x%3x", &a1, &b1, &c1),
                   s21_sscanf(one_, "%1x%2x%3x", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_214) {
  char one_[] = "5F5E0FF 174876E7FF 5AF3107A3FFF";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%11x%22x%33x", &a1, &b1, &c1),
                   s21_sscanf(one_, "%11x%22x%33x", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_215) {
  char one_[] = "5F5E0FF 174876E7FF 5AF3107A3FFF";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%111x%222x%333x", &a1, &b1, &c1),
                   s21_sscanf(one_, "%111x%222x%333x", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_216) {
  char one_[] = "5F5A9CE0FF 174876EA87FF 9F5AF3107A3FFF";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%x%x%x", &a1, &b1, &c1),
                   s21_sscanf(one_, "%x%x%x", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_217) {
  char one_[] = "                     "; /*ПРОБЕЛЫ*/
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%x%x%x", &a1, &b1, &c1),
                   s21_sscanf(one_, "%x%x%x", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_218) {
  char one_[] = "                         "; /*табы*/
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%x%x%x", &a1, &b1, &c1),
                   s21_sscanf(one_, "%x%x%x", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_219) {
  char one_[] = "5F5A9CE0FF\t 174876EA87FF\n 9F5AF3107A3FFF\0";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%x%x%x", &a1, &b1, &c1),
                   s21_sscanf(one_, "%x%x%x", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

/*-----------%X------------*/
START_TEST(test_s21_sscanf_221) {
  char one_[] = "-987654321 987654321 123456789";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%X%X%X", &a1, &b1, &c1),
                   s21_sscanf(one_, "%X%X%X", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_222) {
  char one_[] = "1e240 E1740 75BCD15";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%X%X%X", &a1, &b1, &c1),
                   s21_sscanf(one_, "%X%X%X", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_223) {
  char one_[] = "-1e240 -E1740 -75BCD15";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%X%X%X", &a1, &b1, &c1),
                   s21_sscanf(one_, "%X%X%X", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_224) {
  char one_[] = "5F5E0FF 174876E7FF 5AF3107A3FFF";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%X%X%X", &a1, &b1, &c1),
                   s21_sscanf(one_, "%X%X%X", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_225) {
  char one_[] = "5F5E0FF 174876E7FF 5AF3107A3FFF";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%1X%2X%3X", &a1, &b1, &c1),
                   s21_sscanf(one_, "%1X%2X%3X", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_226) {
  char one_[9999] = "5F5E0FF 174876E7FF 5AF3107A3FFF";
  /*5F5E0FF = 99999999
    174876E7FF = 99999999999
    5AF3107A3FFF = 99999999999999*/
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%11X%22X%33X", &a1, &b1, &c1),
                   s21_sscanf(one_, "%11X%22X%33X", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_227) {
  char one_[9999] = "5F5E0FF 174876E7FF 5AF3107A3FFF";
  /*5F5E0FF = 99999999
    174876E7FF = 99999999999
    5AF3107A3FFF = 99999999999999*/
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%111X%222X%333X", &a1, &b1, &c1),
                   s21_sscanf(one_, "%111X%222X%333X", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_228) {
  char one_[] = "5F5A9CE0FF 174876EA87FF 9F5AF3107A3FFF";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%X%X%X", &a1, &b1, &c1),
                   s21_sscanf(one_, "%X%X%X", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_229) {
  char one_[] = "                     "; /*ПРОБЕЛЫ*/
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%X%X%X", &a1, &b1, &c1),
                   s21_sscanf(one_, "%X%X%X", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_230) {
  char one_[] = "                         "; /*табы*/
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%X%X%X", &a1, &b1, &c1),
                   s21_sscanf(one_, "%X%X%X", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_231) {
  char one_[] = "5F5A9CE0FF\t 174876EA87FF\n 9F5AF3107A3FFF\0";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%X%X%X", &a1, &b1, &c1),
                   s21_sscanf(one_, "%X%X%X", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

/*-----------%p------------*/
START_TEST(test_s21_sscanf_232) {
  char one_[] = "0x7fff92655660 0x7a2c212sd2 0x11111111";
  void *ptr1 = NULL;
  void *ptr2 = NULL;
  void *ptrr1 = NULL;
  void *ptrr2 = NULL;
  void *ptrrr1 = NULL;
  void *ptrrr2 = NULL;

  ck_assert_int_eq(sscanf(one_, "%p%p%p", &ptr1, &ptrr1, &ptrrr1),
                   s21_sscanf(one_, "%p%p%p", &ptr2, &ptrr2, &ptrrr2));
  ck_assert_ptr_eq(ptr1, ptr2);
  ck_assert_ptr_eq(ptrr1, ptrr2);
  ck_assert_ptr_eq(ptrrr1, ptrrr2);
}
END_TEST

START_TEST(test_s21_sscanf_233) {
  char one_[] = "0x7ffcd6d35e3c 0x7ffcd6d35e3a 0x7ffcd6d35e4c";
  void *ptr1 = NULL;
  void *ptr2 = NULL;
  void *ptrr1 = NULL;
  void *ptrr2 = NULL;
  void *ptrrr1 = NULL;
  void *ptrrr2 = NULL;

  ck_assert_int_eq(sscanf(one_, "%p%p%p", &ptr1, &ptrr1, &ptrrr1),
                   s21_sscanf(one_, "%p%p%p", &ptr2, &ptrr2, &ptrrr2));
  ck_assert_ptr_eq(ptr1, ptr2);
  ck_assert_ptr_eq(ptrr1, ptrr2);
  ck_assert_ptr_eq(ptrrr1, ptrrr2);
}
END_TEST

START_TEST(test_s21_sscanf_234) {
  char one_[] = "-0x7ffcd6d35e3c 0x7ffffcdd6d35e3c 00xx7ffcd6d35e3c";
  void *ptr1 = NULL;
  void *ptr2 = NULL;
  void *ptrr1 = NULL;
  void *ptrr2 = NULL;
  void *ptrrr1 = NULL;
  void *ptrrr2 = NULL;

  ck_assert_int_eq(sscanf(one_, "%1p%2p%3p", &ptr1, &ptrr1, &ptrrr1),
                   s21_sscanf(one_, "%1p%2p%3p", &ptr2, &ptrr2, &ptrrr2));
  ck_assert_ptr_eq(ptr1, ptr2);
  ck_assert_ptr_eq(ptrr1, ptrr2);
  ck_assert_ptr_eq(ptrrr1, ptrrr2);
}
END_TEST

START_TEST(test_s21_sscanf_235) {
  char one_[] = "0x7ffcd6d35e3c\n 0x7ffcd6d35e3c\t 0x7ffcd6d35e3c\0";
  void *ptr1 = NULL;
  void *ptr2 = NULL;
  void *ptrr1 = NULL;
  void *ptrr2 = NULL;
  void *ptrrr1 = NULL;
  void *ptrrr2 = NULL;

  ck_assert_int_eq(sscanf(one_, "%p%p%p", &ptr1, &ptrr1, &ptrrr1),
                   s21_sscanf(one_, "%p%p%p", &ptr2, &ptrr2, &ptrrr2));
  ck_assert_ptr_eq(ptr1, ptr2);
  ck_assert_ptr_eq(ptrr1, ptrr2);
  ck_assert_ptr_eq(ptrrr1, ptrrr2);
}
END_TEST

START_TEST(test_s21_sscanf_236) {
  char one_[] =
      "0x7ffcd6d35e3c 0x77777777777777777ffcd6d35e3c 0.0x7ffcd6d35e3c";
  void *ptr1 = NULL;
  void *ptr2 = NULL;
  void *ptrr1 = NULL;
  void *ptrr2 = NULL;
  void *ptrrr1 = NULL;
  void *ptrrr2 = NULL;

  ck_assert_int_eq(sscanf(one_, "%p%p%p", &ptr1, &ptrr1, &ptrrr1),
                   s21_sscanf(one_, "%p%p%p", &ptr2, &ptrr2, &ptrrr2));
  ck_assert_ptr_eq(ptr1, ptr2);
  ck_assert_ptr_eq(ptrr1, ptrr2);
  ck_assert_ptr_eq(ptrrr1, ptrrr2);
}
END_TEST

START_TEST(test_s21_sscanf_237) {
  char one_[99999] =
      "0x7ffffffffffcccccccccccd6d35e3c 0x7ffcd6d35e3c 0x11111111";
  void *ptr1 = NULL;
  void *ptr2 = NULL;
  void *ptrr1 = NULL;
  void *ptrr2 = NULL;
  void *ptrrr1 = NULL;
  void *ptrrr2 = NULL;

  ck_assert_int_eq(sscanf(one_, "%11p%12p%133p", &ptr1, &ptrr1, &ptrrr1),
                   s21_sscanf(one_, "%11p%12p%133p", &ptr2, &ptrr2, &ptrrr2));
  ck_assert_ptr_eq(ptr1, ptr2);
  ck_assert_ptr_eq(ptrr1, ptrr2);
  ck_assert_ptr_eq(ptrrr1, ptrrr2);
}
END_TEST

START_TEST(test_s21_sscanf_238) {
  char one_[] = "Т0x7ffcd6d35e3c AО0x7ffcd6d35e3c А☼80x7ffcd6d35e3c";
  void *ptr1 = NULL;
  void *ptr2 = NULL;
  void *ptrr1 = NULL;
  void *ptrr2 = NULL;
  void *ptrrr1 = NULL;
  void *ptrrr2 = NULL;

  ck_assert_int_eq(sscanf(one_, "%p%p%p", &ptr1, &ptrr1, &ptrrr1),
                   s21_sscanf(one_, "%p%p%p", &ptr2, &ptrr2, &ptrrr2));
  ck_assert_ptr_eq(ptr1, ptr2);
  ck_assert_ptr_eq(ptrr1, ptrr2);
  ck_assert_ptr_eq(ptrrr1, ptrrr2);
}
END_TEST

START_TEST(test_s21_sscanf_239) {
  char one_[] = "0x7ffcd6d35e3c+1 0x7ffcd6d35e3c-1 0x7ffcd6d35e3c0";
  void *ptr1 = NULL;
  void *ptr2 = NULL;
  void *ptrr1 = NULL;
  void *ptrr2 = NULL;
  void *ptrrr1 = NULL;
  void *ptrrr2 = NULL;

  ck_assert_int_eq(sscanf(one_, "%p%p%p", &ptr1, &ptrr1, &ptrrr1),
                   s21_sscanf(one_, "%p%p%p", &ptr2, &ptrr2, &ptrrr2));
  ck_assert_ptr_eq(ptr1, ptr2);
  ck_assert_ptr_eq(ptrr1, ptrr2);
  ck_assert_ptr_eq(ptrrr1, ptrrr2);
}
END_TEST

START_TEST(test_s21_sscanf_240) {
  char one_[] = "0x7ffcd6d35e3c 0x7ffcd6d35e3c 0x1";
  void *ptr1 = NULL;
  void *ptr2 = NULL;
  void *ptrr1 = NULL;
  void *ptrr2 = NULL;
  void *ptrrr1 = NULL;
  void *ptrrr2 = NULL;

  ck_assert_int_eq(sscanf(one_, "%p%p%p", &ptr1, &ptrr1, &ptrrr1),
                   s21_sscanf(one_, "%p%p%p", &ptr2, &ptrr2, &ptrrr2));
  ck_assert_ptr_eq(ptr1, ptr2);
  ck_assert_ptr_eq(ptrr1, ptrr2);
  ck_assert_ptr_eq(ptrrr1, ptrrr2);
}
END_TEST

START_TEST(test_s21_sscanf_241) {
  char one_[] = "0x7ffcd6d35e3c 0x7a2 0x11";
  void *ptr1 = NULL;
  void *ptr2 = NULL;
  void *ptrr1 = NULL;
  void *ptrr2 = NULL;
  void *ptrrr1 = NULL;
  void *ptrrr2 = NULL;

  ck_assert_int_eq(sscanf(one_, "%p%p%p", &ptr1, &ptrr1, &ptrrr1),
                   s21_sscanf(one_, "%p%p%p", &ptr2, &ptrr2, &ptrrr2));
  ck_assert_ptr_eq(ptr1, ptr2);
  ck_assert_ptr_eq(ptrr1, ptrr2);
  ck_assert_ptr_eq(ptrrr1, ptrrr2);
}
END_TEST

START_TEST(test_s21_sscanf_242) {
  char one_[] = "0x7ffcd6d35e3c 0x7ffcd6d35e3c 0x7ffcd6d35e3c";
  void *ptr1 = NULL;
  void *ptr2 = NULL;
  void *ptrr1 = NULL;
  void *ptrr2 = NULL;
  void *ptrrr1 = NULL;
  void *ptrrr2 = NULL;

  ck_assert_int_eq(sscanf(one_, "%p%p%p", &ptr1, &ptrr1, &ptrrr1),
                   s21_sscanf(one_, "%p%p%p", &ptr2, &ptrr2, &ptrrr2));
  ck_assert_ptr_eq(ptr1, ptr2);
  ck_assert_ptr_eq(ptrr1, ptrr2);
  ck_assert_ptr_eq(ptrrr1, ptrrr2);
}
END_TEST

/*-----------%n------------*/
START_TEST(test_s21_sscanf_243) {
  char one_[] = "5F5A9CE0FF\n\n\n\n 174876EA87FF\n 9F5AF3107A3FFF\0";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%n%n%n", &a1, &b1, &c1),
                   s21_sscanf(one_, "%n%n%n", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_244) {
  char one_[] = "a1b2c3\n 1d2r3t\n -0\n";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%n%n%n", &a1, &b1, &c1),
                   s21_sscanf(one_, "%n%n%n", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_245) {
  char one_[] = "EOF \n 1";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%n%n%n", &a1, &b1, &c1),
                   s21_sscanf(one_, "%n%n%n", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_246) {
  char one_[] = "1111122222EOF\n \n\n 1222222222222222222222222222222222\n";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%n%n%n", &a1, &b1, &c1),
                   s21_sscanf(one_, "%n%n%n", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_247) {
  char one_[] = "sssssssssssssssss\n s\n ssssssssssssssssssssssssssssssssss\n";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%n%n%n", &a1, &b1, &c1),
                   s21_sscanf(one_, "%n%n%n", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_248) {
  char one_[9999] = "                   \n  \n                      \n";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%n%n%n", &a1, &b1, &c1),
                   s21_sscanf(one_, "%n%n%n", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_249) {
  char one_[] = "123 \n  321\n                      1111\n";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%n%n%n", &a1, &b1, &c1),
                   s21_sscanf(one_, "%n%n%n", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_250) {
  char one_[] = "0.00000000000\n  000.001\n                      \n";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%n%n%n", &a1, &b1, &c1),
                   s21_sscanf(one_, "%n%n%n", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

/*-----------%%------------*/
START_TEST(test_s21_sscanf_251) {
  char one_[] = "0.00000000000\n  000.001\n                      \n";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%d%%%d%%%d%%", &a1, &b1, &c1),
                   s21_sscanf(one_, "%d%%%d%%%d%%", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_252) {
  char one_[999] = "123 321 999";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%d%%%d%%%d%%", &a1, &b1, &c1),
                   s21_sscanf(one_, "%d%%%d%%%d%%", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_253) {
  char one_[] = "\n \t EOF";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%E%%%E%%%E%%", &a1, &b1, &c1),
                   s21_sscanf(one_, "%E%%%E%%%E%%", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_254) {
  char one_[] = "0.32767%32767 −000.327673%2767 0000000.%3276732767%";
  short int a1 = 0;
  short int b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%hd%%%hd%%%hd%%", &a1, &b1, &c1),
                   s21_sscanf(one_, "%hd%%%hd%%%hd%%", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_255) {
  char one_[] = "0000000032767% −%0000%000000032767 %000000000.32767%";
  short int a1 = 0;
  short int b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%hi%%%hi%%%hi%%", &a1, &b1, &c1),
                   s21_sscanf(one_, "%hi%%%hi%%%hi%%", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_256) {
  char str[100] = "ч x0╝ ";
  char c1 = '0';
  char d1 = '0';
  char e1 = '0';
  char c2 = '0';
  char d2 = '0';
  char e2 = '0';
  ck_assert_int_eq(sscanf(str, "%c%%%c%%%c%%", &c1, &d1, &e1),
                   s21_sscanf(str, "%c%%%c%%%c%%", &c2, &d2, &e2));
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(e1, e2);
}
END_TEST

START_TEST(test_s21_sscanf_257) {
  char one_[] = " .  .  .";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%5d%%%5d%%%5d%%", &a1, &b1, &c1),
                   s21_sscanf(one_, "%5d%%%5d%%%5d%%", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_258) {
  char one_[999] = "0.00 1.002 0.002 .003 0.003.0 04";
  long double a1 = 0;
  long double b1 = 0;
  long double c1 = 0;
  long double a2 = 0;
  long double b2 = 0;
  long double c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%LE%%%LE%%%LE%%", &a1, &b1, &c1),
                   s21_sscanf(one_, "%LE%%%LE%%%LE%%", &a2, &b2, &c2));
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_259) {
  char one_[111] = "strok%a esh%estr%ok%a ieshe%stroch%%ka";
  char a1[111] = {0};
  char b1[111] = {0};
  char c1[111] = {0};
  char a2[111] = {0};
  char b2[111] = {0};
  char c2[111] = {0};
  ck_assert_int_eq(sscanf(one_, "%3s%%%3s%%%3s%%", a1, b1, c1),
                   s21_sscanf(one_, "%3s%%%3s%%%3s%%", a2, b2, c2));
  ck_assert_str_eq(a1, a2);
  ck_assert_str_eq(b1, b2);
  ck_assert_str_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_260) {
  char one_[999] = "-3.4e%";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%g%%%g%%%g%%", &a1, &b1, &c1),
                   s21_sscanf(one_, "%g%%%g%%%g%%", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

/*-----------%c %d %i %e %E %f %g %G %o %s %u %lf %x %X %p %n %%------------*/
START_TEST(test_s21_sscanf_261) {
  char one_[] =
      "char 123 321 1.12 2.2222 33.3333 4.44 5.55 222 stroka 444 5.55 666 777 "
      "0xF213ffff23 132\n";
  char c1;
  char c2;
  int a1 = 0;
  int a2 = 0;
  int i1 = 0;
  int i2 = 0;
  float e1 = 0;
  float e2 = 0;
  float E1 = 0;
  float E2 = 0;
  float f1 = 0;
  float f2 = 0;
  float g1 = 0;
  float g2 = 0;
  float G1 = 0;
  float G2 = 0;
  unsigned int o1 = 0;
  unsigned int o2 = 0;
  char s1[1111] = {0};
  char s2[1111] = {0};
  unsigned int u1 = 0;
  unsigned int u2 = 0;
  double lf1 = 0;
  double lf2 = 0;
  unsigned int x1 = 0;
  unsigned int x2 = 0;
  unsigned int X1 = 0;
  unsigned int X2 = 0;
  void *ptr1 = NULL;
  void *ptr2 = NULL;
  int n1 = 0;
  int n2 = 0;

  ck_assert_int_eq(
      sscanf(one_,
             "%c, %d, %i, %e, %E, %f, %g, %G, %o, %1s, %u, %lf, %x, %X, %p, %n",
             &c1, &a1, &i1, &e1, &E2, &f1, &g1, &G1, &o1, s1, &u1, &lf1, &x1,
             &X1, &ptr1, &n1),
      s21_sscanf(
          one_,
          "%c, %a, %i, %e, %E, %f, %g, %G, %o, %1s, %u, %lf, %x, %X, %p, %n",
          &c2, &a2, &i2, &e2, &E2, &f2, &g2, &G2, &o2, s2, &u2, &lf2, &x2, &X2,
          &ptr2, &n2));
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(i1, i2);
  ck_assert_float_eq(e1, e2);
  ck_assert_float_eq(E1, E2);
  ck_assert_float_eq(f1, f2);
  ck_assert_float_eq(g1, g2);
  ck_assert_float_eq(G1, G2);
  ck_assert_int_eq(o1, o2);
  ck_assert_str_eq(s1, s2);
  ck_assert_int_eq(u1, u2);
  ck_assert_double_eq(lf1, lf2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_ptr_eq(ptr1, ptr2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

/*-------------------*/
START_TEST(test_s21_sscanf_262) {
  char one_[] = "111111111 2222222222222222 asd";
  unsigned long int a1 = 0;
  unsigned long int b1 = 0;
  unsigned long int c1 = 0;
  unsigned long int a2 = 0;
  unsigned long int b2 = 0;
  unsigned long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%lu%lu%lu", &a1, &b1, &c1),
                   s21_sscanf(one_, "%lu%lu%lu", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_263) {
  char one_[] = "111111111 2222222222222222 asd";
  unsigned short int a1 = 0;
  unsigned short int b1 = 0;
  unsigned short int c1 = 0;
  unsigned short int a2 = 0;
  unsigned short int b2 = 0;
  unsigned short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%hu%hu%hu", &a1, &b1, &c1),
                   s21_sscanf(one_, "%hu%hu%hu", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_264) {
  char one_[] = "111111111 2222222222222222 asd";
  unsigned long long int a1 = 0;
  unsigned long long int b1 = 0;
  unsigned long long int c1 = 0;
  unsigned long long int a2 = 0;
  unsigned long long int b2 = 0;
  unsigned long long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%llu%llu%llu", &a1, &b1, &c1),
                   s21_sscanf(one_, "%llu%llu%llu", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_265) {
  char one_[99999] = "123 321 asd";
  unsigned short int a1 = 0;
  unsigned short int b1 = 0;
  unsigned short int c1 = 0;
  unsigned short int a2 = 0;
  unsigned short int b2 = 0;
  unsigned short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%ho%ho%ho", &a1, &b1, &c1),
                   s21_sscanf(one_, "%ho%ho%ho", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_266) {
  char one_[99999] = "123 321 asd";
  unsigned long int a1 = 0;
  unsigned long int b1 = 0;
  unsigned long int c1 = 0;
  unsigned long int a2 = 0;
  unsigned long int b2 = 0;
  unsigned long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%lo%lo%lo", &a1, &b1, &c1),
                   s21_sscanf(one_, "%lo%lo%lo", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_267) {
  char one_[99999] = "123 321 asd";
  unsigned long long int a1 = 0;
  unsigned long long int b1 = 0;
  unsigned long long int c1 = 0;
  unsigned long long int a2 = 0;
  unsigned long long int b2 = 0;
  unsigned long long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%llo%llo%llo", &a1, &b1, &c1),
                   s21_sscanf(one_, "%llo%llo%llo", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_268) {
  char one_[99999] = "123 321 qq";
  unsigned short int a1 = 0;
  unsigned short int b1 = 0;
  unsigned short int c1 = 0;
  unsigned short int a2 = 0;
  unsigned short int b2 = 0;
  unsigned short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%hx%hx%hx", &a1, &b1, &c1),
                   s21_sscanf(one_, "%hx%hx%hx", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_269) {
  char one_[99999] = "123 321 qq";
  unsigned long int a1 = 0;
  unsigned long int b1 = 0;
  unsigned long int c1 = 0;
  unsigned long int a2 = 0;
  unsigned long int b2 = 0;
  unsigned long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%lx%lx%lx", &a1, &b1, &c1),
                   s21_sscanf(one_, "%lx%lx%lx", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_270) {
  char one_[99999] = "123 321 qq";
  unsigned long long int a1 = 0;
  unsigned long long int b1 = 0;
  unsigned long long int c1 = 0;
  unsigned long long int a2 = 0;
  unsigned long long int b2 = 0;
  unsigned long long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%llx%llx%llx", &a1, &b1, &c1),
                   s21_sscanf(one_, "%llx%llx%llx", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_271) {
  char one_[99999] = "123 321 asd";
  unsigned short int a1 = 0;
  unsigned short int b1 = 0;
  unsigned short int c1 = 0;
  unsigned short int a2 = 0;
  unsigned short int b2 = 0;
  unsigned short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%hX%hX%hX", &a1, &b1, &c1),
                   s21_sscanf(one_, "%hX%hX%hX", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_272) {
  char one_[99999] = "123 321 asd";
  unsigned long int a1 = 0;
  unsigned long int b1 = 0;
  unsigned long int c1 = 0;
  unsigned long int a2 = 0;
  unsigned long int b2 = 0;
  unsigned long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%lX%lX%lX", &a1, &b1, &c1),
                   s21_sscanf(one_, "%lX%lX%lX", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_273) {
  char one_[99999] = "123 321 asd";
  unsigned long long int a1 = 0;
  unsigned long long int b1 = 0;
  unsigned long long int c1 = 0;
  unsigned long long int a2 = 0;
  unsigned long long int b2 = 0;
  unsigned long long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%llX%llX%llX", &a1, &b1, &c1),
                   s21_sscanf(one_, "%llX%llX%llX", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_274) {
  char one_[] = "123 321 asd";
  short int a1 = 0;
  signed char b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  signed char b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%hn%hhn%hn", &a1, &b1, &c1),
                   s21_sscanf(one_, "%hn%hhn%hn", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_275) {
  char one_[] = "123 321 asd";
  short int a1 = 0;
  short int b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%hn%hn%hn", &a1, &b1, &c1),
                   s21_sscanf(one_, "%hn%hn%hn", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_276) {
  char one_[] = "123 321 asd";
  long int a1 = 0;
  long int b1 = 0;
  long int c1 = 0;
  long int a2 = 0;
  long int b2 = 0;
  long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%ln%ln%ln", &a1, &b1, &c1),
                   s21_sscanf(one_, "%ln%ln%ln", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_277) {
  char one_[] = "123 321 asd";
  long long int a1 = 0;
  long long int b1 = 0;
  long long int c1 = 0;
  long long int a2 = 0;
  long long int b2 = 0;
  long long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%lln%lln%lln", &a1, &b1, &c1),
                   s21_sscanf(one_, "%lln%lln%lln", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_278) {
  char one_[] = "123 321 asd";
  short int a1 = 0;
  short int b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%hi%hi%hi", &a1, &b1, &c1),
                   s21_sscanf(one_, "%hi%hi%hi", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_279) {
  char one_[] = "123 321 asd";
  long int a1 = 0;
  long int b1 = 0;
  long int c1 = 0;
  long int a2 = 0;
  long int b2 = 0;
  long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%li%li%li", &a1, &b1, &c1),
                   s21_sscanf(one_, "%li%li%li", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_280) {
  char one_[] = "123 321 asd";
  long long int a1 = 0;
  long long int b1 = 0;
  long long int c1 = 0;
  long long int a2 = 0;
  long long int b2 = 0;
  long long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%lli%lli%lli", &a1, &b1, &c1),
                   s21_sscanf(one_, "%lli%lli%lli", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_281) {
  char one_[] = "  ' ' \t \n \0";
  char c1;
  char c2;
  int a1 = 0;
  int a2 = 0;
  int i1 = 0;
  int i2 = 0;
  float e1 = 0;
  float e2 = 0;
  float E1 = 0;
  float E2 = 0;
  float f1 = 0;
  float f2 = 0;
  float g1 = 0;
  float g2 = 0;
  float G1 = 0;
  float G2 = 0;
  unsigned int o1 = 0;
  unsigned int o2 = 0;
  char s1[1111] = {0};
  char s2[1111] = {0};
  unsigned int u1 = 0;
  unsigned int u2 = 0;
  double lf1 = 0;
  double lf2 = 0;
  unsigned int x1 = 0;
  unsigned int x2 = 0;
  unsigned int X1 = 0;
  unsigned int X2 = 0;
  void *ptr1 = NULL;
  void *ptr2 = NULL;
  int n1 = 0;
  int n2 = 0;

  ck_assert_int_eq(
      sscanf(one_,
             "%c, %d, %i, %e, %E, %f, %g, %G, %o, %1s, %u, %lf, %x, %X, %p, %n",
             &c1, &a1, &i1, &e1, &E2, &f1, &g1, &G1, &o1, s1, &u1, &lf1, &x1,
             &X1, &ptr1, &n1),
      s21_sscanf(
          one_,
          "%c, %a, %i, %e, %E, %f, %g, %G, %o, %1s, %u, %lf, %x, %X, %p, %n",
          &c2, &a2, &i2, &e2, &E2, &f2, &g2, &G2, &o2, s2, &u2, &lf2, &x2, &X2,
          &ptr2, &n2));
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(i1, i2);
  ck_assert_float_eq(e1, e2);
  ck_assert_float_eq(E1, E2);
  ck_assert_float_eq(f1, f2);
  ck_assert_float_eq(g1, g2);
  ck_assert_float_eq(G1, G2);
  ck_assert_int_eq(o1, o2);
  ck_assert_str_eq(s1, s2);
  ck_assert_int_eq(u1, u2);
  ck_assert_double_eq(lf1, lf2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_ptr_eq(ptr1, ptr2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(test_s21_sscanf_282) {
  char one_[] = "123 321 999";
  short int a1 = 0;
  short int b1 = 0;
  short int c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  short int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%hd%%%hd%%%hd%%", &a1, &b1, &c1),
                   s21_sscanf(one_, "%hd%%%hd%%%hd%%", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_283) {
  char one_[] = "123 321 999";
  long int a1 = 0;
  long int b1 = 0;
  long int c1 = 0;
  long int a2 = 0;
  long int b2 = 0;
  long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%ld%%%ld%%%ld%%", &a1, &b1, &c1),
                   s21_sscanf(one_, "%ld%%%ld%%%ld%%", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_284) {
  char one_[] = "123 321 999";
  long long int a1 = 0;
  long long int b1 = 0;
  long long int c1 = 0;
  long long int a2 = 0;
  long long int b2 = 0;
  long long int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%lld%%%lld%%%lld%%", &a1, &b1, &c1),
                   s21_sscanf(one_, "%lld%%%lld%%%lld%%", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_285) {
  char one_[] = "113.40282347e+38 111.17549435e-38 1111b111";
  long double a1 = 0;
  long double b1 = 0;
  long double c1 = 0;
  long double a2 = 0;
  long double b2 = 0;
  long double c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%Lf%Lf%Lf", &a1, &b1, &c1),
                   s21_sscanf(one_, "%Lf%Lf%Lf", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_286) {
  char one_[] = "  ' ' \t \n \0";
  int d_d1 = 0;
  int d_d2 = 0;
  int a1 = 0;
  int a2 = 0;
  int i1 = 0;
  int i2 = 0;
  float e1 = 0;
  float e2 = 0;
  float E1 = 0;
  float E2 = 0;
  float f1 = 0;
  float f2 = 0;
  float g1 = 0;
  float g2 = 0;
  float G1 = 0;
  float G2 = 0;
  unsigned int o1 = 0;
  unsigned int o2 = 0;
  char s1[1111] = {0};
  char s2[1111] = {0};
  unsigned int u1 = 0;
  unsigned int u2 = 0;
  double lf1 = 0;
  double lf2 = 0;
  unsigned int x1 = 0;
  unsigned int x2 = 0;
  unsigned int X1 = 0;
  unsigned int X2 = 0;
  void *ptr1 = NULL;
  void *ptr2 = NULL;
  int n1 = 0;
  int n2 = 0;
  char c1;
  char c2;

  ck_assert_int_eq(sscanf(one_,
                          "%d, %c, %d, %i, %e, %E, %f, %g, %G, %o, %1s, %u, "
                          "%lf, %x, %X, %p, %n",
                          &d_d1, &c1, &a1, &i1, &e1, &E2, &f1, &g1, &G1, &o1,
                          s1, &u1, &lf1, &x1, &X1, &ptr1, &n1),
                   s21_sscanf(one_,
                              "%d, %c, %d, %i, %e, %E, %f, %g, %G, %o, %1s, "
                              "%u, %lf, %x, %X, %p, %n",
                              &d_d2, &c2, &a2, &i2, &e2, &E2, &f2, &g2, &G2,
                              &o2, s2, &u2, &lf2, &x2, &X2, &ptr2, &n2));
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(i1, i2);
  ck_assert_float_eq(e1, e2);
  ck_assert_float_eq(E1, E2);
  ck_assert_float_eq(f1, f2);
  ck_assert_float_eq(g1, g2);
  ck_assert_float_eq(G1, G2);
  ck_assert_int_eq(o1, o2);
  ck_assert_str_eq(s1, s2);
  ck_assert_int_eq(u1, u2);
  ck_assert_double_eq(lf1, lf2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_ptr_eq(ptr1, ptr2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(test_s21_sscanf_287) {
  char one_[] = "  ' ' \t \n \0";
  int d_d1 = 0;
  int d_d2 = 0;
  short int a1 = 0;
  short int a2 = 0;
  short int i1 = 0;
  short int i2 = 0;
  long double e1 = 0;
  long double e2 = 0;
  long double E1 = 0;
  long double E2 = 0;
  long double f1 = 0;
  long double f2 = 0;
  long double g1 = 0;
  long double g2 = 0;
  long double G1 = 0;
  long double G2 = 0;
  unsigned short int o1 = 0;
  unsigned short int o2 = 0;
  char s1[1111] = {0};
  char s2[1111] = {0};
  unsigned short int u1 = 0;
  unsigned short int u2 = 0;
  double lf1 = 0;
  double lf2 = 0;
  unsigned short int x1 = 0;
  unsigned short int x2 = 0;
  unsigned short int X1 = 0;
  unsigned short int X2 = 0;
  void *ptr1 = NULL;
  void *ptr2 = NULL;
  short int n1 = 0;
  short int n2 = 0;
  char c1;
  char c2;

  ck_assert_int_eq(
      sscanf(one_,
             "%d, %c, %hd, %hi, %Le, %LE, %Lf, %Lg, %LG, %ho, %1s, %hu, "
             "%lf, %hx, %hX, %p, %hn",
             &d_d1, &c1, &a1, &i1, &e1, &E1, &f1, &g1, &G1, &o1, s1, &u1, &lf1,
             &x1, &X1, &ptr1, &n1),
      s21_sscanf(one_,
                 "%d, %c, %hd, %hi, %Le, %LE, %Lf, %Lg, %LG, %ho, %1s, "
                 "%hu, %lf, %hx, %hX, %p, %hn",
                 &d_d2, &c2, &a2, &i2, &e2, &E2, &f2, &g2, &G2, &o2, s2, &u2,
                 &lf2, &x2, &X2, &ptr2, &n2));
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(i1, i2);
  ck_assert_float_eq(e1, e2);
  ck_assert_float_eq(E1, E2);
  ck_assert_float_eq(f1, f2);
  ck_assert_float_eq(g1, g2);
  ck_assert_float_eq(G1, G2);
  ck_assert_int_eq(o1, o2);
  ck_assert_str_eq(s1, s2);
  ck_assert_int_eq(u1, u2);
  ck_assert_double_eq(lf1, lf2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_ptr_eq(ptr1, ptr2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(test_s21_sscanf_288) {
  char one_[99] = "10\0asd dsa";
  char a1 = 0;
  char a2 = 0;
  int b1 = 0;
  int b2 = 0;
  ck_assert_int_eq(sscanf(one_, "%d%c", &b1, &a1),
                   s21_sscanf(one_, "%d%c", &b2, &a2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sscanf_289) {
  char one_[999] = "10\0asd dsa";
  char a1[999] = {0};
  char a2[999] = {0};
  int b1 = 0;
  int b2 = 0;
  ck_assert_int_eq(sscanf(one_, "%d%1s", &b1, a1),
                   s21_sscanf(one_, "%d%1s", &b2, a2));
  ck_assert_str_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sscanf_290) {
  char one_[9999] = "' '  \t \n1";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "' '  \t \n%d%d%d", &a1, &b1, &c1),
                   s21_sscanf(one_, "' '  \t \n%d%d%d", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_291) {
  char one_[9999] = "INF inf S21_INFINITY";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%f%f%f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%f%f%f", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_292) {
  char one_[9999] = "INF inf INNA";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%f%f%f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%f%f%f", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_293) {
  char one_[9999] = "nan NAN NAiANA";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%f%f%f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%f%f%f", &a2, &b2, &c2));
  ck_assert_float_ne(a1, a2);
  ck_assert_float_ne(a1, a1);
  ck_assert_float_ne(a2, a2);
  ck_assert_float_ne(b1, b2);
  ck_assert_float_ne(b1, b1);
  ck_assert_float_ne(b2, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_295) {
  char one_[9999] = "-nan -NAN -NAiANA";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%f%f%f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%f%f%f", &a2, &b2, &c2));
  ck_assert_float_ne(a1, a2);
  ck_assert_float_ne(a1, a1);
  ck_assert_float_ne(a2, a2);
  ck_assert_float_ne(b1, b2);
  ck_assert_float_ne(b1, b1);
  ck_assert_float_ne(b2, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_294) {
  char one_[9999] = "-INF -inf -S21_INFINITY";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%f%f%f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%f%f%f", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_296) {
  char one_[9999] = "IF -IF Ni";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%f%f%f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%f%f%f", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_297) {
  char one_[9999] = "-if IF -nim";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%f%f%f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%f%f%f", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_298) {
  char one_[9999] = "123 N n -N";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%*f%f%f%f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%*f%f%f%f", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_299) {
  char one_[9999] = "1  2   3";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%f %f %f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%f %f %f", &a2, &b2, &c2));
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_300) {
  char one_[] = "+123 999 -321 *asd";
  short int a1 = 0;
  short int b1 = 0;
  signed char c1 = 0;
  short int a2 = 0;
  short int b2 = 0;
  signed char c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%hi%*i%hi%hhi", &a1, &b1, &c1),
                   s21_sscanf(one_, "%hi%*i%hi%hhi", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_301) {
  char one_[] = "0x7ffcd6d35e3c 0x000cd6d35e3c -0x7FF123 +0x6BAFF987";
  void *ptr1 = NULL;
  void *ptr2 = NULL;
  void *ptrr1 = NULL;
  void *ptrr2 = NULL;
  void *ptrrr1 = NULL;
  void *ptrrr2 = NULL;

  ck_assert_int_eq(sscanf(one_, "%*p%p%p%p", &ptr1, &ptrr1, &ptrrr1),
                   s21_sscanf(one_, "%*p%p%p%p", &ptr2, &ptrr2, &ptrrr2));
  ck_assert_ptr_eq(ptr1, ptr2);
  ck_assert_ptr_eq(ptrr1, ptrr2);
  ck_assert_ptr_eq(ptrrr1, ptrrr2);
}
END_TEST

START_TEST(test_s21_sscanf_302) {
  char one_[] = "0x7ffcd6d35e3c 0x000cd6d35e3c -0x7FF123 +0x6BAFF987";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  unsigned char d1 = 0;
  unsigned char d2 = 0;
  ck_assert_int_eq(sscanf(one_, "%*X%X%X%X%hhx", &a1, &b1, &c1, &d1),
                   s21_sscanf(one_, "%*X%X%X%X%hhx", &a2, &b2, &c2, &d2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_303) {
  char one_[9999] = "013 345 -01234 +12345";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  unsigned char d1 = 0;
  unsigned char d2 = 0;
  ck_assert_int_eq(sscanf(one_, "%*o%o%o%o%hho", &a1, &b1, &c1, &d1),
                   s21_sscanf(one_, "%*o%o%o%o%hho", &a2, &b2, &c2, &d2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_304) {
  char one_[9999] = "013 345 -01234 +12345";
  unsigned int a1 = 0;
  unsigned int b1 = 0;
  unsigned int c1 = 0;
  unsigned int a2 = 0;
  unsigned int b2 = 0;
  unsigned int c2 = 0;
  unsigned char d1 = 0;
  unsigned char d2 = 0;
  ck_assert_int_eq(sscanf(one_, "%*u%u%u%u%hhu", &a1, &b1, &c1, &d1),
                   s21_sscanf(one_, "%*u%u%u%u%hhu", &a2, &b2, &c2, &d2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_305) {
  char one_[] = "-123 +321 987 00456";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  signed char d1 = 0;
  signed char d2 = 0;
  ck_assert_int_eq(sscanf(one_, "%*d%d%d%d%hhd", &a1, &b1, &c1, &d1),
                   s21_sscanf(one_, "%*d%d%d%d%hhd", &a2, &b2, &c2, &d2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_306) {
  char str[100] = "asd dsa 123";
  char c1;
  char d1;
  char e1;
  char c2;
  char d2;
  char e2;
  ck_assert_int_eq(sscanf(str, "%*c%c%c%c", &c1, &d1, &e1),
                   s21_sscanf(str, "%*c%c%c%c", &c2, &d2, &e2));
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(e1, e2);
}
END_TEST

START_TEST(test_s21_sscanf_307) {
  char one_[] = "9223372036 -9223372 -asd";
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%d%d%d", &a1, &b1, &c1),
                   s21_sscanf(one_, "%d%d%d", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_s21_sscanf_308) {
  char one_[] = "9.50282347e+3999 3.40282347e+38 -9.50282347e+3999";
  float a1 = 0;
  float b1 = 0;
  float c1 = 0;
  float a2 = 0;
  float b2 = 0;
  float c2 = 0;
  ck_assert_int_eq(sscanf(one_, "%f%f%f", &a1, &b1, &c1),
                   s21_sscanf(one_, "%f%f%f", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("All");
  TCase *tc1_1 = tcase_create("All");
  SRunner *sr = srunner_create(s1);
  int qs;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, s21_memchrTest);
  tcase_add_test(tc1_1, s21_memcmpTest);
  tcase_add_test(tc1_1, s21_memsetTest);
  tcase_add_test(tc1_1, s21_memcpyTest);
  tcase_add_test(tc1_1, s21_strncatTest);
  tcase_add_test(tc1_1, s21_strchrTest);
  tcase_add_test(tc1_1, s21_strncmpTest);
  tcase_add_test(tc1_1, s21_strncpyTest);
  tcase_add_test(tc1_1, s21_strcspnTest);
  tcase_add_test(tc1_1, s21_strerrorTest);
  tcase_add_test(tc1_1, s21_strlenTest);
  tcase_add_test(tc1_1, s21_strpbrkTest);
  tcase_add_test(tc1_1, s21_strrchrTest);
  tcase_add_test(tc1_1, s21_strstrTest);
  tcase_add_test(tc1_1, s21_strtokTest);
  tcase_add_test(tc1_1, s21_to_upperTest);
  tcase_add_test(tc1_1, s21_to_lowerTest);
  tcase_add_test(tc1_1, s21_insertTest);
  tcase_add_test(tc1_1, s21_trimTest);
  tcase_add_test(tc1_1, s21_sprintfTest);
  tcase_add_test(tc1_1, s21_strcatTest);
  tcase_add_test(tc1_1, s21_strcpyTest);
  /*-----------%c------------*/
  tcase_add_test(tc1_1, test_s21_sscanf);
  tcase_add_test(tc1_1, test_s21_sscanf_2);
  tcase_add_test(tc1_1, test_s21_sscanf_3);
  tcase_add_test(tc1_1, test_s21_sscanf_4);
  tcase_add_test(tc1_1, test_s21_sscanf_5);
  tcase_add_test(tc1_1, test_s21_sscanf_6);
  tcase_add_test(tc1_1, test_s21_sscanf_7);
  tcase_add_test(tc1_1, test_s21_sscanf_8);
  tcase_add_test(tc1_1, test_s21_sscanf_9);
  tcase_add_test(tc1_1, test_s21_sscanf_10);
  tcase_add_test(tc1_1, test_s21_sscanf_11);
  tcase_add_test(tc1_1, test_s21_sscanf_12);
  tcase_add_test(tc1_1, test_s21_sscanf_13);
  tcase_add_test(tc1_1, test_s21_sscanf_14);
  tcase_add_test(tc1_1, test_s21_sscanf_15);
  /*-----------%d------------*/
  tcase_add_test(tc1_1, test_s21_sscanf_16);
  tcase_add_test(tc1_1, test_s21_sscanf_17);
  tcase_add_test(tc1_1, test_s21_sscanf_18);
  tcase_add_test(tc1_1, test_s21_sscanf_19);
  tcase_add_test(tc1_1, test_s21_sscanf_20);
  tcase_add_test(tc1_1, test_s21_sscanf_21);
  tcase_add_test(tc1_1, test_s21_sscanf_22);
  tcase_add_test(tc1_1, test_s21_sscanf_23);
  tcase_add_test(tc1_1, test_s21_sscanf_24);
  tcase_add_test(tc1_1, test_s21_sscanf_25);
  tcase_add_test(tc1_1, test_s21_sscanf_26);
  tcase_add_test(tc1_1, test_s21_sscanf_27);
  tcase_add_test(tc1_1, test_s21_sscanf_28);
  tcase_add_test(tc1_1, test_s21_sscanf_29);
  tcase_add_test(tc1_1, test_s21_sscanf_30);
  tcase_add_test(tc1_1, test_s21_sscanf_31);
  tcase_add_test(tc1_1, test_s21_sscanf_32);
  tcase_add_test(tc1_1, test_s21_sscanf_33);
  /*-----------%ld------------*/
  tcase_add_test(tc1_1, test_s21_sscanf_34);
  tcase_add_test(tc1_1, test_s21_sscanf_35);
  tcase_add_test(tc1_1, test_s21_sscanf_36);
  tcase_add_test(tc1_1, test_s21_sscanf_37);
  tcase_add_test(tc1_1, test_s21_sscanf_38);
  tcase_add_test(tc1_1, test_s21_sscanf_39);
  tcase_add_test(tc1_1, test_s21_sscanf_40);
  tcase_add_test(tc1_1, test_s21_sscanf_41);
  tcase_add_test(tc1_1, test_s21_sscanf_42);
  tcase_add_test(tc1_1, test_s21_sscanf_43);
  /*-----------%lld------------*/
  tcase_add_test(tc1_1, test_s21_sscanf_44);
  tcase_add_test(tc1_1, test_s21_sscanf_45);
  tcase_add_test(tc1_1, test_s21_sscanf_46);
  tcase_add_test(tc1_1, test_s21_sscanf_47);
  tcase_add_test(tc1_1, test_s21_sscanf_48);
  tcase_add_test(tc1_1, test_s21_sscanf_49);
  tcase_add_test(tc1_1, test_s21_sscanf_50);
  tcase_add_test(tc1_1, test_s21_sscanf_51);
  tcase_add_test(tc1_1, test_s21_sscanf_52);
  tcase_add_test(tc1_1, test_s21_sscanf_53);
  /*-----------%hi-%hd------------*/
  tcase_add_test(tc1_1, test_s21_sscanf_54);
  tcase_add_test(tc1_1, test_s21_sscanf_55);
  tcase_add_test(tc1_1, test_s21_sscanf_56);
  tcase_add_test(tc1_1, test_s21_sscanf_57);
  tcase_add_test(tc1_1, test_s21_sscanf_58);
  tcase_add_test(tc1_1, test_s21_sscanf_59);
  tcase_add_test(tc1_1, test_s21_sscanf_60);
  tcase_add_test(tc1_1, test_s21_sscanf_61);
  tcase_add_test(tc1_1, test_s21_sscanf_62);
  tcase_add_test(tc1_1, test_s21_sscanf_63);
  tcase_add_test(tc1_1, test_s21_sscanf_64);
  tcase_add_test(tc1_1, test_s21_sscanf_65);
  tcase_add_test(tc1_1, test_s21_sscanf_66);
  tcase_add_test(tc1_1, test_s21_sscanf_67);
  tcase_add_test(tc1_1, test_s21_sscanf_68);
  tcase_add_test(tc1_1, test_s21_sscanf_69);
  tcase_add_test(tc1_1, test_s21_sscanf_70);
  tcase_add_test(tc1_1, test_s21_sscanf_71);
  /*-----------%f------------*/
  tcase_add_test(tc1_1, test_s21_sscanf_72);
  tcase_add_test(tc1_1, test_s21_sscanf_73);
  tcase_add_test(tc1_1, test_s21_sscanf_74);
  tcase_add_test(tc1_1, test_s21_sscanf_75);
  // tcase_add_test(tc1_1, test_s21_sscanf_76);
  tcase_add_test(tc1_1, test_s21_sscanf_77);
  tcase_add_test(tc1_1, test_s21_sscanf_78);
  tcase_add_test(tc1_1, test_s21_sscanf_79);
  tcase_add_test(tc1_1, test_s21_sscanf_80);
  tcase_add_test(tc1_1, test_s21_sscanf_81);
  tcase_add_test(tc1_1, test_s21_sscanf_82);
  tcase_add_test(tc1_1, test_s21_sscanf_83);
  tcase_add_test(tc1_1, test_s21_sscanf_84);
  tcase_add_test(tc1_1, test_s21_sscanf_85);
  tcase_add_test(tc1_1, test_s21_sscanf_86);
  tcase_add_test(tc1_1, test_s21_sscanf_87);
  tcase_add_test(tc1_1, test_s21_sscanf_88);
  /*-----------%i------------*/
  tcase_add_test(tc1_1, test_s21_sscanf_89);
  tcase_add_test(tc1_1, test_s21_sscanf_90);
  tcase_add_test(tc1_1, test_s21_sscanf_91);
  tcase_add_test(tc1_1, test_s21_sscanf_92);
  tcase_add_test(tc1_1, test_s21_sscanf_93);
  tcase_add_test(tc1_1, test_s21_sscanf_94);
  tcase_add_test(tc1_1, test_s21_sscanf_95);
  /*-----------%e------------*/
  tcase_add_test(tc1_1, test_s21_sscanf_96);
  tcase_add_test(tc1_1, test_s21_sscanf_97);
  tcase_add_test(tc1_1, test_s21_sscanf_98);
  tcase_add_test(tc1_1, test_s21_sscanf_99);
  tcase_add_test(tc1_1, test_s21_sscanf_100);
  tcase_add_test(tc1_1, test_s21_sscanf_101);
  tcase_add_test(tc1_1, test_s21_sscanf_102);
  tcase_add_test(tc1_1, test_s21_sscanf_103);
  tcase_add_test(tc1_1, test_s21_sscanf_104);
  tcase_add_test(tc1_1, test_s21_sscanf_105);
  tcase_add_test(tc1_1, test_s21_sscanf_106);
  /*-----------%LE------------*/
  // tcase_add_test(tc1_1, test_s21_sscanf_107);
  tcase_add_test(tc1_1, test_s21_sscanf_108);
  tcase_add_test(tc1_1, test_s21_sscanf_109);
  tcase_add_test(tc1_1, test_s21_sscanf_110);
  tcase_add_test(tc1_1, test_s21_sscanf_111);
  // tcase_add_test(tc1_1, test_s21_sscanf_112);
  tcase_add_test(tc1_1, test_s21_sscanf_113);
  tcase_add_test(tc1_1, test_s21_sscanf_114);
  tcase_add_test(tc1_1, test_s21_sscanf_115);
  tcase_add_test(tc1_1, test_s21_sscanf_116);
  /*-----------%lf------------*/
  // tcase_add_test(tc1_1, test_s21_sscanf_117);
  tcase_add_test(tc1_1, test_s21_sscanf_118);
  tcase_add_test(tc1_1, test_s21_sscanf_119);
  tcase_add_test(tc1_1, test_s21_sscanf_120);
  tcase_add_test(tc1_1, test_s21_sscanf_121);
  tcase_add_test(tc1_1, test_s21_sscanf_122);
  tcase_add_test(tc1_1, test_s21_sscanf_123);
  tcase_add_test(tc1_1, test_s21_sscanf_124);
  tcase_add_test(tc1_1, test_s21_sscanf_125);
  // tcase_add_test(tc1_1, test_s21_sscanf_126);
  // tcase_add_test(tc1_1, test_s21_sscanf_127);
  /*-----------%E------------*/
  tcase_add_test(tc1_1, test_s21_sscanf_128);
  tcase_add_test(tc1_1, test_s21_sscanf_129);
  tcase_add_test(tc1_1, test_s21_sscanf_130);
  tcase_add_test(tc1_1, test_s21_sscanf_131);
  tcase_add_test(tc1_1, test_s21_sscanf_132);
  tcase_add_test(tc1_1, test_s21_sscanf_133);
  tcase_add_test(tc1_1, test_s21_sscanf_134);
  tcase_add_test(tc1_1, test_s21_sscanf_135);
  tcase_add_test(tc1_1, test_s21_sscanf_136);
  tcase_add_test(tc1_1, test_s21_sscanf_137);
  tcase_add_test(tc1_1, test_s21_sscanf_138);
  /*-----------%g------------*/
  tcase_add_test(tc1_1, test_s21_sscanf_139);
  tcase_add_test(tc1_1, test_s21_sscanf_140);
  tcase_add_test(tc1_1, test_s21_sscanf_141);
  tcase_add_test(tc1_1, test_s21_sscanf_142);
  tcase_add_test(tc1_1, test_s21_sscanf_143);
  tcase_add_test(tc1_1, test_s21_sscanf_144);
  tcase_add_test(tc1_1, test_s21_sscanf_145);
  tcase_add_test(tc1_1, test_s21_sscanf_146);
  tcase_add_test(tc1_1, test_s21_sscanf_147);
  tcase_add_test(tc1_1, test_s21_sscanf_148);
  tcase_add_test(tc1_1, test_s21_sscanf_149);
  tcase_add_test(tc1_1, test_s21_sscanf_150);
  tcase_add_test(tc1_1, test_s21_sscanf_151);
  tcase_add_test(tc1_1, test_s21_sscanf_152);
  /*-----------%G------------*/
  tcase_add_test(tc1_1, test_s21_sscanf_153);
  tcase_add_test(tc1_1, test_s21_sscanf_154);
  tcase_add_test(tc1_1, test_s21_sscanf_155);
  tcase_add_test(tc1_1, test_s21_sscanf_156);
  tcase_add_test(tc1_1, test_s21_sscanf_157);
  tcase_add_test(tc1_1, test_s21_sscanf_158);
  tcase_add_test(tc1_1, test_s21_sscanf_159);
  tcase_add_test(tc1_1, test_s21_sscanf_160);
  tcase_add_test(tc1_1, test_s21_sscanf_161);
  tcase_add_test(tc1_1, test_s21_sscanf_162);
  tcase_add_test(tc1_1, test_s21_sscanf_163);
  tcase_add_test(tc1_1, test_s21_sscanf_164);
  tcase_add_test(tc1_1, test_s21_sscanf_165);
  tcase_add_test(tc1_1, test_s21_sscanf_166);
  tcase_add_test(tc1_1, test_s21_sscanf_167);
  /*-----------%o------------*/
  tcase_add_test(tc1_1, test_s21_sscanf_168);
  tcase_add_test(tc1_1, test_s21_sscanf_169);
  tcase_add_test(tc1_1, test_s21_sscanf_170);
  tcase_add_test(tc1_1, test_s21_sscanf_171);
  tcase_add_test(tc1_1, test_s21_sscanf_172);
  tcase_add_test(tc1_1, test_s21_sscanf_173);
  tcase_add_test(tc1_1, test_s21_sscanf_174);
  tcase_add_test(tc1_1, test_s21_sscanf_175);
  tcase_add_test(tc1_1, test_s21_sscanf_176);
  tcase_add_test(tc1_1, test_s21_sscanf_177);
  tcase_add_test(tc1_1, test_s21_sscanf_178);
  tcase_add_test(tc1_1, test_s21_sscanf_179);
  tcase_add_test(tc1_1, test_s21_sscanf_180);
  tcase_add_test(tc1_1, test_s21_sscanf_181);
  tcase_add_test(tc1_1, test_s21_sscanf_182);
  /*-----------%s------------*/
  tcase_add_test(tc1_1, test_s21_sscanf_183);
  tcase_add_test(tc1_1, test_s21_sscanf_184);
  tcase_add_test(tc1_1, test_s21_sscanf_185);
  tcase_add_test(tc1_1, test_s21_sscanf_186);
  tcase_add_test(tc1_1, test_s21_sscanf_187);
  tcase_add_test(tc1_1, test_s21_sscanf_188);
  tcase_add_test(tc1_1, test_s21_sscanf_189);
  tcase_add_test(tc1_1, test_s21_sscanf_190);
  tcase_add_test(tc1_1, test_s21_sscanf_191);
  tcase_add_test(tc1_1, test_s21_sscanf_192);
  tcase_add_test(tc1_1, test_s21_sscanf_193);
  tcase_add_test(tc1_1, test_s21_sscanf_194);
  tcase_add_test(tc1_1, test_s21_sscanf_195);
  tcase_add_test(tc1_1, test_s21_sscanf_196);
  tcase_add_test(tc1_1, test_s21_sscanf_197);
  /*-----------%u------------*/
  tcase_add_test(tc1_1, test_s21_sscanf_198);
  tcase_add_test(tc1_1, test_s21_sscanf_199);
  tcase_add_test(tc1_1, test_s21_sscanf_200);
  tcase_add_test(tc1_1, test_s21_sscanf_201);
  tcase_add_test(tc1_1, test_s21_sscanf_202);
  tcase_add_test(tc1_1, test_s21_sscanf_203);
  tcase_add_test(tc1_1, test_s21_sscanf_204);
  tcase_add_test(tc1_1, test_s21_sscanf_205);
  tcase_add_test(tc1_1, test_s21_sscanf_206);
  tcase_add_test(tc1_1, test_s21_sscanf_207);
  tcase_add_test(tc1_1, test_s21_sscanf_208);
  tcase_add_test(tc1_1, test_s21_sscanf_209);
  /*-----------%x------------*/
  tcase_add_test(tc1_1, test_s21_sscanf_210);
  tcase_add_test(tc1_1, test_s21_sscanf_211);
  tcase_add_test(tc1_1, test_s21_sscanf_212);
  tcase_add_test(tc1_1, test_s21_sscanf_213);
  tcase_add_test(tc1_1, test_s21_sscanf_214);
  tcase_add_test(tc1_1, test_s21_sscanf_215);
  tcase_add_test(tc1_1, test_s21_sscanf_216);
  tcase_add_test(tc1_1, test_s21_sscanf_217);
  tcase_add_test(tc1_1, test_s21_sscanf_218);
  tcase_add_test(tc1_1, test_s21_sscanf_219);
  tcase_add_test(tc1_1, test_s21_sscanf_220);
  /*-----------%X------------*/
  tcase_add_test(tc1_1, test_s21_sscanf_221);
  tcase_add_test(tc1_1, test_s21_sscanf_222);
  tcase_add_test(tc1_1, test_s21_sscanf_223);
  tcase_add_test(tc1_1, test_s21_sscanf_224);
  tcase_add_test(tc1_1, test_s21_sscanf_225);
  tcase_add_test(tc1_1, test_s21_sscanf_226);
  tcase_add_test(tc1_1, test_s21_sscanf_227);
  tcase_add_test(tc1_1, test_s21_sscanf_228);
  tcase_add_test(tc1_1, test_s21_sscanf_229);
  tcase_add_test(tc1_1, test_s21_sscanf_230);
  tcase_add_test(tc1_1, test_s21_sscanf_231);
  /*-----------%p------------*/
  tcase_add_test(tc1_1, test_s21_sscanf_232);
  tcase_add_test(tc1_1, test_s21_sscanf_233);
  tcase_add_test(tc1_1, test_s21_sscanf_234);
  tcase_add_test(tc1_1, test_s21_sscanf_235);
  tcase_add_test(tc1_1, test_s21_sscanf_236);
  tcase_add_test(tc1_1, test_s21_sscanf_237);
  tcase_add_test(tc1_1, test_s21_sscanf_238);
  tcase_add_test(tc1_1, test_s21_sscanf_239);
  tcase_add_test(tc1_1, test_s21_sscanf_240);
  tcase_add_test(tc1_1, test_s21_sscanf_241);
  tcase_add_test(tc1_1, test_s21_sscanf_242);
  /*-----------%n------------*/
  tcase_add_test(tc1_1, test_s21_sscanf_243);
  tcase_add_test(tc1_1, test_s21_sscanf_244);
  tcase_add_test(tc1_1, test_s21_sscanf_245);
  tcase_add_test(tc1_1, test_s21_sscanf_246);
  tcase_add_test(tc1_1, test_s21_sscanf_247);
  tcase_add_test(tc1_1, test_s21_sscanf_248);
  tcase_add_test(tc1_1, test_s21_sscanf_249);
  tcase_add_test(tc1_1, test_s21_sscanf_250);
  /*-----------%%------------*/
  tcase_add_test(tc1_1, test_s21_sscanf_251);
  tcase_add_test(tc1_1, test_s21_sscanf_252);
  tcase_add_test(tc1_1, test_s21_sscanf_253);
  tcase_add_test(tc1_1, test_s21_sscanf_254);
  tcase_add_test(tc1_1, test_s21_sscanf_255);
  tcase_add_test(tc1_1, test_s21_sscanf_256);
  tcase_add_test(tc1_1, test_s21_sscanf_257);
  tcase_add_test(tc1_1, test_s21_sscanf_258);
  tcase_add_test(tc1_1, test_s21_sscanf_259);
  tcase_add_test(tc1_1, test_s21_sscanf_260);

  tcase_add_test(tc1_1, test_s21_sscanf_261);
  tcase_add_test(tc1_1, test_s21_sscanf_262);
  //

  ///////////////////////////////////////////
  /*----------lu hu llu---------*/
  tcase_add_test(tc1_1, test_s21_sscanf_262);
  tcase_add_test(tc1_1, test_s21_sscanf_263);
  tcase_add_test(tc1_1, test_s21_sscanf_264);
  tcase_add_test(tc1_1, test_s21_sscanf_265);
  tcase_add_test(tc1_1, test_s21_sscanf_266);
  tcase_add_test(tc1_1, test_s21_sscanf_267);
  tcase_add_test(tc1_1, test_s21_sscanf_268);
  tcase_add_test(tc1_1, test_s21_sscanf_269);
  tcase_add_test(tc1_1, test_s21_sscanf_270);
  tcase_add_test(tc1_1, test_s21_sscanf_271);
  tcase_add_test(tc1_1, test_s21_sscanf_272);
  tcase_add_test(tc1_1, test_s21_sscanf_273);
  tcase_add_test(tc1_1, test_s21_sscanf_274);
  tcase_add_test(tc1_1, test_s21_sscanf_275);
  tcase_add_test(tc1_1, test_s21_sscanf_276);
  tcase_add_test(tc1_1, test_s21_sscanf_277);
  tcase_add_test(tc1_1, test_s21_sscanf_278);
  tcase_add_test(tc1_1, test_s21_sscanf_279);
  tcase_add_test(tc1_1, test_s21_sscanf_280);
  tcase_add_test(tc1_1, test_s21_sscanf_281);
  tcase_add_test(tc1_1, test_s21_sscanf_282);
  tcase_add_test(tc1_1, test_s21_sscanf_283);
  tcase_add_test(tc1_1, test_s21_sscanf_284);
  tcase_add_test(tc1_1, test_s21_sscanf_285);
  tcase_add_test(tc1_1, test_s21_sscanf_286);
  // tcase_add_test(tc1_1, test_s21_sscanf_287);
  tcase_add_test(tc1_1, test_s21_sscanf_288);
  tcase_add_test(tc1_1, test_s21_sscanf_289);
  tcase_add_test(tc1_1, test_s21_sscanf_290);
  tcase_add_test(tc1_1, test_s21_sscanf_291);
  tcase_add_test(tc1_1, test_s21_sscanf_292);
  tcase_add_test(tc1_1, test_s21_sscanf_293);
  tcase_add_test(tc1_1, test_s21_sscanf_294);
  tcase_add_test(tc1_1, test_s21_sscanf_295);
  tcase_add_test(tc1_1, test_s21_sscanf_296);
  tcase_add_test(tc1_1, test_s21_sscanf_297);
  tcase_add_test(tc1_1, test_s21_sscanf_298);
  tcase_add_test(tc1_1, test_s21_sscanf_299);
  tcase_add_test(tc1_1, test_s21_sscanf_300);
  tcase_add_test(tc1_1, test_s21_sscanf_301);
  tcase_add_test(tc1_1, test_s21_sscanf_302);
  tcase_add_test(tc1_1, test_s21_sscanf_303);
  tcase_add_test(tc1_1, test_s21_sscanf_304);
  tcase_add_test(tc1_1, test_s21_sscanf_305);
  tcase_add_test(tc1_1, test_s21_sscanf_306);
  tcase_add_test(tc1_1, test_s21_sscanf_307);
  tcase_add_test(tc1_1, test_s21_sscanf_308);

  srunner_run_all(sr, CK_ENV);
  qs = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (qs == 0) ? 0 : 1;
}
