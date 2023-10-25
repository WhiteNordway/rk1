#include <iostream>
#include <cstring>
using std::cout; using std::cin; using std::endl;


struct item
{
    char *name = new char[0];
    unsigned quantity;
    float price;
};


inline bool notValid(item *const i)
{
    return strcmp(i->name, (i - 1)->name) > 0;
}


// Вариант 4
int main()
{
    // Количество товаров
    unsigned n;
    cout << "Enter quantity of ordered products: ";
    cin >> n;
    auto products = new item[n];

    // Общие переменные
    double total = 0;

    // Чтение товаров в цикле
    for (unsigned pos = 1; pos <= n; ++pos)
    {
        auto &product = products[n];
        // Название
        cout << "Enter name of the " << pos << " product: ";
        char *temp = new char[1000];
        cin.getline(temp, 1000);
        
        delete[] product.name;
        product.name = new char[strlen(temp)];
        strcpy(product.name, temp);
        
        // Количество
        cout << "Enter the quantity of products: ";
        cin >> product.quantity;
        // Цена
        cout << "Enter the price of one product: ";
        cin >> product.price;
        // Общая стоимость
        unsigned currentPrice = product.quantity * product.price;
        total += currentPrice;
        cout << "Total price of the order: " << currentPrice;
    }

    // Сортировка пузырьком B]
    for (item *currentOuter = products + 1, *const afterLast = &products[n] + 1; currentOuter != afterLast; ++currentOuter)
        for (auto current = currentOuter; notValid(current); --current)  // меняем местами текущий элемент с тем, что стоит перед ним
        {
            unsigned tempQuantity = current->quantity;
            current->quantity = (current - 1)->quantity;
            (current - 1)->quantity = tempQuantity;
            float tempPrice = current->price;
            current->price = (current - 1)->price;
            (current - 1)->price = tempPrice;

            char *tempString = new char[strlen(current->name)];
            strcpy(tempString, current->name);
            delete[] current->name;
            current->name = new char[strlen((current - 1)->name)];
            strcpy(current->name, (current - 1)->name);
            delete[] (current - 1)->name;
            (current - 1)->name = new char[strlen(tempString)];
            strcpy((current - 1)->name, tempString);
            delete[] tempString;
        }

    // Вывод
    for (item *current = products, *const afterLast = &products[n] + 1; products != afterLast; ++products)
        std::cout << "The " << current - products + 1 << " item: " << current->name 
        << "; quantity: " << current->quantity 
        << "; price of one instance: " << current->price << endl;

    // TODO: очистить память
    return EXIT_SUCCESS;
}
