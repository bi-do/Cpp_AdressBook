#include <iostream>
#include <conio.h>
#include "control.h"
using namespace std;

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
                this->DataInsert();
                _getch();
                break;
            case SEARCHBYNAME:
                cout << "searchName" << endl;
                _getch();
                break;
            case SEARCHBYAGE:
                this->SearchByAge();
                _getch();
                break;
            case PRINT:
                this->PrintAll();
                getch();
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
    void SearchByName()
    {
        using USERDATAINDEX = USERDATAINDEX<string>;
        string input;

        cout << "�˻��� �ּ��� �̸��� �Է����ּ���" << endl;
        input = "kim";
        // cin >> input;
        Leap<string> *startLeap = this->control.SearchByName(input);
        if (startLeap == nullptr)
        {
            cout << "�˻� ��� ����" << endl;
            return;
        }
        else
        {
            USERDATAINDEX *curData = this->control.getStartIndex(*startLeap);
            unsigned int count = 0;
            for (INDEXINFO *element : curData->getUserAdt())
            {
                count++;
                cout << '[' << count << "] " << "�̸� : " << curData->getKey() << "\t���� : " << element->user->age << "\t�޴���ȭ : " << element->user->phone << endl;
            }
            cout << "������ ������ ��ȣ�� �Է��ϼ���" << endl;
            cin >> count;
            if (count >= curData->getUserAdt().size())
            {
                count = curData->getUserAdt().size();
            }
            USERDATA &searchData = *curData->getUserAdt()[count - 1]->user;
            this->DataUpdateUI(*curData->getUserAdt()[count - 1], searchData);
        }
    }
    /**���� ���� �˻�*/
    void SearchByAge()
    {
        using USERDATAINDEX = USERDATAINDEX<unsigned int>;
        cout << "�˻��� ������ ������ �Է����ּ���" << endl;
        unsigned int min = 3, max = 19;
        // cin >> min, max;
        if (min > max)
        {
            int tmp = min;
            min = max;
            max = tmp;
        }
        Leap<unsigned int> *startLeap = this->control.SearchByAge(min, max);
        if (startLeap == nullptr)
        {
            cout << "�˻� ��� ����" << endl;
            return;
        }
        else
        {
            USERDATAINDEX *curData = this->control.getStartIndex(*startLeap);
            unsigned int count = 0;
            while (curData != nullptr && curData->getKey() <= max)
            {
                ++count;
                cout << '[' << count << "] " << "���� : " << curData->getKey() << "\t���� : " << curData->getUserAdt().size() << "��" << endl;
                curData = control.ageIterator(min, startLeap);
            }

            cout << "������ ������ ��ȣ�� �Է��ϼ���" << endl;
            unsigned int input;
            cin >> input;

            if (input > count)
            {
                input = count;
            }

            curData = this->control.getUserIndexFromTemp(input, input);
            count = 0;
            for (INDEXINFO *element : curData->getUserAdt())
            {
                count++;
                cout << '[' << count << "] " << "���� : " << element->user->age << " �̸� : " << element->user->name << " �޴���ȭ : " << element->user->phone << endl;
            }
            cout << "������ ������ ��ȣ�� �Է��ϼ���" << endl;
            cin >> input;
            if (input > count)
            {
                input = count;
            }
            USERDATA &searchData = *curData->getUserAdt()[input - 1]->user;
            this->DataUpdateUI(*curData->getUserAdt()[input - 1], searchData);
        }
    }

    /**������ ������Ʈ ���� Ȯ��*/
    void DataUpdateUI(INDEXINFO &pIndex, USERDATA &pData)
    {
        unsigned int count = 0;
        cout << "���� : " << pData.age << " �̸� : " << pData.name << " �޴���ȭ : " << pData.phone << endl;
        if (pData.description.size() > 0)
        {
            cout << "�ΰ� ���� : " << pData.description << endl;
        }
        cout << "[1] ����\t[2] ����\t[3] �Ѿ��" << endl;
        count = 2;
        // cin >> count;
        if (count > 3)
        {
            count = 3;
        }
        else if (count < 1)
        {
            count = 1;
        }
        switch (count)
        {
        case 3:
            break;
        case 2:
            this->control.DeleteData(pIndex);
            break;
        case 1:
            this->DataCorrectionUI(pIndex,pData);
            break;
        default:
            break;
        }
    }

    /**������ ���� */

    void DataCorrectionUI(INDEXINFO &pIndex, USERDATA &pData)
    {
        int age;
        string name, phone, description;
        char flag;
        cout << "������ �̸��� �Է����ּ���" << endl;
        cin >> name;
        cout << "������ ���̸� �Է����ּ���" << endl;
        cin >> age;
        cout << "������ �޴� ��ȭ ��ȣ�� �Է����ּ���" << endl;
        cin >> phone;
        cout << "�ּҿ� �޸� �����Ͻðڽ��ϱ�? Y/N" << endl;
        cin >> flag;
        if (flag == 'Y' || flag == 'y')
        {
            cout << "������ ������ �Է����ֽʽÿ�" << endl;
            cin >> description;
        }
        this->control.UpdateData(age, name, phone, description, pIndex, pData);
    }

    /**��� ������ ��� */
    void PrintAll()
    {
        this->control.PrintAllData();
    }

    void PrintAllKey()
    {
        this->control.PrintAllKey();
    }

    Control &getControl()
    {
        return this->control;
    }
};
