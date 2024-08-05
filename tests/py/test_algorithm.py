
class Stringer:

    #  Write an algorithm that will return true if input string is a mirror of itself, false otherwise
    #  Eg: abba = true
    #      abcb = false
    #  Option 1. -> ab ba -> ab ab -> a-a=0 b-b=0 if !0, then it's not mirror string
    #  Option 2. -> two ptrs, if ptrs pointing to same char -> good, else, not a mirror string
    def isMirror(self, source):
        if len(source) <= 0:
            return False
        
        # Odd strings are not mirror strings
        if len(source) % 2 != 0:
            return False
        
        for i in range(len(source)):
            if i > len(source)/2:
                return True
            l = source[i]
            r = source[len(source)-1-i]
            if l != r:
                return False
        
        return True
    
def test_string_is_mirror():
    stringer = Stringer()

    assert(stringer.isMirror("abba")) 
    assert(not stringer.isMirror("abbaabbaabbazabbaabbaabba")) 
    assert(not stringer.isMirror("")) 
    assert(not stringer.isMirror("1111111")) 
    assert(stringer.isMirror("abbaabba")) 