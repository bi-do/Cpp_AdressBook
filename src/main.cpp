#include <iostream>
#include <conio.h>
#include "ui.h"
using namespace std;

int main()
{
    UI *ui = new UI();
    // int arr[] = {4, 7, 5, 9, 2, 6, 1, 15, 8};
    string dump;
    USERDATA A{static_cast<unsigned int>(15), "kim", "11111", dump};
    USERDATA B{static_cast<unsigned int>(12), "min", "22222", dump};
    USERDATA C{static_cast<unsigned int>(18), "jae", "33333", dump};
    USERDATA arr[] = {A, B , C};
    for (USERDATA element : arr)
    {
        ui->getControl().NewNode(element.age, element.name, element.phone, element.description);
    }
    ui->SearchByName();
    ui->PrintAllKey();
    delete ui;
    // ui->EventRoop();
    _getch();
}