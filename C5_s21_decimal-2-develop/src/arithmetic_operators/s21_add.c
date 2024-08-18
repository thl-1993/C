#include "../s21_decimal.h"

// int big_decimal_scale_processor(big_decimal *bd_result,big_decimal
// *bd_buffer, int scale) {
//     big_decimal bd_ten;
//     big_decimal_init(&bd_ten);
//     bd_ten.bits[0] = 10;
//     while ((bd_result->bits[5] || bd_result->bits[4] || bd_result->bits[3])
//     && scale) {
//         *bd_buffer = big_decimal_mantissa_div(*bd_result, bd_ten, bd_result);
//         scale --;
//     }
//     return scale;
// }

// int big_decimal_bank_round(big_decimal bd_buffer, big_decimal
// *bd_result,big_decimal *bd_value_1, int scale) {
//     int bits_buffer = bd_buffer.bits[0];
//     int response = 0;
//     big_decimal bd_ten;
//     big_decimal_init(&bd_ten);
//     bd_ten.bits[0] = 10;

//     if (!scale && (bd_result->bits[5] || bd_result->bits[4] ||
//     bd_result->bits[3])) {
//         if (big_decimal_get_sign(*bd_result)) response = 2;
//         else response = 1;
//     } else {
//         if (bits_buffer > 5) {
//             bd_ten.bits[0] = 1;
//             response = big_decimal_mantissa_add(*bd_result, bd_ten,
//             bd_result);
//         } else if (bits_buffer == 5) {
//             bd_buffer = big_decimal_mantissa_div(*bd_result, bd_ten,
//             bd_value_1); int bits_buffer_2 = bd_buffer.bits[0]; if
//             (bits_buffer_2 % 2 == 1) {
//                 bd_ten.bits[0] = 1;
//                 response = big_decimal_mantissa_add(*bd_result, bd_ten,
//                 bd_result);
//             }
//         }
//     }
//     return response;
// }

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  big_decimal bd_value_1;
  big_decimal bd_value_2;
  big_decimal bd_result;
  big_decimal bd_buffer;
  big_decimal bd_ten;
  int response = S21_SUCCESS;
  int scale = 0;
  int sign_result = 0;
  // int bits_buffer = 0;
  // int bits_buffer_2 = 0;
  int sign_value_1 = s21_get_sign(value_1);
  int sign_value_2 = s21_get_sign(value_2);

  s21_decimal_to_big_decimal(value_1, &bd_value_1);
  s21_decimal_to_big_decimal(value_2, &bd_value_2);
  big_decimal_init(&bd_result);
  big_decimal_init(&bd_buffer);
  big_decimal_init(&bd_ten);
  bd_ten.bits[0] = 10;
  big_decimal_equal_scales(&bd_value_1, &bd_value_2);

  if (sign_value_1 == sign_value_2) {
    big_decimal_mantissa_add(bd_value_1, bd_value_2, &bd_result);
    if (sign_value_1) big_decimal_set_sign(&bd_result, sign_value_1);
  } else if (sign_value_1 > sign_value_2) {
    if (big_decimal_mantissa_is_bigger_or_equal(bd_value_1, bd_value_2)) {
      big_decimal_mantissa_sub(bd_value_1, bd_value_2, &bd_result);
      big_decimal_set_sign(&bd_result, sign_value_1);
    } else
      big_decimal_mantissa_sub(bd_value_2, bd_value_1, &bd_result);
  } else {
    if (big_decimal_mantissa_is_bigger_or_equal(bd_value_1, bd_value_2))
      big_decimal_mantissa_sub(bd_value_1, bd_value_2, &bd_result);
    else {
      big_decimal_mantissa_sub(bd_value_2, bd_value_1, &bd_result);
      big_decimal_set_sign(&bd_result, sign_value_2);
    }
  }

  scale = big_decimal_get_scale(bd_value_1);
  sign_result = big_decimal_get_sign(bd_result);
  big_decimal_set_scale(&bd_result, scale);

  // while ((bd_result.bits[5] || bd_result.bits[4] || bd_result.bits[3]) &&
  // scale) {
  //     bd_buffer = big_decimal_mantissa_div(bd_result, bd_ten, &bd_result);
  //     scale --;
  // }

  scale = big_decimal_scale_processor(&bd_result, &bd_buffer, scale);

  // bits_buffer = bd_buffer.bits[0];

  // if (!scale && (bd_result.bits[5] || bd_result.bits[4] ||
  // bd_result.bits[3])) {
  //     if (big_decimal_get_sign(bd_result)) response = 2;
  //     else response = 1;
  // } else {
  //     if (bits_buffer > 5) {
  //         bd_ten.bits[0] = 1;
  //         response = big_decimal_mantissa_add(bd_result, bd_ten, &bd_result);
  //     } else if (bits_buffer == 5) {
  //         bd_buffer = big_decimal_mantissa_div(bd_result, bd_ten,
  //         &bd_value_1); bits_buffer_2 = bd_buffer.bits[0]; if (bits_buffer_2
  //         % 2 == 1) {
  //             bd_ten.bits[0] = 1;
  //             response = big_decimal_mantissa_add(bd_result, bd_ten,
  //             &bd_result);
  //         }
  //     }
  // }

  response = big_decimal_bank_round(bd_buffer, &bd_result, &bd_value_1, scale);

  big_decimal_set_scale(&bd_result, scale);
  big_decimal_set_sign(&bd_result, sign_result);

  if (!response)
    big_decimal_to_s21_decimal(bd_result, result);
  else
    s21_set_zero_decimal(result);

  return response;
}
