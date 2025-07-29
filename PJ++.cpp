#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

class MenuItem 
{
public:
    int id;
    string name;
    float price;

    MenuItem(int id, string name, float price) : id(id), name(name), price(price) {}
};

class OrderItem 
{
public:
    MenuItem item;  
    int quantity;

    OrderItem(MenuItem item, int quantity) : item(item), quantity(quantity) {}

    float getTotal() const
    {return item.price * quantity;}
};

class RestaurantOrderingSystem 
{
private:
    vector<MenuItem> FoodMenu;
    vector<MenuItem> DrinkMenu;
    vector<OrderItem> Orders;
    float totalBill = 0.0;

public:
    RestaurantOrderingSystem() 
    {
        FoodMenu.push_back(MenuItem(1, "Fries rice with fries chicken", 5.00));
        FoodMenu.push_back(MenuItem(2, "Fries rice with BBQ chicken", 5.00));
        FoodMenu.push_back(MenuItem(3, "Rice with fries chicken", 4.50));
        FoodMenu.push_back(MenuItem(4, "Rice with BBQ chicken", 4.50));
        FoodMenu.push_back(MenuItem(5, "Fries rice with fries pork", 5.00));
        FoodMenu.push_back(MenuItem(6, "Fries rice with BBQ pork", 5.00));
        FoodMenu.push_back(MenuItem(7, "Rice with fries pork", 4.50));
        FoodMenu.push_back(MenuItem(8, "Rice with BBQ pork", 4.50));
        FoodMenu.push_back(MenuItem(9, "Pork kathiew", 3.00));
        FoodMenu.push_back(MenuItem(10, "Cow meat ball kathiew", 3.50));

        DrinkMenu.push_back(MenuItem(11, "Ice lemon green tea", 2.00));
        DrinkMenu.push_back(MenuItem(12, "Ice lemon red tea", 2.00));
        DrinkMenu.push_back(MenuItem(13, "Ice latte", 1.60));
        DrinkMenu.push_back(MenuItem(14, "Ice americano", 1.50));
        DrinkMenu.push_back(MenuItem(15, "Ice tea", 0.50));
    }

    void AddItem()
    {
        while (true)
        {
            system("cls");

            DisplayMenu();

            cout << "Add New Menu Item\n";
            cout << "------------------\n";
            
            int id;

            cout << "Enter item ID: ";
            cin >> id;

            if (cin.fail() || id < 1) 
            {
                cin.clear();
                cin.ignore(10000000000, '\n');
                cout << "Invalid input. Try again.\n";
                system("pause");
                continue;
            }

            if (IsIdExist(id))
            {
                cout << "An item with ID " << id << " already exists. Please choose a different ID.\n";
                system("pause");
                continue;
            }

            cin.ignore();

            string name;

            cout << "Enter item name: ";
            getline(cin, name);

            float price;

            cout << "Enter item price: ";
            cin >> price;

            if (cin.fail()) 
            {
                cin.clear();
                cin.ignore(10000000000, '\n');
                cout << "Invalid input. Try again.\n";
                system("pause");
                continue;
            }

            string type;

            cout << "Is this a Food or Drink?: ";
            cin >> type;

            MenuItem NewItem(id, name, price);

            if (type == "food")
            {
                FoodMenu.push_back(NewItem);
                cout << "Food item added successfully!\n";
            }

            else if (type == "drink")
            {
                DrinkMenu.push_back(NewItem);
                cout << "Drink item added successfully!\n";
            }

            else
            {cout << "Invalid type. Item not added.\n";}

            system("pause");
            break;
        }
    }

