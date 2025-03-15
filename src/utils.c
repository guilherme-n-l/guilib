#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

const char *DEFAULT_VAL_TO_STR(const void * ptr) {
    int res_size = 2 * sizeof(void *) + 3;
    char *res = (char *)malloc(res_size);
    (void)snprintf(res, res_size, "%p", ptr);
    return res;
}
