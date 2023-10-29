#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

// Определение максимального количества объектов
const int MAX_OBJECTS = 100;

// Типы объектов
const int TypeUnknown = 0;
const int TypeFurniture = 1;
const int TypeEmployee = 2;
const int TypeCar = 3;

class Base {
public:
    Base();
    Base(const Base& other);
    virtual ~Base();

    virtual void SetAttributes() = 0;
    virtual void GetAttributes() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Base& obj);

};

class Furniture : public Base {
public:
    Furniture();
    Furniture(const Furniture& other);
    ~Furniture();

    void SetAttributes() override;
    void GetAttributes() const override;

private:
    std::string type;
    double height, width, depth;
    std::string color;
    std::string material;
    double cost;
};

class Employee : public Base {
public:
    Employee();
    Employee(const Employee& other);
    ~Employee();

    void SetAttributes() override;
    void GetAttributes() const override;

private:
    std::string name;
    std::string position;
    double salary;
    std::string address;
    std::string phoneNumber;
};

class Car : public Base {
public:
    Car();
    Car(const Car& other);
    ~Car();

    void SetAttributes() override;
    void GetAttributes() const override;

private:
    std::string make;
    std::string model;
    std::string licensePlate;
};

class Keeper {
public:
    Keeper();
    ~Keeper();

    void AddObject(Base* obj);
    int GetObjectCount() const;
    Base* GetObject(int index);
    void ListObjects();
    void RemoveObject(int index);
    void SaveToFile(const std::string& filename);
    void LoadFromFile(const std::string& filename);

private:
    Base* objects[MAX_OBJECTS];
    int objectCount;

    void Clear();
};