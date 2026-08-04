
from itertools import permutations

from utils import run_cmd, check_sorted, count_ops
from config import PUSH_SWAP

def run(ev):
    ev.start_module("Small Inputs")
    def evaluate_case(label, args, max_ops):
        ret, out, err = run_cmd([PUSH_SWAP] + args)
        ops = count_ops(out)
        is_sorted, checker_err = check_sorted(out, args)
        passed = ret == 0 and is_sorted and ops <= max_ops
        details = f"Sorted: {is_sorted} | Ops: {ops} (Max: {max_ops})"
        if not is_sorted:
            details += f" | Checker: {checker_err}"
        ev.add_test(label, passed, details)

    for perm in permutations(["2", "1", "0"]):
        evaluate_case(f"3 numbers {' '.join(perm)}", list(perm), 5)

    cases_5 = [
        ["1", "5", "2", "4", "3"],
        ["5", "1", "4", "2", "3"],
        ["3", "5", "1", "4", "2"],
        ["2", "4", "1", "5", "3"],
    ]

    for index, args in enumerate(cases_5, start=1):
        evaluate_case(f"5 numbers case {index}", args, 15)