    void RemoveItem()
    {
        while (true)
        {
            system("cls");

            DisplayMenu();

            if (FoodMenu.empty() && DrinkMenu.empty()) 
            {
                cout << "No items in the order to cancel.\n";
                system("pause");
                return;
            }

            int id;

            cout << "Enter the ID of the item to remove: ";
            cin >> id;

            bool found = false;

            for (auto it = FoodMenu.begin(); it != FoodMenu.end(); ++it)
            {
                if (it->id == id)
                {
                    FoodMenu.erase(it);
                    cout << "Food item removed successfully.\n";
                    found = true;
                    break;
                }
            }

            for (auto it = DrinkMenu.begin(); it != DrinkMenu.end(); ++it)
            {
                if (it->id == id)
                {
                    DrinkMenu.erase(it);
                    cout << "Drink item removed successfully.\n";
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                cout << "Item with ID " << id << " not found.\n";
            }
            system("pause");
            break;
        }
    }

    void ManageMenu()
    {
        while (true)
        {
            system("cls");

            DisplayMenu();

            cout << "Menu Management Options\n";
            cout << "1. Add Item to Menu\n";
            cout << "2. Remove Item from Menu\n";
            cout << "3. Back to Main Menu\n";

            int MenuManagementOptions;

            cout << "Enter your choice: ";
            cin >> MenuManagementOptions;

            if (cin.fail() || MenuManagementOptions < 1 || MenuManagementOptions > 3) 
            {
                cin.clear();
                cin.ignore(10000000000, '\n');
                cout << "Invalid input. Try again.\n";
                system("pause");
                continue;
            }

            if (MenuManagementOptions == 1)
            {AddItem();}

            else if (MenuManagementOptions == 2)
            {RemoveItem();}

            else if (MenuManagementOptions == 3)
            break;
        }
    }

    void WelcomeCustomerAdmin()
    {

        while (true)
        {
            system("cls");
            cout << "Welcome to Jing Breakfast Ordering System \n";
            cout << "1. Get an Order (Customer)\n";
            cout << "2. Manage Menu (Admin)\n";

            int welcome;

            cout << "Enter your choice: ";
            cin >> welcome;

            if (cin.fail() || welcome < 1 || welcome > 2) 
            {
                cin.clear();
                cin.ignore(10000000000, '\n');
                cout << "Invalid input. Try again.\n";
                system("pause");
                continue;
            }

            if (welcome == 1)
            {TakeOrder();}

            else if (welcome == 2)
            {ManageMenu();}
        }
    }

    MenuItem* FindItemById(int id) 
    {
        for (auto& item : FoodMenu)
        {if (item.id == id) return &item;}

        for (auto& item : DrinkMenu)
        {if (item.id == id) return &item;}

        return nullptr;
    }

    bool IsIdExist(int id)
    {
        for (const auto& item : FoodMenu)
        {if (item.id == id) return true;}

        for (const auto& item : DrinkMenu)
        {if (item.id == id) return true;}

        return false;
    }

    void DisplayMenu() 
    {
        system("cls");
        cout << "=================================================\n";
        cout << "                 Jing Breakfast                  \n";
        cout << "=================================================\n";
        cout << "                      Food                       \n";
        cout << "-------------------------------------------------\n";
        cout << "ID\tFood Name\t\t\tPrice\n";
        cout << "-------------------------------------------------\n";

        for (const auto& item : FoodMenu) 
        {
            cout << item.id << "\t" << setw(30) << left << item.name
                 << "\t$" << fixed << setprecision(2) << item.price << endl;
        }

        cout << "=================================================\n";
        cout << "                     Drinks                      \n";
        cout << "-------------------------------------------------\n";
        cout << "ID\tDrink Name\t\t\tPrice\n";
        cout << "-------------------------------------------------\n";

        for (const auto& item : DrinkMenu) 
        {
            cout << item.id << "\t" << setw(30) << left << item.name
                 << "\t$" << fixed << setprecision(2) << item.price << endl;
        }

        cout << "=================================================\n";
    }

    void TakeOrder() 
    {
        while (true) 
        {
            DisplayMenu();

             if (FoodMenu.empty() && DrinkMenu.empty()) 
            {
                cout << "No items in the Menu to Order.\n";
                system("pause");
                return;
            }

            cout << "0 to Back\n" << "168 To Continue\n";
            cout << "Enter Food/Drink ID: ";

            int IteamID;
            cin >> IteamID;

            if (cin.fail()) 
            {
                cin.clear();
                cin.ignore(10000000000, '\n');
                cout << "Invalid input. Try again.\n";
                system("pause");
                continue;
            }

            if (IteamID == 0)
            break;

            if (IteamID == 168)
            {
                ACC();
                continue;
            }
            
            MenuItem* item = FindItemById(IteamID);
            if (item == nullptr) 
            {
                cout << "Item with ID " << IteamID << " not found. Please try again.\n";
                system("pause");
                continue;
            }

            int quantity;
            cout << "Enter quantity: ";
            cin >> quantity;

            if (cin.fail() || quantity <= 0) 
            {
                cin.clear();
                cin.ignore(10000000000, '\n');
                cout << "Invalid quantity. Try again.\n";
                system("pause");
                continue;
            }

            OrderItem order(*item, quantity);
            Orders.push_back(order);
            totalBill += order.getTotal();

            cout << quantity << " x " << item->name << " added. ";
            cout << "Subtotal: $" << fixed << setprecision(2) << totalBill << endl;
            system("pause");
        }
    }

    void ACC()
    {
        while (true)
        {
            DisplayCurrentOrder();

            cout << "1. Add more items\n";
            cout << "2. Cancel an item\n";
            cout << "3. Checkout\n";

            int choice;

            cout << "Choice: ";
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > 3) 
            {
                cin.clear();
                cin.ignore(10000000000, '\n');
                cout << "Invalid input. Try again.\n";
                system("pause");
                continue;
            }

            if (choice == 1)
            {
                break; // Return to item entry
            }

            else if (choice == 2)
            {CancelItem();}

            else if (choice == 3)
            {
                if (Orders.empty()) 
                {
                    cout << "Cannot checkout with an empty order. Please add items.\n";
                    system("pause");
                    continue;
                }
                PrintBill();
            }
        }
    }
    
