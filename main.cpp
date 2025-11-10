#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
    int getId() const {return id_;}
    const std::vector<Software>& getInstalled() const {return installed_;}

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
    Computer computer_;
public:
    User() = default;
    User (const std::string& name, Computer comp) 
        : username_(name),  computer_(comp) {
        if (name.empty()) throw std::invalid_argument("Empty name");
    }
    const std::string& getName() const {return username_;}
    const Computer& getComputer() const {return computer_;}
};

class Inventory {
    std::vector<User> users_;
    std::vector<int> licenses_;
public:
    // Inventory() = default;
    // Inventory (const std::vector<User>& users, const std::vector<int>& licenses) 
    //     : users_(users), licenses_(licenses) {
    //         if (users.empty() || licenses.empty()) throw std::invalid_argument("Empty list!");
    //     }
    void addUser(User user) {
        users_.push_back(user);
    }    
    void addLicenses(int licenses) {
        licenses_.push_back(licenses);
    }
    // Методы для поиска
    std::vector<std::string> findMatches() const {
        std::vector<std::string> result;
        for (const auto& user : users_) {
            for (const auto& soft : user.getComputer().getInstalled()) {
                if (std::find(licenses_.begin(), licenses_.end(), soft.licenseNo()) != licenses_.end()) {
                    result.push_back(user.getName() + " has " + soft.name() + 
                                    " (license " + std::to_string(soft.licenseNo()) + ")");
                }
            }
        }
        return result;
    }
};

int main () {

    Computer pc1(42, "192.168.7.1");
    Computer pc2(21, "192.168.0.1");
    Computer pc3(33, "192.168.1.3");

    pc1.addSoftware(Software("Browser", 101));
    pc1.addSoftware(Software("Malware", 202));
    pc2.addSoftware(Software("Game", 303));
    pc2.addSoftware(Software("IDE", 404));
    pc3.addSoftware(Software("Browser", 42));
    pc3.addSoftware(Software("MediaPlayer", 11));

    User user1("Alice", pc1);
    User user2("Bob", pc2);
    User user3("George", pc3);

    Inventory inv;

    inv.addUser(user1);
    inv.addUser(user2);
    inv.addUser(user3);

    inv.addLicenses(101);
    inv.addLicenses(202);
    inv.addLicenses(303);

    for (auto& line : inv.findMatches()) {
        std::cout << line << '\n';
    }
};