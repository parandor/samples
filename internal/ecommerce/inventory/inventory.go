// inventory/inventory.go
package inventory

// Product represents a product in the inventory.
type Product struct {
    ID    int
    Name  string
    Price float64
}

// Inventory represents the product inventory.
type Inventory struct {
    Products map[int]Product
}

// NewInventory creates a new inventory.
func NewInventory() *Inventory {
    return &Inventory{
        Products: make(map[int]Product),
    }
}

// AddProduct adds a product to the inventory.
func (inv *Inventory) AddProduct(product Product) {
    inv.Products[product.ID] = product
}
