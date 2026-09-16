# AmiGopher Roadmap

## M0 — Foundation

- Define scope and supported baseline
- AmigaOS 2.04+ / 68000+
- C89-oriented codebase
- Repository layout and build system
- Architecture and protocol documentation
- Minimal CLI executable skeleton
- Host-side static/foundation checks

## M1 — Gopher core

- `gopher://` URL parser
- RFC 1436 request construction
- Menu-line parser
- Item model
- Host unit tests for parser/protocol code
- No live network dependency in core tests

## M2 — Amiga TCP transport

- `bsdsocket.library` abstraction
- DNS resolution
- TCP connect/read/write/close
- Default Gopher port 70
- Timeouts and useful AmigaDOS return codes
- Visible FS-UAE runtime qualification

## M3 — CLI browser

- Open Gopher URLs
- Render item type 0 text
- Render and navigate item type 1 menus
- Back/history navigation
- Type 7 searches
- Type 9 downloads

## M4 — Amiga integration

- Preferences/configuration
- Bookmarks
- Clipboard
- External viewers
- Amiga path handling
- ARexx port and command set

## M5 — Native GUI

- Intuition/GadTools frontend
- Menu list/navigation
- URL/location field
- Status/progress UI
- Keyboard-oriented operation

## M6 — Extended protocol support

- Additional common Gopher item types
- Gopher+ investigation/support where useful
- Robust character-set handling
- Better content dispatch

## M7 — Secure/modern interoperability

- Investigate Gopher-over-TLS interoperability
- Optional AmTLS transport integration
- Keep plain RFC 1436 Gopher fully supported

## M8 — Release qualification

- AmigaOS 2.04 baseline qualification
- 68000 baseline qualification
- Additional AmigaOS/CPU compatibility matrix
- Documentation and user guide
- Release packaging
- Aminet-ready archive
