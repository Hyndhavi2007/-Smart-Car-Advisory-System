#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
#include<string>
using namespace std;

// ------------------ User Class ------------------------
class User {
public:
    string name;
    double annualIncome;
    double budget;
    string usage;

    void inputFromUser(){
        cout << "Enter Your Name: ";
        cin >> name;
        cout << "Enter Your Annual Income(After Tax): ₹";
        cin >> annualIncome;
        cout << "Enter Your Budget: ₹";
        cin >> budget;
        cout << "Usage Purpose (Rural/Urban): ";
        cin >> usage;
    }
};

// -------------------Car Class-------------------
class Car {
public:
    string name;
    double price;
    double mileage;

    Car(string n, double p, double m) {
        name = n;
        price = p;
        mileage = m;
    }

    virtual double getRunningCostPrice() {
        return 0;
    }

    virtual string getTypeOfCar() {
        return "Base Car";
    }
};

// ---------------- Child Classes ----------------
class PetrolCar : public Car {
public:
    PetrolCar(string n , double p , double m) : Car(n , p, m){}

    string getTypeOfCar() {
        return "Petrol Car";
    }

    double getRunningCostPrice() {
        return 9; // ₹ per km (realistic)
    }
};

class DieselCar : public Car {
public:
    DieselCar(string n, double p, double m): Car(n ,p , m){}

    string getTypeOfCar(){
        return "Diesel Car";
    }

    double getRunningCostPrice(){
        return 7; // ₹ per km (realistic)
    }
};

class ElectricCar : public Car{
public: 
    ElectricCar(string n, double p, double m) : Car(n , p , m){}

    string getTypeOfCar(){
        return "Electric Car";
    }

    double getRunningCostPrice(){
        return 2; // ₹ per km
    }
};

class SUV : public Car {
public:
    SUV(string n, double p, double m) : Car(n, p, m){}

    string getTypeOfCar(){
        return "SUV";
    }

    double getRunningCostPrice(){
        return 12; // ₹ per km
    }
};

class SportsCar : public Car {
public:
    SportsCar(string n, double p, double m) : Car(n ,p, m){}

    string getTypeOfCar(){
        return "Sports Car";
    }

    double getRunningCostPrice() {
        return 18; // ₹ per km (high fuel usage)
    }
};

// ------- Finance --------
class Finance{
public:
    static double maxAffordablePrice(double income) {
        return income * 0.8;
    }

    static string affordability(double income, double carPrice) {
        double maxPrice = maxAffordablePrice(income);
        if(carPrice <= maxPrice){
            return "Comfortable";
        } else if(carPrice <= maxPrice * 1.2){
            return "Risky";
        } else {
            return "Not Recommended";
        }
    }
};

// -------- Loan ---------
class Loan{
public:
    static double calculateEMI(double principal, double rate, int months){
        double monthlyRate = rate / (12 * 100);
        return (principal * monthlyRate * pow(1 + monthlyRate, months)) /
               (pow(1+monthlyRate, months) -1);
    }
};

// -------- Cost ---------
class Cost{
public:
    static double monthlyFuelCost(Car* car, int kmPerMonth) {
        return car->getRunningCostPrice() * kmPerMonth;
    }
};

// -------- Eco ---------
class EcoRatingSystem {
public:
    static string getEcoScore(Car* car) {
        if (car->getTypeOfCar() == "Electric Car")
            return "High Eco Friendly";
        else if (car->getTypeOfCar() == "Petrol Car")
            return "Medium Eco Friendly";
        else
            return "Low Eco Friendly";
    }
};

// -------- Recommendation --------
class RecommendationEngine {
public:
    static Car* recommend(vector<Car*>& cars, User& user) {
        Car* bestCar = nullptr;

        for(auto car : cars) {
            if(car->price <= user.budget) {
                if(bestCar == nullptr || car->price > bestCar->price) {
                    bestCar = car; // choose highest price within budget
                }
            }
        }

        return bestCar;
    }
};
// -------- Comparison --------
class ComparisonEngine {
public:
    static void compare(Car* c1, Car* c2) {
        cout << "\n--- Car Comparison ---\n";

        cout << c1->name << " (" << c1->getTypeOfCar() << ")\n";
        cout << "Price: ₹" << c1->price << " | Mileage: " << c1->mileage << endl;

        cout << c2->name << " (" << c2->getTypeOfCar() << ")\n";
        cout << "Price: ₹" << c2->price << " | Mileage: " << c2->mileage << endl;
    }
};

// ---------------- MAIN ----------------
int main() {

    cout << fixed << setprecision(0);

    User user;
    user.inputFromUser();

    vector<Car*> cars;

    cars.push_back(new PetrolCar("Honda City", 1000000, 18));
    cars.push_back(new DieselCar("Hyundai Creta", 1400000, 20));
    cars.push_back(new ElectricCar("Tata Nexon EV", 1500000, 25));
    cars.push_back(new SUV("Mahindra Scorpio", 1800000, 14));
    cars.push_back(new SportsCar("Ford Mustang", 5000000, 8));

    Car* recommended = RecommendationEngine::recommend(cars, user);

    if(recommended != nullptr) {
        cout << "\n Recommended Car: " << recommended->name << endl;
        cout << "Type: " << recommended->getTypeOfCar() << endl;
        cout << "Usage: " << user.usage << endl;

        cout << "Affordability: "
             << Finance::affordability(user.annualIncome, recommended->price) << endl;

        double emi = Loan::calculateEMI(recommended->price, 8, 60);
        cout << "Monthly EMI: ₹" << emi << endl;

        cout << "Monthly Fuel Cost: ₹"
             << Cost::monthlyFuelCost(recommended, 1000) << endl;

        cout << "Eco Score: "
             << EcoRatingSystem::getEcoScore(recommended) << endl;

    } else {
        cout << " No suitable car found.\n";
    }

    ComparisonEngine::compare(cars[0], cars[2]);

    return 0;
}