#include <check.h>
#include <stdlib.h>

Suite *fsm_suite(void);

int main(void) {
  int number_failed = 0;

  SRunner *sr = srunner_create(fsm_suite());
  //srunner_add_suite(sr, backend_suite());
  //srunner_add_suite(sr, pieces_suite());

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}