#include "custom_classes.h"

// Реализация методов класса Base
Base::Base() {
    std::cout << "Base constructor called." << std::endl;
}

Base::Base(const Base& other) {
    std::cout << "Base copy constructor called." << std::endl;
}

Base::~Base() {
    std::cout << "Base destructor called." << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Base& obj) {
    obj.GetAttributes();
    return os;
}

// Реализация методов класса Furniture
Furniture::Furniture() {
    std::cout << "Furniture constructor called." << std::endl;
}

Furniture::Furniture(const Furniture& other) {
    std::cout << "Furniture copy constructor called." << std::endl;
    type = other.type;
    height = other.height;
    width = other.width;
    depth = other.depth;
    color = other.color;
    material = other.material;
    cost = other.cost;
}

Furniture::~Furniture() {
    std::cout << "Furniture destructor called." << std::endl;
}

void Furniture::SetAttributes() {
    std::cout << "Enter furniture type: ";
    std::cin >> type;
    std::cout << "Enter dimensions (height width depth): ";
    std::cin >> height >> width >> depth;
    std::cout << "Enter color: ";
    std::cin >> color;
    std::cout << "Enter material: ";
    std::cin >> material;
    std::cout << "Enter cost: ";
    std::cin >> cost;
}

void Furniture::GetAttributes() const {
    std::cout << "Furniture attributes:" << std::endl;
    std::cout << "Type: " << type << std::endl;
    std::cout << "Dimensions (HxWxD): " << height << "x" << width << "x" << depth << std::endl;
    std::cout << "Color: " << color << std::endl;
    std::cout << "Material: " << material << std::endl;
    std::cout << "Cost: " << cost << std::endl;
}

// Реализация методов класса Employee
Employee::Employee() {
    std::cout << "Employee constructor called." << std::endl;
}

Employee::Employee(const Employee& other) {
    std::cout << "Employee copy constructor called." << std::endl;
    name = other.name;
    position = other.position;
    salary = other.salary;
    address = other.address;
    phoneNumber = other.phoneNumber;
}

Employee::~Employee() {
    std::cout << "Employee destructor called." << std::endl;
}

void Employee::SetAttributes() {
    std::cout << "Enter employee name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Enter position: ";
    std::getline(std::cin, position);
    std::cout << "Enter salary: ";
    std::cin >> salary;
    std::cin.ignore();
    std::cout << "Enter address: ";
    std::getline(std::cin, address);
    std::cout << "Enter phone number: ";
    std::cin >> phoneNumber;
}

void Employee::GetAttributes() const {
    std::cout << "Employee attributes:" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Position: " << position << std::endl;
    std::cout << "Salary: " << salary << std::endl;
    std::cout << "Address: " << address << std::endl;
    std::cout << "Phone Number: " << phoneNumber << std::endl;
}

// Реализация методов класса Car
Car::Car() {
    std::cout << "Car constructor called." << std::endl;
}

Car::Car(const Car& other) {
    std::cout << "Car copy constructor called." << std::endl;
    make = other.make;
    model = other.model;
    licensePlate = other.licensePlate;
}

Car::~Car() {
    std::cout << "Car destructor called." << std::endl;
}

void Car::SetAttributes() {
    std::cout << "Enter car make: ";
    std::cin.ignore();
    std::getline(std::cin, make);
    std::cout << "Enter model: ";
    std::getline(std::cin, model);
    std::cout << "Enter license plate: ";
    std::cin >> licensePlate;
}

void Car::GetAttributes() const {
    std::cout << "Car attributes:" << std::endl;
    std::cout << "Make: " << make << std::endl;
    std::cout << "Model: " << model << std::endl;
    std::cout << "License Plate: " << licensePlate << std::endl;
}

// Реализация методов класса Keeper
Keeper::Keeper() : objectCount(0) {
    std::cout << "Keeper constructor called." << std::endl;
}

