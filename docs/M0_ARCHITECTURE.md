# M0 Architecture

## Purpose

AmiGopher is a native, lightweight Gopher client for classic Amiga systems. The implementation should remain useful on a plain 68000 machine and avoid importing unnecessary Unix assumptions into the Amiga frontend.

## Baseline

- AmigaOS 2.04+
- Motorola 68000+
- C89-compatible implementation style
- `bsdsocket.library` for TCP/IP
- RFC 1436 as the protocol baseline
- Default TCP port 70

## Layering

```text
+-------------------------------+
| CLI / future native GUI       |
+-------------------------------+
| navigation / history          |
+-------------------------------+
| Gopher protocol + item model  |
+-------------------------------+
| transport abstraction         |
+-------------------------------+
| bsdsocket.library             |
+-------------------------------+
```

Protocol parsing must not depend on Intuition or `bsdsocket.library`. This allows parser and request logic to be tested on a normal CI host.

## Proposed source layout

```text
include/amigopher/
    amigopher.h
    gopher.h
    transport.h
src/
    main.c
    gopher.c
    transport_amiga.c
    transport_stub.c
tests/
    test_foundation.c
docs/
```

## Protocol model

A menu item will eventually contain at least:

- item type
- display string
- selector
- host
- port

The parser must use bounded buffers and explicit lengths. A 68000 target means avoiding unnecessary allocation and copies is desirable.

## Networking

M0 deliberately does not implement live networking. M2 will provide an Amiga transport implementation around `bsdsocket.library`. The Gopher core will consume a small transport interface rather than calling socket APIs throughout the application.

## UI strategy

The CLI is implemented first because it provides the smallest path to a useful and testable client. A native Intuition/GadTools frontend is planned later without replacing the protocol core.

## ARexx

ARexx is part of the planned native integration. The eventual port should expose useful operations such as OPEN, BACK, RELOAD, SEARCH, DOWNLOAD, GETURL and QUIT, subject to refinement when the browser/navigation layer exists.

## TLS

Classic Gopher remains plain TCP. A later milestone may add an optional secure transport for servers supporting Gopher over TLS. That layer should be optional and is a candidate for integration with the separate AmTLS project.

## M0 exit criteria

M0 is complete when the repository contains the documented architecture, roadmap, license, build skeleton, public headers, minimal executable skeleton and host-side foundation check. Protocol behavior and networking are intentionally deferred.
