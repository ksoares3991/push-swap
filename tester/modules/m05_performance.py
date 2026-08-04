
from utils import run_cmd, generate_numbers, count_ops, check_sorted
from config import PUSH_SWAP, THRESHOLDS_100, THRESHOLDS_500

def run(ev):
    ev.start_module("Performance (100 & 500)")

    def evaluate_case(label, size, seed, thresholds):
        nums = generate_numbers(size, seed=seed)
        ret, out, err = run_cmd([PUSH_SWAP] + nums)
        ops = count_ops(out)
        is_sorted, checker_err = check_sorted(out, nums)
        tier = "FAIL"
        if ops < thresholds['excellent']:
            tier = "EXCELLENT"
        elif ops < thresholds['good']:
            tier = "GOOD"
        elif ops < thresholds['pass']:
            tier = "PASS"

        passed = ret == 0 and is_sorted and ops < thresholds['pass']
        details = f"Sorted: {is_sorted} | Ops: {ops} | Tier: {tier}"
        if not is_sorted:
            details += f" | Checker: {checker_err}"
        ev.add_test(label, passed, details)

    evaluate_case("100 random numbers seed 1001", 100, 1001, THRESHOLDS_100)
    evaluate_case("100 random numbers seed 1002", 100, 1002, THRESHOLDS_100)
    evaluate_case("500 random numbers seed 5001", 500, 5001, THRESHOLDS_500)
    evaluate_case("500 random numbers seed 5002", 500, 5002, THRESHOLDS_500)
