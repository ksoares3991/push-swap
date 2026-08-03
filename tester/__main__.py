
import sys
from evaluator import Evaluator
from modules import m00_compile, m01_error, m02_identity, m03_small, m04_flags, m05_performance, m06_leaks

def main():
    ev = Evaluator()
    try:
        m00_compile.run(ev)
        if ev.critical_fail:
            ev.generate_feedback()
            sys.exit(1)
            
        m01_error.run(ev)
        m02_identity.run(ev)
        m03_small.run(ev)
        m04_flags.run(ev)
        m05_performance.run(ev)
        m06_leaks.run(ev)
        
    except KeyboardInterrupt:
        print("\nTest aborted by user.")
    finally:
        ev.generate_feedback()

if __name__ == '__main__':
    main()
