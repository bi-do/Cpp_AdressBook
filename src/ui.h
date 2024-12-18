
#include "control.h"
using namespace std;

class UI
{
private:
    Control &control;

public:
    typedef enum INPUTTYPE
    {
        EXIT,
        NEW,
        SEARCHBYNAME,
        SEARCHBYAGE,
        PRINT
    } INPUTTYPE;

    UI();
    ~UI();
    Control &getControl();

    /**���� UI ����� */
    int ViewUI();

    /**�̺�Ʈ ���� */
    void EventRoop();

    /**������ ���� */
    void DataInsert();

    /**�̸� �˻� */
    void SearchByName();

    /**���� ���� �˻�*/
    void SearchByAge();

    /**������ ������Ʈ ���� Ȯ��*/
    void DataUpdateUI(INDEXINFO &pIndex, USERDATA &pData);

    /**������ ���� */
    void DataCorrectionUI(INDEXINFO &pIndex, USERDATA &pData);

    /**��� ������ ��� */
    void PrintAll();

    /**��� ������ Ű ( ���� ) ��� */
    void PrintAllKey();
};
