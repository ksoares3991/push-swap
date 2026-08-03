
from utils import run_cmd, count_ops
from config import PUSH_SWAP

def run(ev):
    ev.start_module("Identity Tests (Already Sorted)")
    tests = [
        (["42"], "Single number"),
        (["2", "3"], "Two numbers"),
        (["0", "1", "2", "3"], "Four numbers"),
        (["-5", "-4", "-3", "-2", "-1"], "Negative sorted numbers"),
        ([str(i) for i in range(15)], "15 sorted numbers")
    ]
    
    for args, desc in tests:
        ret, out, err = run_cmd([PUSH_SWAP] + args)
        passed = (ret == 0 and out.strip() == "" and err == "")
        ev.add_test(desc, passed, f"Output ops: {count_ops(out)}" if not passed else "No instructions printed")
