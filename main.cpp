#include <iostream>
#include <string>
#include <vector>

class Software {
    std::string name_;
    int license_no_;
public:
    Software() = default;
    Software (const std::string& name, int number) 
        : name_(name), license_no_(number) {
        if (number < 0) throw std::invalid_argument("Negative license number");
        if (name.empty()) throw std::invalid_argument("The name can't be empty");
    }
    int licenseNo() const {return license_no_;}
    const std::string& name() const {return name_;}
};

class Computer {
    int id_;
    std::string networkAddress_;
    std::vector<Software> installed_;
public:
    // Конструктор по умолчанию
    Computer() = default;

    // Основной конструктор с проверками
    Computer (int id, const std::string& address) 
        : id_(validateId(id))
    {
        setNetworkAddress(address);
    }

    // Сеттер с проверкой
    void setNetworkAddress(const std::string& addr) {
        if (addr.empty()) throw std::invalid_argument("Invalid IPv4 address" + addr);
        networkAddress_ = addr;
    } 

    // Геттеры
    const std::string getNetworkAddress() const {return networkAddress_;}
    int getId()  {return id_;}
    std::string getSoftwareInfo(int licence) {
        for (const auto& s : installed_) {
            if (s.licenseNo() == licence) {
                return "License №:" + std::to_string(s.licenseNo()) + ", Software: " + s.name();
            }
        }
        return "Software with license " + std::to_string(licence) + " not found";
    }

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
                
class User {
    std::string username_;
    Computer owned_;
public:
    User() = default;
    User (const std::string& name) 
        : username_(name) {
        if (name.empty()) throw std::invalid_argument("Empty name");
    }
    const std::string& name() const {return username_;}
};

int main () {
    // Computer pc1("Alice");
    // pc1.soft.push_back(Software("Windows", 42));
    // pc1.device = Device("Laptop", 21);

    // if (pc1.device.address() == 21 && pc1.device.device() == "Laptop") {
    //     std::cout << "It's " << pc1.person.name() 
    //     << " with Windows 11 with licence №" << pc1.soft[0].licenseNo() << std::endl;
    // }
    Computer pc1(42, "192.168.7.1");
    pc1.addSoftware(Software("Browser", 42));
    std::cout << pc1.getNetworkAddress() << " " << pc1.getId() << std::endl;
    std::cout << pc1.getSoftwareInfo(42) << '\n' << pc1.getSoftwareInfo(52) << '\n';
};