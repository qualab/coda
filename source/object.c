/*
 *  C Objective Data Access (source)
 *  Base object to handle data access
 *  Базовый тип объекта обработки данных
 */

#include <data/object.h>
#include <memory.h>
#include <stdlib.h>

#define DATA_OBJECT_TYPE_ID 0xc0da00b7u

struct data_object
{
    unsigned type_id;
    char buffer[DATA_OBJECT_CAPACITY];
};

struct data_object* data_object_create()
{
    void* address = malloc(sizeof(struct data_object));
    return data_object_place(address);
}

struct data_object* data_object_place(void* address)
{
    if (!address) return NULL;
    struct data_object* result = (struct data_object*)address;
    result->type_id = DATA_OBJECT_TYPE_ID;
    memset(result->buffer, 0, sizeof(result->buffer));
    return result;
}
