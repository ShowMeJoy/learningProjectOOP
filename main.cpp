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

class Device {
    int networkAddress_;
    std::string deviceType_;
public:
    Device() = default;
    Device (const std::string& type, const int address) 
        : networkAddress_(address), deviceType_(type) {
        if (type.empty()) throw std::invalid_argument("Empty device type");
        if (address < 0) throw std::invalid_argument("Negative network address");
    }
    int address() const {return networkAddress_;}
    const std::string& device() const {return deviceType_;}
};

class User {
    std::string username_;
public:
    User() = default;
    User (const std::string& name) 
        : username_(name) {
        if (name.empty()) throw std::invalid_argument("Empty name");
    }
    const std::string& name() const {return username_;}
};

class Computer {
public:
    User person;
    Device device;
    std::vector<Software> soft;

    Computer(const std::string& username) : person(username) {}
};

int main () {
    Computer pc1("Alice");
    pc1.soft.push_back(Software("Windows", 42));
    pc1.device = Device("Laptop", 21);

    if (pc1.device.address() == 21 && pc1.device.device() == "Laptop") {
        std::cout << "It's " << pc1.person.name() 
        << " with Windows 11 with licence №" << pc1.soft[0].licenseNo() << std::endl;
    }
}