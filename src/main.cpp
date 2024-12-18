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
    USERDATA *A = new USERDATA{static_cast<unsigned int>(24), "chovy", "11111", "��ü��"};
    USERDATA *B = new USERDATA{static_cast<unsigned int>(29), "faker", "22222", "hmm....."};
    USERDATA *C = new USERDATA{static_cast<unsigned int>(25), "pyosik", "33333", "��ü��"};
    USERDATA *D = new USERDATA{static_cast<unsigned int>(23), "oner", "44444", "skt�� ���"};
    USERDATA *E = new USERDATA{static_cast<unsigned int>(25), "viper", "44444", "��ü��"};
    USERDATA *F = new USERDATA{static_cast<unsigned int>(27), "ruler", "66666", "��ü���̾�������"};
    USERDATA *G = new USERDATA{static_cast<unsigned int>(23), "gumayusi", "77777", "��������?"};
    USERDATA *H = new USERDATA{static_cast<unsigned int>(23), "keria", "8", "���Ժ���"};
    USERDATA *I = new USERDATA{static_cast<unsigned int>(35), "cvmax", "9", "����"};
    USERDATA *J = new USERDATA{static_cast<unsigned int>(25), "showmaker", "10", "����Ʈ ����Ŀ �ϻ� �ߴ� ����"};
    USERDATA *K = new USERDATA{static_cast<unsigned int>(25), "doran", "11", "\"�ֻ���\""};
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