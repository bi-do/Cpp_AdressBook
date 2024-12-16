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
        cout << "컨트롤러 해제" << endl;
        delete &this->module;
    };

    /**신규 데이터 삽입 컨트롤러 */
    void NewNode(int age, string &name, string &phone, string &description)
    {
        USERDATA *data = new USERDATA{age, name, phone, description};
        this->module.NewNode(*data);
    }

    /**나이 범위 검색 컨트롤러 */
    Leap *SearchByAge(int min, int max)
    {
        this->searchPassTemp.clear();
        this->searchIndexTemp.clear();
        return this->module.SearchByAge(min, max, this->startIndex, searchPassTemp);
    }

    /**데이터 삭제 컨트롤러*/
    void DeleteData(USERDATAINDEX &pIndex, USERDATA &pData)
    {
        this->module.DeleteData(*pIndex.PerentLeap, pIndex, pData, this->searchPassTemp);
        return;
    }

    /**모든 키 출력 컨트롤러 */
    void PrintAllKey()
    {
        this->module.PrintAllKey();
    }

    /**모든 데이터 출력 컨트롤러 */
    void PrintAllData()
    {
        this->module.PrintAllData();
    }

    /**상세 나이 검색 함수*/
    USERDATAINDEX *getUserIndexFromTemp(int param)
    {
        if (param <= this->searchIndexTemp.size())
        {
            return this->searchIndexTemp[param - 1];
        }
        else
            return nullptr;
    }

    /**나이 범위 검색 시작 인덱스 찾아줌 */
    USERDATAINDEX *getStartIndex(Leap &pLeap)
    {
        return pLeap.getUserData()[startIndex];
    }

    /**나이 검색 반복자 */
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

    /**데이터 삽입 */
    void DataInsert()
    {
        int age;
        string name, phone, description;
        char flag;
        cout << "추가할 주소의 이름을 입력해주세요" << endl;
        cin >> name;
        cout << "추가할 주소의 나이를 입력해주세요" << endl;
        cin >> age;
        cout << "추가할 주소의 휴대 전화 번호를 입력해주세요" << endl;
        cin >> phone;
        cout << "주소에 메모를 추가하시겠습니까? Y/N" << endl;
        cin >> flag;
        if (flag == 'Y' || flag == 'y')
        {
            cout << "추가할 설명을 입력해주십시오" << endl;
            cin >> description;
        }
        this->control.NewNode(age, name, phone, description);
    }

    /**나이 범위 검색*/
    void SearchByAge()
    {
        int min = 3, max = 8;
        // cin >> min, max;
        Leap *startLeap = this->control.SearchByAge(min, max);
        if (startLeap == nullptr)
        {
            cout << "검색 결과 없음" << endl;
            return;
        }
        else
        {
            USERDATAINDEX *curData = this->control.getStartIndex(*startLeap);
            unsigned int count = 0;
            while (curData->key <= max)
            {
                ++count;
                cout << '[' << count << "] " << "나이 : " << curData->key << "\t개수 : " << curData->userdata.size() << "개" << endl;
                curData = control.ageIterator(startLeap);
            }
            cout << "가져올 정보의 정확한 나이를 입력하세요" << endl;
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
                cout << '[' << count << "] " << "나이 : " << element->age << " 이름 : " << element->name << " 휴대전화 : " << element->phone << endl;
            }
            cout << "가져올 정보의 번호를 입력하세요" << endl;
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
        cout << "나이 : " << pData.age << " 이름 : " << pData.name << " 휴대전화 : " << pData.phone << endl;
        if (pData.description.size() > 0)
        {
            cout << "부가 설명 : " << pData.description << endl;
        }
        cout << "[1] 수정\t[2] 삭제\t[3] 넘어가기" << endl;
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

    /**모든 데이터 출력 */
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