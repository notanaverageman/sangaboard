#pragma once

#include "Arduino.h"

// https://stackoverflow.com/a/11994395/3670437
#define FE_0(WHAT)
#define FE_1(WHAT, X) WHAT(X)
#define FE_2(WHAT, X, ...) WHAT(X)FE_1(WHAT, __VA_ARGS__)
#define FE_3(WHAT, X, ...) WHAT(X)FE_2(WHAT, __VA_ARGS__)
#define FE_4(WHAT, X, ...) WHAT(X)FE_3(WHAT, __VA_ARGS__)
#define FE_5(WHAT, X, ...) WHAT(X)FE_4(WHAT, __VA_ARGS__)
#define FE_6(WHAT, X, ...) WHAT(X)FE_5(WHAT, __VA_ARGS__)
#define FE_7(WHAT, X, ...) WHAT(X)FE_6(WHAT, __VA_ARGS__)
#define FE_8(WHAT, X, ...) WHAT(X)FE_7(WHAT, __VA_ARGS__)
#define FE_9(WHAT, X, ...) WHAT(X)FE_8(WHAT, __VA_ARGS__)

#define GET_MACRO(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,NAME,...) NAME
#define FOR_EACH(action,...) GET_MACRO(_0,__VA_ARGS__,FE_9,FE_8,FE_7,FE_6,FE_5,FE_4,FE_3,FE_2,FE_1,FE_0)(action,__VA_ARGS__)

#define LOG_LEVEL_DEBUG    0
#define LOG_LEVEL_INFO     1
#define LOG_LEVEL_DISABLED 2

#define LOG_LEVEL LOG_LEVEL_DISABLED

#define PRINT(X) Serial.print(X);
#define LOG(...) FOR_EACH(PRINT,__VA_ARGS__)Serial.println();

#if LOG_LEVEL <= LOG_LEVEL_DEBUG
    #define DEBUG(...) LOG(__VA_ARGS__)
#else
    #define DEBUG(...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_INFO
    #define INFO(...) LOG(__VA_ARGS__)
#else
    #define INFO(...)
#endif