#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype> 
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

bool getBoolInput(const string& prompt) {
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

int main(){

  // Menu myMenu;
  // MenuAdmin menuManage(myMenu);

  // menuManage.addItemToMenu(10,"MEAT",9.20,true);
  // menuManage.addItemToMenu(10,"DRINK",10.20,false);
  // myMenu.DisplayMenu();
  int TempId;
  string TempName;
  double TempPrice;
  bool TempIsFood;
  int Quanity;
  int choice;
  bool StartingLoop = true;
  bool OrderingLoop = true;
  bool MenuAdminLoop = true;
  Menu myMenu;
  MenuAdmin menuManage(myMenu);
  Order myOrder(myMenu);

  menuManage.addItemToMenu(10,"MEAT",9.20,true); //this just add some item to the menu
  menuManage.addItemToMenu(11,"DRINK",10.20,false);

  system("cls");
  do{
    cout << "1 to Enter Ordering" << endl;
    cout << "2 to Enter Menu Manangment" << endl;
    cout << "3 to Exit"<< endl;
    choice = getIntegerInput("Enter your choice: ");
    if (choice == 1){
      do{
        myMenu.DisplayMenu();
        cout << "1. To Start Ordering" << endl;
        cout << "2. To Remove Item Order List" << endl;
        cout << "3. To Fisish Ordering" << endl;
        choice = getIntegerInput("Enter your choice: ");
        if (choice == 1){
          choice = getIntegerInput("Enter your Food Id choice: ");
          Quanity = getIntegerInput("How Many Do You Want?: ");
          myOrder.AddItemToOrder(choice,Quanity);
        }else if(choice == 2){
          choice = getIntegerInput("Enter your Food Id choice: ");
          Quanity = getIntegerInput("How Many Do You Want Gone?: ");
          myOrder.RemoveItemFromOrder(choice,Quanity);
        }else {
          OrderingLoop = false;
        }
      }while (OrderingLoop);
      OrderingLoop = true; 
    }else if(choice == 2){
      do{
        myMenu.DisplayMenu();
        cout << "1. To Add Item to Menu" << endl;
        cout << "2. To Remove Item from Menu" << endl;
        cout << "3. To Exit Menu Management" << endl;
        choice = getIntegerInput("Enter your choice: ");
        if (choice == 1){
          TempId = getIntegerInput("Enter The Food Id: ");
          TempName = getStringInput("Enter The Item's Name: ");
          TempPrice = getDoubleInput("Enter The Price: ");
          TempIsFood = getBoolInput("Enter If The Item is a Food Or Drink: ");
          menuManage.addItemToMenu(TempId,TempName,TempPrice,TempIsFood);
          system("cls");
        }else if(choice == 2){
          choice = getIntegerInput("Enter your Food Id choice: ");
          Quanity = getIntegerInput("How Many Do You Want Gone?: ");
          myOrder.RemoveItemFromOrder(choice,Quanity);
        }else {
          MenuAdminLoop = false;
        }
      }while (MenuAdminLoop);
      MenuAdminLoop = true;  
    }
      
  }while(StartingLoop);

 
}