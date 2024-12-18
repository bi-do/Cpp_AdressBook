#include "modul.h"
class Control
{
private:
    Module<unsigned int> &module;
    Module<string> &NameModule;

    int startIndex = 0;

    vector<Node<string> *> searchNamePassTemp;
    vector<Node<unsigned int> *> searchPassTemp;

    /**나이 범위 검색 temp 값 컨테이너 */
    vector<USERDATAINDEX<unsigned int> *> searchIndexTemp;

public:
    Control(/* args */);
    ~Control();

    /**신규 데이터 삽입 컨트롤러 */
    void NewNode(unsigned int age, string &name, string &phone, string &description);

    void NewNode(USERDATA &pData);

    /**나이 범위 검색 컨트롤러 */
    Leap<unsigned int> *SearchByAge(int min, int max);

    Leap<string> *SearchByName(string input);

    /**데이터 삭제 컨트롤러*/

    void DeleteData(INDEXINFO &pData);

    void UpdateData(unsigned int age, string &name, string &phone, string &description, INDEXINFO &pIndex, USERDATA &pData);

    /**모든 키 출력 컨트롤러 */
    void PrintAllKey();

    /**모든 데이터 출력 컨트롤러 */
    void PrintAllData();

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
