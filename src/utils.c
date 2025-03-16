#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

const char *ptr_to_str (const void * ptr) {
    int res_size = 2 * sizeof(void *) + 3;
    char *res = (char *)malloc(res_size);
    (void)snprintf(res, res_size, "%p", ptr);
    return res;
}

const char *(* const DEFAULT_TO_STR)(const void *) = ptr_to_str;
