// MenuManager.hpp

#ifndef MENU_MANAGER_HPP
#define MENU_MANAGER_HPP

#include <iostream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

struct MenuItem {
    string name;
    double price;

    MenuItem(string name, double price);
};

class MenuManager {
private:
   list<MenuItem> menuItems;

public:
    void addMenuItem(string name, double price);
    void removeMenuItem(string& name);
    void listMenuItems();
    void updateMenuItemPrice(string name, double newPrice);
};

#endif // MENU_MANAGER_HPP
