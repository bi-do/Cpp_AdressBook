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
    void SearchByName()
    {
        using USERDATAINDEX = USERDATAINDEX<string>;
        string input;

        cout << "검색할 주소의 이름을 입력해주세요" << endl;
        input = "kim";
        // cin >> input;
        Leap<string> *startLeap = this->control.SearchByName(input);
        if (startLeap == nullptr)
        {
            cout << "검색 결과 없음" << endl;
            return;
        }
        else
        {
            USERDATAINDEX *curData = this->control.getStartIndex(*startLeap);
            unsigned int count = 0;
            for (INDEXINFO *element : curData->getUserAdt())
            {
                count++;
                cout << '[' << count << "] " << "이름 : " << curData->getKey() << "\t나이 : " << element->user->age << "\t휴대전화 : " << element->user->phone << endl;
            }
            cout << "가져올 정보의 번호를 입력하세요" << endl;
            cin >> count;
            if (count >= curData->getUserAdt().size())
            {
                count = curData->getUserAdt().size();
            }
            USERDATA &searchData = *curData->getUserAdt()[count - 1]->user;
            this->DataUpdateUI(*curData->getUserAdt()[count - 1], searchData);
        }
    }
    /**나이 범위 검색*/
    void SearchByAge()
    {
        using USERDATAINDEX = USERDATAINDEX<unsigned int>;
        cout << "검색할 나이의 범위를 입력해주세요" << endl;
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
            cout << "검색 결과 없음" << endl;
            return;
        }
        else
        {
            USERDATAINDEX *curData = this->control.getStartIndex(*startLeap);
            unsigned int count = 0;
            while (curData != nullptr && curData->getKey() <= max)
            {
                ++count;
                cout << '[' << count << "] " << "나이 : " << curData->getKey() << "\t개수 : " << curData->getUserAdt().size() << "개" << endl;
                curData = control.ageIterator(min, startLeap);
            }

            cout << "가져올 정보의 번호를 입력하세요" << endl;
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
                cout << '[' << count << "] " << "나이 : " << element->user->age << " 이름 : " << element->user->name << " 휴대전화 : " << element->user->phone << endl;
            }
            cout << "가져올 정보의 번호를 입력하세요" << endl;
            cin >> input;
            if (input > count)
            {
                input = count;
            }
            USERDATA &searchData = *curData->getUserAdt()[input - 1]->user;
            this->DataUpdateUI(*curData->getUserAdt()[input - 1], searchData);
        }
    }

    /**데이터 업데이트 여부 확인*/
    void DataUpdateUI(INDEXINFO &pIndex, USERDATA &pData)
    {
        unsigned int count = 0;
        cout << "나이 : " << pData.age << " 이름 : " << pData.name << " 휴대전화 : " << pData.phone << endl;
        if (pData.description.size() > 0)
        {
            cout << "부가 설명 : " << pData.description << endl;
        }
        cout << "[1] 수정\t[2] 삭제\t[3] 넘어가기" << endl;
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

    /**데이터 수정 */

    void DataCorrectionUI(INDEXINFO &pIndex, USERDATA &pData)
    {
        int age;
        string name, phone, description;
        char flag;
        cout << "수정할 이름을 입력해주세요" << endl;
        cin >> name;
        cout << "수정할 나이를 입력해주세요" << endl;
        cin >> age;
        cout << "수정할 휴대 전화 번호를 입력해주세요" << endl;
        cin >> phone;
        cout << "주소에 메모를 수정하시겠습니까? Y/N" << endl;
        cin >> flag;
        if (flag == 'Y' || flag == 'y')
        {
            cout << "수정할 설명을 입력해주십시오" << endl;
            cin >> description;
        }
        this->control.UpdateData(age, name, phone, description, pIndex, pData);
    }

    /**모든 데이터 출력 */
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
