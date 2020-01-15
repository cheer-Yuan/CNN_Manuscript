#include <stdint.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>

#include "data_Images.h"
#include "data_Images.c"

static void test_reader(void **state) {
  //assert_false(true);

  //assert_true(check_same_diagonal(1,1,2,2));
  assert_true(read_Img("hsf_0_00000.ppm"));
  
}





int main(void) {
  int result = 0;
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_reader), 
  };
  result |= cmocka_run_group_tests_name("reader", tests, NULL, NULL);

  return result;
}
