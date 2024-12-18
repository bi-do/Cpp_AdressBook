#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;
template <typename KeyType>
class Leap;

struct INDEXINFO;

/**���� ������ */
typedef struct USERDATA
{
    unsigned int age;
    string name;
    string phone;
    string description;
    ~USERDATA()
    {
        cout << "���� ������ ����. age : " << age << " name : " << name << " phone : " << phone << endl;
    }

} USERDATA;

/**�� Ʈ�� �� �ߺ��� ���� �����̳� ( �ߺ��� Ű���� �����͵� ������ �ֵ��� �� )*/
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
    /**���� ������ ���� */
    void pushData(INDEXINFO &pData);
};

/**�߾� ���� �ε��� */
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
        cout << "������ �ε��� ����" << endl;
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

/**��� Ŭ���� */
template <typename KeyType>
class Node
{
private:
    bool isLeap;
    vector<Node *> child;
    vector<KeyType> keys;
    Node *parent = nullptr;

    /**�θ� ���� �ڽ��� �ε��� */
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

    /**�ڽ� ������ �����ִ� �ڱ� �θ� ���� �ε��� ���� */
    void initializeChildIndex();

    /**�ڱ� �ڽĵ��� �θ� �ڽ����� ���� */
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

    /**�����̳ʿ� ������ ���� */
    void NewKey(KeyType Keyparam, INDEXINFO &pParam);

    /**������ �������� ����� ���� */
    void initializeData();

    vector<USERDATAINDEX *> &getUserData();
    static bool indexCompareByKey(USERDATAINDEX *a, USERDATAINDEX *b);
    Leap *getRightSibling() override;
    Leap *getLeftSibling() override;

    /**�ش� ��������� ù��° �����Ͱ� �ε��� ���� Ű�� �����ϴ��� üũ �� ��ȯ */
    Node *getInternalIndexNode();

    /**�Ķ���� �ٷ� �������� �����ִ� �����̳ʸ� ����� ( ������ ��ȯ ) */
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

    /**������ �ߺ� ���� ������ ���� ��� ������ Ŭ����*/
    void ClearAllLeapData();

    /**���ο� ������ ���� */
    void NewNode(KeyType keyparam, INDEXINFO &pParam);

    /**Ű�� �߽����� �˻� */
    Leap *SearchByKey(KeyType min, KeyType max, int &dataIndex, vector<Node *> &passTemp);

    /**��� ���� */
    void DeleteData(Leap &pLeap, USERDATAINDEX &pIndex, USERDATA &pData, vector<Node *> &passTemp);

    /**�ε��� ������ */
    void IndexReconciliation(Leap &pLeap, USERDATAINDEX &pIndex, USERDATA &pData, vector<Node *> &passTemp);

    /**��� Ű ��� */
    void PrintAllKey();

    /**��� ������ ��� */
    void PrintAllData();
};

#include "modul.tpp"