#include <stddef.h>
#include "../../string-helpers.h"
#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>
#include "test.h"

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void) {
  return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void) {
  return 0;
}

/* The test initialization function.
 * Opens the temporary file used by the test.
 */
void init_test1(void) {
  return;
}

/* The test cleanup function.
 * Closes the temporary file used by the test in particular.
 */
void clean_test1(void) {
  return;
}

/* Simple test of is_digit().
 */
void testISDIGIT_Integers(void) {
  CU_ASSERT_FALSE(is_digit(0));
  CU_ASSERT_FALSE(is_digit(9));
  CU_ASSERT_FALSE(is_digit(-1));
}

void testISDIGIT_Digits(void) {
  CU_ASSERT_TRUE(is_digit('1'));
  CU_ASSERT_TRUE(is_digit('0'));
  CU_ASSERT_TRUE(is_digit('9'));
}

void testISDIGIT_EscChars(void) {
  CU_ASSERT_FALSE(is_digit('\0'));
  CU_ASSERT_FALSE(is_digit('\"'));
  CU_ASSERT_FALSE(is_digit('\n'));
}

void testISSPACE_True(void) {
  CU_ASSERT_TRUE(is_space(' '));
  CU_ASSERT_TRUE(is_space('\n'));
  CU_ASSERT_TRUE(is_space('\t'));
}

void testISSPACE_False(void) {
  CU_ASSERT_FALSE(is_space('1'));
  CU_ASSERT_FALSE(is_space('c'));
  CU_ASSERT_FALSE(is_space('\\'));
}

void testISIDENTIFIERCOMP_Letters(void) {
  CU_ASSERT_TRUE(is_identifier_component('a'));
  CU_ASSERT_TRUE(is_identifier_component('A'));
  CU_ASSERT_TRUE(is_identifier_component('z'));
  CU_ASSERT_TRUE(is_identifier_component('Z'));
}

void testISIDENTIFIERCOMP_Digits(void) {
  CU_ASSERT_TRUE(is_identifier_component('1'));
  CU_ASSERT_TRUE(is_identifier_component('0'));
  CU_ASSERT_TRUE(is_identifier_component('9'));
}

void testISIDENTIFIERCOMP_Symbols(void) {
  CU_ASSERT_FALSE(is_identifier_component('!'));
  CU_ASSERT_FALSE(is_identifier_component('~'));
  CU_ASSERT_FALSE(is_identifier_component('@'));
  CU_ASSERT_FALSE(is_identifier_component('$'));
  CU_ASSERT_FALSE(is_identifier_component('%'));
  CU_ASSERT_FALSE(is_identifier_component('^'));
  CU_ASSERT_FALSE(is_identifier_component('&'));
  CU_ASSERT_FALSE(is_identifier_component('*'));
  CU_ASSERT_FALSE(is_identifier_component('-'));
  CU_ASSERT_TRUE(is_identifier_component('_'));
}

void testISVALIDIDENTIFIER_Valid(void) {
  CU_ASSERT_TRUE(is_valid_identifier("hello"));
  CU_ASSERT_TRUE(is_valid_identifier("hello_world"));
  CU_ASSERT_TRUE(is_valid_identifier("hi_world123"));
  CU_ASSERT_TRUE(is_valid_identifier("Hi123_"));
  CU_ASSERT_TRUE(is_valid_identifier("Hi123_world_"));
}

void testISVALIDIDENTIFIER_Invalid(void) {
  CU_ASSERT_FALSE(is_valid_identifier("_hello"));
  CU_ASSERT_FALSE(is_valid_identifier("123hello"));
  CU_ASSERT_FALSE(is_valid_identifier("hello-worlf"));
  CU_ASSERT_FALSE(is_valid_identifier("hello%world"));
  CU_ASSERT_FALSE(is_valid_identifier("hello world"));
  CU_ASSERT_FALSE(is_valid_identifier("#hello"));
}

void testSTRCONCAT(void) {
  char* s1[] = {"hello"};
  char* s2[] = {"hello", "world"};
  char* s3[] = {"hello-", "world"};
  char* s4[] = {"hello", " world"};
  char* s5[] = {"string", " concat", " test"};

  CU_ASSERT_EQUAL(0, strcmp("hello", str_concat(s1, 1)));
  CU_ASSERT_EQUAL(0, strcmp("helloworld", str_concat(s2, 2)));
  CU_ASSERT_EQUAL(0, strcmp("hello-world", str_concat(s3, 2)));
  CU_ASSERT_EQUAL(0, strcmp("hello world", str_concat(s4, 2)));
  CU_ASSERT_EQUAL(0, strcmp("string concat test", str_concat(s5, 3)));
}


/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main() {
  CU_TestInfo isdigit_tests[] = {{"Test actual digits", testISDIGIT_Digits},
                                 {"Test esc chars", testISDIGIT_EscChars},
                                 {"Test numbers", testISDIGIT_Integers},
                                 CU_TEST_INFO_NULL};

  CU_TestInfo isspace_tests[] = {{"Test true space", testISSPACE_True},
                                 {"Test false space", testISSPACE_False},
				 CU_TEST_INFO_NULL};

  CU_TestInfo isidentifiercomp_tests[] = {{"Test letters", testISIDENTIFIERCOMP_Letters},
                                        {"Test digits", testISIDENTIFIERCOMP_Digits},
                                        {"Test symbols", testISIDENTIFIERCOMP_Symbols},
                                        CU_TEST_INFO_NULL};

  CU_TestInfo isvalididentifier_tests[] = {{"Test valid id", testISVALIDIDENTIFIER_Valid},
                                           {"Test invalid id", testISVALIDIDENTIFIER_Invalid},
                                           CU_TEST_INFO_NULL};

  CU_TestInfo strconcat_tests[] = {{"Test str_concat", testSTRCONCAT},
                                   CU_TEST_INFO_NULL};

  CU_SuiteInfo suites[] = {{"is_digit testing", init_suite1, clean_suite1,
                           .pTests=isdigit_tests},
	                   {"is_space testing", init_suite1, clean_suite1,
			   .pTests=isspace_tests},
			   {"is_identifier_comp testing", init_suite1, clean_suite1,
			   .pTests=isidentifiercomp_tests},
			   {"is_valid_identifier testing", init_suite1, clean_suite1,
			   .pTests=isvalididentifier_tests},
			   {"str_concat testing", init_suite1, clean_suite1,
			   .pTests=strconcat_tests},
                           CU_SUITE_INFO_NULL};

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  if (CU_register_suites(suites)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
