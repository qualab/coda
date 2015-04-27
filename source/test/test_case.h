/*
 *  C Objective Data Access (test)
 *  Test case declaration
 *  Объявление набора тестов
 */

struct test_case;

enum test_result
{
    TEST_FAILED = 0,
    TEST_SUCCEED = 1,
    TEST_ABORT_CASE = -1,
    TEST_ABORT_RUN = -2
};

typedef enum test_result (*test_function)(struct test_case*);

struct test_case* test_case_create(char* name);
unsigned test_case_append(struct test_case* scope, test_function entry,
                                char* description);
char* test_case_name(struct test_case* scope);
enum test_result test_case_run(struct test_case* scope);
unsigned test_case_entry_count(struct test_case* scope);
void test_case_delete(struct test_case* scope);
