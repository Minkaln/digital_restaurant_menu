#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

int main()
{
    int foodnum[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};   // Number of food
    int drinknum[] = {11, 12, 13, 14, 15};            // Number of drink
    
    string foodnames[] = {"Fries rice with fries chicken", "Fries rice with BBQ chicken", 
    "Rice with fries chicken", "Rice with BBQ chicken", "Fries rice with fries pork",
    "Fries rice with BBQ pork", "Rice with fries pork", "Rice with BBQ pork", 
    "Pork kathiew", "Cow meat ball kathiew"};
    string drinknames[] = {"Ice lemon green tea", "Ice lemon red tea", "Ice latte", 
    "Ice americano", "Ice tea"};

    float foodprice[] = {5.00, 5.00, 4.50, 4.50, 5.00, 5.00, 4.50, 4.50, 3.00, 3.50};
    float drinkprice[] = {2.00, 2.00, 1.60, 1.50, 0.50};
    
    // Variables to track orders
    int options = -1;
    int quantity = 0;
    float total = 0.0;

    // Vectors to track orders details
    vector<string> orderedItems;    // Stores the names of ordered items
    vector<int> orderedQuantities; // Stores the quantities ordered
    vector<float> orderedPrices;   // Stores the prices of ordered items

    while (true) 
    {
        system("cls");
        cout << "=================================================\n";
        cout << "                 Jing Breakfast                  \n";
        cout << "=================================================\n";
        cout << "                      Food                       \n";
        cout << "-------------------------------------------------\n";
        cout << "ID\tFood Name\t\t\tPrice\n";
        cout << "-------------------------------------------------\n";
        
        // Display ID FoodName Price
        for (int food = 0; food < 10; ++food) 
        {
            cout << foodnum[food] << "\t" << setw(30) << left << foodnames[food] 
            << "\t$" << fixed << setprecision(2) << foodprice[food] << endl;
        }

        cout << "-------------------------------------------------\n";
        cout << "                   Drinks                        \n";
        cout << "-------------------------------------------------\n";
        cout << "ID\tDrink Name\t\t\tPrice\n";
        cout << "-------------------------------------------------\n";

        // Display ID DrinkName Price
        for (int drink = 0; drink < 5; ++drink) 
        {
            cout << drinknum[drink] << "\t" << setw(30) << left << drinknames[drink] 
            << "\t$" << fixed << setprecision(2) << drinkprice[drink] << endl;
        }

        cout << " 0\tExit\n";
        cout << "=================================================\n";
        cout << "Enter Food or Drink ID you want to order: ";
        cin >> options;

        if (cin.fail()) // Check if the input is invalid
        {
            cin.clear(); // Clear the error state of cin
            cin.ignore(100, '\n'); // Ignore leftover invalid input
            cout << "Invalid input. Please try again.\n";
            system("pause");
            continue; // Restart the loop
        }

        // Exit if the user chooses 0
        if (options == 0) 
        {break;}

        if (options < 1 || options > 15) 
        {   
            cout << "Invalid ID. Please try again.\n";
            system("pause");
            continue;
        }

        // Get the quantity
        cout << "Enter the quantity: ";
        cin >> quantity;

        if (cin.fail()) // Check if the input is invalid
        {
            cin.clear(); // Clear the error state of cin
            cin.ignore(100, '\n'); // Ignore leftover invalid input
            cout << "Invalid input. Please try again.\n";
            system("pause");
            continue; // Restart the loop
        }

        if (quantity < 1) 
        {
            cout << "Invalid quantity. Please try again.\n";
            system("pause");
            continue;
        }

                 // Calculate the food price and store the order details for later use
                 if (options >= 1 && options <= 10)  // Food IDs
                 {   
                 float price = foodprice[options - 1] * quantity;
                 total += price;

                 // Add details to vectors for final bill summary
                 orderedItems.push_back(foodnames[options - 1]);
                 orderedQuantities.push_back(quantity);
                 orderedPrices.push_back(price);
            
                 cout << quantity << " x " << foodnames[options - 1] << " added to your order. ";
                 cout << "Subtotal: $" << fixed << setprecision(2) << total << endl;
                 } 
                 
                 // Calculate the drink price and store the order details for later use
                 else if (options >= 11 && options <= 15)  // Drink IDs
                 {
                 float price = drinkprice[options - 11] * quantity;
                 total += price;
                 
                 // Add details to vectors for final bill summary
                 orderedItems.push_back(drinknames[options - 11]);
                 orderedQuantities.push_back(quantity);
                 orderedPrices.push_back(price);

                 cout << quantity << " x " << drinknames[options - 11] << " added to your order. ";
                 cout << "Subtotal: $" << fixed << setprecision(2) << total << endl;
                 }

        system("pause"); // Pause to let the user see the output
    }

    // Display the final bill summary
    system("cls");
    cout << "=======================================================\n";
    cout << "|                   Final Bill Summary                |\n";
    cout << "|=====================================================|\n";
    cout << "| Item                          | Quantity |  Price   |\n";
    cout << "|-----------------------------------------------------|\n";

    // Loop through the ordered items and display them
    for (size_t i = 0; i < orderedItems.size(), i < orderedQuantities.size(), i < orderedPrices.size(); ++i)
    {
        cout << "| " << setw(29) << left << orderedItems[i] << " | " 
             << setw(8) << right << orderedQuantities[i] << " | $ "
             << setw(6) << fixed << setprecision(2) << orderedPrices[i] << " |\n";
    }

    cout << "|=====================================================|\n";
    cout << "|                                    Total | $ " << setw(6) 
         << fixed << setprecision(2) << total << " |\n";
    cout << "=======================================================\n";
    cout << "Thank you for visiting Jing Breakfast!\n";

    return 0;
}