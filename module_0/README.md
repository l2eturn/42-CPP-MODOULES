# CPP Module 00

This module introduces the fundamentals of C++ through namespaces, classes,
member functions, initialization lists, `static` members, and standard I/O.

## Requirements

- A C++ compiler with C++98 support
- `make`

The exercises are compiled with:

```text
-Wall -Wextra -Werror -std=c++98
```

## Exercises

### ex00 — Megaphone

Builds `megaphone`, which converts command-line arguments to uppercase. When
no argument is provided, it prints the default feedback-noise message.

```sh
cd ex00
make
./megaphone hello world
make fclean
```

### ex01 — PhoneBook

Builds `phonebook`, an interactive phone book with a fixed capacity of eight
contacts. Supported commands are:

- `ADD` — create a contact
- `SEARCH` — list contacts and display one contact by index
- `EXIT` — quit the program

```sh
cd ex01
make
./phonebook
make fclean
```

When all eight slots are used, adding a new contact replaces the oldest one.

### ex02 — Account

Builds `account`, an implementation of the `Account` class based on the
provided header, test program, and reference log. It demonstrates shared
class-level statistics using `static` data members.

```sh
cd ex02
make
./account
make fclean
```

## Common Makefile targets

Run these targets from any exercise directory:

```sh
make        # build the executable
make clean  # remove object files
make fclean # remove object files and the executable
make re     # rebuild from scratch
```

## Repository layout

```text
.
├── ex00/          Megaphone
├── ex01/          PhoneBook and Contact
├── ex02/          Account
└── en.subject.pdf Module subject
```
