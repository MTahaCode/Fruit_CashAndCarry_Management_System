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

class Supplier;

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
class Product;

ostream& operator<<(ostream& os, const Product& product);

//Inventory
class Inventory;

Inventory Inventory1("Inventory1");

class InventoryReport
{
private:
    Inventory inventory;
    int TotalPriceOfAllProducts;
public:

    //allow for products that need ordering
    //allow for products that have a stock of more than 1000
    //allow to show the products by supplier


};

class Cart;

void Manager();

void SalesMan()
{
    //--to make a cart
    //--allow to add item to cart
    //allow to say done to the cart
    //allow to empty the cart
    //allow to get the total price of cart
    //allow to use discounts
    //allow to do refunds
    bool ExitFromSalesman = 0;
    while (!ExitFromSalesman)
    {
        int Action = 0;
        cout << ")To make a cart press 1\n";
        cout << ")To issue a refund press 2\n";
        cout << "To go to main press 3\n==>";
        cin >> Action;
        switch (Action)
        {
        case 1:
            {
                Cart cart(Inventory1);
                bool ExitFromCart = 0;
                while (!ExitFromCart)
                {
                    int CartAction = 0;
                    cout << ")To add item to cart press 1\n";
                    cout << ")To remove item in cart press 2\n";
                    cout << ")To Update Quantity of an item in Cart press 3\n";
                    cout << ")To empty cart press 4\n";
                    cout << ")To get Total price of cart press 5\n";
                    cout << ")To apply discount press 6\n";
                    cout << ")To make a new cart press 7\n";
                    cout << ")To go back press 8\n==>";
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
                            cin >> quantity;
                            while (quantity < 0)
                            {
                                if (quantity < 0)
                                {
                                    cout << "invalid quantity\n";
                                }
                                cout << "Enter Quantity: ";
                                cin >> quantity;
                            }
                            Added.setName(name);
                            Added.setQuantity(quantity);
                            cart.AddToCart(Added);
                            cart.Print();
                            Inventory1.Print();
                            break;
                        }
                    case 2:
                        {
                            Product Removed;
                            string name;
                            cout << "Enter Product Name: ";
                            cin.ignore();
                            getline(cin, name);
                            Removed.setName(name);
                            int quantity1 = cart.RemoveFromCart(Removed);
                            //cout << quantity1 << endl;
                            Product* productFromInv = Inventory1.FindProduct(Removed);
                            productFromInv->setQuantity(productFromInv->getQuantity() + quantity1);
                            cart.Print();
                            cart.PrintInventory();
                            break;
                        }
                    case 3:
                        {
                            Product Update;
                            string name;
                            int quantity = 0;
                            cout << "Enter Product Name: ";
                            cin.ignore();
                            getline(cin, name);
                            cout << "Enter Quantity: ";
                            cin >> quantity;
                            while (quantity < 0)
                            {
                                if (quantity < 0)
                                {
                                    cout << "invalid quantity\n";
                                }
                                cout << "Enter Quantity: ";
                                cin >> quantity;
                            }
                            Update.setName(name);
                            Update.setQuantity(quantity);
                            cart.UpdateProduct(Update);
                            cart.Print();
                            cart.PrintInventory();
                            break;
                        }
                    case 4:
                        {
                            cart.EmptyCart();
                            cart.Print();
                            cart.PrintInventory();
                            break;
                        }
                    case 5:
                        {
                            cout << "The Total Bill is : "<<cart.GetTotalPrice()<<endl;
                            break;
                        }
                    case 6:
                        {

                            break;
                        }
                    case 7:
                        {

                            break;
                        }
                    case 8:
                        {

                            break;
                        }
                    default:
                        cout << "Invalid Input\n";
                    }
                }
                break;
            }
        case 2:
            {
                Product Refunded;
                string name;
                int quantity = 0;
                cout << "Enter Product Name to be refunded: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Quantity to be refunded: ";
                cin >> quantity;
                while (quantity < 0)
                {
                    if (quantity < 0)
                    {
                        cout << "invalid quantity\n";
                    }
                    cout << "Enter Quantity: ";
                    cin >> quantity;
                }
                Refunded.setName(name);
                Refunded.setQuantity(quantity);
                if (Inventory1.isPresent(Refunded))
                {
                    Inventory1.IncreaseProductQuantity(Refunded);
                }
                else
                {
                    int price;
                    cout << "Enter Price of the product: ";
                    cin >> price;
                    while (price < 0)
                    {
                        if (price < 0)
                        {
                            cout << "invalid quantity\n";
                        }
                        cout << "Enter Quantity: ";
                        cin >> price;
                    }
                    Refunded.setBasePrice(price);
                    Inventory1.AddProduct(Refunded);
                }
                Inventory1.Print();
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

class Product
{
private:
    string Name;
    int Quantity;
    int BasePrice;
    char location;
public:
    Product(string name = "", int base = 0, int quantity = 0) : Quantity(quantity), BasePrice(base), Name(name)
    {
        if (Name[0] >= 'a' && Name[0] <= 'z')
        {
            Name[0] = Name[0] - ('a' - 'A');
        }
        location = 'A' + rand() % ('Z' - 'A');
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
    os << "   BasePrice: " << product.BasePrice;
    os << "   Location: " << product.location << endl;
    return os;
}

class Inventory
{
protected:
    string Name;
    Product* AllProducts;//composition
    int NoOfProducts;
    int arraysize;
    Supplier* suppliers;//aggregation
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
    Inventory(string name = "", int size = 5) : Name(name), suppliers(Suppliers)
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
            return;
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
    Product* FindProduct(Product& product)
    {
        for (int i = 0; i < NoOfProducts; i++)
        {
            if (AllProducts[i].getName() == product.getName())
            {
                return &AllProducts[i];
            }
        }
        Product* p = new Product(product.getName(), 0, 0);
        return p;
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
                bool supplierAvaliable = 0;
                for (int j = 0; j < 10; j++)
                {
                    if (AllProducts[i].getName() == suppliers[j].getProduct())
                    {
                        cout << "Ordering a batch of 100 " << AllProducts[i].getName() << " from " << suppliers[j].getName() << endl;
                        AllProducts[i].setQuantity(100 + AllProducts[i].getQuantity());
                        supplierAvaliable = 1;
                        break;
                    }
                }
                if (supplierAvaliable == 0)
                {
                    cout << "No Supplier avaliable for " << AllProducts[i].getName() << endl;
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

class Cart
{
private:
    Inventory& inventory;//aggregation
    Product* SelectedProducts;
    int NoOfSelected;
    int arraysize;
    float TotalAfterDiscount;
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
        for (int i = 0; i < arraysize; i++)
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
        Product* temp = new Product[arraysize];
        for (int i = 0; i < arraysize; i++)
        {
            temp[i] = SelectedProducts[i];
        }
        delete[] SelectedProducts;
        arraysize++;
        SelectedProducts = new Product[arraysize];
        for (int i = 0; i < arraysize - 1; i++)
        {
            SelectedProducts[i] = temp[i];
        }
        delete[] temp;
    }
    void FixArray()
    {
        for (int i = 0; i < arraysize; i++)
        {
            if (i + 1 != arraysize && SelectedProducts[i].getName() == "")
            {
                Product temp = SelectedProducts[i];
                SelectedProducts[i] = SelectedProducts[i + 1];
                SelectedProducts[i + 1] = temp;
            }
        }
    }
public:
    Cart(Inventory& inv, int selected = 0, float discount = 0, int size = 5)
        :inventory(inv), NoOfSelected(selected), TotalAfterDiscount(discount), arraysize(size)
    {
        SelectedProducts = new Product[arraysize];
        for (int i = 0; i < arraysize; i++)
        {
            Product empty;
            SelectedProducts[i] = empty;
        }
    }
    ~Cart()
    {
        delete[] SelectedProducts;
    }
    void AddToCart(const Product& product)
    {
        //if product is not in invenotry
        if (!inventory.isPresent(product))
        {
            cout << "Product is not present in inventory\n";
            return;
        }
        //checking if the amount is less in inventory
        for (int i = 0; i < inventory.getNoOfProducts(); i++)
        {
            if (product.getName() == inventory.getProductFromIndex(i)->getName() && product.getQuantity() > inventory.getProductFromIndex(i)->getQuantity())
            {
                cout << "Not enough items in invenotry\n";
                return;
            }
        }
        //checking if the array is filled
        if (isArrayFilled())
        {
            cout << "array increased\n";
            increaseArray();
        }
        //checking if the product is present in cart
        if (isPresent(product))
        {
            for (int i = 0; i < NoOfSelected; i++)
            {
                for (int j = 0; j < inventory.getNoOfProducts(); j++)
                {
                    cout << "chekcindfa\n";
                    if (SelectedProducts[i] == product && *inventory.getProductFromIndex(j) == product)
                    {
                        Product* FromInventory = inventory.getProductFromIndex(j);
                        FromInventory->setQuantity(FromInventory->getQuantity() - product.getQuantity());
                        SelectedProducts[i].setQuantity(SelectedProducts[i].getQuantity() + product.getQuantity());
                        return;
                    }
                }
            }
        }
        else
        {
            Product empty;
            for (int i = 0; i < arraysize; i++)
            {
                for (int j = 0; j < inventory.getNoOfProducts(); j++)
                {
                    cout << "cheksaldfkjalksdjf;lja\n";
                    if (SelectedProducts[i] == empty && *inventory.getProductFromIndex(j) == product)
                    {
                        Product* FromInventory = inventory.getProductFromIndex(j);
                        FromInventory->setQuantity(FromInventory->getQuantity() - product.getQuantity());
                        SelectedProducts[i] = product;
                        SelectedProducts[i].setBasePrice(FromInventory->getBasePrice());
                        NoOfSelected++;
                        return;
                    }
                }
            }
        }
        cout << NoOfSelected << " " << arraysize << endl;
    }
    int RemoveFromCart(const Product& product)
    {
        if (!isPresent(product))
        {
            cout << "The Product is not present in cart\n";
            return 0;
        }
        for (int i = 0; i < NoOfSelected; i++)
        {
            if (SelectedProducts[i] == product)
            {
                Product empty;
                int quantity = SelectedProducts[i].getQuantity();
                SelectedProducts[i] = empty;
                NoOfSelected--;
                FixArray();
                //adding the removed quantity to inventory
                inventory.IncreaseProductQuantity(product);
                return quantity;
            }
        }
    }
    int GetTotalPrice()
    {
        int TotalPrice = 0;
        for (int i = 0; i < NoOfSelected; i++)
        {
            TotalPrice += (SelectedProducts[i].getQuantity() * SelectedProducts[i].getBasePrice());
        }
        return TotalPrice;
    }
    void Print()
    {
        for (int i = 0; i < NoOfSelected; i++)
        {
            cout << SelectedProducts[i] << endl;
        }
    }
    void PrintInventory()
    {
        inventory.Print();
    }
    void UpdateProduct(Product& product)
    {
        if (!isPresent(product) || !inventory.isPresent(product))
        {
            cout << "Product is not present in cart\n";
            return;
        }
        for (int i = 0; i < NoOfSelected; i++)
        {
            if (SelectedProducts[i] == product)
            {
                Product* FromInv = inventory.FindProduct(product);
                FromInv->setQuantity(FromInv->getQuantity() + SelectedProducts[i].getQuantity());
                SelectedProducts[i].setQuantity(0);
                AddToCart(product);
                return;
            }
        }
    }
    void EmptyCart()
    {
        for (int i = 0; i < NoOfSelected; i++)
        {
            Product empty;
            inventory.IncreaseProductQuantity(SelectedProducts[i]);
            SelectedProducts[i] = empty;
        }
        NoOfSelected = 0;
    }
    //void ApplyDiscount();
    //void PrintSelectedProducts();
};

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