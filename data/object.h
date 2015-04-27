/*
 *  C Objective Data Access
 *  Base object to handle data access
 *  Базовый тип объекта обработки данных
 */

#pragma once

#include <data/api.h>

#define DATA_OBJECT_CAPACITY 64u

struct data_object;

CODA_API struct data_object* data_object_create();
CODA_API struct data_object* data_object_place(void* address);
CODA_API int data_object_is_null(struct data_object* object);
CODA_API void data_object_delete(struct data_object* object);
