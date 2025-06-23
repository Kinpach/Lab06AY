#include <iostream>
#include <string>
#include <stdexcept>
#include <ctime>

using namespace std;

// Класс "Хлеб"
class Bread {
private:
    string flour_type;       // Тип муки
    string manufacture_date; // Дата изготовления в формате ДД.ММ.ГГГГ

// Класс исключения для недопустимых параметров хлеба
class BreadException : public out_of_range {
private:
    string flour_type;
    string manufacture_date;
    
public:
    BreadException(const string& msg, const string& flour, const string& date)
        : out_of_range(msg), flour_type(flour), manufacture_date(date) {}
    
    void printDetails() const {
        cout << "Error: " << what() << endl;
        cout << "Wrong dough/date:" << endl;
        cout << "Flour: " << flour_type << endl;
        cout << "Date: " << manufacture_date << endl;
    }
};
    
    // Проверка даты
    bool isValidDate(const string& date) const {
        if (date.length() != 10) return false;
        if (date[2] != '.' || date[5] != '.') return false;
        
        try {
            int day = stoi(date.substr(0, 2));
            int month = stoi(date.substr(3, 2));
            int year = stoi(date.substr(6, 4));
            
            if (day < 1 || day > 31) return false;
            if (month < 1 || month > 12) return false;
            if (year < 2020 || year > 2023) return false;
            
            return true;
        } catch (...) {
            return false;
        }
    }
    
public:
    // Конструктор с проверкой
    Bread(const string& flour, const string& date) {
        // Проверка муки
        if (flour != "wheat" && flour != "rice") {
            throw BreadException("wrong flour", flour, date);
        }
        
        // Проверка даты
        if (!isValidDate(date)) {
            throw BreadException("wrong date", flour, date);
        }
        
        flour_type = flour;
        manufacture_date = date;
    }
    
    void printInfo() const {
        cout << "Bread (" << flour_type << "), date: " << manufacture_date << endl;
    }
};

int main() {
    try {
        // Создаем правильный хлеб
        cout << "Good bread attempt:" << endl;
        Bread good_bread("wheat", "15.04.2025");
        good_bread.printInfo();
        cout << endl;
        
        // Попытка создать хлеб с неправильной мукой
        cout << "Wrong flour attempt:" << endl;
        Bread bad_flour("bone", "15.04.2025");
    } catch (const BreadException& e) {
        e.printDetails();
        cout << endl;
    }
    
    try {
        // Попытка создать хлеб с неправильной датой
        cout << "Wrong date attempt:" << endl;
        Bread bad_date("wheat", "32.13.2023");
    } catch (const BreadException& e) {
        e.printDetails();
        cout << endl;
    }
    
    // Создаем правильный хлеб после неудачных попыток
    try {
        cout << "One more good bread attempt:" << endl;
        Bread another_good_bread("rice", "20.06.2023");
        another_good_bread.printInfo();
    } catch (const BreadException& e) {
        e.printDetails();
    }
    
    return 0;
}
