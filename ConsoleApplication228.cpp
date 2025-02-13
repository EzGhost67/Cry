#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

class Product {
public:
    Product(int id, const std::string& name, double price)
        : id(id), name(name), price(price) {
    }

    int getId() const { return id; }
    std::string getName() const { return name; }
    double getPrice() const { return price; }

private:
    int id;
    std::string name;
    double price;
};

class Customer {
public:
    Customer(int id, const std::string& name)
        : id(id), name(name) {
    }

    int getId() const { return id; }
    std::string getName() const { return name; }

private:
    int id;
    std::string name;
};

class Order {
public:
    Order(int orderId, const Customer& customer)
        : orderId(orderId), customer(customer) {
    }

    void addProduct(const Product& product) {
        products.push_back(product);
    }

    double calculateTotal() const {
        double total = 0;
        for (const auto& product : products) {
            total += product.getPrice();
        }
        return total;
    }

    void printOrder() const {
        std::cout << "Order ID: " << orderId << "\nCustomer: " << customer.getName() << "\nProducts:\n";
        for (const auto& product : products) {
            std::cout << "- " << product.getName() << " ($" << product.getPrice() << ")\n";
        }
        std::cout << "Total: $" << calculateTotal() << "\n";
    }

private:
    int orderId;
    Customer customer;
    std::vector<Product> products;
};

class Store {
public:
    void addProduct(const Product& product) {
        products.push_back(product);
    }

    void createOrder(const Customer& customer) {
        int orderId = orders.size() + 1; 
        orders.emplace_back(orderId, customer);
    }

    Order& getOrder(int orderId) {
        if (orderId <= 0 || orderId > orders.size()) {
            throw std::out_of_range("Order ID is out of range.");
        }
        return orders[orderId - 1];
    }

private:
    std::vector<Product> products;
    std::vector<Order> orders;
};
int main() {
    try {
        Store store;

        
        store.addProduct(Product(1, "Apple", 0.99));
        store.addProduct(Product(2, "Banana", 0.59));
        store.addProduct(Product(3, "Orange", 0.79));

        
        Customer customer(1, "John Doe");

        
        store.createOrder(customer);
        Order& order = store.getOrder(1);

       
        order.addProduct(Product(1, "Apple", 0.99));
        order.addProduct(Product(2, "Banana", 0.59));

        
        order.printOrder();

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