Keeper::~Keeper() {
    Clear();
    std::cout << "Keeper destructor called." << std::endl;
}

void Keeper::AddObject(Base* obj) {
    if (objectCount < MAX_OBJECTS) {
        objects[objectCount++] = obj;
    }
}

void Keeper::RemoveObject(int index) {
    if (index >= 0 && index < objectCount) {
        delete objects[index];
        for (int i = index; i < objectCount - 1; i++) {
            objects[i] = objects[i + 1];
        }
        objectCount--;
    }
}

void Keeper::SaveToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        for (int i = 0; i < objectCount; i++) {
            Base* obj = objects[i];
            int objectType = TypeUnknown;
            if (dynamic_cast<Furniture*>(obj)) {
                objectType = TypeFurniture;
            }
            else if (dynamic_cast<Employee*>(obj)) {
                objectType = TypeEmployee;
            }
            else if (dynamic_cast<Car*>(obj)) {
                objectType = TypeCar;
            }
            file.write(reinterpret_cast<const char*>(&objectType), sizeof(int));
            if (objectType != TypeUnknown) {
                if (objectType == TypeFurniture) {
                    Furniture* furniture = dynamic_cast<Furniture*>(obj);
                    file << *furniture;
                }
                else if (objectType == TypeEmployee) {
                    Employee* employee = dynamic_cast<Employee*>(obj);
                    file << *employee;
                }
                else if (objectType == TypeCar) {
                    Car* car = dynamic_cast<Car*>(obj);
                    file << *car;
                }
            }
        }
        file.close();
    }
    else {
        throw std::runtime_error("Error: Unable to open the file for saving.");
    }
}

void Keeper::LoadFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        Clear();
        while (true) {
            int type;
            if (!file.read(reinterpret_cast<char*>(&type), sizeof(int))) {
                break;
            }
            Base* obj = nullptr;
            switch (type) {
            case TypeFurniture: {
                Furniture furniture;
                file >> furniture;
                obj = new Furniture(furniture);
                break;
            }
            case TypeEmployee: {
                Employee employee;
                file >> employee;
                obj = new Employee(employee);
                break;
            }
            case TypeCar: {
                Car car;
                file >> car;
                obj = new Car(car);
                break;
            }
            default:
                break;
            }
            if (obj) {
                AddObject(obj);
            }
        }
        file.close();
    }
    else {
        throw std::runtime_error("Error: Unable to open the file for loading.");
    }
}


int Keeper::GetObjectCount() const {
    return objectCount;
}

Base* Keeper::GetObject(int index) {
    if (index >= 0 && index < objectCount) {
        return objects[index];
    }
    return nullptr; // Возвращаем nullptr, если индекс некорректный
}

void Keeper::Clear() {
    for (int i = 0; i < objectCount; i++) {
        delete objects[i];
        objects[i] = nullptr;
    }
    objectCount = 0;
}


void Keeper::ListObjects() {
    if (objectCount == 0) {
        std::cout << "No objects to display." << std::endl;
        return;
    }

    std::cout << "List of Objects:" << std::endl;
    std::cout << "---------------------------------------------------------" << std::endl;
    std::cout << "|  Index  |    Type    |           Attributes            |" << std::endl;
    std::cout << "---------------------------------------------------------" << std::endl;

    for (int i = 0; i < objectCount; i++) {
        const Base* obj = GetObject(i);
        std::string objectType = "Unknown";

        if (dynamic_cast<const Furniture*>(obj)) {
            objectType = "Furniture";
        }
        else if (dynamic_cast<const Employee*>(obj)) {
            objectType = "Employee";
        }
        else if (dynamic_cast<const Car*>(obj)) {
            objectType = "Car";
        }

        std::cout << "|   " << i << "    |  " << objectType << "  | ";
        obj->GetAttributes(); // Output object attributes
        std::cout << "---------------------------------------------------------" << std::endl;
    }
}