// inventory/inventory_test.go
package inventory_test

import (
	"testing"

	inventory "github.com/parandor/samples/internal/ecommerce/inventory"
)

func TestAddProduct(t *testing.T) {
	// Test case 1
	inv := inventory.NewInventory()
	inv.AddProduct(inventory.Product{ID: 1, Name: "Laptop", Price: 1000.0})
	if _, exists := inv.Products[1]; !exists {
		t.Errorf("AddProduct(Product{ID: 1}) did not add the product to the inventory")
	}

	// Test case 2
	inv.AddProduct(inventory.Product{ID: 2, Name: "Phone", Price: 500.0})
	if _, exists := inv.Products[2]; !exists {
		t.Errorf("AddProduct(Product{ID: 2}) did not add the product to the inventory")
	}

	// Add more test cases as needed
}
