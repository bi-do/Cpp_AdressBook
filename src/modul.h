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

} USERDATA;

template <typename T>
class USERDATAINDEX
{
private:
    vector<INDEXINFO *> userdata;
    Leap<T> *PerentLeap = nullptr;
    T key;

public:
    USERDATAINDEX(T key)
    {
        this->key = key;
    }
    ~USERDATAINDEX()
    {
        for (INDEXINFO *element : userdata)
        {
            delete element;
        }
        // cout << key << "������ ����" << endl;
        this->userdata.clear();
    }

    void setKey(T key)
    {
        this->key = key;
    }

    void setParent(Leap<T> &pLeap)
    {
        this->PerentLeap = &pLeap;
    }

    vector<INDEXINFO *> &getUserAdt()
    {
        return this->userdata;
    }

    T &getKey()
    {
        return this->key;
    }

    Leap<T> *getParent()
    {
        return this->PerentLeap;
    }

    void pushData(INDEXINFO &pData)
    {
        pData.setIndexParent(*this);
        userdata.push_back(&pData);
    };
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

/**�� Ʈ�� �� �ߺ��� ���� �����̳� ( �ߺ��� Ű���� �����͵� ������ �ֵ��� �� )*/

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

    Node(KeyType key, USERDATA &pParam)
    {
        this->keys.push_back(key);
    };
    virtual ~Node()
    {
        for (Node *element : child)
        {
            delete element;
        }
        if (this->isLeap != true)
        {
            for (KeyType element : keys)
            {
                cout << element << '\t';
            }
            cout << " ��� ����" << endl;
        }
        child.clear();
        keys.clear();
    }

    void serParent(Node *pParam)
    {
        this->parent = pParam;
    }

    Node *getParent()
    {
        return this->parent;
    }
    vector<Node *> &getChilds()
    {
        return this->child;
    }

    vector<KeyType> &getKeys()
    {
        return this->keys;
    }

    int getIndexByParent()
    {
        return this->indexByParent;
    }

    void pushChild(Node &pParam)
    {
        this->child.push_back(&pParam);
        sort(this->child.begin(), this->child.end(), childCompareByKey);
        initializeChildIndex();
    }

    /**�ڽ� ������ �����ִ� �ڱ� �θ� ���� �ε��� ���� */
    void initializeChildIndex()
    {
        int index = this->child.size();
        for (int i = 0; i < index; i++)
        {
            child[i]->indexByParent = i;
        }
    }

    /**�ڱ� �ڽĵ��� �θ� �ڽ����� ���� */
    void initializeParent()
    {
        for (Node *element : this->child)
        {
            element->serParent(this);
        }
    }

    void pushKey(KeyType param)
    {
        this->keys.push_back(param);
        sort(this->keys.begin(), this->keys.end());
    }

    bool checkLeap()
    {
        return this->isLeap;
    }

    static bool childCompareByKey(Node *a, Node *b)
    {
        if (a->keys.size() == 0)
        {
            return true;
        }
        else if (b->keys.size() == 0)
        {
            return false;
        }
        else
            return a->getKeys().back() < b->getKeys().back();
    }

    void changeLeap()
    {
        this->isLeap = true;
    }

    virtual Node *getRightSibling()
    {
        if (indexByParent >= parent->getChilds().size() - 1)
        {
            return nullptr;
        }
        else
            return parent->getChilds()[indexByParent + 1];
    }

    virtual Node *getLeftSibling()
    {
        if (indexByParent == 0)
        {
            return nullptr;
        }
        else
            return parent->getChilds()[indexByParent - 1];
    }
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
    Leap()
    {
        this->changeLeap();
    };

    Leap(USERDATA &pParam) : Node(pParam)
    {
        this->changeLeap();
    }
    ~Leap()
    {
        for (USERDATAINDEX *element : userdata)
        {
            cout << element->getKey() << '\t';
            delete element;
        }
        cout << "���� ��� ����" << endl;
        this->userdata.clear();
    }
    void setPrev(Leap *pParam)
    {
        this->prev = pParam;
    }
    void setNext(Leap *pParam)
    {
        this->next = pParam;
    }
    Leap *getPrev()
    {
        return this->prev;
    }
    Leap *getNext()
    {
        return this->next;
    }

    void pushData(INDEXINFO &pParam, int index)
    {
        USERDATAINDEX *tmpIndex = this->userdata[index];
        tmpIndex->getUserAdt().push_back(&pParam);
    }

