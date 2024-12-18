#include "modul.h"

/**USERDATAINDEX ���� ���� */

template <typename T>
USERDATAINDEX<T>::USERDATAINDEX(T key)
{
    this->key = key;
}

template <typename T>
USERDATAINDEX<T>::~USERDATAINDEX()
{
    for (INDEXINFO *element : userdata)
    {
        delete element;
    }
    // cout << key << "������ �����̳� ����" << endl;
    this->userdata.clear();
}

template <typename T>
void USERDATAINDEX<T>::setKey(T key)
{
    this->key = key;
}
template <typename T>
void USERDATAINDEX<T>::setParent(Leap<T> &pLeap)
{
    this->PerentLeap = &pLeap;
}
template <typename T>
vector<INDEXINFO *> &USERDATAINDEX<T>::getUserAdt()
{
    return this->userdata;
}
template <typename T>
T &USERDATAINDEX<T>::getKey()
{
    return this->key;
}

template <typename T>
Leap<T> *USERDATAINDEX<T>::getParent()
{
    return this->PerentLeap;
}

template <typename T>
void USERDATAINDEX<T>::pushData(INDEXINFO &pData)
{
    pData.setIndexParent(*this);
    userdata.push_back(&pData);
};
/**USERDATAINDEX Ŭ���� ���� �� */

/**Node Ŭ���� ���� ���� */

template <typename KeyType>
Node<KeyType>::Node(KeyType key, USERDATA &pParam)
{
    this->keys.push_back(key);
};

template <typename KeyType>
Node<KeyType>::~Node()
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

template <typename KeyType>
void Node<KeyType>::serParent(Node *pParam)
{
    this->parent = pParam;
}
template <typename KeyType>
Node<KeyType> *Node<KeyType>::getParent()
{
    return this->parent;
}
template <typename KeyType>
vector<Node<KeyType> *> &Node<KeyType>::getChilds()
{
    return this->child;
}

template <typename KeyType>
vector<KeyType> &Node<KeyType>::getKeys()
{
    return this->keys;
}

template <typename KeyType>
int Node<KeyType>::getIndexByParent()
{
    return this->indexByParent;
}

template <typename KeyType>
void Node<KeyType>::pushChild(Node<KeyType> &pParam)
{
    this->child.push_back(&pParam);
    sort(this->child.begin(), this->child.end(), childCompareByKey);
    initializeChildIndex();
}

/**�ڽ� ������ �����ִ� �ڱ� �θ� ���� �ε��� ���� */
template <typename KeyType>
void Node<KeyType>::initializeChildIndex()
{
    int index = this->child.size();
    for (int i = 0; i < index; i++)
    {
        child[i]->indexByParent = i;
    }
}

/**�ڱ� �ڽĵ��� �θ� �ڽ����� ���� */
template <typename KeyType>
void Node<KeyType>::initializeParent()
{
    for (Node *element : this->child)
    {
        element->serParent(this);
    }
}

template <typename KeyType>
void Node<KeyType>::pushKey(KeyType param)
{
    this->keys.push_back(param);
    sort(this->keys.begin(), this->keys.end());
}

template <typename KeyType>
bool Node<KeyType>::checkLeap()
{
    return this->isLeap;
}

template <typename KeyType>
bool Node<KeyType>::childCompareByKey(Node<KeyType> *a, Node<KeyType> *b)
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

template <typename KeyType>
void Node<KeyType>::changeLeap()
{
    this->isLeap = true;
}

template <typename KeyType>
Node<KeyType> *Node<KeyType>::getRightSibling()
{
    if (indexByParent >= parent->getChilds().size() - 1)
    {
        return nullptr;
    }
    else
        return parent->getChilds()[indexByParent + 1];
}

template <typename KeyType>
Node<KeyType> *Node<KeyType>::getLeftSibling()
{
    if (indexByParent == 0)
    {
        return nullptr;
    }
    else
        return parent->getChilds()[indexByParent - 1];
}
/**Node Ŭ���� ���� �� */

/**Leap Ŭ���� ���� ���� */

template <typename KeyType>
Leap<KeyType>::Leap()
{
    this->changeLeap();
};

template <typename KeyType>
Leap<KeyType>::Leap(KeyType key, USERDATA &pParam) : Node(key, pParam)
{
    this->changeLeap();
}

template <typename KeyType>
Leap<KeyType>::~Leap()
{
    for (USERDATAINDEX *element : userdata)
    {
        cout << element->getKey() << '\t';
        delete element;
    }
    cout << "���� ��� ����" << endl;
    this->userdata.clear();
}

template <typename KeyType>
void Leap<KeyType>::setPrev(Leap *pParam)
{
    this->prev = pParam;
}

template <typename KeyType>
void Leap<KeyType>::setNext(Leap *pParam)
{
    this->next = pParam;
}
template <typename KeyType>
Leap<KeyType> *Leap<KeyType>::getPrev()
{
    return this->prev;
}
template <typename KeyType>
Leap<KeyType> *Leap<KeyType>::getNext()
{
    return this->next;
}

template <typename KeyType>
void Leap<KeyType>::pushData(INDEXINFO &pParam, int index)
{
    USERDATAINDEX *tmpIndex = this->userdata[index];
    tmpIndex->getUserAdt().push_back(&pParam);
}
template <typename KeyType>
void Leap<KeyType>::NewKey(KeyType Keyparam, INDEXINFO &pParam)
{
    this->pushKey(Keyparam);
    USERDATAINDEX *newDataArr = new USERDATAINDEX(Keyparam);
    newDataArr->pushData(pParam);
    newDataArr->setKey(Keyparam);
    newDataArr->setParent(*this);
    userdata.push_back(newDataArr);
    sort(userdata.begin(), userdata.end(), indexCompareByKey);
}

