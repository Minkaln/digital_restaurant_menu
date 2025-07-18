#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm> 
#include <cctype>    
#include <limits>    
#include <iomanip>   
#include <cstdlib>   
#include <fstream>   

using namespace std;

int getIntegerInput(const string& prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a whole number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return value;
}

string getStringInput(const string& prompt) {
    string value;
    cout << prompt;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, value);
    return value;
}

double getDoubleInput(const string& prompt) {
    double value;
    cout << prompt;
    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return value;
}

bool getFoodDrinkChoice(const string& prompt) {
    string input;
    bool isValidInput = false;
    bool result = false;

    while (!isValidInput) {
        cout << prompt;
        cin >> input;

        transform(input.begin(), input.end(), input.begin(),
                       [](unsigned char c){ return tolower(c); });

        if (input == "food") {
            result = true;
            isValidInput = true;
        } else if (input == "drink") {
            result = false;
            isValidInput = true;
        } else {
            cout << "Invalid input. Please enter 'Food' or 'Drink'.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return result;
}

class Product {
public:
    int ItemId;
    double ItemPrice;
    bool IsFood;
    string FoodName;

    Product(int _id, const string& _name, double _price, bool _isfood)
        : ItemId(_id), FoodName(_name), ItemPrice(_price), IsFood(_isfood) {}

    Product() : ItemId(0), ItemPrice(0.0), IsFood(false), FoodName("N/A") {}
};

class Menu {
private:
    map<int, Product> items;
    const string filename = "menu_data.txt"; 

public:
    Menu() {
        loadMenuFromFile(); 
    }

    ~Menu() {
        saveMenuToFile(); 
    }

    void loadMenuFromFile() {
        ifstream inFile(filename);
        if (!inFile.is_open()) {
            cout << "No existing menu data file found. Starting with an empty menu or initial default items.\n";
            return;
        }

        items.clear(); 

        string line;
        while (getline(inFile, line)) {
            size_t firstPipe = line.find('|');
            size_t secondPipe = line.find('|', firstPipe + 1);
            size_t thirdPipe = line.find('|', secondPipe + 1);

            if (firstPipe == string::npos || secondPipe == string::npos || thirdPipe == string::npos) {
                cerr << "Warning: Skipping malformed line in menu data: " << line << endl;
                continue;
            }

            try {
                int id = stoi(line.substr(0, firstPipe));
                string name = line.substr(firstPipe + 1, secondPipe - (firstPipe + 1));
                double price = stod(line.substr(secondPipe + 1, thirdPipe - (secondPipe + 1)));
                bool isFood = (stoi(line.substr(thirdPipe + 1)) == 1);

                items.emplace(id, Product(id, name, price, isFood));
            } catch (const exception& e) {
                cerr << "Error parsing line: '" << line << "' - " << e.what() << endl;
            }
        }
        inFile.close();
        cout << "Menu loaded from " << filename << ".\n";
    }

    void saveMenuToFile() const {
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cerr << "Error: Could not open " << filename << " for writing. Menu data not saved.\n";
            return;
        }

        for (const auto& pair : items) {
            const Product& item = pair.second;
            outFile << item.ItemId << "|"
                    << item.FoodName << "|"
                    << fixed << setprecision(2) << item.ItemPrice << "|"
                    << (item.IsFood ? 1 : 0) << "\n";
        }
        outFile.close();
        cout << "Menu saved to " << filename << ".\n";
    }


    bool addItemToList(const Product& item) {
        auto [it, inserted] = items.try_emplace(item.ItemId, item);
        if (inserted) {
            saveMenuToFile(); 
        }
        return inserted;
    }

    bool removeItemFromList(int ItemId) {
        bool removed = items.erase(ItemId) > 0;
        if (removed) {
            saveMenuToFile(); 
        }
        return removed;
    }

    const Product* getItemById(int ItemId) const {
        auto it = items.find(ItemId);
        if (it != items.end()) {
            return &it->second;
        }
        return nullptr;
    }

    void DisplayMenu() const {
        system("cls"); 
        cout << "=================================================\n";
        cout << "                 Jing Breakfast Menu             \n";
        cout << "=================================================\n";

        if (items.empty()) {
            cout << "Menu is currently empty.\n";
            cout << "=================================================\n";
            return;
        }

        cout << "ID\tItem Name\t\t\tPrice\tType\n";
        cout << "-------------------------------------------------\n";

        for (const auto& pair : items) {
            cout << pair.second.ItemId << "\t"
                 << setw(30) << left << pair.second.FoodName << "\t$"
                 << fixed << setprecision(2) << pair.second.ItemPrice << "\t"
                 << (pair.second.IsFood ? "Food" : "Drink") << endl;
        }
        cout << "=================================================\n";
    }
};

class MenuAdmin {
private:
    Menu& TargetMenu; 
public:
    MenuAdmin(Menu& MenuToManage) : TargetMenu(MenuToManage) {}

    void addItemToMenu(int id, const string& name, double price, bool isFood) {
        if (TargetMenu.getItemById(id) != nullptr) {
            cout << "Error: Item with ID " << id << " already exists. Please choose a different ID or remove the existing item first." << endl;
            return;
        }

        Product newItem(id, name, price, isFood);
        if (TargetMenu.addItemToList(newItem)) {
            cout << "Added item: " << name << " (ID: " << id << ") to the menu." << endl;
        } else {
            cout << "Failed to add item " << name << " (ID: " << id << ") due to an unexpected error." << endl;
        }
    }

    void removeMenuItem(int id) {
        if (TargetMenu.removeItemFromList(id)) {
            cout << "Removed item with ID " << id << " from the menu." << endl;
        } else {
            cout << "Error: Item with ID " << id << " not found." << endl;
        }
    }
};

class Order {
private:
    map<int, int> orderedItems; 
    const Menu& menu;           
    double totalBill;           

public:
    Order(const Menu& _menu) : menu(_menu), totalBill(0.0) {}

    void AddItemToOrder(int id, int quantity) {
        if (quantity <= 0) {
            cout << "Error: Quantity must be a positive number." << endl;
            return;
        }

        const Product* item = menu.getItemById(id);

        if (item != nullptr) {
            orderedItems[id] += quantity; 
            totalBill += item->ItemPrice * quantity;
            cout << "Added " << quantity << "x " << item->FoodName << " to the order." << endl;
        } else {
            cout << "Error: Item with ID " << id << " not found on the menu." << endl;
        }
    }

    void RemoveItemFromOrder(int id, int quantity) {
        auto it = orderedItems.find(id);
        if (it == orderedItems.end()) {
            cout << "Error: Item with ID " << id << " was not in the order." << endl;
            return;
        }
        if (quantity <= 0) {
            cout << "Error: Quantity to remove must be a positive number." << endl;
            return;
        }

        int& currentQuantity = it->second;
        const Product* item = menu.getItemById(id); 

        if (item == nullptr) { 
            cout << "Error: Product details for ID " << id << " not found in menu (unexpected)." << endl;
            orderedItems.erase(id);
            return;
        }

        if (quantity >= currentQuantity) {
            totalBill -= item->ItemPrice * currentQuantity;
            orderedItems.erase(id);
            cout << "Removed all " << currentQuantity << "x " << item->FoodName << " (ID: " << id << ") from the order." << endl;
        } else {
            totalBill -= item->ItemPrice * quantity;
            currentQuantity -= quantity;
            cout << "Removed " << quantity << "x " << item->FoodName << " (ID: " << id << ") from the order. Remaining: " << currentQuantity << endl;
        }
    }

    void DisplayCurrentOrder() const {
        cout << "\n";
        cout << "==================================================================\n";
        cout << "                      Current Order Summary                       \n";
        cout << "==================================================================\n";

        if (orderedItems.empty()) {
            cout << "No items in the order.\n";
            cout << "==================================================================\n";
            return;
        }

        cout << "O.N\tID\tItem Name\t\t\tQty\tT.Price\n";
        cout << "------------------------------------------------------------------\n";

        int orderNum = 1;
        for (const auto& pair : orderedItems) {
            int id = pair.first;
            int quantity = pair.second;
            const Product* item = menu.getItemById(id);

            if (item != nullptr) {
                double itemTotal = item->ItemPrice * quantity;
                cout << orderNum++ << "\t" << item->ItemId << "\t"
                     << setw(30) << left << item->FoodName << "\t"
                     << quantity << "\t$" << fixed << setprecision(2) << itemTotal << endl;
            } else {
                cout << orderNum++ << "\t" << id << "\t" << setw(30) << left << "[Item Not Found]" << "\t"
                     << quantity << "\t$" << fixed << setprecision(2) << (0.0 * quantity) << endl;
            }
        }
        cout << "==================================================================\n";
        cout << "Total Bill: $" << fixed << setprecision(2) << totalBill << endl;
        cout << "==================================================================\n";
    }

    void generateReceipt() const {
        system("cls");
        cout << "==================================================================\n";
        cout << "                       Final Bill Summary                         \n";
        cout << "==================================================================\n";

        if (orderedItems.empty()) {
            cout << "Order is empty. No receipt to print." << endl;
            cout << "==================================================================\n";
            return;
        }

        cout << "O.N\tID\tItem Name\t\t\tQty\tT.Price\n";
        cout << "------------------------------------------------------------------\n";

        int orderNum = 1;
        for (const auto& pair : orderedItems) {
            int id = pair.first;
            int quantity = pair.second;
            const Product* item = menu.getItemById(id);

            if (item != nullptr) {
                double itemTotal = item->ItemPrice * quantity;
                cout << orderNum++ << "\t" << item->ItemId << "\t"
                     << setw(30) << left << item->FoodName << "\t"
                     << quantity << "\t$" << fixed << setprecision(2) << itemTotal << endl;
            } else {
                cout << orderNum++ << "\t" << id << "\t" << setw(30) << left << "[Item Not Found]" << "\t"
                     << quantity << "\t$" << fixed << setprecision(2) << (0.0 * quantity) << endl;
            }
        }
        cout << "==================================================================\n";
        cout << "Total Bill: $" << fixed << setprecision(2) << totalBill << endl;
        cout << "==================================================================\n";
        cout << "Thank you for visiting Jing Breakfast!\n";
    }
};

int main() {
    system("cls"); 

    Menu myMenu; 
    MenuAdmin menuManage(myMenu);
    Order myOrder(myMenu);

    // This is just for add data to menu. so u can uncommand it
    // menuManage.addItemToMenu(1, "Fries rice with fries chicken", 5.00, true);
    // menuManage.addItemToMenu(2, "Fries rice with BBQ chicken", 5.00, true);
    // menuManage.addItemToMenu(3, "Rice with fries chicken", 4.50, true);
    // menuManage.addItemToMenu(4, "Rice with BBQ chicken", 4.50, true);
    // menuManage.addItemToMenu(5, "Fries rice with fries pork", 5.00, true);
    // menuManage.addItemToMenu(6, "Fries rice with BBQ pork", 5.00, true);
    // menuManage.addItemToMenu(7, "Rice with fries pork", 4.50, true);
    // menuManage.addItemToMenu(8, "Rice with BBQ pork", 4.50, true);
    // menuManage.addItemToMenu(9, "Pork kathiew", 3.00, true);
    // menuManage.addItemToMenu(10, "Cow meat ball kathiew", 3.50, true);
    // menuManage.addItemToMenu(11, "Ice lemon green tea", 2.00, false);
    // menuManage.addItemToMenu(12, "Ice lemon red tea", 2.00, false);
    // menuManage.addItemToMenu(13, "Ice latte", 1.60, false);
    // menuManage.addItemToMenu(14, "Ice americano", 1.50, false);
    // menuManage.addItemToMenu(15, "Ice tea", 0.50, false);

    int choice;
    bool startingLoop = true;

    do {
        cout << "\n--- Welcome to Jing Breakfast Ordering System ---\n";
        cout << "1. Place a New Order\n";
        cout << "2. Manage Menu (Admin)\n";
        cout << "3. Exit Application\n";
        choice = getIntegerInput("Enter your choice: ");

        system("cls");

        if (choice == 1) {
            bool orderingLoop = true;
            do {
                myMenu.DisplayMenu();
                myOrder.DisplayCurrentOrder();
                cout << "\n--- Ordering Options ---\n";
                cout << "1. Add Item to Order\n";
                cout << "2. Remove Item from Order\n";
                cout << "3. Finalize Order and Print Receipt\n";
                cout << "4. Back to Main Menu\n";
                choice = getIntegerInput("Enter your choice: ");

                if (choice == 1) {
                    int itemId = getIntegerInput("Enter Item ID to add: ");
                    int quantity = getIntegerInput("Enter quantity: ");
                    myOrder.AddItemToOrder(itemId, quantity);
                } else if (choice == 2) {
                    int itemId = getIntegerInput("Enter Item ID to remove: ");
                    int quantity = getIntegerInput("Enter quantity to remove: ");
                    myOrder.RemoveItemFromOrder(itemId, quantity);
                } else if (choice == 3) {
                    myOrder.generateReceipt();
                    cout << "\nOrder finalized. Thank you for your business!\n";
                    system("pause");
                    orderingLoop = false;
                } else if (choice == 4) {
                    orderingLoop = false;
                } else {
                    cout << "Invalid choice. Please try again.\n";
                }
                system("pause");
                system("cls");
            } while (orderingLoop);
            system("cls");
        } else if (choice == 2) {
            bool menuAdminLoop = true;
            do {
                myMenu.DisplayMenu();
                cout << "\n--- Menu Management Options ---\n";
                cout << "1. Add New Item to Menu\n";
                cout << "2. Remove Item from Menu\n";
                cout << "3. Back to Main Menu\n";
                choice = getIntegerInput("Enter your choice: ");

                if (choice == 1) {
                    int tempId = getIntegerInput("Enter The Item ID (must be unique): ");
                    string tempName = getStringInput("Enter The Item's Name: ");
                    double tempPrice = getDoubleInput("Enter The Price: ");
                    bool tempIsFood = getFoodDrinkChoice("Is The Item a 'food' or 'drink'?: ");
                    menuManage.addItemToMenu(tempId, tempName, tempPrice, tempIsFood);
                } else if (choice == 2) {
                    int tempId = getIntegerInput("Enter The Item ID to remove: ");
                    menuManage.removeMenuItem(tempId);
                } else if (choice == 3) {
                    menuAdminLoop = false;
                } else {
                    cout << "Invalid choice. Please try again.\n";
                }
                system("pause");
                system("cls");
            } while (menuAdminLoop);
            system("cls");
        } else if (choice == 3) {
            startingLoop = false;
            cout << "Exiting. Goodbye!\n";
        } else {
            cout << "Invalid choice. Please try again.\n";
            system("pause");
            system("cls");
        }
    } while (startingLoop);

    return 0;
}