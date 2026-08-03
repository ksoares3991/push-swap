*This project has been created as part of the 42 curriculum by vicdos-s, kasoares.*

# push_swap

[![Norminette](https://img.shields.io/badge/Norminette-passing-success?style=for-the-badge&logo=42)](https://github.com/42School/norminette)
[![C](https://img.shields.io/badge/language-C-blue.svg?style=for-the-badge&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))

## Description

`push_swap` is a C program that receives a list of integers and prints the smallest valid sequence of Push_swap operations needed to sort stack `a` in ascending order.

The program works with two stacks, `a` and `b`, and only the allowed operations from the subject. It validates the input, rejects duplicates and invalid integers, computes the disorder of the initial stack, and can select a strategy at runtime.

Current supported selectors in this repository are:

- `--simple`
- `--medium`
- `--complex`
- `--adaptive`
- `--bench`

## Instructions

Build the project with:

```sh
make
```

This produces the `push_swap` executable in the repository root.

Clean build artifacts with:

```sh
make clean
make fclean
```

Run the program with a stack of integers:

```sh
./push_swap 3 2 1
./push_swap --adaptive 4 67 3 87 23
```

Optional benchmark mode:

```sh
./push_swap --medium --bench 3 2 1 5 4
```

If no parameters are provided, the program prints nothing and returns immediately.

## Project Rules Covered Here

- Written in C.
- Uses `cc` with `-Wall -Wextra -Werror` in the Makefile.
- Provides the required `all`, `clean`, `fclean`, and `re` rules.
- Builds the bundled libft and ft_printf dependencies through their own Makefiles.
- Contains no global variables.
- Frees heap allocations on error paths and normal exit paths.

## Input and Output Rules

- Input must be a list of valid integers.
- Duplicate values are rejected.
- Invalid characters or out-of-range values produce `Error\n` on stderr.
- The operation stream is printed on stdout.
- Benchmark data is printed on stderr only when `--bench` is present.

## Strategies

### `--simple`

This mode uses `selection_sort`.

It repeatedly finds the smallest value in stack `a`, rotates the stack with `ra` or `rra` depending on which side is cheaper, pushes that smallest value to stack `b`, and repeats until only three elements remain. The remaining three elements are ordered with a dedicated `order_three` routine, then the values are pushed back from `b` to `a`.

Why this is a valid `O(n^2)` strategy in the Push_swap model:

- each extraction scans the current stack to find the minimum
- each round can traverse most of the remaining stack
- the process repeats for many elements
- the total number of Push_swap operations grows quadratically in the worst case

This is a good baseline, but it is not the best choice for large random inputs.

### `--medium`

This mode uses `medium_sort`, implemented as a K-sort style strategy.

The algorithm first creates a sorted auxiliary array to rank the values, then performs two phases:

- Phase 1 pushes values from `a` to `b` using a sliding window of roughly $1.4\sqrt{n}$ ranks.
- Phase 2 pulls values back from `b` to `a` by always bringing the current maximum in `b` to the top with the fewest rotations.

Why this is a reasonable `O(n\sqrt{n})`-style strategy in practice:

- the window size limits how many values are skipped before a push happens
- the structure reduces the number of full-stack traversals compared with `simple`
- the stack `b` is organized so that the largest values are recovered efficiently
- the operation count is much lower on large, mixed inputs

This is the strategy currently used for the random 500-element benchmark in this repository.

### `--complex`

This selector is reserved for the high-complexity strategy.

Placeholder for the final implementation:

- target complexity class: `O(n log n)`
- internal method: `{{DESCRIBE_IMPLEMENTATION_HERE}}`
- selection rationale: `{{DESCRIBE_SELECTION_CRITERIA_HERE}}`
- space argument: `{{DESCRIBE_SPACE_BOUND_HERE}}`

### `--adaptive`

This mode chooses a strategy automatically from the measured disorder.

Current thresholds in the code:

- disorder below `0.2`: `selection_sort`
- disorder from `0.2` to below `0.5`: `medium_sort`
- disorder at or above `0.5`: complex placeholder branch

This is documented so the runtime decision matches the implementation and can be defended during evaluation.

## Benchmark

When `--bench` is enabled, the program prints metrics to stderr after sorting:

- computed disorder with two decimals
- strategy name
- total number of operations
- count for each operation type

Example output format:

```text
[bench] disorder: XX.XX%
[bench] strategy: ...
[bench] total_ops: N
[bench] sa: ... sb: ... ss: ... pa: ... pb: ...
[bench] ra: ... rb: ... rr: ... rra: ... rrb: ... rrr: ...
```

### The Real Worst Case for `--simple`

A random input is a practical worst case for the simple strategy because the smallest value is frequently far from the top of stack `a`, which forces repeated rotations before each push.

Run this exact comparison locally:

```sh
ARG=$(shuf -i 1-1000 -n 500)
./push_swap $ARG --simple --bench
./push_swap $ARG --medium --bench
```

Example result from the current codebase with one such random sample:

| Mode | total_ops |
| --- | ---: |
| simple | 32967 |
| medium | 16967 |

## Algorithm Justification

The chosen strategies reflect the current implementation and the Push_swap operation model:

- `simple` is intentionally quadratic and easy to reason about.
- `medium` reduces the number of rotations by using rank windows and a second recovery phase.
- `adaptive` uses the measured disorder to decide which implementation is the most appropriate.
- `complex` is reserved for the future `O(n log n)` path and is documented here as a placeholder until the real algorithm is finalized.

## Resources

- The official 42 Push_swap subject and evaluation guide.
- The C `read`, `write`, `malloc`, and `free` man pages.
- Libft and ft_printf, both bundled in this repository.
- The `checker_linux` binary included in the workspace for local verification.
- AI usage: ChatGPT/Copilot was used to review README structure, align the documentation with the subject requirements, and refine the benchmark explanation. All content was checked against the repository code before being kept.

## Links

[![GitHub](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/ksoares3991/push-swap)
