#ifndef CMENU_H
#define CMENU_H
#include "../stdafx.h"
///FILE
#define   MENU_NEW   40003
#define   MENU_OPEN   40001
#define   MENU_SAVE   40002
#define   MENU_SAVE_AS   40031
///EDIT

#define   MENU_UNDO   40004
#define   MENU_REDO   40005
#define   MENU_NEG   40006
#define   MENU_CUT   40016
#define   MENU_COPY  40013
#define   MENU_PASTE 40014
#define   MENU_SELECT_ALL 40015
///VIEW
#define   MENU_PALETE_FILE 40033
#define   MENU_PALETE 40008
#define   MENU_TOOLS 40009
#define   MENU_FULLSCREEN 40010
#define   MENU_ADD_SKETCH 40044
#define   MENU_ENABLE_SKETCH 40045
#define   MENU_DISABLE_SKETCH 40046

///EXIT
#define   MENU_EXIT 40007
class CMenu{
public:
    HMENU bar;
    CMenu();
    void set(HWND);
    virtual ~CMenu();
protected:

private:
};

#endif // CMENU_H

