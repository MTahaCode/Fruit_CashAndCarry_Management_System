//M_Taha_Makhdoom_22i-1547
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;



class Customer
{
private:
    static int TotalCustomers;
    int SrNo;
    string Name;
    string Email;
public:
    Customer(string name = "", string email = "") : Name(name), Email(email)
    {
        TotalCustomers++;
        SrNo = TotalCustomers;
    }
};

int Customer::TotalCustomers = 0;

class Supplier
{
    string Name;
    string Product;
public:
    Supplier(string name, string product) : Name(name), Product(product) {}
    string getName() const
    {
        return Name;
    }
    string getProduct() const
    {
        return Product;
    }
};

Supplier Suppliers[10] = {
    Supplier("ABC Fruits", "Apple"),
    Supplier("XYZ Farms", "Banana"),
    Supplier("Green Grocers", "Cherry"),
    Supplier("Fresh Produce Co.", "Durian"),
    Supplier("Juicy Farms", "Elderberry"),
    Supplier("Sunny Orchards", "Fig"),
    Supplier("Harvest Time", "Grape"),
    Supplier("Berrylicious", "Huckleberry"),
    Supplier("Sweet Treats", "Kiwi"),
    Supplier("Tropical Delights", "Mango")
};

//the product class
class Product
{
private:
	string Name;
	int Quantity;
	int BasePrice;
public:
    Product(string name = "", int base = 0, int quantity = 0) : Quantity(quantity), BasePrice(base), Name(name)
    {
        if (Name[0] >= 'a' && Name[0] <= 'z')
        {
            Name[0] = Name[0] - ('a' - 'A');
        }
    }
    //getters
    string getName() const {
        return Name;
    }
    int getQuantity() const {
        return Quantity;
    }
    int getBasePrice() const {
        return BasePrice;
    }
    // setters
    void setName(string name) {
        Name = name;
        if (Name[0] >= 'a' && Name[0] <= 'z')
        {
            Name[0] = Name[0] - ('a' - 'A');
        }
    }
    void setQuantity(int quantity) {
        Quantity = quantity;
    }
    void setBasePrice(int basePrice) {
        BasePrice = basePrice;
    }

    bool operator==(const Product& product)
    {
        if (this->Name == product.Name)
        {
            return 1;
        }
        return 0;
    }
    friend ostream& operator<<(ostream& os, const Product& product);
};

ostream& operator<<(ostream& os, const Product& product)
{
    os << "\nName: " << product.Name;
    os << "   Quantity: " << product.Quantity;
    os << "   BasePrice: " << product.BasePrice << endl;
    return os;
}

//Inventory
class Inventory
{
private:
    string Name;
    Product* AllProducts;//composition
    int NoOfProducts;
    int arraysize;
    Supplier* suppliers;//aggregation
    bool isPresent(const Product& product)
    {
        //checks if the product is present
        for (int i = 0; i < arraysize; i++)
        {
            if (AllProducts[i] == product)
            {
                return 1;
            }
        }
        return 0;
    }
    bool isArrayFilled()
    {
        Product empty;
        for (int i = 0; i < arraysize; i++)
        {
            if (AllProducts[i] == empty)
            {
                return 0;
            }
        }
        return 1;
    }
    void increaseArray()
    {
        Product* temp = new Product[arraysize];
        for (int i = 0; i < arraysize; i++)
        {
            temp[i] = AllProducts[i];
        }
        delete[] AllProducts;
        arraysize++;
        //NoOfProducts++;
        AllProducts = new Product[arraysize];
        for (int i = 0; i < arraysize - 1; i++)
        {
            AllProducts[i] = temp[i];
        }
        delete[] temp;
    }
    void FixArray()
    {
        for (int i = 0; i < arraysize; i++)
        {
            if (i + 1 != arraysize && AllProducts[i].getName() == "")
            {
                Product temp = AllProducts[i];
                AllProducts[i] = AllProducts[i + 1];
                AllProducts[i + 1] = temp;
            }
        }
    }
public:
    Inventory(string name="", int size = 5) : Name(name), suppliers(Suppliers)
    {
        arraysize = size;
        NoOfProducts = 0;
        AllProducts = new Product[size];
    }
    int getNoOfProducts() const
    {
        return NoOfProducts;
    }
    Product* getProductFromIndex(int i)
    {
        return &AllProducts[i];
    }
    
