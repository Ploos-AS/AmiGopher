#ifndef AMIGOPHER_TRANSPORT_H
#define AMIGOPHER_TRANSPORT_H

#include <stddef.h>

#define AG_TRANSPORT_OK 0
#define AG_TRANSPORT_ERROR -1
#define AG_TRANSPORT_TIMEOUT -2
#define AG_TRANSPORT_DNS -3
#define AG_TRANSPORT_CONNECT -4

struct ag_transport {
    int socket_fd;
    int last_error;
};

void ag_transport_init(struct ag_transport *transport);
int ag_transport_connect(struct ag_transport *transport,
                         const char *host, unsigned short port,
                         unsigned long timeout_ms);
long ag_transport_read(struct ag_transport *transport,
                       void *buffer, size_t length);
long ag_transport_write(struct ag_transport *transport,
                        const void *buffer, size_t length);
void ag_transport_close(struct ag_transport *transport);

#endif
