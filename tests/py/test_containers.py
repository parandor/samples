# test_containers.py

def test_list_usage():
    my_list = [1, 2, 3, 4, 5]
    
    # Beginner Level: List
    assert my_list == [1, 2, 3, 4, 5]

    # Intermediate Level: List
    my_list.append(6)
    my_list.extend([7, 8, 9])
    assert my_list == [1, 2, 3, 4, 5, 6, 7, 8, 9]

    # Advanced Level: List
    squared_values = [x**2 for x in my_list]
    assert squared_values == [1, 4, 9, 16, 25, 36, 49, 64, 81]

    # Additional tests for list methods
    assert my_list.pop() == 9
    assert my_list.count(4) == 1


def test_tuple_usage():
    my_tuple = (1, 2, 3, 4, 5)
    
    # Beginner Level: Tuple
    assert my_tuple == (1, 2, 3, 4, 5)

    # Intermediate Level: Tuple
    my_tuple += (6, 7, 8)
    assert my_tuple == (1, 2, 3, 4, 5, 6, 7, 8)

    # Additional tests for tuple methods
    assert my_tuple.index(6) == 5


def test_set_usage():
    my_set = {1, 2, 3, 4, 5}
    
    # Beginner Level: Set
    assert my_set == {1, 2, 3, 4, 5}

    # Intermediate Level: Set
    my_set.add(6)
    my_set.update({7, 8, 9})
    assert my_set == {1, 2, 3, 4, 5, 6, 7, 8, 9}

    # Additional tests for set methods
    my_set.remove(6)
    assert len(my_set) == 8


def test_dict_usage():
    my_dict = {'a': 1, 'b': 2, 'c': 3}
    
    # Beginner Level: Dictionary
    assert my_dict == {'a': 1, 'b': 2, 'c': 3}

    # Intermediate Level: Dictionary
    my_dict['d'] = 4
    my_dict.update({'e': 5, 'f': 6})
    assert my_dict == {'a': 1, 'b': 2, 'c': 3, 'd': 4, 'e': 5, 'f': 6}

    # Additional tests for dictionary methods
    assert my_dict.get('d') == 4
    assert 'e' in my_dict.keys()