    void NewKey(KeyType Keyparam, INDEXINFO &pParam)
    {
        this->pushKey(Keyparam);
        USERDATAINDEX *newDataArr = new USERDATAINDEX(Keyparam);
        newDataArr->pushData(pParam);
        newDataArr->setKey(Keyparam);
        newDataArr->setParent(*this);
        userdata.push_back(newDataArr);
        sort(userdata.begin(), userdata.end(), indexCompareByKey);
    }

    void initializeData()
    {
        for (USERDATAINDEX *element : this->userdata)
        {
            element->setParent(*this);
        }
    }
    vector<USERDATAINDEX *> &getUserData()
    {
        return this->userdata;
    }

    static bool indexCompareByKey(USERDATAINDEX *a, USERDATAINDEX *b)
    {
        return a->getKey() < b->getKey();
    }

    Leap *getRightSibling() override
    {
        if (this->getIndexByParent() >= this->getParent()->getChilds().size() - 1)
        {
            return nullptr;
        }
        else
            return static_cast<Leap *>(this->getParent()->getChilds()[this->getIndexByParent() + 1]);
    }

    Leap *getLeftSibling() override
    {
        if (this->getIndexByParent() == 0)
        {
            return nullptr;
        }
        else
            return static_cast<Leap *>(this->getParent()->getChilds()[this->getIndexByParent() - 1]);
    }
    Node *getInternalIndexNode()
    {
        KeyType key = this->getKeys().front();

        Node *curNode = this->getParent();
        while (curNode != nullptr)
        {
            for (KeyType element : curNode.getKeys())
            {
                if (element == key)
                {
                    return curNode;
                }
            }
            curNode = curNode->getParent();
        }
        cout << "�ε��� ����" << endl;
        return nullptr;
    }

    USERDATAINDEX &getSuccesor(Leap &pNode, int Param)
    {
        Leap *curLeap = &pNode;
        USERDATAINDEX *succesor = curLeap->getUserData().front();
        int index = 0;
        while (succesor->getKey() <= Param)
        {
            succesor = curLeap->getUserData()[index];
            index++;
            if (curLeap->getKeys().size() == index)
            {
                curLeap = curLeap->getNext();
                index = 0;
            }
        }
        return *succesor;
    }
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
    Module()
    {
    }
    ~Module()
    {
        delete rootNode;
    }

    void ClearAllLeapData()
    {
        Leap *curLeap = this->firstStart;
        while (curLeap != nullptr)
        {
            for (USERDATAINDEX *element : curLeap->getUserData())
            {
                element->getUserAdt().clear();
            }
            curLeap = curLeap->getNext();
        }
    }

