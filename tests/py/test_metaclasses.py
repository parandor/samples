# test_metaclasses.py

# Metaclasses in Python are classes for classes. They define how classes are created and behave.
# Metaclasses allow developers to customize the creation and behavior of classes at the time of definition.

# Metaclasses are often used in advanced scenarios where you need to control the structure or behavior
# of classes across an entire codebase. They provide a powerful mechanism for code organization and
# enforcing conventions.

# This file contains pytest tests showcasing different aspects of metaclasses.

class CustomMeta(type):
    def __new__(cls, name, bases, dct):
        # Advanced Level: Metaclass Example
        if 'custom_attribute' not in dct:
            dct['custom_attribute'] = 'Default Value'
        return super().__new__(cls, name, bases, dct)

class MyClass(metaclass=CustomMeta):
    pass

def test_metaclass_basic():
    # Beginner Level: Basic Metaclass Test
    assert hasattr(MyClass, 'custom_attribute')
    assert MyClass.custom_attribute == 'Default Value'

def test_metaclass_basic():
    # Beginner Level: Basic Metaclass Test
    assert hasattr(MyClass, 'custom_attribute')
    assert MyClass.custom_attribute == 'Default Value'

def test_metaclass_attribute_override():
    # Intermediate Level: Metaclass Attribute Override
    class MyDerivedClass(MyClass):
        custom_attribute = 'Overridden Value'
    
    assert MyDerivedClass.custom_attribute == 'Overridden Value'

def test_metaclass_instance():
    # Intermediate Level: Metaclass with Instance
    instance = MyClass()
    assert hasattr(instance, 'custom_attribute')
    assert instance.custom_attribute == 'Default Value'

def test_metaclass_inheritance():
    # Intermediate Level: Metaclass Inheritance
    class MyDerivedClassWithInheritance(MyClass):
        pass

    assert hasattr(MyDerivedClassWithInheritance, 'custom_attribute')
    assert MyDerivedClassWithInheritance.custom_attribute == 'Default Value'

def test_advanced_metaclass_usage():
    # Advanced Level: Advanced Metaclass Usage
    class AdvancedClass(metaclass=CustomMeta):
        additional_attribute = 'Additional Value'

    assert hasattr(AdvancedClass, 'custom_attribute')
    assert AdvancedClass.custom_attribute == 'Default Value'
    assert hasattr(AdvancedClass, 'additional_attribute')
    assert AdvancedClass.additional_attribute == 'Additional Value'
