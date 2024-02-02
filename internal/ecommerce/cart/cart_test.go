// cart/cart_test.go
package cart

import "testing"

func TestAddToCart(t *testing.T) {
    // Test case 1
    c := NewCart()
    c.AddToCart(1, 2)
    if c.Items[1] != 2 {
        t.Errorf("AddToCart(1, 2) returned %d, expected %d", c.Items[1], 2)
    }

    // Test case 2
    c.AddToCart(2, 1)
    if c.Items[2] != 1 {
        t.Errorf("AddToCart(2, 1) returned %d, expected %d", c.Items[2], 1)
    }

    // Add more test cases as needed
}
