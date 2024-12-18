#include "modul.h"

/**USERDATAINDEX 정의 시작 */

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
    // cout << key << "데이터 컨테이너 삭제" << endl;
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
/**USERDATAINDEX 클래스 정의 끝 */

/**Node 클래스 정의 시작 */

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
        cout << " 노드 삭제" << endl;
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

/**자식 노드들이 갖고있는 자기 부모에 대한 인덱스 갱신 */
template <typename KeyType>
void Node<KeyType>::initializeChildIndex()
{
    int index = this->child.size();
    for (int i = 0; i < index; i++)
    {
        child[i]->indexByParent = i;
    }
}

/**자기 자식들의 부모를 자신으로 세팅 */
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
/**Node 클래스 정의 끝 */

/**Leap 클래스 정의 시작 */

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
    cout << "리프 노드 삭제" << endl;
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

/**데이터 컨테이터 양방향 연결 */
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
/**해당 리프노드의 첫번째 데이터가 인덱스 내에 키로 존재하는지 체크 및 반환 */
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
    cout << "인덱스 없음" << endl;
    return nullptr;
}

/**파라미터 바로 다음값을 갖고있는 컨테이너를 뱉어줌 ( 석세서 반환 ) */
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
/**Leap 클래스 정의 끝 */

/**Moudule 클래스 정의 시작 */
template <typename KeyType>
Module<KeyType>::Module()
{
}
template <typename KeyType>
Module<KeyType>::~Module()
{
    delete rootNode;
}

/**데이터 중복 삭제 방지용 리프 노드 데이터 클리어*/
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

/**새로운 데이터 삽입 */
template <typename KeyType>
void Module<KeyType>::NewNode(KeyType keyparam, INDEXINFO &pParam)
{
    KeyType key = keyparam;
    /**데이터 처음 삽입 시 */
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
                        cout << "동일 값 데이터 삽입" << endl;
                        return;
                    }
                    else
                        index++;
                }
                curLeap->NewKey(keyparam, pParam);
                /**현재 노드의 키 수가 최대 키 수를 넘었다면 */
                while (curNode->getKeys().size() > maxKey)
                {
                    /**현재 노드가 루트노드라면 */
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
                    /**현재 노드가 리프노드라면 */
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
                cout << "데이터 삽입 완료" << endl;
                return;
            }
        }
    }
}
/**키를 중심으로 검색 */
template <typename KeyType>
Leap<KeyType> *Module<KeyType>::SearchByKey(KeyType min, KeyType max, int &dataIndex, vector<Node *> &passTemp)
{
    Node *curNode = this->rootNode;
    if (curNode == nullptr)
    {
        return nullptr;
    }

    /**현재 노드가 리프노드일때까지 */
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

/**노드 삭제 */
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

/**인덱싱 재조정 */
template <typename KeyType>
void Module<KeyType>::IndexReconciliation(Leap &pLeap, USERDATAINDEX &pIndex, USERDATA &pData, vector<Node *> &passTemp)
{
    KeyType key = pIndex.getKey();
    /**만약 삭제한 데이터가 해당되는 키가 비어있는 경우 */
    if (pIndex.getUserAdt().size() == 0)
    {
        /**인덱싱 변환 ( 현재 리프노드가 첫번째 리프노드가 아니고 , 현재 삭제되는 인덱스가 노드의 첫번째 값 및 트리의 최댓값이 아닐 시. )*/
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
        /**키 삭제 후 해당 리프노드의 키 수가 최소 키 수보다 적을 경우 */
        while (curNode->getKeys().size() < this->minKey)
        {
            /**현재 노드가 루트노드일 경우 */
            if (curNode == this->rootNode)
            {
                if (curNode->getKeys().size() == 0)
                {
                    curNode = rootNode->getChilds().front();
                    rootNode->getChilds().clear();
                    delete rootNode;
                    rootNode = curNode;
                    rootNode->serParent(nullptr);
                    /**모든 데이터가 삭제되었을 시 */
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
            /**현재 노드가 루트노드가 아닐 경우 */
            else
            {
                curParent = curNode->getParent();
                /**왼쪽 형제의 키가 충분할 경우 */
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
                /**오른쪽 형제의 키가 충분할 경우 */
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
                /**양쪽 형제의 키가 불충분할 때*/
                else
                {
                    /**왼쪽 형제가 존재하는 경우 */
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
                    /**오른쪽 형제가 존재하는 경우 */
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
/**모든 키 출력 */

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
/**모든 데이터 출력 */
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
                cout << '[' << count << "]\t" << "나이 : " << data->user->age << "\t이름 : " << data->user->name << "\t휴대전화 : " << data->user->phone << endl;
            }
        }
        curLeap = curLeap->getNext();
    }
    if (count == 0)
    {
        cout << "출력할 데이터가 없습니다." << endl;
    }
}