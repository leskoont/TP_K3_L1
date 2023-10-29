#include "custom_classes.h"

Base::Base() {
    OutputDebugString(L"Base constructor called\n");
}

Base::Base(const Base& other) {
    OutputDebugString(L"Base copy constructor called\n");
}

Base::~Base() {
    OutputDebugString(L"Base destructor called\n");
}

std::ostream& operator<<(std::ostream& os, const Base& obj) {
    obj.GetAttributes();
    return os;
}

Furniture::Furniture() {
    OutputDebugString(L"Furniture constructor called\n");
}

Furniture::Furniture(const Furniture& other) {
    OutputDebugString(L"Furniture copy constructor called\n");
    type = other.type;
    height = other.height;
    width = other.width;
    depth = other.depth;
    color = other.color;
    material = other.material;
    cost = other.cost;
}

Furniture::~Furniture() {
    OutputDebugString(L"Furniture destructor called\n");
}

Furniture* Furniture::Clone() const {
    return new Furniture(*this);
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
    std::cout << "Enter cost ($): ";
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

std::ostream& operator<<(std::ostream& os, const Furniture& furniture) {
    os.write(reinterpret_cast<const char*>(&furniture), sizeof(Furniture));
    return os;
}

std::istream& operator>>(std::istream& is, Furniture& furniture) {
    is.read(reinterpret_cast<char*>(&furniture), sizeof(Furniture));
    return is;
}

Employee::Employee() {
    OutputDebugString(L"Employee constructor called\n");
}

Employee::Employee(const Employee& other) {
    OutputDebugString(L"Employee copy constructor called\n");
    name = other.name;
    position = other.position;
    salary = other.salary;
    address = other.address;
    phoneNumber = other.phoneNumber;
}

Employee::~Employee() {
    OutputDebugString(L"Employee destructor called\n");
}

Employee* Employee::Clone() const {
    return new Employee(*this);
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

std::ostream& operator<<(std::ostream& os, const Employee& employee) {
    os.write(reinterpret_cast<const char*>(&employee), sizeof(Employee));
    return os;
}

std::istream& operator>>(std::istream& is, Employee& employee) {
    is.read(reinterpret_cast<char*>(&employee), sizeof(Employee));
    return is;
}

Car::Car() {
    OutputDebugString(L"Car constructor called\n");
}

Car::Car(const Car& other) {
    OutputDebugString(L"Car copy constructor called\n");
    make = other.make;
    model = other.model;
    licensePlate = other.licensePlate;
}

Car::~Car() {
    OutputDebugString(L"Car destructor called\n");
}

Car* Car::Clone() const {
    return new Car(*this);
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

std::ostream& operator<<(std::ostream& os, const Car& car) {
    os.write(reinterpret_cast<const char*>(&car), sizeof(Car));
    return os;
}

std::istream& operator>>(std::istream& is, Car& car) {
    is.read(reinterpret_cast<char*>(&car), sizeof(Car));
    return is;
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

void Keeper::InsertObject(const Base* obj) {
    if (objectCount < MAX_OBJECTS) {
        objects[objectCount++] = obj->Clone(); // Создаем копию объекта и добавляем в массив.
    }
}

void Keeper::SaveToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Unable to open the file for saving.");
    }

    // Записываем количество объектов
    file.write(reinterpret_cast<const char*>(&objectCount), sizeof(int));

    for (int i = 0; i < objectCount; i++) {
        Base* obj = objects[i];
        int objectType = TypeUnknown;

        // Определяем тип объекта
        if (dynamic_cast<Furniture*>(obj)) {
            objectType = TypeFurniture;
        }
        else if (dynamic_cast<Employee*>(obj)) {
            objectType = TypeEmployee;
        }
        else if (dynamic_cast<Car*>(obj)) {
            objectType = TypeCar;
        }

        // Записываем тип объекта
        file.write(reinterpret_cast<const char*>(&objectType), sizeof(int));

        // Записываем данные объекта (если не TypeUnknown)
        if (objectType != TypeUnknown) {
            if (objectType == TypeFurniture) {
                Furniture* furniture = dynamic_cast<Furniture*>(obj);
                file.write(reinterpret_cast<const char*>(furniture), sizeof(Furniture));
            }
            else if (objectType == TypeEmployee) {
                Employee* employee = dynamic_cast<Employee*>(obj);
                file.write(reinterpret_cast<const char*>(employee), sizeof(Employee));
            }
            else if (objectType == TypeCar) {
                Car* car = dynamic_cast<Car*>(obj);
                file.write(reinterpret_cast<const char*>(car), sizeof(Car));
            }
        }
    }

    file.close();
}

void Keeper::LoadFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Unable to open the file for loading.");
    }

    Clear();

    // Читаем количество объектов
    int objectCount;
    if (!file.read(reinterpret_cast<char*>(&objectCount), sizeof(int))) {
        throw std::runtime_error("Error: Failed to read object count.");
    }

    for (int i = 0; i < objectCount; i++) {
        int type;
        if (!file.read(reinterpret_cast<char*>(&type), sizeof(int))) {
            throw std::runtime_error("Error: Failed to read object type.");
        }

        Base* obj = nullptr;

        switch (type) {
        case TypeFurniture:
            obj = new Furniture();
            if (!file.read(reinterpret_cast<char*>(obj), sizeof(Furniture))) {
                throw std::runtime_error("Error: Failed to read Furniture data.");
            }
            break;
        case TypeEmployee:
            obj = new Employee();
            if (!file.read(reinterpret_cast<char*>(obj), sizeof(Employee))) {
                throw std::runtime_error("Error: Failed to read Employee data.");
            }
            break;
        case TypeCar:
            obj = new Car();
            if (!file.read(reinterpret_cast<char*>(obj), sizeof(Car))) {
                throw std::runtime_error("Error: Failed to read Car data.");
            }
            break;
        default:
            break;
        }

        if (obj) {
            InsertObject(obj);
        }
    }

    file.close();
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
