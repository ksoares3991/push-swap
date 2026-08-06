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

## Contributions

| Area | Files | Author |
| --- | --- | --- |
| Stack operations (`sa`/`sb`/`ss`, `ra`/`rb`/`rr`, `rra`/`rrb`/`rrr`, `pa`/`pb`) | `op_swap.c`, `op_rotate.c`, `op_rev_rotate.c`, `op_push.c` | kasoares |
| Simple sort baseline | `algo_simple_sort.c` | kasoares |
| Parsing, flags, error handling | `parser_utils.c`, `flag_utils.c`, `utils.c`, `compare_utils.c` | vicdos-s |
| Main dispatch, disorder metric, adaptive routing | `push_swap.c` | vicdos-s |
| Medium algorithm (K-sort / chunk-based) | `algo_medium_sort.c`, `algo_medium_sort_utils.c` | vicdos-s and kasoares |
| Complex algorithm (rank-based quicksort variant) | `algo_complex_sort.c` | kasoares |
| Shared utilities, init/free | `init.c`, `algo_sort_utils.c` | vicdos-s |
| Benchmark subsystem | `bench.c` | vicdos-s |
| README, testing | — | vicdos-s and kasoares |

Both learners reviewed and understand every algorithm in this repository, as required for the defense.

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

### `--complex`

This mode uses `quick_sort`, a rank-based quicksort variant adapted to the
two-stack model.

The algorithm first calls `normalize_ranks`, which assigns every value in `a`
its rank (0 to n-1) by counting how many other values are smaller. All
subsequent decisions operate on ranks instead of raw integers, which lets the
partition logic work with plain index arithmetic instead of caring about the
actual value range.

`order_chunk(state, low, high)` then recurses on rank ranges:

- The pivot is the deterministic midpoint `(low + high) / 2` of the current
  rank range, not a value drawn from the data. Because ranks form a
  permutation of `0..n-1`, this midpoint always splits the range into two
  halves of equal size, regardless of input order.
- `partition_chunk` walks the top of `a`: values with rank `<= pivot` are
  pushed to `b` with `pb`; values with rank `> pivot` are rotated to the
  bottom of `a` with `ra` and counted as "stays".
- `restore_stays` brings the "stays" group back to the top of `a` with `rra`
  (skipped when the chunk being partitioned is the whole of `a`, since in
  that case the rotations already restored the original order).
- The algorithm recurses on the high half first (still in `a`), then pulls
  the low half back from `b` with `pa`, then recurses on the low half.

Why this is an `O(n log n)`-class strategy in the Push_swap operation model:

- the deterministic midpoint pivot guarantees an exact 50/50 split at every
  level, so the recursion has depth `ceil(log2(n))` regardless of input —
  there is no data-dependent worst case, unlike a classic quicksort with a
  first/last-element pivot
- each level partitions every element it touches with a bounded number of
  operations (one `pb`/`ra` per element, plus the restore passes), so total
  work per level is `O(chunk size)`
- summed over `O(log n)` levels, the total operation count is `O(n log n)`

Space argument: the algorithm uses no heap allocation beyond the ranks
already stored in `t_node`. The only "space" cost in the Push_swap model is
recursion depth, which is `O(log n)` stack frames — negligible even at
n = 500.

Selection rationale: a rank-normalized quicksort was chosen over a
merge-sort-style adaptation because merge sort on two stacks needs an
auxiliary buffer to interleave runs, and the two available stacks *are* the
only buffers this model gives you. Partitioning in place onto `b` and back
avoids needing a third structure.

### `--adaptive`

This mode chooses a strategy automatically from the measured disorder.

Current thresholds in the code:

- disorder below `0.2`: `selection_sort`
- disorder from `0.2` to below `0.5`: `medium_sort`
- disorder at or above `0.5`: `quick_sort`

This is documented so the runtime decision matches the implementation and can be defended during evaluation.

> **Note on the 0.5 boundary:** a uniformly random permutation has an
> *expected* disorder of exactly 0.5, since every pair is inverted with
> probability 1/2. This means a random `shuf`-generated benchmark input will
> land on either side of the `medium`/`complex` threshold roughly at random.
> This is a direct consequence of the subject's mandated thresholds
> (VI.3.3), not an implementation choice — the boundary cannot be moved
> without violating the disorder-regime requirement.

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

### Measured performance against the subject's targets (VI.6)

Each cell is the worst observed operation count across 10 runs (n=100) or
5 runs (n=500) of uniformly random input, generated with `shuf`.

| n | strategy | worst ops | target for "pass" | target for "excellent" |
| --- | --- | ---: | ---: | ---: |
| 100 | `--adaptive` (default) | 1121 | < 2000 | < 700 |
| 100 | `--medium` | 606 | < 2000 | < 700 |
| 100 | `--complex` | 1123 | < 2000 | < 700 |
| 500 | `--adaptive` (default) | 7641 | < 12000 | < 5500 |
| 500 | `--medium` | 5168 | < 12000 | < 5500 |
| 500 | `--complex` | 7635 | < 12000 | < 5500 |
| 500 | `--simple` | 33440 | *n/a* | *n/a — O(n²) is required by VI.3.3, not optimized for this size* |

Reproduce with:

```sh
ARG=$(shuf -i 0-9999 -n 500 | tr '\n' ' ')
./push_swap $ARG --bench
```

### The Real Worst Case for `--simple`

A random input is a practical worst case for the simple strategy because the
smallest value is frequently far from the top of stack `a`, which forces
repeated rotations before each push. See the measured `n=500` row for
`--simple` in the benchmark table above for the actual operation count on
this codebase.

Run this exact comparison locally:

```sh
ARG=$(shuf -i 0-9999 -n 500 | tr '\n' ' ')
./push_swap $ARG --simple --bench
./push_swap $ARG --medium --bench
```
## Algorithm Justification

The chosen strategies reflect the current implementation and the Push_swap operation model:

- `simple` is intentionally quadratic and easy to reason about.
- `medium` reduces the number of rotations by using rank windows and a second recovery phase.
- `adaptive` uses the measured disorder to decide which implementation is the most appropriate.
- `complex` implements a rank-based quicksort variant with a deterministic
  midpoint pivot, guaranteeing `O(n log n)` operation count regardless of
  input order (see the `--complex` section above for the full argument).

## Resources

- The official 42 Push_swap subject and evaluation guide.
- The C `read`, `write`, `malloc`, and `free` man pages.
- Libft and ft_printf, both bundled in this repository.
- The `checker_linux` binary included in the workspace for local verification.

## AI Usage

- **Claude** was used to (1) statically review the codebase for Norm
  compliance, memory safety, and logic bugs — every issue it raised was
  independently verified by compiling with
  `-Wall -Wextra -Werror -fsanitize=address,undefined` and by running
  `norminette`, not taken on faith; (2) generate an end-to-end bash/Python
  test harness (`tester.sh`, `ps_check.py`) that is tooling used during
  development and is not part of the graded submission; (3) help structure
  and word this README.
- **Google Gemini** was used occasionally for (1) interpreting Valgrind
  error output during debugging, and (2) English localization of this
  README.
- No push_swap algorithm or logic code was written by AI. The code policy
  for this project required all implementation to be done by the learners
  themselves; AI use was limited to review, testing, and documentation.


## Links

[![GitHub](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/ksoares3991/push-swap)
