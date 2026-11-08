# UNO Pin Loop - Remote Control Simulator

![Language](https://img.shields.io/github/languages/top/panhavad/uno-pin-loop) ![Last commit](https://img.shields.io/github/last-commit/panhavad/uno-pin-loop) [![Release](https://img.shields.io/github/v/release/panhavad/uno-pin-loop?include_prereleases)](https://github.com/panhavad/uno-pin-loop/releases/latest)

An **Arduino UNO sketch that simulates pressing a remote-control button** by switching an output pin from serial commands. Use manual `on`/`off` or an **auto loop** with custom on/off timing - great for testing RF switches and devices.

![System snapshot](docs/snapshot.svg)

## Features

- Serial commands: `on`, `off`, `auto <loops> <on_ms> <off_ms>`
- Auto mode with countdown output
- Manual command instantly exits auto mode
- Pin 12 output, pin 13 input

## How it works

```mermaid
flowchart LR
    PC["Serial monitor"] -->|"command"| A["Arduino UNO"]
    A --> M{"Command"}
    M -->|"on / off"| P["Pin 12 HIGH / LOW"]
    M -->|"auto n on off"| L["Loop n times"]
    L --> P
    P --> R["Remote / relay"]
```

## Getting started

Upload `rfsw.ino`, open Serial Monitor at **9600 baud** and type:

```
on
off
auto 10 500 2000
```

## Download

Grab the packaged source from the [latest release](https://github.com/panhavad/uno-pin-loop/releases/latest).

## Tech stack

- Arduino C++
- Arduino UNO

## Project structure

```text
uno-pin-loop/
├── docs/
├── README.md
├── rfsw.ino
└── Screenshot 2025-02-07 190413.png
```
