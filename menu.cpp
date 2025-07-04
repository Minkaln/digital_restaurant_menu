#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

int main()
{
    int foodnum[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};   // Number of food
    int drinknum[] = {11, 12, 13, 14, 15};            // Number of drink
    
    std::string foodnames[] = {"Fries rice with fries chicken", "Fries rice with BBQ chicken", 
    "Rice with fries chicken", "Rice with BBQ chicken", "Fries rice with fries pork",
    "Fries rice with BBQ pork", "Rice with fries pork", "Rice with BBQ pork", 
    "Pork kathiew", "Cow meat ball kathiew"};
    std::string drinknames[] = {"Ice lemon green tea", "Ice lemon red tea", "Ice latte", 
    "Ice americano", "Ice tea"};

    float foodprice[] = {5.00, 5.00, 4.50, 4.50, 5.00, 5.00, 4.50, 4.50, 3.00, 3.50};
    float drinkprice[] = {2.00, 2.00, 1.60, 1.50, 0.50};
    
    // Variables to track orders
    int options = -1;
    int quantity = 0;
    float total = 0.0;

    // Vectors to track orders details
    std::vector<std::string> orderedItems;    // Stores the names of ordered items
    std::vector<int> orderedQuantities; // Stores the quantities ordered
    std::vector<float> orderedPrices;   // Stores the prices of ordered items

    while (true) 
    {
        system("cls");
        std::cout << "=================================================\n";
        std::cout << "                 Jing Breakfast                  \n";
        std::cout << "=================================================\n";
        std::cout << "                      Food                       \n";
        std::cout << "-------------------------------------------------\n";
        std::cout << "ID\tFood Name\t\t\tPrice\n";
        std::cout << "-------------------------------------------------\n";
        
        // Display ID FoodName Price
        for (int food = 0; food < 10; ++food) 
        {
            std::cout << foodnum[food] << "\t" << std::setw(30) << std::left << foodnames[food] 
            << "\t$" << std::fixed << std::setprecision(2) << foodprice[food] << std::endl;
        }

        std::cout << "-------------------------------------------------\n";
        std::cout << "                   Drinks                        \n";
        std::cout << "-------------------------------------------------\n";
        std::cout << "ID\tDrink Name\t\t\tPrice\n";
        std::cout << "-------------------------------------------------\n";

        // Display ID DrinkName Price
        for (int drink = 0; drink < 5; ++drink) 
        {
            std::cout << drinknum[drink] << "\t" << std::setw(30) << std::left << drinknames[drink] 
            << "\t$" << std::fixed << std::setprecision(2) << drinkprice[drink] << std::endl;
        }

        std::cout << " 0\tExit\n";
        std::cout << "=================================================\n";
        std::cout << "Enter Food or Drink ID you want to order: ";
        std::cin >> options;

        if (std::cin.fail()) // Check if the input is invalid
        {
            std::cin.clear(); // Clear the error state of cin
            std::cin.ignore(100, '\n'); // Ignore leftover invalid input
            std::cout << "Invalid input. Please try again.\n";
            system("pause");
            continue; // Restart the loop
        }

        // Exit if the user chooses 0
        if (options == 0) 
        {break;}

        if (options < 1 || options > 15) 
        {   
            std::cout << "Invalid ID. Please try again.\n";
            system("pause");
            continue;
        }

        // Get the quantity
        std::cout << "Enter the quantity: ";
        std::cin >> quantity;

        if (std::cin.fail()) // Check if the input is invalid
        {
            std::cin.clear(); // Clear the error state of cin
            std::cin.ignore(100, '\n'); // Ignore leftover invalid input
            std::cout << "Invalid input. Please try again.\n";
            system("pause");
            continue; // Restart the loop
        }

        if (quantity < 1) 
        {
            std::cout << "Invalid quantity. Please try again.\n";
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
            
                 std::cout << quantity << " x " << foodnames[options - 1] << " added to your order. ";
                 std::cout << "Subtotal: $" << std::fixed << std::setprecision(2) << total << std::endl;
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

                 std::cout << quantity << " x " << drinknames[options - 11] << " added to your order. ";
                 std::cout << "Subtotal: $" << std::fixed << std::setprecision(2) << total << std::endl;
                 }

        system("pause"); // Pause to let the user see the output
    }

    // Display the final bill summary
    system("cls");
    std::cout << "=======================================================\n";
    std::cout << "|                   Final Bill Summary                |\n";
    std::cout << "|=====================================================|\n";
    std::cout << "| Item                          | Quantity |  Price   |\n";
    std::cout << "|-----------------------------------------------------|\n";

    // Loop through the ordered items and display them
    for (size_t i = 0; i < orderedItems.size(), i < orderedQuantities.size(), i < orderedPrices.size(); ++i)
    {
        std::cout << "| " << std::setw(29) << std::left << orderedItems[i] << " | " 
             << std::setw(8) << std::right << orderedQuantities[i] << " | $ "
             << std::setw(6) << std::fixed << std::setprecision(2) << orderedPrices[i] << " |\n";
    }

    std::cout << "|=====================================================|\n";
    std::cout << "|                                    Total | $ " << std::setw(6) 
         << std::fixed << std::setprecision(2) << total << " |\n";
    std::cout << "=======================================================\n";
    std::cout << "Thank you for visiting Jing Breakfast!\n";

    return 0;
}