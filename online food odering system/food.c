#include <stdio.h>

#define TAX_RATE 0.07
#define MAX_ITEMS 10

typedef struct {
    int code;
    char name[30];
    float price;
} MenuItem;

typedef struct {
    MenuItem item;
    int quantity;
} OrderItem;

void displayMenu(MenuItem menu[], int size) {
    printf("\n--- MENU ---\n");
    printf("Code\tName\t\t\tPrice\n");
    for (int i = 0; i < size; i++) {
        printf("%d\t%-20s\t$%.2f\n", menu[i].code, menu[i].name, menu[i].price);
    }
}

MenuItem* findItem(MenuItem menu[], int size, int code) {
    for (int i = 0; i < size; i++) {
        if (menu[i].code == code)
            return &menu[i];
    }
    return NULL;
}

void calculateTotal(OrderItem orders[], int orderCount) {
    float subtotal = 0.0;
    printf("\n--- RECEIPT ---\n");
    printf("Item\t\tQty\tPrice\tTotal\n");
    
    for (int i = 0; i < orderCount; i++) {
        float total = orders[i].item.price * orders[i].quantity;
        printf("%-15s\t%d\t$%.2f\t$%.2f\n", orders[i].item.name, orders[i].quantity, orders[i].item.price, total);
        subtotal += total;
    }
    
    float tax = subtotal * TAX_RATE;
    float grandTotal = subtotal + tax;
    
    printf("\nSubtotal: $%.2f", subtotal);
    printf("\nTax (7%%): $%.2f", tax);
    printf("\nGrand Total: $%.2f\n", grandTotal);
}

int main() {
    MenuItem menu[] = {
        {101, "Burger", 5.99},
        {102, "Pizza", 8.49},
        {103, "Fries", 2.99},
        {104, "Soda", 1.99},
        {105, "Chicken Wrap", 6.75}
    };
    int menuSize = sizeof(menu) / sizeof(MenuItem);
    
    OrderItem orders[MAX_ITEMS];
    int orderCount = 0;
    int code, quantity;
    char choice;
    
    printf("Welcome to the Takeout Ordering System!\n");
    
    do {
        displayMenu(menu, menuSize);
        
        printf("\nEnter item code: ");
        scanf("%d", &code);
        
        MenuItem *selected = findItem(menu, menuSize, code);
        if (selected == NULL) {
            printf("Invalid code. Please try again.\n");
            continue;
        }
        
        printf("Enter quantity: ");
        scanf("%d", &quantity);
        
        if (quantity <= 0) {
            printf("Quantity must be greater than zero.\n");
            continue;
        }

        if (orderCount < MAX_ITEMS) {
            orders[orderCount].item = *selected;
            orders[orderCount].quantity = quantity;
            orderCount++;
        } else {
            printf("Order limit reached!\n");
            break;
        }

        printf("Would you like to order another item? (y/n): ");
        scanf(" %c", &choice);
        
    } while (choice == 'y' || choice == 'Y');
    
    calculateTotal(orders, orderCount);
    
    printf("\nThank you for your order!\n");
    
    return 0;
}
