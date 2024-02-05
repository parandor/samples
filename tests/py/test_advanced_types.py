# test_advanced_types.py

def test_complex_usage():
    # Advanced Level: Complex
    complex_number = 3 + 4j
    assert complex_number.real == 3
    assert complex_number.imag == 4

    # Additional tests for complex numbers
    conjugate_complex = complex_number.conjugate()
    assert conjugate_complex.real == 3
    assert conjugate_complex.imag == -4


def test_type_usage():
    # Advanced Level: Type
    my_int = 42
    assert type(my_int) == int

    my_str = "Hello, World!"
    assert type(my_str) == str

    my_list = [1, 2, 3]
    assert type(my_list) == list

    # Additional tests for type
    assert not isinstance(3.14, type(my_int)) 


def test_object_usage():
    class CustomObject:
        def __init__(self, value):
            self.value = value

    # Advanced Level: Object
    my_object = CustomObject(42)
    assert isinstance(my_object, CustomObject)
    assert my_object.value == 42

    # Additional tests for object
    another_object = object()
    assert isinstance(another_object, object)

