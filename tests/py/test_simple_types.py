def test_integer_type():
    assert isinstance(42, int)

def test_float_type():
    assert isinstance(3.14, float)

def test_string_type():
    assert isinstance("Hello, World!", str)

def test_boolean_type():
    assert isinstance(True, bool)

def test_none_type():
    assert isinstance(None, type(None))

