#include "amigopher/gopher.h"

#include <assert.h>
#include <string.h>

int main(void)
{
    struct ag_url url;
    struct ag_item item;
    char req[128];

    assert(ag_parse_url("gopher://example.org/1/foo", &url) == 0);
    assert(strcmp(url.host, "example.org") == 0);
    assert(url.port == 70);
    assert(url.item_type == '1');
    assert(strcmp(url.selector, "/foo") == 0);

    assert(ag_parse_url("gopher://example.org:7070/0/readme", &url) == 0);
    assert(url.port == 7070);
    assert(url.item_type == '0');
    assert(strcmp(url.selector, "/readme") == 0);

    assert(ag_build_request("/foo", NULL, req, sizeof(req)) == 6);
    assert(strcmp(req, "/foo\r\n") == 0);
    assert(ag_build_request("/search", "amiga", req, sizeof(req)) == 15);
    assert(strcmp(req, "/search\tamiga\r\n") == 0);

    assert(ag_parse_menu_line("1Software\t/software\tgopher.example\t70\r\n", &item) == 0);
    assert(item.type == '1');
    assert(strcmp(item.display, "Software") == 0);
    assert(strcmp(item.selector, "/software") == 0);
    assert(strcmp(item.host, "gopher.example") == 0);
    assert(item.port == 70);

    assert(ag_parse_url("http://example.org/", &url) != 0);
    assert(ag_parse_menu_line("broken", &item) != 0);
    return 0;
}
