# AmiGopher Roadmap

## M0 — Foundation

- Define scope and supported baseline
- AmigaOS 2.04+ / 68000+
- C89-oriented codebase
- Repository layout and build system
- Architecture and protocol documentation
- Minimal CLI executable skeleton
- Host-side static/foundation checks
- ARexx designed as a first-class application interface

## M1 — Gopher core — PASS

Qualified on GitHub Actions run 35156667903 (2026-09-16), commit `951d4ad610f3c5d20841553733e4e1dff9712497`.

- [x] `gopher://` URL parser
- [x] RFC 1436 request construction
- [x] Menu-line parser
- [x] Item model
- [x] Host unit tests for parser/protocol code
- [x] No live network dependency in core tests
- [x] GitHub Actions host qualification

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

## M3.5 — ARexx interface

ARexx arrives before the GUI so the browser/navigation core is scriptable from the beginning.

- Public ARexx port `AMIGOPHER`
- Command dispatcher separated from CLI and future GUI
- `OPEN <url>`
- `GETURL`
- `BACK`
- `FORWARD`
- `RELOAD`
- `SEARCH <query>`
- `DOWNLOAD <item> [path]`
- `STATUS`
- `BOOKMARK [url]`
- `QUIT`
- Standard `RC`/`RESULT` behavior
- Unknown-command and bad-argument handling
- Example `.rexx` scripts
- Host-testable command parsing where possible
- Visible AmigaOS runtime qualification with RexxMast

## M4 — Amiga integration

- Preferences/configuration
- Bookmarks
- Clipboard
- External viewers
- Amiga path handling
- Extend ARexx commands for integration features

## M5 — Native GUI

- Intuition/GadTools frontend
- Menu list/navigation
- URL/location field
- Status/progress UI
- Keyboard-oriented operation
- GUI actions and ARexx commands share the same application command layer

## M6 — Extended protocol support

- Additional common Gopher item types
- Gopher+ investigation/support where useful
- Robust character-set handling
- Better content dispatch
- Extend ARexx API when new protocol operations warrant it

## M7 — Secure/modern interoperability

- Investigate Gopher-over-TLS interoperability
- Optional AmTLS transport integration
- Keep plain RFC 1436 Gopher fully supported
- Make secure transport selectable through the common command/API layer

## M8 — Release qualification

- AmigaOS 2.04 baseline qualification
- 68000 baseline qualification
- ARexx qualification on supported AmigaOS baseline
- Additional AmigaOS/CPU compatibility matrix
- Documentation and user guide
- ARexx command reference and examples
- Release packaging
- Aminet-ready archive
