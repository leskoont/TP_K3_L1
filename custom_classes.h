#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <windows.h>

// ����������� ������������� ���������� ��������
const int MAX_OBJECTS = 100;

// ���� ��������
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
    virtual Base* Clone() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Base& obj);

};

class Furniture : public Base {
public:
    Furniture();
    Furniture(const Furniture& other);
    ~Furniture();

    Furniture* Clone() const override;
    void SetAttributes() override;
    void GetAttributes() const override;
    friend std::ostream& operator<<(std::ostream& os, const Furniture& furniture);
    friend std::istream& operator>>(std::istream& is, Furniture& furniture);

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

    Employee* Clone() const override;
    void SetAttributes() override;
    void GetAttributes() const override;
    friend std::ostream& operator<<(std::ostream& os, const Employee& employee);
    friend std::istream& operator>>(std::istream& is, Employee& employee);

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

    Car* Clone() const override;
    void SetAttributes() override;
    void GetAttributes() const override;
    friend std::ostream& operator<<(std::ostream& os, const Car& car);
    friend std::istream& operator>>(std::istream& is, Car& car);

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
    void InsertObject(const Base* obj);
    int GetObjectCount() const;
    Base* GetObject(int index);
    void ListObjects();
    void RemoveObject(int index);
    void SaveToFile(const std::string& filename);
    void LoadFromFile(const std::string& filename);

private:
    Base** objects;  // ������������ ������ ���������� �� ������� Base
    int objectCount;
    int capacity;  // ������� �������

    void Clear();
    void Resize(int newCapacity);
};