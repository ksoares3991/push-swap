
from utils import run_cmd
import os


def has_object_files(root="."):
    for current_root, _, files in os.walk(root):
        for name in files:
            if name.endswith(".o"):
                return True
    return False

def run(ev):
    ev.start_module("Compilation")
    if not os.path.exists("Makefile"):
        ev.add_test("Makefile exists", False, "Makefile not found in root")
        ev.fail_critical("No Makefile")
        return

    # Clean first
    run_cmd(["make", "fclean"])
    
    # Make
    ret, out, err = run_cmd(["make"])
    passed = ret == 0 and os.path.exists("./push_swap")
    ev.add_test("make builds push_swap", passed, "Compiled successfully" if passed else f"Error:\n{err}")
    
    if not passed:
        ev.fail_critical("Failed to compile push_swap")
        return

    ret, out, err = run_cmd(["make", "clean"])
    clean_ok = ret == 0 and not has_object_files() and os.path.exists("./push_swap")
    ev.add_test("make clean removes object files", clean_ok, "Object files removed" if clean_ok else f"make clean left artifacts:\n{err}")

    ret, out, err = run_cmd(["make", "fclean"])
    fclean_ok = ret == 0 and not os.path.exists("./push_swap") and not has_object_files()
    ev.add_test("make fclean removes binary and objects", fclean_ok, "Binary removed" if fclean_ok else f"make fclean left artifacts:\n{err}")

    ret, out, err = run_cmd(["make", "re"])
    re_ok = ret == 0 and os.path.exists("./push_swap") and not has_object_files()
    ev.add_test("make re rebuilds the project", re_ok, "Rebuilt successfully" if re_ok else f"Error:\n{err}")
