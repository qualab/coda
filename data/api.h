/*
 *  C Objective Data Access library API
 *  Основной модуль для объявления API
 */

#pragma once

#if defined(WIN32) && !defined(CODA_STATIC)
#   if defined(CODA_EXPORTS)
#       define CODA_API __declspec(dllexport)
#   else
#       define CODA_API __declspec(dllimport)
#   endif
#else
#   define CODA_API
#endif
