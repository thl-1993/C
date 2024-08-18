#include "tests/test.h"

void run() {
  Suite *tests[] = {
      suite_create_matrix(), suite_remove_matrix(),  suite_eq_matrix(),
      suite_sum_matrix(),    suite_sub_matrix(),     suite_mult_number(),
      suite_mult_matrix(),   suite_transpose(),      suite_calc_complements(),
      suite_determinant(),   suite_inverse_matrix(), NULL,
  };

  int total = 0;
  int failed = 0;

  for (Suite **current = tests; *current; current++) {
    SRunner *sr = srunner_create(*current);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    total += srunner_ntests_run(sr);
    failed += srunner_ntests_failed(sr);

    srunner_free(sr);
  }

  printf("\n" WHITE_BG BLACK " total: %d " RESET GREEN_BG WHITE
         " success: %d " RESET RED_BG WHITE " failed: %d " RESET "\n",
         total, total - failed, failed);
}

int main() {
  run();

  return 0;
}