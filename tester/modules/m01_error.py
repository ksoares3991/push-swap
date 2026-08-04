
from utils import run_cmd
from config import PUSH_SWAP

def run(ev):
    ev.start_module("Error Management")
    tests = [
        (["abc"], True, "Non-numeric parameters"),
        (["1", "2", "2"], True, "Duplicate numeric parameter"),
        (["2147483648"], True, "Greater than MAXINT"),
        (["-2147483649"], True, "Lower than MININT"),
        ([""], True, "Empty argument"),
        (["1", "2", "3", "a"], True, "Mixed valid and invalid"),
        ([], False, "No parameters")
    ]
    
    for args, expect_err, desc in tests:
        ret, out, err = run_cmd([PUSH_SWAP] + args)
        if expect_err:
            passed = ret != 0 and out == "" and err.strip() == "Error"
            ev.add_test(desc, passed, f"Expected exact 'Error\\n' on stderr, got: stdout={repr(out)} stderr={repr(err)} return={ret}")
        else:
            passed = (ret == 0 and out == "" and err == "")
            ev.add_test(desc, passed, "Expected completely silent output")