    void AddProduct(Product NewProduct)
    {
        if (isPresent(NewProduct))
        {
            cout << "The Product is already present in inventory\n";
            return;
        }
        else if (!isArrayFilled())
        {
            Product empty;
            for (int i = 0; i < arraysize; i++)
            {
                if (AllProducts[i] == empty)
                {
                    AllProducts[i] = NewProduct;
                    NoOfProducts++;
                    cout << "There was space in array and the new product has been added\n";
                    break;
                }
            }
        }
        else
        {
            increaseArray();
            Product empty;
            for (int i = 0; i < arraysize; i++)
            {
                if (AllProducts[i] == empty)
                {
                    AllProducts[i] = NewProduct;
                    NoOfProducts++;
                    cout << "The array has been extended and the new product has been added\n";
                    break;
                }
            }
        }
    }
    void RemoveProduct(Product ToBeRemoved)
    {
        if (!isPresent(ToBeRemoved))
        {
            cout << "The Product is not present in inventory\n";
            return ;
        }
        for (int i = 0; i < arraysize; i++)
        {
            if (AllProducts[i] == ToBeRemoved)
            {
                Product empty;
                AllProducts[i] = empty;
                NoOfProducts--;
                FixArray();
                break;
            }
        }
    }

    void IncreaseProductQuantity(const Product& product)
    {
        
        if (isPresent(product))
        {
            for (int i = 0; i < NoOfProducts; i++)
            {
                if (AllProducts[i] == product)
                {
                    AllProducts[i].setQuantity(product.getQuantity() + AllProducts[i].getQuantity());
                    cout << "The product quantity has been increased\n";
                    break;
                }
            }
        }
        else
        {
            cout << "The product is not present in Inventory\n";
        }
    }
    void DecreaseProductQuantity(const Product& product)
    {
        if (!isPresent(product))
        {
            cout << "The product is not present in Inventory\n";
            //return 0;
        }
        for (int i = 0; i < arraysize; i++)
        {
            if (AllProducts[i] == product)
            {
                if (AllProducts[i].getQuantity() < product.getQuantity())
                {
                    cout << "The amount of product in inventory is less than the amount to be subtracted\n";
                   // return 0;
                }
                else
                {
                    AllProducts[i].setQuantity(AllProducts[i].getQuantity() - product.getQuantity());
                    cout << "The Product has been decreased\n";
                    //return 1;
                }
                break;
            }
        }
    }
    void SetProductPrice(const Product& product)
    {
        if (!isPresent(product))
        {
            cout << "The product is not present\n";
            return;
        }
        for (int i = 0; i < NoOfProducts; i++)
        {
            if (AllProducts[i] == product)
            {
                AllProducts[i].setBasePrice(product.getBasePrice());
                cout << "Price has been updated\n";
                break;
            }
        }
    }
    //return the index for the product that has quantity less than 100
    int FindProductToOrder()
    {
        cout << "The Products that need ordering are: ";
        int ordercounter = 0;
        for (int i = 0; i < NoOfProducts; i++)
        {
            if (AllProducts[i].getQuantity() < 100)
            {
                cout << endl << AllProducts[i];
                ordercounter++;
            }
        }
        if (ordercounter == 0)
        {
            cout << "None\n";
        }
        return ordercounter;
    }
    void OrderProducts()
    {
        for (int i = 0; i < NoOfProducts; i++)
        {
            if (AllProducts[i].getQuantity() < 100)
            {
                bool supplierAvaliable=0;
                for (int j = 0; j < 10; j++)
                {
                    if (AllProducts[i].getName() == suppliers[j].getProduct())
                    {
                        cout << "Ordering a batch of 100 " << AllProducts[i].getName() <<" from "<<suppliers[j].getName()<<endl;
                        AllProducts[i].setQuantity(100 + AllProducts[i].getQuantity());
                        supplierAvaliable = 1;
                        break;
                    }
                }
                if (supplierAvaliable == 0)
                {
                    cout << "No Supplier avaliable for "<<AllProducts[i].getName()<<endl;
                }
            }
        }
    }
    void Print()
    {
        for (int i = 0; i < NoOfProducts; i++)
        {
            cout << AllProducts[i] << endl;
        }
    }
    ~Inventory()
    {
        //deletes the array
        delete[] AllProducts;
    }
};

Inventory Inventory1("Inventory1");

