#include <iostream>
#include "classes.hpp"

int main () {

    Computer pc1(42, "192.168.7.1");
    pc1.addSoftware({"Browser", 101});
    pc1.addSoftware({"Malware", 202});

    Computer pc2(21, "192.168.0.1");
    pc2.addSoftware({"Game", 303});
    pc2.addSoftware({"IDE", 404});

    Computer pc3(33, "192.168.1.3");
    pc3.addSoftware({"Browser", 42});
    pc3.addSoftware({"MediaPlayer", 11});

    std::vector<User> users = {
        {"Alice", pc1},
        {"Bob", pc2},
        {"George", pc3}
    };
    std::vector<int> licenses = {101, 202, 303};

    Inventory inv(users, licenses);

    for (auto& line : inv.findMatches()) {
        std::cout << line << '\n';
    }
};