    /**���ο� ������ ���� */
    void NewNode(KeyType keyparam, INDEXINFO &pParam)
    {
        KeyType key = keyparam;
        /**������ ó�� ���� �� */
        if (rootNode == nullptr)
        {
            Node &newNode = *new Internal<KeyType>();
            rootNode = &newNode;
            Leap &dummy = *new Leap();
            Leap &newLeap = *new Leap();

            this->firstStart = &dummy;
            newLeap.NewKey(keyparam, pParam);
            newNode.pushKey(keyparam);

            dummy.setNext(&newLeap);
            newLeap.setPrev(&dummy);
            newNode.pushChild(dummy);
            newNode.pushChild(newLeap);
            newNode.initializeParent();
            return;
        }
        else
        {
            Node *curNode = rootNode;
            Node *parent = curNode;
            int index;

            while (parent->checkLeap() != true)
            {
                index = 0;
                if (curNode->checkLeap() != true)
                {
                    for (KeyType element : curNode->getKeys())
                    {
                        if (element > key)
                        {
                            break;
                        }
                        else
                            index++;
                    }
                    parent = curNode;
                    curNode = curNode->getChilds()[index];
                }
                else
                {
                    Leap *curLeap = static_cast<Leap *>(curNode);
                    for (KeyType element : curNode->getKeys())
                    {
                        if (element == key)
                        {
                            curLeap->pushData(pParam, index);
                            cout << "���� �� ������ ����" << endl;
                            return;
                        }
                        else
                            index++;
                    }
                    curLeap->NewKey(keyparam, pParam);
                    /**���� ����� Ű ���� �ִ� Ű ���� �Ѿ��ٸ� */
                    while (curNode->getKeys().size() > maxKey)
                    {
                        /**���� ��尡 ��Ʈ����� */
                        if (curNode == rootNode)
                        {
                            parent = new Internal<KeyType>();
                            rootNode = parent;
                            curNode->serParent(parent);
                            parent->pushChild(*curNode);
                        }
                        int middleIndex = ((curNode->getKeys().size()) / 2);
                        parent->pushKey(curNode->getKeys()[middleIndex]);
                        Node *newNode;
                        /**���� ��尡 ��������� */
                        if (curNode->checkLeap() == true)
                        {
                            newNode = new Leap();
                            Leap *newLeap = static_cast<Leap *>(newNode);
                            newLeap->getUserData().insert(newLeap->getUserData().end(), curLeap->getUserData().begin() + middleIndex, curLeap->getUserData().end());
                            newLeap->initializeData();
                            curLeap->getUserData().erase(curLeap->getUserData().begin() + middleIndex, curLeap->getUserData().end());
                            newNode->getKeys().insert(newNode->getKeys().end(), curNode->getKeys().begin() + middleIndex, curNode->getKeys().end());
                            curLeap->setNext(newLeap);
                            newLeap->setPrev(curLeap);
                        }
                        else
                        {
                            newNode = new Internal<KeyType>();
                            newNode->getKeys().insert(newNode->getKeys().end(), curNode->getKeys().begin() + middleIndex + 1, curNode->getKeys().end());
                            newNode->getChilds().insert(newNode->getChilds().end(), curNode->getChilds().begin() + middleIndex + 1, curNode->getChilds().end());
                            newNode->initializeParent();
                            curNode->getChilds().erase(curNode->getChilds().begin() + middleIndex + 1, curNode->getChilds().end());
                            newNode->initializeChildIndex();
                        }
                        newNode->serParent(parent);
                        parent->pushChild(*newNode);
                        parent->initializeChildIndex();
                        parent->initializeParent();
                        curNode->getKeys().erase(curNode->getKeys().begin() + middleIndex, curNode->getKeys().end());
                        curNode = parent;
                        parent = curNode->getParent();
                    }
                    cout << "������ ���� �Ϸ�" << endl;
                    return;
                }
            }
        }
    }
    Leap *SearchByKey(KeyType min, KeyType max, int &dataIndex, vector<Node *> &passTemp)
    {
        Node *curNode = this->rootNode;
        /**���� ��尡 ��������϶����� */
        while (curNode->checkLeap() != true)
        {
            int index = 0;
            for (KeyType element : curNode->getKeys())
            {
                if (min < element)
                {
                    break;
                }
                else
                    index++;
            }
            passTemp.push_back(curNode);
            curNode = curNode->getChilds()[index];
        }
        int index = 0;
        Leap *curLeap = static_cast<Leap *>(curNode);
        while (curLeap == this->firstStart || curLeap->getUserData()[index]->getKey() <= max)
        {
            if (curLeap->getUserData().size() > 0 && curLeap->getUserData()[index]->getKey() >= min)
            {
                dataIndex = index;
                return curLeap;
            }
            else
                index++;
            if (index >= curLeap->getKeys().size())
            {
                curLeap = curLeap->getNext();
                index = 0;
            }
        }
        return nullptr;
    }

    /**��� ���� */
    void DeleteData(Leap &pLeap, INDEXINFO &pIndex, USERDATA &pData, vector<Node *> &passTemp)
    {
        USERDATAINDEX *temp;
        if (is_same<KeyType, unsigned int>::value)
        {
            temp = pIndex.ageIndex;
        }
        else
            temp = pIndex.nameIndex;
        int index = 0;
        KeyType key = pIndex.getKey();
        for (INDEXINFO *element : pIndex.getUserAdt())
        {
            if (&pData == element->user)
            {
                temp.getUserAdt().erase(pIndex.getUserAdt().begin() + index);
                break;
            }
            else
                index++;
        }
        this->IndexReconciliation(pLeap, *temp, pData, passTemp);
    }

