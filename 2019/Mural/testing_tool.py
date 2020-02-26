""" Python script for local testing (compatible with both Python 2 and Python 3)

Disclaimer: this is a way to test your solutions, but it is NOT the real judging
system. The judging system behavior might be different.

########## THIS SCRIPT DOES NOT WORK ##########

"""

from __future__ import print_function
import subprocess
import sys

USAGE_MSG = """
Usage:
Linux and Mac users:
  From your terminal, run
    python testing_tool.py command_to_run_your_script_or_executable
  Note that command_to_run_your_script_or_executable is read as a list of
  arguments, so you should NOT wrap it with quotation marks.

Examples:
C++, after compilation:
  python testing_tool.py ./my_binary
Python:
  python testing_tool.py python my_code.py
Java, after compilation:
  python testing_tool.py java my_main_class_name

See https://code.google.com/codejam/resources/faq#languages for how we compile
and run your solution in the language of your choice.

Windows users:
  Follow the instructions for Linux and Mac users if you are familiar with
  terminal tools on Windows. Otherwise, please be advised that this script might
  not work with Python 2 (it works with Python 3). In addition, if you cannot
  pass arguments to Python, you will need to modify the "cmd = sys.argv[1:]"
  line below.
"""

# Number of test cases derived from the length of the "WALLS" list. Enter ALL walls as strings of ints!
# The lengths of each wall will be determined from "len(WALLS[i])" at print time.
WALLS = ["1332", "9583", "616", "1029384756"]
ANSWERS = [6, 14, 7, 31]
NUM_TEST_CASES = len(WALLS)
# You can set PRINT_INTERACTION_HISTORY to True to print out the interaction
# history between your code and the judge.
PRINT_INTERACTION_HISTORY = True

"""Helper functions"""
def JudgePrint(p, s):
  # Print the judge output to your code's input stream. Log this interaction
  # to console (stdout) if PRINT_INTERACTION_HISTORY is True.
  print(s, file=p.stdin)
  p.stdin.flush()
  if PRINT_INTERACTION_HISTORY:
    print("Judge prints:", s)


def PrintSubprocessResults(p):
  # Print the return code and stderr output for your code.
  print("Your code finishes with exit status {}.".format(p.returncode))
  code_stderr_output = p.stderr.read()
  if code_stderr_output:
    print("The stderr output of your code is:")
    sys.stdout.write(code_stderr_output)
  else:
    print("Your code doesn't have stderr output.")


def WaitForSubprocess(p):
  # Wait for your code to finish and print the stderr output of your code for
  # debugging purposes.
  if p.poll() is None:
    print("Waiting for your code to finish...")
    p.wait()
  PrintSubprocessResults(p)


def CheckSubprocessExit(p, case_id):
  # Exit if your code finishes in the middle of a test case.
  if p.poll() is not None:
    print("Your code exited early, in the middle of Case #{}.".format(case_id))
    PrintSubprocessResults(p)
    sys.exit(-1)


def WrongAnswerExit(p, case_id, error_msg):
  print("\nCase #{} failed: {}".format(case_id, error_msg))
  WaitForSubprocess(p)
  sys.exit(-1)


"""Main function begins"""
# Retrieve the command to run your code from the arguments.
# If you cannot pass arguments to Python when running this testing tool, please
# replace sys.argv[1:] with the command list to run your code.
# e.g. C++ users: cmd = ["./my_binary"]
#      Python users: cmd = [sys.executable, "my_code.py"]
#      Java users: cmd = ["java", "my_main_class_name"]
cmd = sys.argv[1:]
assert cmd, "There should be at least one argument." + USAGE_MSG
if (cmd[0] == "-h") or (cmd[0] == "-help") or (cmd[0] == "--h") or (
    cmd[0] == "--help"):
  print(USAGE_MSG)
  sys.exit(0)

# Run your code in a separate process. You can debug your code by printing to
# stderr inside your code, or adding print statements in this testing tool.
# Note that your stderr output will be printed by this testing tool only after
# your code finishes, e.g. if your code hangs, you wouldn't get your stderr
# output.
try:
  p = subprocess.Popen(
      cmd,
      stdin=subprocess.PIPE,
      stdout=subprocess.PIPE,
      stderr=subprocess.PIPE,
      bufsize=1,
      universal_newlines=True)
except Exception as e:
  print("Failed to start running your code. Error:")
  print(e)
  sys.exit(-1)

JudgePrint(p, NUM_TEST_CASES)
for i in range(NUM_TEST_CASES):
    if PRINT_INTERACTION_HISTORY:
        print("Test Case #{}:".format(i + 1))
    JudgePrint(p, "{}".format(len(WALLS[i])))  # The length of the wall
    JudgePrint(p, WALLS[i])  # The actual wall itself
    p.stdin.flush()
    answer = "Guess #{}: {}".format(i + 1, ANSWERS[i])

    # Check user input
    CheckSubprocessExit(p, i + 1)
    user_input = ""
    try:
        user_input = p.stdout.readline()
    except:
        # Note that your code might finish after the first CheckSubprocessExit
        # check above but before the readline(), so we will need to again check
        # whether your code has finished.
        CheckSubprocessExit(p, i + 1)
        exit_msg = ""
        if user_input == "":
            exit_msg = ("Read an empty string for the guess. This might happen "
                    "because your code exited early, or printed an extra "
                    "newline character.")
        elif user_input is None:
            exit_msg = (
            "Unable to read the guess. This might happen because your "
            "code exited early, printed an extra new line character, or did "
            "not print the output correctly.")
        else:
            exit_msg = ("Failed to read the guess. Expected an answer of the form "
                    "Case #i: X. Read \"{}\" (quotes added to "
                    "isolate your output) instead.").format(user_input)
        WrongAnswerExit(p, i + 1, exit_msg)
    if PRINT_INTERACTION_HISTORY:
        print("Judge reads:", user_input)
        if (user_input == answer):
            print("Answer for case {} was correct.".format(i + 1))
        else:
            print("Answer for case {} was incorrect.".format(i + 1))
            print("Expected '{}', but instead received '{}'.".format(answer, user_input))

extra_output = p.stdout.readline()
WaitForSubprocess(p)
if extra_output == "":
  print("Congratulations! All test cases passed :)")
else:
  print("Wrong Answer because of extra output:")
  sys.stdout.write(extra_output)
  sys.exit(-1)