/**������ �������� ����� ���� */
template <typename KeyType>
void Leap<KeyType>::initializeData()
{
    for (USERDATAINDEX *element : this->userdata)
    {
        element->setParent(*this);
    }
}

template <typename KeyType>
vector<USERDATAINDEX<KeyType> *> &Leap<KeyType>::getUserData()
{
    return this->userdata;
}
template <typename KeyType>
bool Leap<KeyType>::indexCompareByKey(USERDATAINDEX *a, USERDATAINDEX *b)
{
    return a->getKey() < b->getKey();
}
template <typename KeyType>
Leap<KeyType> *Leap<KeyType>::getRightSibling()
{
    if (this->getIndexByParent() >= this->getParent()->getChilds().size() - 1)
    {
        return nullptr;
    }
    else
        return static_cast<Leap *>(this->getParent()->getChilds()[this->getIndexByParent() + 1]);
}
template <typename KeyType>
Leap<KeyType> *Leap<KeyType>::getLeftSibling()
{
    if (this->getIndexByParent() == 0)
    {
        return nullptr;
    }
    else
        return static_cast<Leap *>(this->getParent()->getChilds()[this->getIndexByParent() - 1]);
}
/**�ش� ��������� ù��° �����Ͱ� �ε��� ���� Ű�� �����ϴ��� üũ �� ��ȯ */
template <typename KeyType>
Node<KeyType> *Leap<KeyType>::getInternalIndexNode()
{
    KeyType key = this->getKeys().front();
    Node *curNode = this->getParent();
    while (curNode != nullptr)
    {
        for (KeyType element : curNode->getKeys())
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

/**�Ķ���� �ٷ� �������� �����ִ� �����̳ʸ� ����� ( ������ ��ȯ ) */
template <typename KeyType>
USERDATAINDEX<KeyType> &Leap<KeyType>::getSuccesor(Leap &pNode, KeyType Param)
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
/**Leap Ŭ���� ���� �� */

/**Moudule Ŭ���� ���� ���� */
template <typename KeyType>
Module<KeyType>::Module()
{
}
template <typename KeyType>
Module<KeyType>::~Module()
{
    delete rootNode;
}

/**������ �ߺ� ���� ������ ���� ��� ������ Ŭ����*/
template <typename KeyType>
void Module<KeyType>::ClearAllLeapData()
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
template <typename KeyType>
void Module<KeyType>::NewNode(KeyType keyparam, INDEXINFO &pParam)
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
/**Ű�� �߽����� �˻� */
template <typename KeyType>
Leap<KeyType> *Module<KeyType>::SearchByKey(KeyType min, KeyType max, int &dataIndex, vector<Node *> &passTemp)
{
    Node *curNode = this->rootNode;
    if (curNode == nullptr)
    {
        return nullptr;
    }

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
    while (curLeap != nullptr && (curLeap == this->firstStart || curLeap->getUserData()[index]->getKey() <= max))
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
template <typename KeyType>
void Module<KeyType>::DeleteData(Leap &pLeap, USERDATAINDEX &pIndex, USERDATA &pData, vector<Node *> &passTemp)
{
    int index = 0;
    KeyType key = pIndex.getKey();
    for (INDEXINFO *element : pIndex.getUserAdt())
    {
        if (&pData == element->user)
        {
            pIndex.getUserAdt().erase(pIndex.getUserAdt().begin() + index);
            break;
        }
        else
            index++;
    }
    this->IndexReconciliation(pLeap, pIndex, pData, passTemp);
}

/**�ε��� ������ */
template <typename KeyType>
void Module<KeyType>::IndexReconciliation(Leap &pLeap, USERDATAINDEX &pIndex, USERDATA &pData, vector<Node *> &passTemp)
{
    KeyType key = pIndex.getKey();
    /**���� ������ �����Ͱ� �ش�Ǵ� Ű�� ����ִ� ��� */
    if (pIndex.getUserAdt().size() == 0)
    {
        /**�ε��� ��ȯ ( ���� ������尡 ù��° ������尡 �ƴϰ� , ���� �����Ǵ� �ε����� ����� ù��° �� �� Ʈ���� �ִ��� �ƴ� ��. )*/
        if (&pLeap != firstStart && &pIndex == pLeap.getUserData()[0] && (pLeap.getNext() != nullptr || pLeap.getUserData().size() > 1))
        {
            if (passTemp.size() == 0)
            {
                Node *tmp = pLeap.getInternalIndexNode();
                passTemp.push_back(tmp);
            }
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
                            dummy.setNext(static_cast<Leap *>(rootNode->getChilds().back()));
                            dummy.getNext()->setPrev(&dummy);
                            this->firstStart = &dummy;
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

template <typename KeyType>
void Module<KeyType>::PrintAllKey()
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
/**��� ������ ��� */
template <typename KeyType>
void Module<KeyType>::PrintAllData()
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
                cout << '[' << count << "]\t" << "���� : " << data->user->age << "\t�̸� : " << data->user->name << "\t�޴���ȭ : " << data->user->phone << endl;
            }
        }
        curLeap = curLeap->getNext();
    }
    if (count == 0)
    {
        cout << "����� �����Ͱ� �����ϴ�." << endl;
    }
}