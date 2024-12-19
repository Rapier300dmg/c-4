#include <iostream>
#include <cstring>
#include <vector>

class Person {
private:
    char* name;
    int age;

public:
    Person() : name(nullptr), age(0) {}

    Person(const char* name, int age) : age(age) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    Person(const Person& other) : age(other.age) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    }

    Person& operator=(const Person& other) {
        if (this != &other) {
            delete[] name;
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
            age = other.age;
        }
        return *this;
    }

    ~Person() {
        delete[] name;
    }

    void print() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};

class Apartment {
private:
    Person* residents;
    size_t residentCount;

public:
    Apartment() : residents(nullptr), residentCount(0) {}

    Apartment(size_t count) : residentCount(count) {
        residents = new Person[residentCount];
    }

    Apartment(const Apartment& other) : residentCount(other.residentCount) {
        residents = new Person[residentCount];
        for (size_t i = 0; i < residentCount; ++i) {
            residents[i] = other.residents[i];
        }
    }

    Apartment& operator=(const Apartment& other) {
        if (this != &other) {
            delete[] residents;
            residentCount = other.residentCount;
            residents = new Person[residentCount];
            for (size_t i = 0; i < residentCount; ++i) {
                residents[i] = other.residents[i];
            }
        }
        return *this;
    }

    ~Apartment() {
        delete[] residents;
    }

    void addResident(const Person& person, size_t index) {
        if (index < residentCount) {
            residents[index] = person;
        }
    }

    void print() const {
        std::cout << "Apartment with " << residentCount << " residents:" << std::endl;
        for (size_t i = 0; i < residentCount; ++i) {
            residents[i].print();
        }
    }
};

class House {
private:
    std::vector<Apartment> apartments;

public:
    House() {}

    void addApartment(const Apartment& apartment) {
        apartments.push_back(apartment);
    }

    void print() const {
        std::cout << "House with " << apartments.size() << " apartments:" << std::endl;
        for (size_t i = 0; i < apartments.size(); ++i) {
            std::cout << "Apartment " << i + 1 << ":" << std::endl;
            apartments[i].print();
        }
    }
};

int main() {
    Person p1("John Doe", 30);
    Person p2("Jane Smith", 28);
    Person p3("Alice Johnson", 35);

    Apartment a1(2);
    a1.addResident(p1, 0);
    a1.addResident(p2, 1);

    Apartment a2(1);
    a2.addResident(p3, 0);

    House house;
    house.addApartment(a1);
    house.addApartment(a2);

    house.print();

    return 0;
}
