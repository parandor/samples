// cart/cart.go
package cart

// Cart represents a shopping cart.
type Cart struct {
    Items map[int]int
}

// NewCart creates a new shopping cart.
func NewCart() *Cart {
    return &Cart{
        Items: make(map[int]int),
    }
}

// AddToCart adds a specified quantity of a product to the cart.
func (c *Cart) AddToCart(productID, quantity int) {
    c.Items[productID] += quantity
}
