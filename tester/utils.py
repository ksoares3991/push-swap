
import os
import subprocess
import random
import re
from config import PUSH_SWAP, CHECKER

def run_cmd(cmd, input_data=None, timeout=10):
    try:
        proc = subprocess.run(cmd, input=input_data, text=True, capture_output=True, timeout=timeout)
        return proc.returncode, proc.stdout, proc.stderr
    except subprocess.TimeoutExpired:
        return -1, "", "Timeout"
    except Exception as e:
        return -1, "", str(e)

def run_valgrind(cmd, input_data=None):
    valgrind_cmd = ["valgrind", "--leak-check=full", "--show-leak-kinds=all", "--error-exitcode=42"] + cmd
    ret, out, err = run_cmd(valgrind_cmd, input_data)
    has_leaks = ret == 42 or ("definitely lost:" in err and "definitely lost: 0 bytes" not in err)
    return has_leaks, err

def generate_numbers(size, sorted_arr=False, reverse_arr=False, seed=None):
    nums = list(range(1, size + 1))
    if reverse_arr:
        nums.reverse()
    elif not sorted_arr:
        rng = random.Random(seed) if seed is not None else random
        rng.shuffle(nums)
    return [str(n) for n in nums]

def count_ops(output):
    if not output: return 0
    return len([line for line in output.strip().split('\n') if line])

def output_lines(output):
    if not output:
        return []
    return [line for line in output.splitlines() if line.strip()]

def bench_has_expected_fields(stderr):
    if not stderr:
        return False
    expected = [
        "[bench] disorder:",
        "[bench] strategy:",
        "[bench] total_ops:",
        "[bench] sa:",
        " sb:",
        " ss:",
        " pa:",
        " pb:",
        "[bench] ra:",
        " rb:",
        " rr:",
        " rra:",
        " rrb:",
        " rrr:",
    ]
    return all(token in stderr for token in expected)

def bench_disorder_is(stderr, expected_value):
    if not stderr:
        return False
    match = re.search(r"\[bench\] disorder:\s*(\d+\.\d{2})%", stderr)
    return bool(match) and match.group(1) == expected_value

def check_sorted(instructions, numbers_list):
    if not os.path.exists(CHECKER): return False, "checker_linux not found"
    ret, out, err = run_cmd([CHECKER] + numbers_list, input_data=instructions)
    return out.strip() == "OK", err
