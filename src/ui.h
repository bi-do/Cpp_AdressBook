
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

    /**선택 UI 띄워줌 */
    int ViewUI();

    /**이벤트 루프 */
    void EventRoop();

    /**데이터 삽입 */
    void DataInsert();

    /**이름 검색 */
    void SearchByName();

    /**나이 범위 검색*/
    void SearchByAge();

    /**데이터 업데이트 여부 확인*/
    void DataUpdateUI(INDEXINFO &pIndex, USERDATA &pData);

    /**데이터 수정 */
    void DataCorrectionUI(INDEXINFO &pIndex, USERDATA &pData);

    /**모든 데이터 출력 */
    void PrintAll();

    /**모든 데이터 키 ( 숫자 ) 출력 */
    void PrintAllKey();
};
