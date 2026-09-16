#include "amigopher/transport.h"

#ifdef __AMIGA__

#include <exec/types.h>
#include <exec/libraries.h>
#include <proto/exec.h>
#include <proto/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

struct Library *SocketBase = NULL;

static int ensure_socket_library(void)
{
    if (SocketBase)
        return 0;
    SocketBase = OpenLibrary("bsdsocket.library", 4);
    return SocketBase ? 0 : -1;
}

void ag_transport_init(struct ag_transport *transport)
{
    if (transport) {
        transport->socket_fd = -1;
        transport->last_error = AG_TRANSPORT_OK;
    }
}

int ag_transport_connect(struct ag_transport *transport,
                         const char *host, unsigned short port,
                         unsigned long timeout_ms)
{
    struct hostent *he;
    struct sockaddr_in address;
    int fd;

    (void)timeout_ms;
    if (!transport || !host || ensure_socket_library() != 0)
        return AG_TRANSPORT_ERROR;

    he = gethostbyname(host);
    if (!he || !he->h_addr_list || !he->h_addr_list[0]) {
        transport->last_error = AG_TRANSPORT_DNS;
        return AG_TRANSPORT_DNS;
    }

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        transport->last_error = AG_TRANSPORT_ERROR;
        return AG_TRANSPORT_ERROR;
    }

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    memcpy(&address.sin_addr, he->h_addr_list[0], sizeof(address.sin_addr));

    if (connect(fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        CloseSocket(fd);
        transport->last_error = AG_TRANSPORT_CONNECT;
        return AG_TRANSPORT_CONNECT;
    }

    transport->socket_fd = fd;
    transport->last_error = AG_TRANSPORT_OK;
    return AG_TRANSPORT_OK;
}

long ag_transport_read(struct ag_transport *transport,
                       void *buffer, size_t length)
{
    if (!transport || transport->socket_fd < 0 || !buffer)
        return AG_TRANSPORT_ERROR;
    return (long)recv(transport->socket_fd, buffer, length, 0);
}

long ag_transport_write(struct ag_transport *transport,
                        const void *buffer, size_t length)
{
    if (!transport || transport->socket_fd < 0 || !buffer)
        return AG_TRANSPORT_ERROR;
    return (long)send(transport->socket_fd, buffer, length, 0);
}

void ag_transport_close(struct ag_transport *transport)
{
    if (!transport)
        return;
    if (transport->socket_fd >= 0)
        CloseSocket(transport->socket_fd);
    transport->socket_fd = -1;
}

#else
#error transport_amiga.c is for Amiga targets only
#endif
