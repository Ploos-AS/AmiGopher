#ifndef AMIGOPHER_GOPHER_H
#define AMIGOPHER_GOPHER_H

#include <stddef.h>

#define AG_HOST_MAX 255
#define AG_SELECTOR_MAX 1023
#define AG_DISPLAY_MAX 255
#define AG_DEFAULT_PORT 70

struct ag_url {
    char host[AG_HOST_MAX + 1];
    unsigned short port;
    char item_type;
    char selector[AG_SELECTOR_MAX + 1];
};

struct ag_item {
    char type;
    char display[AG_DISPLAY_MAX + 1];
    char selector[AG_SELECTOR_MAX + 1];
    char host[AG_HOST_MAX + 1];
    unsigned short port;
};

int ag_parse_url(const char *text, struct ag_url *out);
int ag_build_request(const char *selector, const char *query,
                     char *out, size_t out_size);
int ag_parse_menu_line(const char *line, struct ag_item *out);

#endif
