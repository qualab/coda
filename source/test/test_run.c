/*
 *  C Objective Data Access
 *  Test runner
 *  Запуск тестов
 */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "test_run.h"

struct test_run_node
{
    struct test_case* scope;
    struct test_run_node* next;
};

static int test_run_count = 0;
static struct test_run_node* test_run_begin = NULL;
static struct test_run_node* test_run_end = NULL;

int test_run_register(struct test_case* test_scope)
{
    struct test_run_node* node = 
            (struct test_run_node*)malloc(sizeof(struct test_run_node));
    if (!node)
        return 0;
    node->next = NULL;
    if (!test_run_end)
        test_run_begin = test_run_end = node;
    else
    {
        test_run_end->next = node;
        test_run_end = node;
    }
    return ++test_run_count;
}

int main(int argc, char** argv)
{
    printf("Run %d of test cases\n", test_run_count);
    enum test_result run_result = TEST_SUCCEED;
    unsigned case_run = 0;
    for (struct test_run_node* node = test_run_begin; node && 
            run_result != TEST_ABORT_RUN; node = node->next, ++case_run)
    {
        char* name = test_case_name(node->scope);
        printf("Run test case \"%s\"", name);
        run_result = test_case_run(node->scope);
        switch (run_result)
        {
        case TEST_SUCCEED:
            printf("Test case \"%s\" succeed", name);
            break;
        case TEST_FAILED:
            printf("Test case \"%s\" failed", name);
            break;
        case TEST_ABORT_CASE:
            printf("Test case \"%s\" has been aborted", name);
            run_result = TEST_FAILED;
            break;
        case TEST_ABORT_RUN:
            printf("Test case \"%s\" initiate abort of all test run", name);
            break;
        default:
            printf("Test case \"%s\" returned illegal result: %d", name, run_result);
        }
    }
    printf("Test run of %u test cases finished\n", case_run);
    printf("Result: %s", run_result == TEST_SUCCEED ? "succeed" : "failed");
    if (argc >= 2 && strcmp(argv[1], "pause") == 0)
        getch();
    return 0;
}
