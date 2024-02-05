# test_sequences.py

def test_range_usage():
    # Beginner Level: Range
    my_range = range(5)
    assert list(my_range) == [0, 1, 2, 3, 4]

    # Intermediate Level: Range
    my_range = range(2, 10, 2)
    assert list(my_range) == [2, 4, 6, 8]

    # Advanced Level: Range
    # Using the sum function with range to calculate the sum of values from 1 to 5
    sum_values = sum(range(1, 6))
    assert sum_values == 15


def test_bytes_usage():
    # Beginner Level: Bytes
    my_bytes = b'hello'
    assert list(my_bytes) == [104, 101, 108, 108, 111]

    # Intermediate Level: Bytes
    # Decoding bytes to string using utf-8
    decoded_str = my_bytes.decode('utf-8')
    assert decoded_str == 'hello'


def test_bytearray_usage():
    # Beginner Level: Bytearray
    my_bytearray = bytearray(b'world')
    assert list(my_bytearray) == [119, 111, 114, 108, 100]

    # Intermediate Level: Bytearray
    # Modifying the first element of the bytearray
    my_bytearray[0] = 120
    assert list(my_bytearray) == [120, 111, 114, 108, 100]


def test_memoryview_usage():
    # Beginner Level: Memoryview
    my_bytes = b'python'
    my_memoryview = memoryview(my_bytes)
    assert list(my_memoryview) == [112, 121, 116, 104, 111, 110]

    # Advanced Level: Memoryview
    # Slicing the memoryview and decoding the bytes to get the first three characters
    first_three_chars = bytes(my_memoryview[:3]).decode('utf-8')
    assert first_three_chars == 'pyt'

    # Advanced Level: Memoryview
    # Reversing the memoryview and decoding the bytes to check for reversal
    reversed_bytes = bytes(my_memoryview[::-1])
    assert reversed_bytes.decode('utf-8') == 'nohtyp'

    # Advanced Level: Memoryview
    # Concatenating two memoryviews and decoding the bytes to check for concatenation
    combined_bytes = bytes(my_memoryview) + bytes(memoryview(b' is great'))
    assert combined_bytes.decode('utf-8') == 'python is great'
