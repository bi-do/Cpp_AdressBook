#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;
template <typename KeyType>
class Leap;

struct INDEXINFO;

/**실제 데이터 */
typedef struct USERDATA
{
    unsigned int age;
    string name;
    string phone;
    string description;
    ~USERDATA()
    {
        cout << "실제 데이터 삭제. age : " << age << " name : " << name << " phone : " << phone << endl;
    }

} USERDATA;

/**각 트리 별 중복값 저장 컨테이너 ( 중복된 키값의 데이터도 담을수 있도록 함 )*/
template <typename T>
class USERDATAINDEX
{
private:
    vector<INDEXINFO *> userdata;
    Leap<T> *PerentLeap = nullptr;
    T key;

public:
    USERDATAINDEX(T key);
    ~USERDATAINDEX();
    void setKey(T key);
    void setParent(Leap<T> &pLeap);
    vector<INDEXINFO *> &getUserAdt();
    T &getKey();
    Leap<T> *getParent();
    /**실제 데이터 삽입 */
    void pushData(INDEXINFO &pData);
};

/**중앙 집권 인덱스 */
typedef struct INDEXINFO
{
    USERDATA *user;
    USERDATAINDEX<unsigned int> *ageIndex;
    USERDATAINDEX<string> *nameIndex;
    INDEXINFO(USERDATA &pData)
    {
        this->user = &pData;
    }
    ~INDEXINFO()
    {
        cout << "데이터 인덱스 삭제" << endl;
        delete user;
    }
    void setIndexParent(USERDATAINDEX<unsigned int> &pParent)
    {
        ageIndex = &pParent;
    }
    void setIndexParent(USERDATAINDEX<string> &pParent)
    {
        nameIndex = &pParent;
    }
} INDEXINFO;

/**노드 클래스 */
template <typename KeyType>
class Node
{
private:
    bool isLeap;
    vector<Node *> child;
    vector<KeyType> keys;
    Node *parent = nullptr;

    /**부모에 대한 자신의 인덱스 */
    int indexByParent;

public:
    explicit Node() {};
    Node(KeyType key, USERDATA &pParam);
    virtual ~Node();
    void serParent(Node *pParam);
    Node *getParent();
    vector<Node *> &getChilds();
    vector<KeyType> &getKeys();
    int getIndexByParent();
    void pushChild(Node &pParam);

    /**자식 노드들이 갖고있는 자기 부모에 대한 인덱스 갱신 */
    void initializeChildIndex();

    /**자기 자식들의 부모를 자신으로 세팅 */
    void initializeParent();

    void pushKey(KeyType param);

    bool checkLeap();

    static bool childCompareByKey(Node *a, Node *b);

    void changeLeap();

    virtual Node *getRightSibling();
    virtual Node *getLeftSibling();
};

template <typename KeyType>
class Internal : public Node<KeyType>
{
public:
    explicit Internal() {};
    Internal(USERDATA &pParam) : Node<KeyType>(pParam) {
                                 };
    ~Internal()
    {
    }
};

template <typename KeyType>
class Leap : public Node<KeyType>
{
    vector<USERDATAINDEX<KeyType> *> userdata;
    Leap *next = nullptr;
    Leap *prev = nullptr;

public:
    using Node = Node<KeyType>;
    using USERDATAINDEX = USERDATAINDEX<KeyType>;

    Leap();
    Leap(KeyType key, USERDATA &pParam);
    ~Leap();

    void setPrev(Leap *pParam);
    void setNext(Leap *pParam);
    Leap *getPrev();
    Leap *getNext();
    void pushData(INDEXINFO &pParam, int index);

    /**컨테이너에 데이터 삽입 */
    void NewKey(KeyType Keyparam, INDEXINFO &pParam);

    /**데이터 컨테이터 양방향 연결 */
    void initializeData();

    vector<USERDATAINDEX *> &getUserData();
    static bool indexCompareByKey(USERDATAINDEX *a, USERDATAINDEX *b);
    Leap *getRightSibling() override;
    Leap *getLeftSibling() override;

    /**해당 리프노드의 첫번째 데이터가 인덱스 내에 키로 존재하는지 체크 및 반환 */
    Node *getInternalIndexNode();

    /**파라미터 바로 다음값을 갖고있는 컨테이너를 뱉어줌 ( 석세서 반환 ) */
    USERDATAINDEX &getSuccesor(Leap &pNode, KeyType Param);
};

template <typename KeyType>
class Module
{
private:
    Node<KeyType> *rootNode = nullptr;
    Leap<KeyType> *firstStart = nullptr;
    int maxChild = 3;
    int maxKey = maxChild - 1;
    int minChild = (maxChild + 1) / 2;
    int minKey = minChild - 1;

public:
    using Node = Node<KeyType>;
    using Leap = Leap<KeyType>;
    using USERDATAINDEX = USERDATAINDEX<KeyType>;
    Module();
    ~Module();

    /**데이터 중복 삭제 방지용 리프 노드 데이터 클리어*/
    void ClearAllLeapData();

    /**새로운 데이터 삽입 */
    void NewNode(KeyType keyparam, INDEXINFO &pParam);

    /**키를 중심으로 검색 */
    Leap *SearchByKey(KeyType min, KeyType max, int &dataIndex, vector<Node *> &passTemp);

    /**노드 삭제 */
    void DeleteData(Leap &pLeap, USERDATAINDEX &pIndex, USERDATA &pData, vector<Node *> &passTemp);

    /**인덱싱 재조정 */
    void IndexReconciliation(Leap &pLeap, USERDATAINDEX &pIndex, USERDATA &pData, vector<Node *> &passTemp);

    /**모든 키 출력 */
    void PrintAllKey();

    /**모든 데이터 출력 */
    void PrintAllData();
};

#include "modul.tpp"