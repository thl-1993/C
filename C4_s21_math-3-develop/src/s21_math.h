#include <stdio.h>

#define S21_M_PI 3.14159265358979323846
#define S21_M_E 2.71828182845904523536
#define EPS 1e-16
#define S21_NAN 0.0 / 0.0L
#define S21_INFINITY 1.0 / 0.0L
#define S21_M_PI_2 1.570796326794896619231321691639751442L
#define S21_M_LN2 0.69314718055994530942 /* log_e 2 */

int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);