#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits>
using namespace std;

class Product{
  public:
   int ItemId;
   double ItemPrice;
   bool IsFood;
   string FoodName;
   Product(int _id, const string& _name, double _price, bool _isfood): ItemId(_id), FoodName(_name),ItemPrice(_price),IsFood(_isfood){}
   Product(){
    cout << "There Nothing\n";
   }
};

class Menu{
  private:
    map<int, Product> items;
  public:
    void addItemToList(const Product& item){
      items.emplace(item.ItemId, item);
    }
    bool removeItemFromList(int ItemId) {
        return items.erase(ItemId) > 0;
    }
    const Product* getItemById(int ItemId) const{
      auto it = items.find(ItemId);
      if (it != items.end()){
        return &it->second;
      }
      return nullptr;
    }

    void DisplayMenu() const{
      cout << "Menu\n";
      for (const auto& pair : items) {
        cout << "ID: " << pair.second.ItemId << " | Name: " << pair.second.FoodName << " | Price: $" << pair.second.ItemPrice << " | Type: " << (pair.second.IsFood ? "Food" : "Drink") << endl;
        }
    }
};

class MenuAdmin{
  private:
    Menu& TargetMenu;
  public:
    MenuAdmin(Menu& MenuToManage): TargetMenu(MenuToManage){}
    void addItemToMenu(int id, const string& name, double price, bool isFood) {
        Product newItem(id, name, price, isFood);
        TargetMenu.addItemToList(newItem);
        cout << "Added item: " << name << " (ID: " << id << ") to the menu." << endl;
    }
    void removeMenuItem(int id) {
        if (TargetMenu.removeItemFromList(id)) {
            cout << "Removed item with ID " << id << " from the menu." << endl;
        } else {
            cout << "Error: Item with ID " << id << " not found." << endl;
        }
    }
};

class Order{
  private:
    map<int, int> orderedItems;
    const Menu& menu;
  public:
    Order(const Menu& _menu): menu(_menu){}

    void AddItemToOrder(int id, int quantity){  
      if (quantity <= 0) {
          cout << "Error: Quantity must be a positive number." << endl;
          return;
      }

      const Product* item = menu.getItemById(id);
        
      if (item != nullptr) {
        orderedItems[id] += quantity;
        cout << "Added " << quantity << "x " << item->FoodName << " to the order." << endl;
      } 
      else {
        cout << "Error: Item with ID " << id << " not found on the menu." << endl;
      }
    }

    void RemoveItemFromOrder(int id, int quantity){
      auto it = orderedItems.find(id);
      if (it == orderedItems.end()){
        cout << "Error: Item with ID " << id << " was not in the order." << endl;
        return;
      }
      if (quantity <= 0){
        cout << "Error: Quantity to remove must be a positive number." << endl;
        return;  
      }
      int& currentQuantity = it->second;
      if (quantity == 1){
         orderedItems.erase(id);
         cout << "Item has been remove." << endl;
      }
      if (quantity >= currentQuantity) {
            orderedItems.erase(id);
            cout << "Removed all " << currentQuantity << "x " << menu.getItemById(id)->FoodName << " (ID: " << id << ") from the order." << endl;
        } else {
            currentQuantity -= quantity;
            cout << "Removed " << quantity << "x " << menu.getItemById(id)->FoodName << " (ID: " << id << "from the order." << endl;
        }
    }

    void generateReceipt(){
      if (orderedItems.empty()) {
        cout << "\nOrder is empty. Nothing to print on receipt." << endl;
        return;
      }

      cout << "\n--- RECEIPT ---" << endl;
        double subtotal = 0.0;

      for (const auto& pair : orderedItems) {
        int id = pair.first;
        int quantity = pair.second;

        const Product* item = menu.getItemById(id);

            if (item != nullptr) {
                double itemTotal = item->ItemPrice * quantity;
                cout << quantity << "x " << item->FoodName << " @ $" << item->ItemPrice << " = $" << itemTotal << endl;
                subtotal += itemTotal;
            }
        }
    }
};

int getIntegerInput(const string& prompt) {
  int value;
  cout << prompt;
  while (!(cin >> value)) {
    cout << "Invalid input. Please enter a number: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  return value;
}

int main(){
  Menu myMenu;
  MenuAdmin menuManage(myMenu);
  Order myOrder(myMenu);

  int choise;
  do{

  }while(choise == 15);

 
}