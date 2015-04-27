/*
 *  C Objective Data Access (test)
 *  Test case declaration
 *  Объявление набора тестов
 */

#include "test_case.h"
#include <string.h>
#include <stdio.h>

#define TEST_CASE_TYPE_ID 0xc0da4e54u
#define TEST_CASE_MAX_NAME 256u

struct test_case_node
{
    test_function entry;
    char test_name[TEST_CASE_MAX_NAME];
    struct test_case_node* next;
};

struct test_case
{
    unsigned type_id;
    char name[TEST_CASE_MAX_NAME];
    unsigned test_count;
    struct test_case_node* begin;
    struct test_case_node* end;
};

struct test_case* test_case_create(char* name)
{
    if (!name || !name[0])
        return NULL;
    struct test_case* result = (struct test_case*)
            malloc(sizeof(struct test_case));
    if (result)
    {
        result->type_id = TEST_CASE_TYPE_ID;
        strncpy(result->name, name, TEST_CASE_MAX_NAME);
        result->name[TEST_CASE_MAX_NAME - 1] = '\0';
        result->test_count = 0;
        result->begin = result->end = NULL;
    }
    return result;
}

unsigned test_case_append(struct test_case* scope, test_function entry, 
                            char* description)
{
    struct test_case_node* node;
    if (!scope || scope->type_id != TEST_CASE_TYPE_ID ||
        !entry || !description || !description[0])
    {
        return 0;
    }
    node = (struct test_case_node*) malloc(sizeof(struct test_case_node));
    if (!node)
        return 0;
    node->entry = entry;
    strncpy(node->test_name, description, TEST_CASE_MAX_NAME);
    node->next = NULL;
    if (!scope->end)
        scope->begin = scope->end = node;
    else
    {
        scope->end->next = node;
        scope->end = node;
    }
    return ++scope->test_count;
}

char* test_case_name(struct test_case* test_scope)
{
    if (!test_scope || test_scope->type_id != TEST_CASE_TYPE_ID)
        return NULL;
    return test_scope->name;
}

enum test_result test_case_run(struct test_case* scope)
{
    if (!scope && scope->type_id != TEST_CASE_TYPE_ID)
        return TEST_ABORT_CASE;
    else
    {
        struct test_case_node* node;
        enum test_result run_result = TEST_SUCCEED;
        printf("Test case \"%s\" started with %d of tests", scope->name, scope->test_count);
        int abort_run = 0;
        for (node = scope->begin; node && !abort_run; node = node->next)
        {
            enum test_result result;
            result = node->entry(scope);
            switch (result)
            {
            case TEST_SUCCEED:
                printf("Test \"%s\" succeed\n", node->test_name);
                break;
            case TEST_FAILED:
                printf("Test \"%s\" failed\n", node->test_name);
                break;
            case TEST_ABORT_CASE:
                printf("Test \"%s\" initiate abort test case run\n", node->test_name);
                abort_run = 1;
                break;
            case TEST_ABORT_RUN:
                printf("Test \"%s\" initiate abort of all test run\n", node->test_name);
                abort_run = 1;
                break;
            default:
                printf("Test \"%s\" return illegal result: %d\n", node->test_name, (int)result);
            }
            if (result != TEST_SUCCEED && result != TEST_FAILED)
                return result;
            if (result == TEST_FAILED)
                run_result = TEST_FAILED;
        }
        return run_result;
    }
}
