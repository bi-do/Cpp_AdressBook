#include "control.h"

Control::Control(/* args */) : module(*new Module<unsigned int>()), NameModule(*new Module<string>()) {};
Control::~Control()
{
    cout << "컨트롤러 해제" << endl;
    delete &this->module;
    NameModule.ClearAllLeapData();
    delete &this->NameModule;
};

/**신규 데이터 삽입 컨트롤러 */
void Control::NewNode(unsigned int age, string &name, string &phone, string &description)
{
    USERDATA *data = new USERDATA{age, name, phone, description};
    INDEXINFO *newIndex = new INDEXINFO(*data);
    this->module.NewNode(age, *newIndex);
    this->NameModule.NewNode(name, *newIndex);
}

void Control::NewNode(USERDATA &pData)
{
    INDEXINFO *newIndex = new INDEXINFO(pData);
    this->module.NewNode(pData.age, *newIndex);
    this->NameModule.NewNode(pData.name, *newIndex);
}

/**나이 범위 검색 컨트롤러 */
Leap<unsigned int> *Control::SearchByAge(int min, int max)
{
    this->searchPassTemp.clear();
    this->searchIndexTemp.clear();
    this->searchNamePassTemp.clear();
    this->startIndex = 0;
    return this->module.SearchByKey(min, max, this->startIndex, searchPassTemp);
}

Leap<string> *Control::SearchByName(string input)
{
    this->searchPassTemp.clear();
    this->searchIndexTemp.clear();
    this->searchNamePassTemp.clear();
    this->startIndex = 0;
    return this->NameModule.SearchByKey(input, input, this->startIndex, this->searchNamePassTemp);
}

/**데이터 삭제 컨트롤러*/

void Control::DeleteData(INDEXINFO &pData)
{
    this->module.DeleteData(*pData.ageIndex->getParent(), *pData.ageIndex, *pData.user, this->searchPassTemp);
    this->NameModule.DeleteData(*pData.nameIndex->getParent(), *pData.nameIndex, *pData.user, this->searchNamePassTemp);
    delete &pData;
    return;
}

void Control::UpdateData(unsigned int age, string &name, string &phone, string &description, INDEXINFO &pIndex, USERDATA &pData)
{
    if (age != pData.age)
    {
        this->module.DeleteData(*pIndex.ageIndex->getParent(), *pIndex.ageIndex, pData, this->searchPassTemp);
        pData.age = age;
        module.NewNode(age, pIndex);
    }
    if (name != pData.name)
    {
        this->NameModule.DeleteData(*pIndex.nameIndex->getParent(), *pIndex.nameIndex, pData, this->searchNamePassTemp);
        pData.name = name;
        NameModule.NewNode(name, pIndex);
    }
    pData.phone = phone;
    pData.description = description;
}

/**모든 키 출력 컨트롤러 */
void Control::PrintAllKey()
{
    this->module.PrintAllKey();
}

/**모든 데이터 출력 컨트롤러 */
void Control::PrintAllData()
{
    this->module.PrintAllData();
}

