#include <iostream>
#include <conio.h>
#include "modul.h"
using namespace std;
class Control
{
private:
    Module &module;

    int startIndex = 0;
    Leap *leapTemp = nullptr;
    vector<Node *> searchPassTemp;
    vector<USERDATAINDEX *> searchIndexTemp;

public:
    Control(/* args */) : module(*new Module()) {};

    ~Control()
    {
        cout << "��Ʈ�ѷ� ����" << endl;
        delete &this->module;
    };

    /**�ű� ������ ���� ��Ʈ�ѷ� */
    void NewNode(int age, string &name, string &phone, string &description)
    {
        USERDATA *data = new USERDATA{age, name, phone, description};
        this->module.NewNode(*data);
    }

    /**���� ���� �˻� ��Ʈ�ѷ� */
    Leap *SearchByAge(int min, int max)
    {
        this->searchPassTemp.clear();
        this->searchIndexTemp.clear();
        return this->module.SearchByAge(min, max, this->startIndex, searchPassTemp);
    }

    /**������ ���� ��Ʈ�ѷ�*/
    void DeleteData(USERDATAINDEX &pIndex, USERDATA &pData)
    {
        this->module.DeleteData(*pIndex.PerentLeap, pIndex, pData, this->searchPassTemp);
        return;
    }

    /**��� Ű ��� ��Ʈ�ѷ� */
    void PrintAllKey()
    {
        this->module.PrintAllKey();
    }

    /**��� ������ ��� ��Ʈ�ѷ� */
    void PrintAllData()
    {
        this->module.PrintAllData();
    }

    /**�� ���� �˻� �Լ�*/
    USERDATAINDEX *getUserIndexFromTemp(int param)
    {
        if (param <= this->searchIndexTemp.size())
        {
            return this->searchIndexTemp[param - 1];
        }
        else
            return nullptr;
    }

    /**���� ���� �˻� ���� �ε��� ã���� */
    USERDATAINDEX *getStartIndex(Leap &pLeap)
    {
        return pLeap.getUserData()[startIndex];
    }

    /**���� �˻� �ݺ��� */
    USERDATAINDEX *ageIterator(Leap *&pLeap)
    {
        this->searchIndexTemp.push_back(pLeap->getUserData()[startIndex]);
        this->startIndex++;
        if (this->startIndex == pLeap->getKeys().size())
        {
            this->startIndex = 0;
            pLeap = pLeap->getNext();
        }
        return pLeap->getUserData()[this->startIndex];
    }
};
class UI
{
private:
    Control &control;

public:
    UI() : control(*new Control()) {

           };
    ~UI()
    {

        delete &this->control;
    }

    typedef enum INPUTTYPE
    {
        EXIT,
        NEW,
        SEARCHBYNAME,
        SEARCHBYAGE,
        PRINT
    } INPUTTYPE;

    int ViewUI()
    {
        int input;
        system("cls");
        cout << "[1]New\t[2]Search By Name\t[3]Search By Age\t[4]Print All\t[0]EXIT" << endl;
        cin >> input;
        return input;
    }

    void EventRoop()
    {
        int input;
        while (EXIT != (input = this->ViewUI()))
        {
            switch (input)
            {
            case NEW:
                cout << "NEW" << endl;
                _getch();
                break;
            case SEARCHBYNAME:
                cout << "searchName" << endl;
                _getch();
                break;
            case SEARCHBYAGE:
                cout << "searchAge" << endl;
                _getch();
                break;
            case PRINT:
                cout << "print" << endl;
                break;
            default:
                break;
            }
        }
        cout << "Exit" << endl;
    }

    /**������ ���� */
    void DataInsert()
    {
        int age;
        string name, phone, description;
        char flag;
        cout << "�߰��� �ּ��� �̸��� �Է����ּ���" << endl;
        cin >> name;
        cout << "�߰��� �ּ��� ���̸� �Է����ּ���" << endl;
        cin >> age;
        cout << "�߰��� �ּ��� �޴� ��ȭ ��ȣ�� �Է����ּ���" << endl;
        cin >> phone;
        cout << "�ּҿ� �޸� �߰��Ͻðڽ��ϱ�? Y/N" << endl;
        cin >> flag;
        if (flag == 'Y' || flag == 'y')
        {
            cout << "�߰��� ������ �Է����ֽʽÿ�" << endl;
            cin >> description;
        }
        this->control.NewNode(age, name, phone, description);
    }

    /**���� ���� �˻�*/
    void SearchByAge()
    {
        int min = 3, max = 8;
        // cin >> min, max;
        Leap *startLeap = this->control.SearchByAge(min, max);
        if (startLeap == nullptr)
        {
            cout << "�˻� ��� ����" << endl;
            return;
        }
        else
        {
            USERDATAINDEX *curData = this->control.getStartIndex(*startLeap);
            unsigned int count = 0;
            while (curData->key <= max)
            {
                ++count;
                cout << '[' << count << "] " << "���� : " << curData->key << "\t���� : " << curData->userdata.size() << "��" << endl;
                curData = control.ageIterator(startLeap);
            }
            cout << "������ ������ ��Ȯ�� ���̸� �Է��ϼ���" << endl;
            unsigned int input;
            cin >> input;
            if (input > count)
            {
                input = count;
            }
            curData = this->control.getUserIndexFromTemp(input);
            count = 0;
            for (USERDATA *element : curData->userdata)
            {
                count++;
                cout << '[' << count << "] " << "���� : " << element->age << " �̸� : " << element->name << " �޴���ȭ : " << element->phone << endl;
            }
            cout << "������ ������ ��ȣ�� �Է��ϼ���" << endl;
            cin >> input;
            if (input > count)
            {
                input = count;
            }
            USERDATA &searchData = *curData->userdata[input - 1];
            this->DataUpdateUI(*curData, searchData);
        }
    }

    void DataUpdateUI(USERDATAINDEX &pIndex, USERDATA &pData)
    {
        unsigned int count = 0;
        cout << "���� : " << pData.age << " �̸� : " << pData.name << " �޴���ȭ : " << pData.phone << endl;
        if (pData.description.size() > 0)
        {
            cout << "�ΰ� ���� : " << pData.description << endl;
        }
        cout << "[1] ����\t[2] ����\t[3] �Ѿ��" << endl;
        cin >> count;
        if (count < 3)
        {
            count = 3;
        }
        else if (count > 1)
        {
            count = 1;
        }

        switch (count)
        {
        case 3:

            break;
        case 2:
            this->control.DeleteData(pIndex, pData);
            break;
        case 1:
            break;
        default:
            break;
        }
    }

    /**��� ������ ��� */
    void PrintAll()
    {
        this->control.PrintAllData();
    }

    Control &getControl()
    {
        return this->control;
    }
};

int main()
{
    UI *ui = new UI();
    int arr[] = {4, 7, 5, 9, 2, 4, 6, 1, 5, 15, 8, 12, 8};
    string a, b, c;
    for (int element : arr)
    {

        ui->getControl().NewNode(element, a, b, c);
    }
    ui->SearchByAge();
    ui->PrintAll();
    delete ui;
    // ui->EventRoop();
    _getch();
}