//work in progress
class Cart
{
private:
    Inventory& inventory;//aggregation
    Product* SelectedProducts;
    int NoOfSelected;
    int TotalPrice;
    int Discount;
    Customer customer;
    bool isPresent(const Product& product)
    {
        //checks if the product is present
        for (int i = 0; i < NoOfSelected; i++)
        {
            if (SelectedProducts[i] == product)
            {
                return 1;
            }
        }
        return 0;
    }
    bool isArrayFilled()
    {
        Product empty;
        for (int i = 0; i < NoOfSelected; i++)
        {
            if (SelectedProducts[i] == empty)
            {
                return 0;
            }
        }
        return 1;
    }
    void increaseArray()
    {
        Product* temp = new Product[NoOfSelected];
        for (int i = 0; i < NoOfSelected; i++)
        {
            temp[i] = SelectedProducts[i];
        }
        delete[] SelectedProducts;
        NoOfSelected++;
        SelectedProducts = new Product[NoOfSelected];
        for (int i = 0; i < NoOfSelected - 1; i++)
        {
            SelectedProducts[i] = temp[i];
        }
        delete[] temp;
    }
public:
    Cart(Inventory& inv=Inventory1, int selected = 0, int total = 0, int discount = 0)
        :inventory(inv), NoOfSelected(selected), TotalPrice(total), Discount(discount)
    {
        SelectedProducts = new Product[NoOfSelected];
    }
    ~Cart()
    {
        delete[] SelectedProducts;
    }
    void AddToCart(const Product& product)
    {
        if (isPresent(product))
        {
            for (int i = 0; i < NoOfSelected; i++)
            {
                if (SelectedProducts[i] == product)
                {
                    for (int j = 0; j < inventory.getNoOfProducts(); j++)
                    {
                        Product* FromInventory = inventory.getProductFromIndex(j);
                        if (*FromInventory == product)
                        {
                            if (product.getQuantity() > FromInventory->getQuantity())
                            {
                                cout << "Not enough items in invenotry\n";
                                break;
                            }
                            FromInventory->setQuantity(FromInventory->getQuantity()-product.getQuantity());
                            SelectedProducts[i].setQuantity(SelectedProducts[i].getQuantity()+product.getQuantity());
                            break;
                        }
                    }
                }
            }
        }
        else if (!isArrayFilled())
        {
            Product empty;
            for (int i = 0; i < NoOfSelected; i++)
            {
                if (SelectedProducts[i] == empty)
                {
                    for (int j = 0; j < inventory.getNoOfProducts(); j++)
                    {
                        Product* FromInventory = inventory.getProductFromIndex(j);
                        if (*FromInventory == product)
                        {
                            if (product.getQuantity() > FromInventory->getQuantity())
                            {
                                cout << "Not enough items in invenotry\n";
                                break;
                            }
                            FromInventory->setQuantity(FromInventory->getQuantity() - product.getQuantity());
                            SelectedProducts[i] = product;
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            increaseArray();
            Product empty;
            for (int i = 0; i < NoOfSelected; i++)
            {
                if (SelectedProducts[i] == empty)
                {
                    for (int j = 0; j < inventory.getNoOfProducts(); j++)
                    {
                        Product* FromInventory = inventory.getProductFromIndex(j);
                        if (*FromInventory == product)
                        {
                            if (product.getQuantity() > FromInventory->getQuantity())
                            {
                                cout << "Not enough items in invenotry\n";
                                break;
                            }
                            FromInventory->setQuantity(FromInventory->getQuantity() - product.getQuantity());
                            SelectedProducts[i] = product;
                            break;
                        }
                    }
                }
            }
        }
        TotalPrice += product.getBasePrice() * product.getQuantity();
    }
    void RemoveFromCart(const Product& product)
    {
        //first find the product if present
        //if it is there then simply subtract the product from the price
    }
    void GetTotalPrice();
    void Print()
    {
        for (int i = 0; i < NoOfSelected; i++)
        {
            cout << SelectedProducts[i] << endl;
        }
    }
    //void ApplyDiscount();
    //void PrintSelectedProducts();
};

void Manager();

void SalesMan()
{
    //--to make a cart
    //allow to add item to cart
    //allow to say done to the cart
    //allow to empty the cart
    //allow to get the total price of cart
    //allow to use discounts
    //allow to do refunds
    bool ExitFromSalesman = 0;
    while (!ExitFromSalesman)
    {
        int Action = 0;
        cout << "To make a cart press 1\n";
        cout << "To issue a refund press 2\n";
        cin >> Action;
        switch (Action)
        {
        case 1:
            {
                Cart cart;
                bool ExitFromCart = 0;
                while (!ExitFromCart)
                {
                    int CartAction = 0;
                    cout << "To add item to cart press 1\n";
                    cout << "To remove item to cart press 2\n";
                    cout << "To empty cart press 3\n";
                    cout << "To get Total price of cart press 4\n";
                    cout << "To apply discount press 5\n";
                    cin >> CartAction;
                    switch (CartAction)
                    {
                    case 1:
                        {
                            Product Added;
                            string name;
                            int quantity = 0;
                            cout << "Enter Product Name: ";
                            cin.ignore();
                            getline(cin, name);
                            cout << "Enter Quantity: ";
                            while (quantity < 0)
                            {
                                cin >> quantity;
                                if (quantity < 0)
                                {
                                    cout << "invalid quantity\n";
                                }
                            }
                            Added.setName(name);
                            Added.setQuantity(quantity);
                            cart.AddToCart(Added);
                            cart.Print();
                            break;
                        }
                    case 2:
                        {
                            break;
                        }
                    case 3:
                        {
                            break;
                        }
                    case 4:
                        {
                            break;
                        }
                    case 5:
                        {
                            break;
                        }
                    }
                }
                break;
            }
        case 2:
            {
                break;
            }
        default:
            cout << "Invalid Input\n";
        }
    }
}

int main()
{
    int selection=0;
    while (selection < 1 || selection>3)
    {
        cout << ")Welcome to a Cash And Carry Management System.\n";
        cout << ")For Manager Press 1\n";
        cout << ")For SalesMan Press 2\n";
        cout << ")To Exit Press 3\n";
        cout << "==>";
        cin >> selection;
        switch (selection)
        {
        case 1:
            Manager();
            break;
        case 2:
            SalesMan();
            break;
        case 3:
            return 0;
            break;
        default:
            cout << "Wrong input\n";
        }
    }
}

void Manager()
{
    bool Exit = 0;
    bool DontShowInventory = 0;
    while (!Exit)
    {
        DontShowInventory = 0;
        cout << ")To add a product press 1\n";
        cout << ")To remove a product press 2\n";
        cout << ")To update a product quantity press 3\n";
        cout << ")To update a product price press 4\n";
        cout << ")To check the products that need ordering press 5\n";
        cout << ")To exit to main press 6\n==>";
        int Action = 0;
        cin >> Action;
        switch (Action)
        {
        case 1:
        {
            Product ToBeAdded;
            string name;
            int price;
            cout << "Enter Product Name : ";
            cin.ignore();
            getline(cin, name);
            ToBeAdded.setName(name);
            cout << "Enter Product price: ";
            cin >> price;
            ToBeAdded.setBasePrice(price);
            Inventory1.AddProduct(ToBeAdded);
            break;
        }
        case 2:
        {
            Product ToBeRemoved;
            string name;
            cout << "Enter Product Name : ";
            cin.ignore();
            getline(cin, name);
            ToBeRemoved.setName(name);
            Inventory1.RemoveProduct(ToBeRemoved);
            break;
        }
        case 3:
        {
            cout << "Do You Want to increase or decrease a product Quantity\n";
            cout << "To Increase press 1\n";
            cout << "To Decrease press 2\n";
            int IncOrDec = 0;
            cin >> IncOrDec;
            if (IncOrDec < 1 || IncOrDec > 2)
            {
                cout << "Invalid Input\n";
                break;
            }
            Product ToBeModified;
            string name;
            int quantity = 0;
            cout << "Enter the name of Product : ";
            cin.ignore();
            getline(cin, name);
            ToBeModified.setName(name);
            if (IncOrDec == 1)
            {
                cout << "Enter the quantity to be added : ";
                cin >> quantity;
                ToBeModified.setQuantity(quantity);
                Inventory1.IncreaseProductQuantity(ToBeModified);
                break;
            }
            else
            {
                cout << "Enter the quantity to be decreased : ";
                cin >> quantity;
                ToBeModified.setQuantity(quantity);
                Inventory1.DecreaseProductQuantity(ToBeModified);
                break;
            }
        }
        case 4:
        {
            Product NewPrice;
            string name;
            int price = 0;
            cout << "Enter the name of Product : ";
            cin.ignore();
            getline(cin, name);
            NewPrice.setName(name);
            do
            {
                cout << "Enter the new price : ";
                cin >> price;
                if (price < 0)
                {
                    cout << "Invalid price\n";
                }
            } while (price < 0);
            NewPrice.setBasePrice(price);
            Inventory1.SetProductPrice(NewPrice);
            break;
        }
        case 5:
        {
            int IfOrderNeeded = Inventory1.FindProductToOrder();
            DontShowInventory = 1;
            int order = 0;
            if (IfOrderNeeded > 0)
            {
                cout << "Do you want to order these\n(All of them will be ordered)\n";
                cout << "For Yes Press 1\n";
                cout << "For No Press 2\n==>";
                cin >> order;
                if (order == 1)
                {
                    Inventory1.OrderProducts();
                }
            }
            break;
        }
        case 6:
            main();
            break;
        default:
            cout << "Invalid Input\n";
        }
        if (DontShowInventory == 0)
        {
            Inventory1.Print();
        }
    }
}