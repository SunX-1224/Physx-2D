#pragma once
#include <stdio.h>

#ifdef _DEBUG

#define LOG_INFO(form, ...) {printf("\033[1;32m" form "\033[1;0m", __VA_ARGS__);}
#define LOG_WARN(form, ...) {printf("\033[1;33m" form "\033[1;0m", __VA_ARGS__);}
#define LOG_ERROR(form, ...) {printf("\033[1;31m" form "\033[1;0m", __VA_ARGS__);}

#else

#define LOG_INFO
#define LOG_WARN
#define LOG_ERROR

#endif