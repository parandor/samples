// main.go
package main

import (
    "fmt"

	"github.com/parandor/samples/internal/ecommerce/cart"
	"github.com/parandor/samples/internal/ecommerce/inventory"
	"github.com/parandor/samples/internal/ecommerce/utils"
)

func main() {
    // Initialize inventory
    inv := inventory.NewInventory()

    // Add products to the inventory
    inv.AddProduct(inventory.Product{ID: 1, Name: "Laptop", Price: 1000.0})
    inv.AddProduct(inventory.Product{ID: 2, Name: "Phone", Price: 500.0})

    // Initialize shopping cart
    myCart := cart.NewCart()

    // Add products to the cart
    myCart.AddToCart(1, 2)
    myCart.AddToCart(2, 1)

    // Calculate total price using the utility function from the utils package
    totalPrice := utils.Add(int(inv.Products[1].Price*float64(myCart.Items[1])), int(inv.Products[2].Price*float64(myCart.Items[2])))

    // Display the cart contents and total price
    fmt.Println("Shopping Cart Contents:")
    for productID, quantity := range myCart.Items {
        fmt.Printf("Product ID: %d, Quantity: %d\n", productID, quantity)
    }
    fmt.Printf("Total Price: $%d\n", totalPrice)
}
