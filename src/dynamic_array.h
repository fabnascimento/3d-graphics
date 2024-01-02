//
// Created by ffnas on 2023-12-29.
//

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include <stdlib.h>

#define ARRAY_SIZE(ARR) (*((size_t *) ARR - 2))
#define ARRAY_CAPACITY(ARR) (*((size_t *) ARR - 1))

#define ARRAY_INIT(T, arr) \
    do {\
        size_t *raw = malloc(2 * sizeof(size_t));\
        raw[0] = 0;\
        raw[1] = 0;\
        arr = (T *) &raw[2];\
    } while (0)

#define ARRAY_DESTROY(arr) \
    do {\
        size_t *raw = ((size_t *) (arr) -2);\
        free(raw);\
        arr = NULL;\
    } while (0)


#define ARRAY_RESIZE(raw, value) (realloc(raw, 2 * sizeof(size_t) * raw[1] * sizeof((value))))

#define ARRAY_PUSH(arr, value)\
    do {\
        size_t *raw = ((size_t *) (arr) -2);\
        raw[0] = raw[0] + 1;\
        if (raw[1] == 0) {\
            raw[1] = 1;\
            raw = realloc(raw, 2 * sizeof(size_t) * raw[1] * sizeof((value)));\
            (arr) = (void *) &raw[2];\
        }\
        if (raw[0] > raw[1]) {\
            raw[1] = 2 * raw[1];\
            raw = realloc(raw, 2 * sizeof(size_t) + raw[1] * sizeof((value)));\
            (arr) = (void *) &raw[2];\
        }\
        arr[raw[0] - 1] = (value);\
    } while (0)

#endif //DYNAMIC_ARRAY_H
