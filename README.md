# AmiGopher

A lightweight native Gopher client for classic Amiga systems.

## Goals

AmiGopher aims to provide a small, efficient Gopher client for AmigaOS with a classic-Amiga-first design rather than a Unix port wrapped for Amiga.

Initial target:

- AmigaOS 2.04+
- Motorola 68000+
- `bsdsocket.library` networking
- RFC 1436 Gopher support
- CLI first, native GUI later
- Small memory footprint and minimal dependencies

## Planned protocol support

- Item type `0` — text files
- Item type `1` — Gopher menus
- Item type `7` — search services
- Item type `9` — binary files/downloads
- URL parsing for `gopher://` URLs
- Selector handling
- External viewer hooks for unsupported item types

## Planned Amiga integration

- Native Amiga filesystem paths
- Config file and bookmarks
- History
- Clipboard integration
- ARexx port
- Optional GUI frontend
- Future optional TLS transport through AmTLS where appropriate

## Development status

M0 — project foundation.

See [ROADMAP.md](ROADMAP.md) and [docs/M0_ARCHITECTURE.md](docs/M0_ARCHITECTURE.md).

## Build

Host-side foundation checks:

```sh
make check
```

The Amiga target is prepared for a Bebbo-style `m68k-amigaos-gcc` toolchain:

```sh
make amiga
```

## License

MIT. See [LICENSE](LICENSE).