    void DisplayCurrentOrder() 
    {
        system("cls");
        cout << "==================================================================\n";
        cout << "                      Current Order Summary            \n";
        cout << "==================================================================\n";
        cout << "O.N\tID\tItem\t\t\t\tQty\tT.Price\n";
        cout << "------------------------------------------------------------------\n";

        for (int i = 0; i < Orders.size(); i++) 
        {
            OrderItem& oi = Orders[i];

            cout << i+1 << "\t" << oi.item.id << "\t" << setw(30) << left << oi.item.name << "\t" 
                 << oi.quantity << "\t$" << fixed << setprecision(2) << oi.getTotal() << endl;
        }
            
        cout << "==================================================================\n";
        cout << "Total Bill: $" << totalBill << endl;
        cout << "==================================================================\n";
    }
    
    void CancelItem() 
    {
        DisplayCurrentOrder();

        if (Orders.empty()) 
        {
            cout << "No items in the order to cancel.\n";
            system("pause");
            return;
        }

        int CancelID;
        cout << "Enter O.N of item to remove (0 to cancel): ";
        cin >> CancelID;

        if (CancelID == 0) 
        {return;}

        if (cin.fail() || CancelID < 1 || CancelID > Orders.size()) 
        {
            cin.clear();
            cin.ignore(10000000000, '\n');
            cout << "Invalid input. Try again.\n";
            system("pause");
            return;
        }

        int index = CancelID - 1;
        totalBill -= Orders[index].getTotal();
        Orders.erase(Orders.begin() + index);
        cout << "Item removed successfully.\n";
        system("pause");
    }
    
    void PrintBill() 
    {
        system("cls");
        cout << "==================================================================\n";
        cout << "                       Final Bill Summary                         \n";
        cout << "==================================================================\n";
        cout << "O.N\tID\tItem\t\t\t\tQty\tT.Price\n";
        cout << "------------------------------------------------------------------\n";

        for (int i = 0; i < Orders.size(); i++)
        {
            OrderItem& oi = Orders[i];
            cout << i+1 << "\t" << oi.item.id << "\t" << setw(30) << left << oi.item.name 
                 << "\t" << oi.quantity << "\t$" << fixed << setprecision(2) << oi.getTotal() << endl;
        }

        cout << "==================================================================\n";
        cout << "Total Bill: $" << totalBill << endl;
        cout << "==================================================================\n";
        cout << "Thank you for visiting Jing Breakfast!\n";
        exit(0);
    }
};

int main() 
{
    RestaurantOrderingSystem app;
    app.WelcomeCustomerAdmin();
}