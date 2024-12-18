#include "modul.h"
class Control
{
private:
    Module<unsigned int> &module;
    Module<string> &NameModule;

    int startIndex = 0;

    vector<Node<string> *> searchNamePassTemp;
    vector<Node<unsigned int> *> searchPassTemp;

    /**���� ���� �˻� temp �� �����̳� */
    vector<USERDATAINDEX<unsigned int> *> searchIndexTemp;

public:
    Control(/* args */);
    ~Control();

    /**�ű� ������ ���� ��Ʈ�ѷ� */
    void NewNode(unsigned int age, string &name, string &phone, string &description);

    void NewNode(USERDATA &pData);

    /**���� ���� �˻� ��Ʈ�ѷ� */
    Leap<unsigned int> *SearchByAge(int min, int max);

    Leap<string> *SearchByName(string input);

    /**������ ���� ��Ʈ�ѷ�*/

    void DeleteData(INDEXINFO &pData);

    void UpdateData(unsigned int age, string &name, string &phone, string &description, INDEXINFO &pIndex, USERDATA &pData);

    /**��� Ű ��� ��Ʈ�ѷ� */
    void PrintAllKey();

    /**��� ������ ��� ��Ʈ�ѷ� */
    void PrintAllData();

    /**�� ���� �˻� �Լ�*/
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

    /**���� ���� �˻� ���� �ε��� ã���� */
    template <typename T>
    USERDATAINDEX<T> *getStartIndex(Leap<T> &pLeap)
    {
        return pLeap.getUserData()[startIndex];
    }

    /**���� �˻� �ݺ��� */
    template <typename T>
    USERDATAINDEX<T> *ageIterator(Leap<T> *&pLeap)
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
