#include "amigopher/transport.h"

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
    (void)host;
    (void)port;
    if (!transport)
        return AG_TRANSPORT_ERROR;
    transport->timeout_ms = timeout_ms ? timeout_ms : 10000UL;
    transport->last_error = AG_TRANSPORT_CONNECT;
    return AG_TRANSPORT_CONNECT;
}

long ag_transport_read(struct ag_transport *transport,
                       void *buffer, size_t length)
{
    (void)buffer;
    (void)length;
    if (!transport)
        return AG_TRANSPORT_ERROR;
    transport->last_error = AG_TRANSPORT_ERROR;
    return AG_TRANSPORT_ERROR;
}

long ag_transport_write(struct ag_transport *transport,
                        const void *buffer, size_t length)
{
    (void)buffer;
    (void)length;
    if (!transport)
        return AG_TRANSPORT_ERROR;
    transport->last_error = AG_TRANSPORT_ERROR;
    return AG_TRANSPORT_ERROR;
}

void ag_transport_close(struct ag_transport *transport)
{
    if (transport) {
        transport->socket_fd = -1;
        transport->last_error = AG_TRANSPORT_OK;
    }
}
