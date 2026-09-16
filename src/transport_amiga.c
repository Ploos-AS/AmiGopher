#include "amigopher/transport.h"

#ifdef __AMIGA__

#include <exec/types.h>
#include <exec/libraries.h>
#include <proto/exec.h>
#include <proto/socket.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

struct Library *SocketBase = NULL;

static int ensure_socket_library(void)
{
    if (SocketBase)
        return 0;
    SocketBase = OpenLibrary("bsdsocket.library", 4);
    return SocketBase ? 0 : -1;
}

static void make_timeout(struct timeval *tv, unsigned long timeout_ms)
{
    tv->tv_sec = (long)(timeout_ms / 1000UL);
    tv->tv_usec = (long)((timeout_ms % 1000UL) * 1000UL);
}

static int wait_socket(int fd, int writing, unsigned long timeout_ms)
{
    fd_set readfds;
    fd_set writefds;
    struct timeval tv;
    int rc;

    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    if (writing)
        FD_SET(fd, &writefds);
    else
        FD_SET(fd, &readfds);
    make_timeout(&tv, timeout_ms);
    rc = WaitSelect(fd + 1, writing ? NULL : &readfds,
                    writing ? &writefds : NULL, NULL, &tv, NULL);
    if (rc == 0)
        return AG_TRANSPORT_TIMEOUT;
    if (rc < 0)
        return AG_TRANSPORT_ERROR;
    return AG_TRANSPORT_OK;
}

void ag_transport_init(struct ag_transport *transport)
{
    if (transport) {
        transport->socket_fd = -1;
        transport->last_error = AG_TRANSPORT_OK;
        transport->timeout_ms = 10000UL;
    }
}

int ag_transport_connect(struct ag_transport *transport,
                         const char *host, unsigned short port,
                         unsigned long timeout_ms)
{
    struct hostent *he;
    struct sockaddr_in address;
    int fd;

    if (!transport || !host || !host[0] || ensure_socket_library() != 0)
        return AG_TRANSPORT_ERROR;
    if (timeout_ms == 0)
        timeout_ms = 10000UL;
    transport->timeout_ms = timeout_ms;

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

    /* Connect is kept blocking for broad bsdsocket compatibility. The
       configured timeout is enforced for subsequent reads/writes. */
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
    int ready;
    long rc;

    if (!transport || transport->socket_fd < 0 || !buffer || length == 0)
        return AG_TRANSPORT_ERROR;
    ready = wait_socket(transport->socket_fd, 0, transport->timeout_ms);
    if (ready != AG_TRANSPORT_OK) {
        transport->last_error = ready;
        return ready;
    }
    rc = (long)recv(transport->socket_fd, buffer, length, 0);
    if (rc < 0)
        transport->last_error = AG_TRANSPORT_ERROR;
    else
        transport->last_error = AG_TRANSPORT_OK;
    return rc;
}

long ag_transport_write(struct ag_transport *transport,
                        const void *buffer, size_t length)
{
    const char *p;
    size_t remaining;
    long total;

    if (!transport || transport->socket_fd < 0 || !buffer || length == 0)
        return AG_TRANSPORT_ERROR;
    p = (const char *)buffer;
    remaining = length;
    total = 0;
    while (remaining > 0) {
        int ready = wait_socket(transport->socket_fd, 1,
                                transport->timeout_ms);
        long rc;
        if (ready != AG_TRANSPORT_OK) {
            transport->last_error = ready;
            return ready;
        }
        rc = (long)send(transport->socket_fd, p, remaining, 0);
        if (rc <= 0) {
            transport->last_error = AG_TRANSPORT_ERROR;
            return AG_TRANSPORT_ERROR;
        }
        p += rc;
        remaining -= (size_t)rc;
        total += rc;
    }
    transport->last_error = AG_TRANSPORT_OK;
    return total;
}

void ag_transport_close(struct ag_transport *transport)
{
    if (!transport)
        return;
    if (transport->socket_fd >= 0)
        CloseSocket(transport->socket_fd);
    transport->socket_fd = -1;
    transport->last_error = AG_TRANSPORT_OK;
}

#else
#error transport_amiga.c is for Amiga targets only
#endif
