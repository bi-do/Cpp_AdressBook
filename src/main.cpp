#include <iostream>
#include <conio.h>
#include "ui.h"
using namespace std;

void test1(UI *ui)
{
    ui->SearchByName();
    ui->PrintAllKey();
}

void testInsert(UI *ui)
{
    string dump;
    USERDATA *A = new USERDATA{static_cast<unsigned int>(24), "chovy", "11111", "세체미"};
    USERDATA *B = new USERDATA{static_cast<unsigned int>(29), "faker", "22222", "hmm....."};
    USERDATA *C = new USERDATA{static_cast<unsigned int>(25), "pyosik", "33333", "세체정"};
    USERDATA *D = new USERDATA{static_cast<unsigned int>(23), "oner", "44444", "skt의 희망"};
    USERDATA *E = new USERDATA{static_cast<unsigned int>(25), "viper", "44444", "세체원"};
    USERDATA *F = new USERDATA{static_cast<unsigned int>(27), "ruler", "66666", "세체원이었던남자"};
    USERDATA *G = new USERDATA{static_cast<unsigned int>(23), "gumayusi", "77777", "누구세요?"};
    USERDATA *H = new USERDATA{static_cast<unsigned int>(23), "keria", "8", "하입보이"};
    USERDATA *I = new USERDATA{static_cast<unsigned int>(35), "cvmax", "9", "명장"};
    USERDATA *J = new USERDATA{static_cast<unsigned int>(25), "showmaker", "10", "포스트 페이커 일뻔 했던 남자"};
    USERDATA *K = new USERDATA{static_cast<unsigned int>(25), "doran", "11", "\"주사위\""};
    USERDATA *arr[] = {A, B, C, D, E, F, G, H, I, J, K};
    // int arr[] = {4, 7, 5, 9, 2, 6, 1, 15, 8};
    for (USERDATA *element : arr)
    {
        // ui->getControl().NewNode(element->age, element->name, element->phone, element->description);
        ui->getControl().NewNode(*element);
    }
}

int main()
{
    UI *ui = new UI();
    testInsert(ui);
    // test1(ui);
    ui->EventRoop();
    delete ui;
    _getch();
}