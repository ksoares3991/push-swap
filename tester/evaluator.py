
from config import C_GREEN, C_RED, C_YELLOW, C_BLUE, C_CYAN, C_RESET
import time

class Evaluator:
    def __init__(self):
        self.results = {}
        self.current_module = ""
        self.critical_fail = False

    def start_module(self, name):
        self.current_module = name
        self.results[name] = []
        print(f"\n{C_CYAN}======================================================{C_RESET}")
        print(f"{C_CYAN}  MODULE: {name.upper()}{C_RESET}")
        print(f"{C_CYAN}======================================================{C_RESET}")

    def add_test(self, desc, passed, details=""):
        status = f"{C_GREEN}[ OK ]{C_RESET}" if passed else f"{C_RED}[ KO ]{C_RESET}"
        print(f"{status} {desc}")
        if details:
            color = C_GREEN if passed else C_YELLOW
            print(f"       -> {color}{details}{C_RESET}")
        
        self.results[self.current_module].append({
            'desc': desc, 'passed': passed, 'details': details
        })

    def fail_critical(self, reason):
        self.critical_fail = True
        print(f"\n{C_RED}CRITICAL FAILURE: {reason}{C_RESET}")
        
    def generate_feedback(self):
        print(f"\n{C_BLUE}>>> Generating feedback.txt...{C_RESET}")
        lines = []
        lines.append("="*70)
        lines.append("                  PUSH_SWAP DETAILED REPORT")
        lines.append("="*70)
        lines.append(f"Date: {time.strftime('%Y-%m-%d %H:%M:%S')}\n")
        
        total_passed = 0
        total_tests = 0
        
        for module, tests in self.results.items():
            mod_pass = sum(1 for t in tests if t['passed'])
            mod_tot = len(tests)
            total_passed += mod_pass
            total_tests += mod_tot
            
            lines.append(f"--- {module.upper()} ({mod_pass}/{mod_tot}) ---")
            for t in tests:
                status = "[OK]" if t['passed'] else "[KO]"
                lines.append(f"{status} {t['desc']}")
                if t['details']: lines.append(f"    > {t['details']}")
            lines.append("")
            
        lines.append("="*70)
        if self.critical_fail:
            lines.append("FINAL GRADE: 0 (Critical Failure Detected - Check Makefile or Norm)")
        else:
            score = int((total_passed / max(1, total_tests)) * 100)
            lines.append(f"FINAL SCORE ESTIMATE: {score}% ({total_passed}/{total_tests} tests passed)")
            
        with open("feedback.txt", "w") as f: f.write("\n".join(lines))
        print(f"{C_GREEN}Done! See feedback.txt for the full summary.{C_RESET}\n")
