# AmiGopher ARexx Interface

ARexx is a first-class AmiGopher interface. It is not merely GUI automation: CLI, GUI and ARexx should ultimately invoke the same application command layer.

## Port

The public port name is planned as:

```text
AMIGOPHER
```

Only one public command port is required initially. Instance handling can be revisited if running multiple AmiGopher processes becomes a supported use case.

## Initial command set

| Command | Purpose |
| --- | --- |
| `OPEN <url>` | Navigate to a Gopher URL |
| `GETURL` | Return the current URL |
| `BACK` | Navigate backward |
| `FORWARD` | Navigate forward |
| `RELOAD` | Reload the current resource |
| `SEARCH <query>` | Submit a search to the active type-7 item/context |
| `DOWNLOAD <item> [path]` | Download an item |
| `STATUS` | Return machine-readable application/navigation status |
| `BOOKMARK [url]` | Bookmark the supplied or current URL |
| `QUIT` | Request clean application shutdown |

Exact argument and result formats will be frozen when the relevant browser functions exist.

## Semantics

- Commands are case-insensitive.
- Commands must return meaningful ARexx `RC` values.
- Commands returning data use `RESULT` when invoked with the ARexx `RESULT` option.
- Bad arguments and unavailable operations must fail predictably rather than silently succeeding.
- The ARexx layer must not duplicate Gopher/network logic.
- GUI, CLI and ARexx operations should call a shared application command API.

## Architecture

```text
       CLI       ARexx       GUI
        |          |          |
        +----------+----------+
                   |
          application commands
                   |
        navigation / bookmarks
                   |
             Gopher core
                   |
              transport
```

This keeps scripts stable when the native GUI is introduced.

## Runtime requirements

ARexx support depends on the normal Amiga ARexx environment and RexxMast. Runtime qualification will explicitly test startup, command dispatch, returned values, error cases and clean port removal on exit.

## Example target usage

```rexx
/* AmiGopher example -- syntax subject to milestone qualification */
ADDRESS 'AMIGOPHER'
'OPEN gopher://gopher.floodgap.com/1/'
'GETURL'
SAY RESULT
```

Examples in the release must be validated on the supported AmigaOS baseline before being described as qualified.