    /**�ε��� ������ */
    void IndexReconciliation(Leap &pLeap, USERDATAINDEX &pIndex, USERDATA &pData, vector<Node *> &passTemp)
    {
        /**���� ������ �����Ͱ� �ش�Ǵ� Ű�� ����ִ� ��� */
        if (pIndex.getUserAdt().size() == 0)
        {
            /**�ε��� ��ȯ */
            if (&pLeap != firstStart && &pIndex == pLeap.getUserData()[0] && (pLeap.getNext() != nullptr || pLeap.getUserData().size() > 1))
            {
                for (Node *element : passTemp)
                {
                    bool flag = false;
                    for (KeyType &elementKey : element->getKeys())
                    {
                        if (elementKey == key)
                        {
                            elementKey = pLeap.getSuccesor(pLeap, key).getKey();
                            flag = true;
                            break;
                        }
                    }
                    if (flag == true)
                    {
                        break;
                    }
                }
            }
            int dataIndex = 0;
            for (KeyType element : pLeap.getKeys())
            {
                if (key == element)
                {
                    pLeap.getUserData().erase(pLeap.getUserData().begin() + dataIndex);
                    pLeap.getKeys().erase(pLeap.getKeys().begin() + dataIndex);
                    delete &pIndex;
                    break;
                }
                else
                    dataIndex++;
            }
            Node *curNode = &pLeap;
            Node *curParent = pLeap.getParent();
            /**Ű ���� �� �ش� ��������� Ű ���� �ּ� Ű ������ ���� ��� */
            while (curNode->getKeys().size() < this->minKey)
            {
                /**���� ��尡 ��Ʈ����� ��� */
                if (curNode == this->rootNode)
                {
                    if (curNode->getKeys().size() == 0)
                    {
                        curNode = rootNode->getChilds().front();
                        rootNode->getChilds().clear();
                        delete rootNode;
                        rootNode = curNode;
                        rootNode->serParent(nullptr);
                        /**��� �����Ͱ� �����Ǿ��� �� */
                        if (curNode->checkLeap() == true)
                        {
                            if (curNode->getKeys().size() == 0)
                            {
                                delete rootNode;
                                this->firstStart = nullptr;
                                this->rootNode = nullptr;
                                return;
                            }
                            else
                            {
                                Leap &dummy = *new Leap();
                                rootNode = new Internal<KeyType>();
                                rootNode->pushKey(curNode->getKeys().front());
                                rootNode->pushChild(dummy);
                                rootNode->pushChild(*curNode);
                                rootNode->initializeParent();
                            }
                        }
                    }
                    else
                        break;
                }
                /**���� ��尡 ��Ʈ��尡 �ƴ� ��� */
                else
                {
                    curParent = curNode->getParent();
                    /**���� ������ Ű�� ����� ��� */
                    if (curNode->getLeftSibling() != nullptr && curNode->getLeftSibling()->getKeys().size() > this->minKey)
                    {
                        Node *leftSibling = curNode->getLeftSibling();
                        if (curNode->checkLeap() == true)
                        {
                            Leap *leftSibling = pLeap.getPrev();
                            pLeap.getUserData().insert(pLeap.getUserData().begin(), leftSibling->getUserData().back());
                            pLeap.getUserData().front()->setParent(pLeap);
                            leftSibling->getUserData().pop_back();
                            curNode->pushKey(leftSibling->getKeys().back());
                        }
                        else
                        {
                            curNode->getChilds().insert(curNode->getChilds().begin(), leftSibling->getChilds().back());
                            curNode->initializeChildIndex();
                            curNode->initializeParent();
                            leftSibling->getChilds().pop_back();
                            curNode->pushKey(curParent->getKeys()[curNode->getIndexByParent() - 1]);
                        }
                        curParent->getKeys()[curNode->getIndexByParent() - 1] = leftSibling->getKeys().back();
                        leftSibling->getKeys().pop_back();
                        break;
                    }
                    /**������ ������ Ű�� ����� ��� */
                    else if (curNode->getRightSibling() != nullptr && curNode->getRightSibling()->getKeys().size() > this->minKey)
                    {
                        Node *RightSibling = curNode->getRightSibling();
                        if (curNode->checkLeap() == true)
                        {
                            Leap *RightSibling = pLeap.getNext();
                            pLeap.getUserData().insert(pLeap.getUserData().begin(), RightSibling->getUserData().front());
                            pLeap.getUserData().back()->setParent(pLeap);
                            RightSibling->getUserData().erase(RightSibling->getUserData().begin());
                            curNode->pushKey(RightSibling->getKeys().front());
                        }
                        else
                        {
                            curNode->getChilds().insert(curNode->getChilds().end(), RightSibling->getChilds().front());
                            curNode->initializeChildIndex();
                            curNode->initializeParent();
                            RightSibling->getChilds().erase(RightSibling->getChilds().begin());
                            curNode->pushKey(curParent->getKeys()[curNode->getIndexByParent()]);
                        }
                        RightSibling->getKeys().erase(RightSibling->getKeys().begin());
                        curParent->getKeys()[curNode->getIndexByParent()] = RightSibling->getKeys().front();
                        break;
                    }
                    /**���� ������ Ű�� ������� ��*/
                    else
                    {
                        /**���� ������ �����ϴ� ��� */
                        if (curNode->getLeftSibling() != nullptr)
                        {
                            Node *leftSibling = curNode->getLeftSibling();
                            if (curNode->checkLeap() == true)
                            {
                                Leap *leftSibling = pLeap.getPrev();
                                leftSibling->getUserData().insert(leftSibling->getUserData().end(), pLeap.getUserData().begin(), pLeap.getUserData().end());
                                leftSibling->initializeData();
                                pLeap.getUserData().clear();
                                if (pLeap.getNext() != nullptr)
                                {
                                    pLeap.getNext()->setPrev(leftSibling);
                                }
                                leftSibling->setNext(pLeap.getNext());
                            }
                            else
                            {
                                leftSibling->pushKey(curParent->getKeys()[curNode->getIndexByParent() - 1]);
                                leftSibling->getChilds().insert(leftSibling->getChilds().end(), curNode->getChilds().begin(), curNode->getChilds().end());
                                leftSibling->initializeChildIndex();
                                leftSibling->initializeParent();
                                curNode->getChilds().clear();
                            }
                            leftSibling->getKeys().insert(leftSibling->getKeys().end(), curNode->getKeys().begin(), curNode->getKeys().end());
                            curParent->getChilds().erase(curParent->getChilds().begin() + curNode->getIndexByParent());
                            curParent->getKeys().erase(curParent->getKeys().begin() + curNode->getIndexByParent() - 1);
                            curParent->initializeChildIndex();
                            delete curNode;
                            curNode = curParent;
                        }
                        /**������ ������ �����ϴ� ��� */
                        else if (curNode->getRightSibling() != nullptr)
                        {
                            Node *rightSibling = curNode->getRightSibling();
                            if (curNode->checkLeap() == true)
                            {
                                Leap *rightSibling = pLeap.getNext();
                                pLeap.getUserData().insert(pLeap.getUserData().end(), rightSibling->getUserData().begin(), rightSibling->getUserData().end());
                                pLeap.initializeData();
                                rightSibling->getUserData().clear();
                                if (rightSibling->getNext() != nullptr)
                                {
                                    rightSibling->getNext()->setPrev(&pLeap);
                                }
                                pLeap.setNext(rightSibling->getNext());
                            }
                            else
                            {
                                curNode->pushKey(curParent->getKeys()[curNode->getIndexByParent()]);
                                curNode->getChilds().insert(curNode->getChilds().end(), rightSibling->getChilds().begin(), rightSibling->getChilds().end());
                                curNode->initializeChildIndex();
                                curNode->initializeParent();
                                rightSibling->getChilds().clear();
                            }
                            curNode->getKeys().insert(curNode->getKeys().end(), rightSibling->getKeys().begin(), rightSibling->getKeys().end());
                            curParent->getChilds().erase(curParent->getChilds().begin() + curNode->getIndexByParent() + 1);
                            curParent->getKeys().erase(curParent->getKeys().begin() + curNode->getIndexByParent());
                            curParent->initializeChildIndex();
                            delete rightSibling;
                            curNode = curParent;
                        }
                    }
                }
            }
        }
    }
    /**��� Ű ��� */
    void PrintAllKey()
    {
        // Node *curnode = rootNode;
        // while (curnode->checkLeap() != true)
        // {
        //     curnode = curnode->getChilds()[0];
        // }
        // Leap *curLeap = static_cast<Leap *>(curnode);

        Leap *curLeap = this->firstStart;

        while (curLeap != nullptr)
        {
            for (KeyType element : curLeap->getKeys())
            {
                cout << element << '\t';
            }
            cout << "\n";
            curLeap = curLeap->getNext();
        }
    }
    void PrintAllData()
    {
        Leap *curLeap = this->firstStart;
        unsigned int count = 0;
        while (curLeap != nullptr)
        {
            for (USERDATAINDEX *element : curLeap->getUserData())
            {
                for (INDEXINFO *data : element->getUserAdt())
                {
                    ++count;
                    cout << '[' << count << "]\t" << "���� : " << data->user->age << " �̸� : " << data->user->name << " �޴���ȭ : " << data->user->phone << endl;
                }
            }
            curLeap = curLeap->getNext();
        }
    }
};