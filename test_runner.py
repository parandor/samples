# Author: Peter Arandorenko
# Date: January 21, 2024

import os
import subprocess

class TestRunner:
    def __init__(self, test_directory, output_directory="bin", language="cpp", blacklist=None):
        self.test_directory = os.path.join(test_directory, language)
        self.output_directory = os.path.join(output_directory, language)
        self.language = language.lower()
        self.blacklist = blacklist or []
        os.makedirs(self.output_directory, exist_ok=True)

    def discover_tests(self):
        test_files = [file for file in os.listdir(self.test_directory) if file.endswith(f".{self.language}")]
        return test_files

    def compile_and_run_test(self, test_file):
        test_name = os.path.splitext(test_file)[0]
        output_binary = os.path.join(self.output_directory, test_name)

        self.compile_and_check(test_file, output_binary)
        self.run_and_check(output_binary)

    def compile_and_check(self, test_file, output_binary):
        compile_command = self.get_compile_command(test_file, output_binary)
        compile_result = subprocess.run(compile_command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

        if compile_result.returncode != 0:
            # Compilation failed
            print(f"Compilation failed for {test_file}")
            print(compile_result.stdout)
            print(compile_result.stderr)
            exit(1)  # Exit with a non-zero status code

    def run_and_check(self, output_binary):
        run_command = self.get_run_command(output_binary)
        run_result = subprocess.run(run_command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

        print(run_result.stdout)
        print(run_result.stderr)

        if run_result.returncode != 0:
            # Run failed
            print(f"Run failed for {output_binary}")
            print(run_result.stdout)
            print(run_result.stderr)
            exit(1)  # Exit with a non-zero status code

    def get_compile_command(self, test_file, output_binary):
        # Customize compile commands for different languages
        if self.language == "cpp":
            return f"g++ -fdiagnostics-color=always -g -std=c++17 {os.path.join(self.test_directory, test_file)} -o {output_binary} -lgtest -lgtest_main -pthread -I cget/include/ -L cget/lib/**"
                
        # Add more languages as needed
        else:
            raise ValueError(f"Unsupported language: {self.language}")

    def get_run_command(self, output_binary):
        # Customize run commands for different languages
        if self.language == "cpp":
            return output_binary
        # Add more languages as needed
        else:
            raise ValueError(f"Unsupported language: {self.language}")

    def run_tests(self):
        tests = self.discover_tests()

        for test_file in tests:
            if test_file in self.blacklist:
                print(f"Skipping test (blacklisted): {test_file}")
                continue

            print(f"Running test: {test_file}")
            self.compile_and_run_test(test_file)

if __name__ == "__main__":
    blacklist = ["serialization.cpp"]
    # Example usage for C++ tests
    cpp_test_runner = TestRunner(test_directory="tests", language="cpp", blacklist=blacklist)
    cpp_test_runner.run_tests()

    # Example usage for other language tests
    # Modify the language and test_directory accordingly
    # python_test_runner = TestRunner(test_directory="tests/python", language="python")
    # python_test_runner.run_tests()
