#include <iostream>
#include <string>

// Abstract base class Vehicle
class Vehicle {
protected:
    std::string make;
    std::string model;
    int year;

public:
    // Constructor
    Vehicle(const std::string& mk, const std::string& mdl, int yr)
        : make(mk), model(mdl), year(yr) {}

    // Virtual destructor
    virtual ~Vehicle() {}

    // Pure virtual function to calculate rental cost
    virtual double calculateRentalCost(int rentalDays) const = 0;

    // Function to display vehicle details
    virtual void display() const {
        std::cout << "Make: " << make << ", Model: " << model << ", Year: " << year;
    }
};

// Derived class Car
class Car : public Vehicle {
private:
    bool isLuxury;

public:
    // Constructor
    Car(const std::string& mk, const std::string& mdl, int yr, bool luxury)
        : Vehicle(mk, mdl, yr), isLuxury(luxury) {}

    // Override calculateRentalCost
    double calculateRentalCost(int rentalDays) const {
        double baseRate = isLuxury ? 1000.0 : 30.0;
        return baseRate * rentalDays;
    }

    // Override display
    void display() const {
        Vehicle::display();
        std::cout << ", Type: Car, Luxury: " << (isLuxury ? "Yes" : "No") << std::endl;
    }
};

// Derived class SUV
class SUV : public Vehicle {
private:
    bool hasFourWheelDrive;

public:
    // Constructor
    SUV(const std::string& mk, const std::string& mdl, int yr, bool fourWheelDrive)
        : Vehicle(mk, mdl, yr), hasFourWheelDrive(fourWheelDrive) {}

    // Override calculateRentalCost
    double calculateRentalCost(int rentalDays) const {
        double baseRate = hasFourWheelDrive ? 5000.0 : 400.0;
        return baseRate * rentalDays;
    }

    // Override display
    void display() const {
        Vehicle::display();
        std::cout << ", Type: SUV, Four-Wheel Drive: " << (hasFourWheelDrive ? "Yes" : "No") << std::endl;
    }
};

// Derived class Truck
class Truck : public Vehicle {
private:
    double loadCapacity; // in tons

public:
    // Constructor
    Truck(const std::string& mk, const std::string& mdl, int yr, double capacity)
        : Vehicle(mk, mdl, yr), loadCapacity(capacity) {}

    // Override calculateRentalCost
    double calculateRentalCost(int rentalDays) const {
        double baseRate = 2500.0;
        double capacityRate = 100.0 * loadCapacity; // additional cost based on load capacity
        return (baseRate + capacityRate) * rentalDays;
    }

    // Override display
    void display() const {
        Vehicle::display();
        std::cout << ", Type: Truck, Load Capacity: " << loadCapacity << " tons" << std::endl;
    }
};

int main() {
    // Create objects of derived classes
    Car car("mazda", "Cx5", 2021, true);
    SUV suv("rolls royce", "maybach", 2018, true);
    Truck truck("Toyota", "isuzu", 2020, 15.0);

    // Display vehicle details and calculate rental costs
    car.display();
    std::cout << "Rental cost for 4 days: Ksh" << car.calculateRentalCost(4) << std::endl << std::endl;

    suv.display();
    std::cout << "Rental cost for 3 days: Ksh" << suv.calculateRentalCost(3) << std::endl << std::endl;

    truck.display();
    std::cout << "Rental cost for 10 days: Ksh" << truck.calculateRentalCost(10) << std::endl << std::endl;

    return 0;
}
