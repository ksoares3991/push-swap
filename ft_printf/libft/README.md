*This project has been created as part of the 42 curriculum by vicdos-s.*

# Libft

## Description

Libft is a custom C library developed for the 42 curriculum. Its goal is to provide a reusable foundation of low-level utilities by reimplementing common C standard library functions, string and memory helpers, and a simple singly linked list API. The project is designed to reinforce concepts such as pointer handling, dynamic memory allocation, and manual resource management while producing a portable static library.

The library includes:
- standard libc-style functions for character checks, memory operations, and string handling
- extra string utilities for common tasks such as joining, trimming, splitting, and integer conversion
- file descriptor output helpers for controlled text and number printing
- linked list operations for basic list creation, traversal, modification, and cleanup

## Instructions

### Compilation

Run the following command inside the project folder:

```bash
make
```

This produces the static library `libft.a`.

### Cleaning

```bash
make clean      # remove object files (*.o)
make fclean     # remove object files and the library file
make re         # run fclean then make
```

### Using the library

Include the library header in your source code:

```c
#include "libft.h"
```

Compile your program with the static library:

```bash
cc -Wall -Wextra -Werror your_program.c -L. -lft -o your_program
```

If your program uses functions from `libft.h`, make sure the library is linked after the source files.

## Library Overview

The project library is divided into three main groups:

### 1. libc-style reimplemented functions

These functions mirror the behavior of common standard C library functions:

- `int ft_isalpha(int c)` — checks whether `c` is an alphabetic character.
- `int ft_isdigit(int c)` — checks whether `c` is a digit (0–9).
- `int ft_isalnum(int c)` — checks whether `c` is alphanumeric.
- `int ft_isascii(int c)` — checks whether `c` is a valid ASCII character.
- `int ft_isprint(int c)` — checks whether `c` is a printable character.
- `size_t ft_strlen(const char *s)` — returns the length of string `s`.
- `void *ft_memset(void *b, int c, size_t len)` — fills `len` bytes of memory pointed by `b` with value `c`.
- `void ft_bzero(void *s, size_t n)` — sets `n` bytes of memory pointed by `s` to zero.
- `void *ft_memcpy(void *dest, const void *src, size_t n)` — copies `n` bytes from `src` to `dest`.
- `void *ft_memmove(void *dest, const void *src, size_t len)` — copies `len` bytes from `src` to `dest`, safe for overlapping memory.
- `size_t ft_strlcpy(char *dest, const char *src, size_t dstsize)` — copies up to `dstsize - 1` characters from `src` to `dest` and null-terminates.
- `size_t ft_strlcat(char *dest, const char *src, size_t dstsize)` — appends `src` to `dest` without exceeding `dstsize` and returns the total length.
- `int ft_toupper(int c)` — converts a lowercase character to uppercase.
- `int ft_tolower(int c)` — converts an uppercase character to lowercase.
- `char *ft_strchr(const char *s, int c)` — returns a pointer to the first occurrence of `c` in `s`.
- `char *ft_strrchr(const char *s, int c)` — returns a pointer to the last occurrence of `c` in `s`.
- `int ft_strncmp(const char *s1, const char *s2, size_t n)` — compares up to `n` characters of `s1` and `s2`.
- `void *ft_memchr(const void *s, int c, size_t n)` — scans `n` bytes of memory for the byte `c`.
- `int ft_memcmp(const void *s1, const void *s2, size_t n)` — compares `n` bytes of two memory blocks.
- `char *ft_strnstr(const char *haystack, const char *needle, size_t len)` — locates a substring in the first `len` bytes of `haystack`.
- `int ft_atoi(const char *str)` — converts a string to an integer.
- `void *ft_calloc(size_t count, size_t size)` — allocates zero-initialized memory for an array.
- `char *ft_strdup(const char *s1)` — allocates and duplicates the string `s1`.

### 2. string utilities and I/O helpers

Additional helper functions implemented in the library:

- `char *ft_substr(char const *s, unsigned int start, size_t len)` — returns a newly allocated substring from `s` starting at `start`.
- `char *ft_strjoin(char const *s1, char const *s2)` — returns a new string that is the concatenation of `s1` and `s2`.
- `char *ft_strtrim(char const *s1, char const *set)` — returns a new string with characters from `set` removed from both ends of `s1`.
- `char **ft_split(char const *s, char c)` — splits `s` by delimiter `c` and returns a NULL-terminated array of strings.
- `char *ft_itoa(int n)` — converts integer `n` to a newly allocated string.
- `char *ft_strmapi(char const *s, char (*f)(unsigned int, char))` — applies function `f` to each character of `s` and returns a new string.
- `void ft_striteri(char *s, void (*f)(unsigned int, char *))` — applies function `f` to each character of `s` in place.
- `void ft_putchar_fd(char c, int fd)` — writes character `c` to file descriptor `fd`.
- `void ft_putstr_fd(char *s, int fd)` — writes string `s` to file descriptor `fd`.
- `void ft_putendl_fd(char *s, int fd)` — writes string `s` followed by a newline to file descriptor `fd`.
- `void ft_putnbr_fd(int n, int fd)` — writes integer `n` as characters to file descriptor `fd`.

### 3. linked list management

The library also provides a simple singly linked list API. The list node type is defined as:

```c
typedef struct s_list
{
    void          *content;
    struct s_list *next;
}   t_list;
```

Implemented linked list functions:

- `t_list *ft_lstnew(void *content)` — allocates a new list node with `content`.
- `void ft_lstadd_front(t_list **lst, t_list *new)` — adds node `new` to the beginning of `lst`.
- `int ft_lstsize(t_list *lst)` — returns the number of nodes in `lst`.
- `t_list *ft_lstlast(t_list *lst)` — returns the last node of `lst`.
- `void ft_lstadd_back(t_list **lst, t_list *new)` — adds node `new` to the end of `lst`.
- `void ft_lstdelone(t_list *lst, void (*del)(void *))` — deletes one node using `del` to free its content.
- `void ft_lstclear(t_list **lst, void (*del)(void *))` — deletes all nodes in `lst` and frees their contents using `del`.
- `void ft_lstiter(t_list *lst, void (*f)(void *))` — applies function `f` to the content of each node.
- `t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))` — creates a new list by applying `f` to each content element and frees on failure using `del`.

## Resources

- 42 libft subject (PDF) — the official spec, defining mandatory and bonus functions, constraints and the Norm.

- man pages — consulted function by function.

- OpenBSD manual pages — reference for functions such as `strlcpy`, `strnstr`, and `strlcat`, which are not part of the C standard library but are included in this implementation following OpenBSD's specifications.

- GNU libc documentation — used when POSIX and OpenBSD left ambiguities (especially for functions like calloc and itoa edge cases).

- Norminette — 42’s style checker, kept running after every commit to guarantee compliance with the school’s code standard.

### AI usage

DeepSeek AI was used specifically to help review and polish this README.md file.
Its contributions were limited to:

- suggesting a clear, project‑friendly structure for the documentation,

- rephrasing sentences to better match the tone expected in 42 projects,

- ensuring all sections (description, building, usage, resources) were aligned with the libft subject’s scope.

        No source code was generated by AI; the implementation of library functions was written manually.
