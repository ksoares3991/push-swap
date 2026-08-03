
from utils import run_valgrind
from config import PUSH_SWAP

def run(ev):
    ev.start_module("Memory Leaks (Valgrind)")
    
    # Test valid input
    has_leaks, err = run_valgrind([PUSH_SWAP, "5", "1", "4", "2", "3"])
    ev.add_test("Valid input (5 numbers)", not has_leaks, "No leaks detected" if not has_leaks else "Leaks detected! Check valgrind log.")

    # Test benchmark path
    has_leaks, err = run_valgrind([PUSH_SWAP, "--bench", "--adaptive", "5", "4", "3", "2", "1"])
    ev.add_test("Valid input with --bench", not has_leaks, "No leaks detected in bench mode" if not has_leaks else "Leaks detected in bench mode!")
    
    # Test error input
    has_leaks, err = run_valgrind([PUSH_SWAP, "a", "b"])
    ev.add_test("Invalid input (Error trigger)", not has_leaks, "No leaks on error exit" if not has_leaks else "Leaks detected on error exit!")

    # Test empty argument error path
    has_leaks, err = run_valgrind([PUSH_SWAP, ""])
    ev.add_test("Invalid empty argument", not has_leaks, "No leaks on empty-argument error" if not has_leaks else "Leaks detected on empty-argument error!")
