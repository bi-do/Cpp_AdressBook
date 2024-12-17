#include "modul.h"
class Control
{
private:
    Module<unsigned int> &module;
    Module<string> &NameModule;

    int startIndex = 0;
    vector<Node<string> *> searchNamePassTemp;
    vector<Node<unsigned int> *> searchPassTemp;
    vector<USERDATAINDEX<unsigned int> *> searchIndexTemp;

public:
    Control(/* args */) : module(*new Module<unsigned int>()), NameModule(*new Module<string>()) {};

    ~Control()
    {
        cout << "컨트롤러 해제" << endl;
        delete &this->module;
        NameModule.ClearAllLeapData();
        delete &this->NameModule;
    };

    /**신규 데이터 삽입 컨트롤러 */
    void NewNode(unsigned int age, string &name, string &phone, string &description)
    {
        USERDATA *data = new USERDATA{age, name, phone, description};
        INDEXINFO *newIndex = new INDEXINFO(*data);
        this->module.NewNode(age, *newIndex);
        this->NameModule.NewNode(name, *newIndex);
    }

    /**나이 범위 검색 컨트롤러 */
    Leap<unsigned int> *SearchByAge(int min, int max)
    {
        this->searchPassTemp.clear();
        this->searchIndexTemp.clear();
        return this->module.SearchByKey(min, max, this->startIndex, searchPassTemp);
    }

    Leap<string> *SearchByName(string input)
    {
        this->searchNamePassTemp.clear();
        this->startIndex = 0;
        return this->NameModule.SearchByKey(input, input, this->startIndex, this->searchNamePassTemp);
    }

    /**데이터 삭제 컨트롤러*/

    void DeleteData(INDEXINFO &pData)
    {
        this->module.DeleteData(*pData.ageIndex->getParent(), pData, *pData.user, this->searchPassTemp);
        this->NameModule.DeleteData(*pData.nameIndex->getParent(), pData, *pData.user, this->searchNamePassTemp);
        delete &pData;
        return;
    }

    void UpdateData(unsigned int age, string &name, string &phone, string &description, INDEXINFO &pIndex, USERDATA &pData)
    {
        if (age != pData.age)
        {
            this->module.DeleteData(*pIndex.ageIndex->getParent(), pIndex, pData, this->searchPassTemp);
            USERDATA *data = new USERDATA{age, name, phone, description};
            // this->module.NewNode(age, *data);
        }
        else
        {
            pData.name = name;
            pData.description = description;
            pData.phone = phone;
        }
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
    template <typename T>
    USERDATAINDEX<T> *getUserIndexFromTemp(T type, int param)
    {
        if (param <= this->searchIndexTemp.size())
        {
            return this->searchIndexTemp[param - 1];
        }
        else
            return nullptr;
    }

    /**나이 범위 검색 시작 인덱스 찾아줌 */
    template <typename T>
    USERDATAINDEX<T> *getStartIndex(Leap<T> &pLeap)
    {
        return pLeap.getUserData()[startIndex];
    }

    /**나이 검색 반복자 */
    template <typename T>
    USERDATAINDEX<T> *ageIterator(T type, Leap<T> *&pLeap)
    {
        this->searchIndexTemp.push_back(pLeap->getUserData()[startIndex]);
        this->startIndex++;
        if (this->startIndex == pLeap->getKeys().size())
        {
            this->startIndex = 0;
            pLeap = pLeap->getNext();
            if (pLeap == nullptr)
            {
                return nullptr;
            }
        }
        return pLeap->getUserData()[this->startIndex];
    }
};
