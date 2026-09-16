#include "amigopher/gopher.h"

#include <stdlib.h>
#include <string.h>

static int copy_part(char *dst, size_t cap, const char *src, size_t len)
{
    if (len >= cap)
        return -1;
    memcpy(dst, src, len);
    dst[len] = '\0';
    return 0;
}

int ag_parse_url(const char *text, struct ag_url *out)
{
    const char *p;
    const char *host_end;
    const char *colon;
    const char *path;
    char portbuf[6];
    long port;

    if (!text || !out || strncmp(text, "gopher://", 9) != 0)
        return -1;

    memset(out, 0, sizeof(*out));
    out->port = AG_DEFAULT_PORT;
    out->item_type = '1';
    p = text + 9;
    path = strchr(p, '/');
    host_end = path ? path : p + strlen(p);
    colon = memchr(p, ':', (size_t)(host_end - p));

    if (colon) {
        size_t n = (size_t)(host_end - colon - 1);
        if (copy_part(out->host, sizeof(out->host), p, (size_t)(colon - p)) ||
            n == 0 || n >= sizeof(portbuf))
            return -1;
        memcpy(portbuf, colon + 1, n);
        portbuf[n] = '\0';
        port = strtol(portbuf, NULL, 10);
        if (port < 1 || port > 65535)
            return -1;
        out->port = (unsigned short)port;
    } else if (copy_part(out->host, sizeof(out->host), p,
                         (size_t)(host_end - p))) {
        return -1;
    }

    if (out->host[0] == '\0')
        return -1;

    if (path && path[1] != '\0') {
        out->item_type = path[1];
        if (copy_part(out->selector, sizeof(out->selector), path + 2,
                      strlen(path + 2)))
            return -1;
    }
    return 0;
}

int ag_build_request(const char *selector, const char *query,
                     char *out, size_t out_size)
{
    size_t a;
    size_t b = 0;
    size_t need;

    if (!selector || !out)
        return -1;
    a = strlen(selector);
    if (query)
        b = strlen(query);
    need = a + (query ? 1 + b : 0) + 2 + 1;
    if (need > out_size)
        return -1;

    memcpy(out, selector, a);
    if (query) {
        out[a] = '\t';
        memcpy(out + a + 1, query, b);
        a += 1 + b;
    }
    out[a++] = '\r';
    out[a++] = '\n';
    out[a] = '\0';
    return (int)a;
}

int ag_parse_menu_line(const char *line, struct ag_item *out)
{
    const char *p;
    const char *tab;
    const char *fields[4];
    size_t lens[4];
    int i;
    long port;
    char portbuf[6];

    if (!line || !out || line[0] == '\0' || strcmp(line, ".") == 0)
        return -1;
    memset(out, 0, sizeof(*out));
    out->type = line[0];
    p = line + 1;

    for (i = 0; i < 3; ++i) {
        fields[i] = p;
        tab = strchr(p, '\t');
        if (!tab)
            return -1;
        lens[i] = (size_t)(tab - p);
        p = tab + 1;
    }
    fields[3] = p;
    lens[3] = strcspn(p, "\r\n\t");

    if (copy_part(out->display, sizeof(out->display), fields[0], lens[0]) ||
        copy_part(out->selector, sizeof(out->selector), fields[1], lens[1]) ||
        copy_part(out->host, sizeof(out->host), fields[2], lens[2]) ||
        lens[3] == 0 || lens[3] >= sizeof(portbuf))
        return -1;

    memcpy(portbuf, fields[3], lens[3]);
    portbuf[lens[3]] = '\0';
    port = strtol(portbuf, NULL, 10);
    if (port < 1 || port > 65535)
        return -1;
    out->port = (unsigned short)port;
    return 0;
}
