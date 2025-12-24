#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

// Класс, представляющий программное обеспечение
class Software {
    std::string name_;      // Название ПО
    int license_no_;        // Номер лицензии
public:
    // Конструктор по умолчанию
    Software() = default;

    // Конструктор с параметрами
    // name - название ПО, number - номер лицензии
    // Генерирует исключение, если номер отрицательный или имя пустое
    Software (const std::string& name, int number) 
        : name_(name), license_no_(number) {
        if (number < 0) throw std::invalid_argument("Negative license number");
        if (name.empty()) throw std::invalid_argument("The name can't be empty");
    }

    // Возвращает номер лицензии
    int licenseNo() const {return license_no_;}

    // Возвращает имя лицензии
    const std::string& name() const {return name_;}
};

// Класс, представляющий компьютер
class Computer {
    int id_;                                // Идентификатор компьютера
    std::string networkAddress_;            // Адрес в локальной сети
    std::vector<Software> installed_;       // Список классов программного обеспечения
public:
    // Конструктор по умолчанию
    Computer() = default;

    // Конструктор с параметрами
    // id - идентификатор компьютера, address - локальный адрес
    Computer (int id, const std::string& address) 
        : id_(validateId(id))
    {
        setNetworkAddress(address);
    }

    // Сеттер с проверкой. Вернет исключение, если адрес пустой
    void setNetworkAddress(const std::string& addr) {
        if (addr.empty()) throw std::invalid_argument("Empty IPv4 address" + addr);
        networkAddress_ = addr;
    } 

    // Геттер для сетевого адреса компьютера
    // Возвращает копию строки с адресом
    const std::string getNetworkAddress() const {return networkAddress_;}

    // Геттер для сетевого идентификатора компьютера
    // Возвращает копию строки с айди
    int getId() const {return id_;}

    // Геттер для списка установленного ПО
    // Возвращает ссылку на вектор установленных объектов Software
    // Использование const гарантирует, что вектор нельзя изменить через этот геттер
    const std::vector<Software>& getInstalled() const {return installed_;}

    // Метод для добавления нового ПО в список
    void addSoftware(Software s) {
        installed_.push_back(s);
    }

private:
    // Вспомогательная функция для проверки id
    static int validateId(int id) {
        if (id < 0) throw std::invalid_argument("Negative id");
        return id;
    }
};

// Класс, определяющий пользователя
class User {
    std::string username_;      // Имя пользователя
    Computer computer_;         // Класс компьютера

public:
    // Конструктор по умолчанию
    User() = default;

    // Конструктор с параметрами
    // name - имя пользователя, comp - компьютер
    User (const std::string& name, Computer comp) 
        : username_(name),  computer_(comp) {
        if (name.empty()) throw std::invalid_argument("Empty name");
    }

    // Геттер для имени пользователя
    const std::string& getName() const {return username_;}

    // Геттер для компьтера
    const Computer& getComputer() const {return computer_;}
};

// Класс, объединяющий список пользователй и список номеров лицензий ПО
class Inventory {
    std::vector<User> users_;       // Список пользователей
    std::vector<int> licenses_;     // Список номеров лиценщий

public:
    // Конструктор по умолчанию
    Inventory() = default;

    // Конструктор с параметрами
    // users - список пользователей, licenses - список лицензий
    Inventory (const std::vector<User> users, std::vector<int> licenses)
        : users_(users), licenses_(licenses) {}
    
    // Метод для добавления пользователя в список
    void addUser(User user) {
        users_.push_back(user);
    }    

    // Метод для добавления лицензии в список
    void addLicenses(int licenses) {
        licenses_.push_back(licenses);
    }

    // Метод для поиска соответствий
    // Позволяет найти, какому пользователю принадлежит ПО с определенными номерами лицензий
    std::vector<std::string> findMatches() const {
        // В качестве результата вернет список с парами Пользователь + номер лицензии
        std::vector<std::string> result;
        for (const auto& user : users_) {
            for (const auto& soft : user.getComputer().getInstalled()) {
                if (std::find(licenses_.begin(), licenses_.end(), soft.licenseNo()) != licenses_.end()) {
                    result.push_back(user.getName() + " → " + user.getComputer().getNetworkAddress());
                }
            }
        }
        return result;
    }
};

#endif