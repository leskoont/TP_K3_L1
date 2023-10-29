#include <iostream>
#include "custom_classes.h"

int main() {
    Keeper keeper;

    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Furniture\n";
        std::cout << "2. Add Employee\n";
        std::cout << "3. Add Car\n";
        std::cout << "4. Copy Object\n";
        std::cout << "5. Remove Object\n";
        std::cout << "6. Save to File\n";
        std::cout << "7. Load from File\n";
        std::cout << "8. List Objects\n";
        std::cout << "9. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            Furniture* furniture = new Furniture();
            furniture->SetAttributes();
            keeper.AddObject(furniture);
            break;
        }
        case 2: {
            Employee* employee = new Employee();
            employee->SetAttributes();
            keeper.AddObject(employee);
            break;
        }
        case 3: {
            Car* car = new Car();
            car->SetAttributes();
            keeper.AddObject(car);
            break;
        }
        case 4: {
            std::cout << "Enter the index of the object to copy: ";
            int index;
            std::cin >> index;
            Base* objectToCopy = keeper.GetObject(index);
            if (objectToCopy) {
                if (dynamic_cast<Furniture*>(objectToCopy)) {
                    Furniture* copy = new Furniture(*dynamic_cast<Furniture*>(objectToCopy));
                    keeper.AddObject(copy);
                }
                else if (dynamic_cast<Employee*>(objectToCopy)) {
                    Employee* copy = new Employee(*dynamic_cast<Employee*>(objectToCopy));
                    keeper.AddObject(copy);
                }
                else if (dynamic_cast<Car*>(objectToCopy)) {
                    Car* copy = new Car(*dynamic_cast<Car*>(objectToCopy));
                    keeper.AddObject(copy);
                }
            }
            else {
                std::cout << "Invalid index. Object not found." << std::endl;
            }
            break;
        }
        case 5: {
            std::cout << "Enter the index of the object to remove: ";
            int index;
            std::cin >> index;
            keeper.RemoveObject(index);
            break;
        }
        case 6: {
            std::cout << "Enter the filename to save: ";
            std::string filename;
            std::cin >> filename;
            keeper.SaveToFile(filename);
            break;
        }
        case 7: {
            std::cout << "Enter the filename to load: ";
            std::string filename;
            std::cin >> filename;
            keeper.LoadFromFile(filename);
            break;
        }
        case 8: {
            keeper.ListObjects();
            break;
        }
        case 9: {
            return 0;
        }
        default:
            std::cout << "Invalid choice. Try again." << std::endl;
        }
    }

    return 0;
}