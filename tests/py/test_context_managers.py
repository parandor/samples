# test_context_managers.py

# Context Managers in Python provide a convenient way to manage resources,
# such as file handling or network connections, by ensuring that resources
# are acquired and released properly.

# They are implemented using a pair of methods: __enter__ and __exit__.
# The __enter__ method is called when entering the context, and __exit__
# is called when exiting the context, allowing for resource cleanup.

# Context Managers are commonly used with the 'with' statement to ensure
# that resources are properly managed and released even in the presence
# of exceptions.

# This file contains pytest tests showcasing different aspects of context managers.

import os
import pytest

def create_temp_file(content):
    # Intermediate Level: Context Manager for Temporary File
    import tempfile
    with tempfile.NamedTemporaryFile(mode='w+', delete=False) as file:
        file.write(content)
        return file.name

def test_basic_context_manager():
    # Beginner Level: Basic Context Manager Test
    filepath = 'sample.txt' 
    with open(filepath, 'w') as file:
        file.write('Hello, World!')

    with open(filepath, 'r') as file:
        content = file.read()

    assert content == 'Hello, World!'

    # Remove the file after the test
    if os.path.exists(filepath):
        os.remove(filepath)

def test_custom_context_manager():
    # Intermediate Level: Custom Context Manager Test
    class SampleContextManager:
        def __enter__(self):
            print("Entering the context")
            return self

        def __exit__(self, exc_type, exc_value, traceback):
            print("Exiting the context")

    with SampleContextManager() as scm:
        print("Inside the context")
        assert isinstance(scm, SampleContextManager)

def test_context_manager_for_file(tmpdir):
    # Intermediate Level: Context Manager for Temporary File Test
    content_to_write = "This is a temporary file."
    file_path = create_temp_file(content_to_write)

    with open(file_path, 'r') as file:
        content = file.read()

    assert content == content_to_write

def test_advanced_context_manager_usage(capsys):
    # Advanced Level: Advanced Context Manager Usage
    class CustomContextManager:
        def __enter__(self):
            print("Entering the advanced context")
            return self

        def __exit__(self, exc_type, exc_value, traceback):
            print("Exiting the advanced context")
            if exc_type is not None:
                print(f"An exception of type {exc_type} occurred with message: {exc_value}")

    with CustomContextManager() as ccm:
        print("Inside the advanced context")
        assert isinstance(ccm, CustomContextManager)

        with pytest.raises(ValueError, match="Simulated error"):
            # Use pytest.raises to check for the expected exception without printing its traceback
            raise ValueError("Simulated error")
