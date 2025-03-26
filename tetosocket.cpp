#include <iostream>
#include <daytime.hpp>
#include <netimpl.hpp>
using namespace std;

int main()
{
    // DayTime teto;
    std::cout << "Server - 1; Client - 2" << std::endl;
    std::cout << "Teto (1/2): ";
    int choice;
    std::cin >> choice;
    if (choice == 1)
    {
        Server serv;
        serv.loop();
    }
    else if (choice == 2)
    {
        Client clie;
        clie.loop();
    }

    return 0;
}