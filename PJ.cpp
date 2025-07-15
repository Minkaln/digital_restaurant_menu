#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

// Class for menu items (food or drink)
class MenuItem 
{
public:
        int id;
        string name;
        float price;

        MenuItem(int id, string name, float price) 
        : id(id), name(name), price(price) {}
};

// Class for ordered items
class OrderItem 
{
public:
       MenuItem item;
       int quantity;

       OrderItem(MenuItem item, int quantity)
       : item(item), quantity(quantity) {}

       float getTotal() 
       const {return item.price * quantity;}
};

// Main system class
class RestaurantOrderingSystem 
{
private:
        vector<MenuItem> foodMenu;
        vector<MenuItem> drinkMenu;
        vector<OrderItem> orders;
        float totalBill = 0.0;

public:
       RestaurantOrderingSystem() 
       {
       // Food items
       foodMenu.push_back(MenuItem(1, "Fries rice with fries chicken", 5.00));
       foodMenu.push_back(MenuItem(2, "Fries rice with BBQ chicken", 5.00));
       foodMenu.push_back(MenuItem(3, "Rice with fries chicken", 4.50));
       foodMenu.push_back(MenuItem(4, "Rice with BBQ chicken", 4.50));
       foodMenu.push_back(MenuItem(5, "Fries rice with fries pork", 5.00));
       foodMenu.push_back(MenuItem(6, "Fries rice with BBQ pork", 5.00));
       foodMenu.push_back(MenuItem(7, "Rice with fries pork", 4.50));
       foodMenu.push_back(MenuItem(8, "Rice with BBQ pork", 4.50));
       foodMenu.push_back(MenuItem(9, "Pork kathiew", 3.00));
       foodMenu.push_back(MenuItem(10, "Cow meat ball kathiew", 3.50));

       // Drink items
       drinkMenu.push_back(MenuItem(11, "Ice lemon green tea", 2.00));
       drinkMenu.push_back(MenuItem(12, "Ice lemon red tea", 2.00));
       drinkMenu.push_back(MenuItem(13, "Ice latte", 1.60));
       drinkMenu.push_back(MenuItem(14, "Ice americano", 1.50));
       drinkMenu.push_back(MenuItem(15, "Ice tea", 0.50));
       }

    void displayMenu() 
    {
        system("cls");
        cout << "=================================================\n";
        cout << "                 Jing Breakfast                  \n";
        cout << "=================================================\n";
        cout << "                      Food                       \n";
        cout << "-------------------------------------------------\n";
        cout << "ID\tFood Name\t\t\tPrice\n";
        cout << "-------------------------------------------------\n";

        for (const auto& item : foodMenu) 
        {
            cout << item.id << "\t" << setw(30) << left << item.name
                 << "\t$" << fixed << setprecision(2) << item.price << endl;
        }

        cout << "-------------------------------------------------\n";
        cout << "                    Drinks                       \n";
        cout << "-------------------------------------------------\n";
        cout << "ID\tDrink Name\t\t\tPrice\n";
        cout << "-------------------------------------------------\n";

        for (const auto& item : drinkMenu) 
        {
            cout << item.id << "\t" << setw(30) << left << item.name
                 << "\t$" << fixed << setprecision(2) << item.price << endl;
        }

        cout << " 0\tExit\n";
        cout << "=================================================\n";
    }

    MenuItem* findItemById(int id) 
    {
        for (auto& item : foodMenu)
            if (item.id == id) return &item;

        for (auto& item : drinkMenu)
            if (item.id == id) return &item;

        return nullptr;
    }

    void takeOrder() 
    {
        int option = -1;

        while (true) 
        {
            displayMenu();
            cout << "Enter Food or Drink ID you want to order: ";
            cin >> option;

            if (cin.fail() || option < 0 || option > 15) 
            {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid input. Try again.\n";
                system("pause");
                continue;
            }

            if (option == 0) break;

            MenuItem* item = findItemById(option);

            int quantity;

            cout << "Enter quantity: ";
            cin >> quantity;

            if (cin.fail() || quantity <= 0) 
            {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid quantity. Try again.\n";
                system("pause");
                continue;
            }

            OrderItem order(*item, quantity);
            orders.push_back(order);
            totalBill += order.getTotal();

            cout << quantity << " x " << item->name << " added. ";
            cout << "Subtotal: $" << fixed << setprecision(2) << totalBill << endl;
            system("pause");
        }
    }

    void printBill() {
        system("cls");
        cout << "=======================================================\n";
        cout << "|                   Final Bill Summary                |\n";
        cout << "|=====================================================|\n";
        cout << "| Item                          | Quantity |  Price   |\n";
        cout << "|-----------------------------------------------------|\n";

        for (const auto& item : orders) {
            cout << "| " << setw(29) << left << item.item.name << " | "
                 << setw(8) << right << item.quantity << " | $ "
                 << setw(6) << fixed << setprecision(2) << item.getTotal() << " |\n";
        }

        cout << "|=====================================================|\n";
        cout << "|                                    Total | $ "
             << setw(6) << fixed << setprecision(2) << totalBill << " |\n";
        cout << "=======================================================\n";
        cout << "Thank you for visiting Jing Breakfast!\n";
    }
};

// Main function
int main() 
{
    RestaurantOrderingSystem app;
    app.takeOrder();
    app.printBill();

    return 0;
}