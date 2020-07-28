#ifndef ERROR_H
#define ERROR_H

#define error(m, ...) fprintf(stderr, "\x1B[31mError\e[0m: " m, ##__VA_ARGS__)

#endif
