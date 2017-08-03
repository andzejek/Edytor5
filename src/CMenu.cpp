#include "CMenu.h"

CMenu::CMenu(){

    bar = CreateMenu();
    HMENU sub;
    HMENU subb;
    sub = CreateMenu();
    AppendMenu( sub, MF_STRING, MENU_NEW, L"New\tCtrl+N" );
    AppendMenu( sub, MF_STRING, MENU_OPEN, L"Open\tCtrl+O" );
    AppendMenu( sub, MF_STRING, MENU_SAVE, L"Save \tCtrl+S" );
    AppendMenu( sub, MF_STRING, MENU_SAVE_AS, L"Save as\tCtrl+" );
    AppendMenu( sub, MF_SEPARATOR, 0, 0 );
    AppendMenu( sub, MF_STRING, MENU_EXIT, L"Exit" );
    AppendMenu( bar, MF_POPUP, (unsigned int) sub, L"File" );
    sub = CreateMenu();
    AppendMenu( sub, MF_STRING, MENU_UNDO, L"Undo \tCtrl+Z" );
    AppendMenu( sub, MF_STRING, MENU_REDO, L"Redo \tCtrl+Shift+Z" );
    AppendMenu( sub, MF_SEPARATOR, 0, 0 );
    AppendMenu( sub, MF_STRING, MENU_CUT, L"Cut \tCtrl+X" );
    AppendMenu( sub, MF_STRING, MENU_COPY, L"Copy \tCtrl+C" );
    AppendMenu( sub, MF_STRING, MENU_PASTE, L"Paste \tCtrl+V" );
    AppendMenu( sub, MF_STRING, MENU_SELECT_ALL, L"Select all \tCtrl+A" );
    AppendMenu( sub, MF_SEPARATOR, 0, 0 );
    AppendMenu( sub, MF_STRING, MENU_NEG, L"Negative" );
    AppendMenu( bar, MF_POPUP, (unsigned int) sub, L"Edit" );
    sub = CreateMenu();
    subb=CreatePopupMenu();
    AppendMenu(sub, MF_STRING | MF_POPUP, (UINT_PTR) subb, L"Toolbars");

    AppendMenuW(subb, MF_STRING, MENU_TOOLS, L"Tools");
    AppendMenuW(subb, MF_STRING, MENU_PALETE, L"Color palette");
    AppendMenuW(subb, MF_STRING, MENU_PALETE_FILE, L"Palette from file");

    AppendMenu(sub, MF_STRING, MENU_FULLSCREEN, L"FullScreen \tF11");
     AppendMenu(sub, MF_STRING, MENU_ADD_SKETCH, L"Add Sketch");

     AppendMenu(sub, MF_STRING, MENU_ENABLE_SKETCH, L"Enable Sketch");
     AppendMenu(sub, MF_STRING, MENU_DISABLE_SKETCH, L"Disable Sketch");
    //AppendMenu( sub, MF_STRING, MENU_REDO, L"Redo \tCtrl+Shift+Z" );
    //AppendMenu( sub, MF_STRING, MENUC, L"pozycja c\tCtrl+c" );
    AppendMenu( bar, MF_POPUP, (unsigned int) sub, L"View" );


    AppendMenu( bar, MF_HELP|MF_STRING, (unsigned int) MENU_EXIT, L"EXIT" );//(PTSTR) (LONG) hbmMorda
}
void CMenu::set(HWND hwnd){
    SetMenu(hwnd,bar);
}
CMenu::~CMenu(){

}

