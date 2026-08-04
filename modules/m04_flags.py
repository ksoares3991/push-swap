
from utils import (
    run_cmd,
    check_sorted,
    generate_numbers,
    count_ops,
    bench_has_expected_fields,
    bench_disorder_is,
)
from config import PUSH_SWAP

def run(ev):
    ev.start_module("Strategy Flags & Bench")
    nums = generate_numbers(20, seed=2026)
    
    for flag in ["--simple", "--medium", "--complex", "--adaptive"]:
        ret, out, err = run_cmd([PUSH_SWAP, flag] + nums)
        is_sorted, _ = check_sorted(out, nums)
        ev.add_test(f"Flag {flag}", ret == 0 and is_sorted, f"Ops: {count_ops(out)}" if is_sorted else "Falha na ordenacao")

    ret, adaptive_out, adaptive_err = run_cmd([PUSH_SWAP, "--adaptive"] + nums)
    ret, default_out, default_err = run_cmd([PUSH_SWAP] + nums)
    same_as_default = ret == 0 and default_out == adaptive_out
    ev.add_test("Default selector matches --adaptive", same_as_default, "Default output matches adaptive output" if same_as_default else "Outputs differ")

    ret, out, err = run_cmd([PUSH_SWAP, "--bench", "--simple", "5", "4", "3", "2", "1"])
    bench_ok = ret == 0 and count_ops(out) > 0 and bench_has_expected_fields(err)
    ev.add_test("Benchmark output includes all metrics", bench_ok, err if bench_ok else f"Stderr was: {err}")

    ret, out, err = run_cmd([PUSH_SWAP, "--bench", "--adaptive", "1", "2", "3", "4", "5"])
    disorder_ok = ret == 0 and count_ops(out) == 0 and bench_disorder_is(err, "0.00")
    ev.add_test("Benchmark disorder for sorted input", disorder_ok, err if disorder_ok else f"Stderr was: {err}")

    ret, out, err = run_cmd([PUSH_SWAP, "--adaptive", "--bench", "5", "4", "3", "2", "1"])
    reverse_bench_ok = ret == 0 and count_ops(out) > 0 and bench_disorder_is(err, "100.00")
    ev.add_test("Benchmark disorder for reverse input", reverse_bench_ok, err if reverse_bench_ok else f"Stderr was: {err}")
